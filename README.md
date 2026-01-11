# Fizzbuzz

## Running

Compile:

```bash
clang++ -std=c++17 -oFizzbuzz Fizzbuzz.cc
```

Execute:

```bash
./Fizzbuzz
```

## Expanding

To add new rules, create a type that extends `BasicRule`. It must have an `Execute` member function. `Execute` should return true if it should conclude execution, and false if it should move to the next rule.
Add the new rule into the `FizzbuzzProgram` template parameter in the order you want it to execute.
