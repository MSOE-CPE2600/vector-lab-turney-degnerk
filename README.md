## Program Description
The vector calculator program uses dynamic memory to create and perform math with vectors. This MATLAB-style program allows you to perform add, subtract, multiply, divide, scalar multiply, load csv, and save csv vector operations.

## Build Program
To build the program, perform a `make clean` and `make all`. To build by hand, perform the command `gcc -o minimat minimat.c vector_array.c vector_math.c parser.c`.

## Run Program
To run the program, perform a `./minimat` command. Running `./minimat -h` will display the possible program options.

## Supported Commands
The following are commands that are supported by the program.

    var = x y z      assign 3D vector
    var = a + b      add vectors
    var = a - b      subtract vectors
    var = a * k      scalar multiply (or k * a)
    a + b            display result of addition
    a - b            display result of subtraction
    a * k            display result of scalar multiplication
    var              display stored vector
    list             list all vectors
    clear            clear vector storage
    load <filename>  load vectors from file
    save <filename>  save vectors to file
    quit             exit program

## Dynamic Memory
In v2.0 of this program, we needed to use dynamic memory to store the vectors. This way, the program only uses as little memory as required to store the current vector list. When adding a new vector, I used `malloc()` to allocate the memory for the new vector. When I was clearing the vector list, I used `free()` to free the memory that I allocated previously, preventing memory leaks.
