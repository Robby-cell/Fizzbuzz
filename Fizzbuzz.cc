#include <cstddef>
#include <iostream>
#include <tuple>
#include <type_traits>
#include <utility>

struct BasicRule {};

struct FizzRule : BasicRule {
  template <typename Stream> static bool Execute(Stream &&os, unsigned number) {
    if (number % 3 == 0) {
      os << "Fizz";
      return true;
    }
    return false;
  }
};

struct BuzzRule : BasicRule {
  template <typename Stream> static bool Execute(Stream &&os, unsigned number) {
    if (number % 5 == 0) {
      os << "Buzz";
      return true;
    }
    return false;
  }
};

template <typename... Rules> struct FizzbuzzProgram {
  static_assert((std::is_base_of_v<BasicRule, Rules> and ...), "Must be rules");

  std::tuple<Rules...> rules{};

  template <typename Stream> void Run(Stream &&os, unsigned limit) {
    for (unsigned i = 1; i <= limit; ++i) {
      ExecuteRules(std::forward<Stream>(os), i);
    }
  }

  template <typename Stream> void ExecuteRules(Stream &&os, unsigned number) {
    ExecuteRuleImpl(
        std::forward<Stream>(os), number,
        std::make_integer_sequence<size_t,
                                   std::tuple_size_v<decltype(rules)>>{});
  }

  template <typename Stream, size_t... Idx>
  void ExecuteRuleImpl(Stream &&os, unsigned number,
                       std::integer_sequence<size_t, Idx...>) {
    [[maybe_unused]] const auto executed =
        (((std::get<Idx>(rules).Execute(std::forward<Stream>(os), number))
              ? 1
              : 0) +
         ...);
    if (executed == 0) {
      os << number;
    }
    os << '\n';
  }
};

struct BazzRule : BasicRule {
  template <typename Stream> static bool Execute(Stream &&os, unsigned number) {
    if (number % 7 == 0) {
      os << "Bazz";
      return true;
    }
    return false;
  }
};

int main() {
  using Fizzbuzz = FizzbuzzProgram<FizzRule, BuzzRule, BazzRule>;
  Fizzbuzz fizzbuzz;
  fizzbuzz.Run(std::cout, 100);
}
