
## Arbitrary Precision Calculator (APC)

The **Arbitrary Precision Calculator (APC)** is a command-line based project developed in **C** to perform arithmetic operations on very large integers that exceed the limits of standard data types.

This project uses a **Doubly Linked List** data structure, where each node stores a single digit, enabling efficient handling of large numbers with dynamic memory allocation.

### Features

* Addition of large integers
* Subtraction of large integers
* Multiplication of large integers
* Division of large integers
* Supports positive and negative numbers
* Input validation and error handling
* Dynamic memory management
* Modular code implementation

### Technologies Used

* **C Programming**
* **Data Structures**
* **Doubly Linked List**
* **Dynamic Memory Allocation**
* **GCC Compiler**
* **Makefile**

### Project Structure

* `main.c` → Main driver code and operation handling 
* `apc.h` → Header file containing structures and function declarations 
* `apc_ADD_SUB.c` → Addition and subtraction logic 
* `apc_MUL.c` → Multiplication logic 
* `apc_DIV.c` → Division logic 
* `apc_utils.c` → Utility functions and linked list operations 

### How It Works

1. Takes two operands and one operator as command-line arguments.
2. Stores each digit of operands into a doubly linked list.
3. Performs arithmetic operations digit by digit.
4. Displays the final result.

### Compilation

```bash
make
```

### Execution

```bash
./a.out <operand1> <operator> <operand2>
```

### Example

```bash
./a.out 123456789123456789 + 987654321987654321
```

Output:

```bash
Result : 1111111111111111110
```

### Learning Outcomes

Through this project, I gained practical knowledge in:

* Advanced C Programming
* Linked List Implementation
* Memory Management
* Algorithm Optimization
* Problem Solving

### Future Improvements

* Modulus operation
* Exponentiation
* Floating-point big number support
* Performance optimization for division

---

**Developed by Shareef Sab**
Electronics and Communication Engineering (ECE)
