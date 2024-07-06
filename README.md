# Interpreter Implementation: Elements of Declarative and Functional Styles

## Purpose of Work

Gain experience in programming using multi-paradigm programming and preparing your own declarative `language` that will support a basic functional style.

## Task

Implement a simple interpreter in C++ that can evaluate arithmetic expressions, define functions, and call functions. The interpreter should support the following features:

1. Basic arithmetic operations: `+`, `-`, `*`, `/`
2. Function definitions with two parameters (`pow`, `abs`, `max`, `min`)
3. Expression combinations
4. Function calls (combination of the above expressions with a dedicated name)
5. Variables saving for reusing them (e.g., `var a = pow(2, 4)`)

The following is an example of interpreter usage:

### 6 points:
```
> 5 + 3 * 2
> 11 # <---- here and below it is an answer
```

### 8 points:
```
> max(5, 2)
> 5
> min(3, 4)
> 3
```

### 10 points:
```
> max(min(3 * 2, 2), 2)
> 6
```

### Extra 11 points:
```
> var a = max(min(3 * 2, 2), 2)
> a + 3
> 5
```

### Extra 12 points:
```
> def myfunc(a, b) { min(a, b) + max(a, b) }
> myfunc(3, 4)
> 7
```

## Testing

To test the implemented interpreter, you should implement a Python script that will execute your program with different input combinations and then it should verify the correctness of the result.

### Example C++ program:
```cpp
#include <iostream>
#include <string>

int main() {
    std::string input;
    std::getline(std::cin, input);  // Read input from stdin

    // Echo back the input
    std::cout << "Echo: " << input << std::endl;

    return 0;
}
```

### Example Python script for testing (test_script.py):
```python
import subprocess

def run_echo(input_data):
    process = subprocess.Popen(
        ['myprogram.exe'],  
        stdin=subprocess.PIPE,  
        stdout=subprocess.PIPE,  
        stderr=subprocess.PIPE,  
        text=True
    )
    stdout, stderr = process.communicate(input_data)
    return stdout.strip(), stderr.strip()

def test_echo():
    tests = [
        {
            "input": "Hello, world!\n",
            "expected_output": "Echo: Hello, world!"
        },
        {
            "input": "12345\n",
            "expected_output": "Echo: 12345"
        },
        {
            "input": "Testing echo program\n",
            "expected_output": "Echo: Testing echo program"
        }
        # Add more test cases as needed
    ]

    for test in tests:
        input_data = test["input"]
        expected_output = test["expected_output"]
        
        output, error = run_echo(input_data)
        
        if error:
            print(f"Test failed for input:\n{input_data}")
            print(f"Error:\n{error}")
        elif output.strip() != expected_output:
            print(f"Test failed for input:\n{input_data}")
            print(f"Expected:\n{expected_output}")
            print(f"Got:\n{output}")
        else:
            print(f"Test passed for input:\n{input_data}")

if __name__ == "__main__":
    test_echo()
```

Execution:
```
> py.exe .\test_script.py
Test passed for input:
Hello, world!

Test passed for input:
12345

Test passed for input:
Testing echo program
```

## General Theory

An interpreter is a program that executes code written in a high-level programming language. It processes the code line by line, interpreting and executing it as it goes, which is different from a compiler that translates the entire code into machine code before execution.

Functional programming is a programming paradigm that treats computation as the evaluation of mathematical functions. Key principles include:

- Immutability: Data structures and variables are not modified once created.
  - Python:
    ```python
    # Immutable list in Python
    numbers = (1, 2, 3, 4, 5)
    ```
  - Haskell:
    ```haskell
    -- Immutable list in Haskell
    numbers :: [Int]
    numbers = [1, 2, 3, 4, 5]
    ```

- Pure Functions: Functions that produce the same output for the same input, with no side effects on other program parts, the function doesn’t modify the program’s state.
  - Python:
    ```python
    # A pure function in Python
    def square(x):
        return x * x
    ```
  - Haskell:
    ```haskell
    -- A pure function in Haskell
    square :: Int -> Int
    square x = x * x
    ```

