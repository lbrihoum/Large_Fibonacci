# Large Fibonacci
Implementing a Huge Fibonacci program that avoids repetitive computation by computing the sequence linearly from the bottom up using linked lists and recursive functions.

## To read about the fibonacci sequence
https://en.wikipedia.org/wiki/Fibonacci_number

## Fibonacci.c
This file is the main file that contains all the logic for the Large Fibonacci. Below is a breakdown of all the functions and how they work.

## Fibonacci.h
Included with this project is a customer header file that includes the struct definitions and functional prototypes for the functions that are implemented.
This file was intended to be a bridge for the main source files.
There are three structs in this file.

## Testcases
There is a folder labeled "testcases" that can be used to see how the program executes with different cases.

### Representing Huge integers in C
A linear Fibonacci function has a big problem which is when computing the sequence, it will quickly exceed the limits of C’s 32-bit integer representation. On most modern systems, the maximum int value in C is 232-1, or 12,147,483,647. The first Fibonacci number to exceed that limit is F(47) = 2,971,215,073.

To overcome this limitation, the program will represent integers in this program using arrays, where each index holds a single digit of an integer.

## Each function implemented
### HugeInteger hugeAdd(HugeInteger p, HugeInteger q);
Returns a pointer to a new, dynamically allocated HugeInteger struct that contains the result of adding the huge integers represented by p and q.

### HugeInteger hugeDestroyer(HugeInteger p);
Destroys any and all dynamically allocated memory associated with p.

### HugeInteger parseInt(unsigned int n);
COnverts the unsigned integer n to HugeInteger format.

### unsigned int toUnsignedInt(HugeInteger p);
Converts the integer represented by p to a dynamically allocated unsigned int, and return a pointer to that value.

### HugeInteger fib(int n);
The best function!
This function implements an iterative solution and returns a pointer to a HugeInteger struct that contains F(n).

## Compiling
To compile a file at the command line:
- gcc Fibonacci.c

To run the file:
- ./Fibonacci.exe

To run with a test case:
- gcc Fibonacci.c testcase01.c

Running the program could potentially dump a lot of output to the screen. If you want to redirect your output to a text file in Linux just run the program using the following command, which will create a file called whatever.txt that contains the output from your program
- ./Fibonacci.exe > whatever.txt

I personally used Code::Blocks to write this program.
- http://www.codeblocks.org/
