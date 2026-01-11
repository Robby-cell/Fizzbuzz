#include <cstddef>
#include <iostream>
#include <tuple>
#include <type_traits>
#include <utility>

struct BasicRule {};

struct FizzbuzzRule : BasicRule {
  static bool Execute(unsigned number) {
    if (number % 15 == 0) {
      std::cout << "Fizzbuzz\n";
      return true;
    }
    return false;
  }
};

struct FizzRule : BasicRule {
  static bool Execute(unsigned number) {
    if (number % 3 == 0) {
      std::cout << "Fizz\n";
      return true;
    }
    return false;
  }
};

struct BuzzRule : BasicRule {
  static bool Execute(unsigned number) {
    if (number % 5 == 0) {
      std::cout << "Buzz\n";
      return true;
    }
    return false;
  }
};

struct BaseRule : BasicRule {
  static bool Execute(unsigned number) {
    std::cout << number << '\n';
    return true;
  }
};

template <typename... Rules> struct FizzbuzzProgram {
  static_assert((std::is_base_of_v<BasicRule, Rules> and ...), "Must be rules");

  static constexpr std::tuple<Rules...> rules{};

  void Run(unsigned limit) {
    for (unsigned i = 1; i <= limit; ++i) {
      ExecuteRules(i);
    }
  }

  void ExecuteRules(unsigned number) {
    ExecuteRuleImpl(number, std::make_integer_sequence<
                                size_t, std::tuple_size_v<decltype(rules)>>{});
  }

  template <size_t... Idx>
  void ExecuteRuleImpl(unsigned number, std::integer_sequence<size_t, Idx...>) {
    [[maybe_unused]] const auto executed =
        ((std::get<Idx>(rules).Execute(number)) or ...);
  }
};

int main() {
  using Fizzbuzz = FizzbuzzProgram<FizzbuzzRule, FizzRule, BuzzRule, BaseRule>;
  Fizzbuzz fizzbuzz;
  fizzbuzz.Run(100);
}