- Higher-Order Functions: Functions can take other functions as arguments or return them.
  - Python:
    ```python
    # Higher-order function in Python
    def apply_function(f, x):
        return f(x)
    
    # Using the higher-order function
    def square(x):
        return x * x
    
    result = apply_function(square, 5)
    ```
  - Haskell:
    ```haskell
    -- Higher-order function in Haskell
    applyFunction :: (a -> b) -> a -> b
    applyFunction f x = f x
    
    -- Using the higher-order function
    square :: Int -> Int
    square x = x * x
    result = applyFunction square 5
    ```

- Referential Transparency: Expressions can be replaced with their values without changing the program's behavior. This property is a key aspect of functional programming, as it simplifies reasoning about code and facilitates optimization. In both code examples function calls can be replaced with their computed values, and it won't change the behavior of the program.
  - Python:
    ```python
    # Referential transparency in Python
    def add(a, b):
        return a + b
    
    x = 5
    y = 3
    
    result = add(x, y)
    ```
  - Haskell:
    ```haskell
    -- Referential transparency in Haskell
    add :: Int -> Int -> Int
    add a b = a + b
    x :: Int
    x = 5
    y :: Int
    y = 3
    result :: Int
    result = add x y
    ```

- Using Anonymous/Lambda Functions: Anonymous functions (lambdas) can be used to define functions on the fly.
  - Python:
    ```python
    # Anonymous (lambda) function in Python
    multiply_by_two = lambda x: x * 2
    ```
  - Haskell:
    ```haskell
    -- Anonymous (lambda) function in Haskell
    multiplyByTwo :: Int -> Int
    multiplyByTwo = \x -> x * 2
    ```

Functional paradigms can be implemented in code through the following techniques:
- Defining pure functions that don't modify state or produce side effects.
- Using higher-order functions to create composable and reusable code.
- Embracing immutability by not modifying data in place.

### Example Functional-Styled Program

The below code calculates the sum of the squares of even numbers.
```python
from functools import reduce

# Define a pure function to square a number
def square(x):
    return x * x

# Define a pure function to check if a number is even
def is_even(x):
    return x % 2 == 0

# Define a pure function to calculate the sum of squares of even numbers
def sum_of_squares_of_evens(numbers):
    # Filter even numbers
    evens = filter(is_even, numbers)
    
    # Square each even number
    squared_evens = map(square, evens)
    
    # Use reduce to sum the squared even numbers
    total = reduce(lambda x, y: x + y, squared_evens)
    return total

# Example Input
numbers = [1, 2, 3, 4, 5, 6]
# Calculate the sum of squares of even numbers
result = sum_of_squares_of_evens(numbers)
# Output the result
print(result)  # Output: 56
```

## Control Questions

1. What is an interpreter?
2. What is a declarative programming language?
3. What is the functional programming paradigm, and what are its key principles?
4. Explain the concept of immutability in functional programming and its benefits.
5. How can you create pure functions in Python/Haskell/your language?
6. What are higher-order functions?
7. Describe the role of I/O operations in functional programming and how they are typically handled.
8. Compare and contrast interpreted languages with compiled languages.

## Evaluation

- Correct git usage flow: 1
- Basic arithmetic operations: `+`, `-`, `*`, `/`: 2
- Python test script: 2

#### Milestone 1 (5 points total)
- Function definitions with two parameters: 2

#### Milestone 2 (7 points total)
- Expressions combination: 2

#### Milestone 3 (9 points total)
- Extra 1: function calls: 1
- Extra 2: variables: 1

#### Total: 9 + 2

Please note that to get the highest evaluation point you should implement error-safe code. The program should not crash in unexpected situations.

#### Theory is evaluated separately:
- Theory: 1

## Links
- PLPP – Programming Languages Principles and Paradigms book
- CSAPP – Computer Systems A Programming Perspective book

1. Functional Programming: PLPP Chapter 11
2. Interpreter: PLPP Chapter 1.1, 1.1.1
