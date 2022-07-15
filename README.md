To run the compiler you might need to install llvm-14
The make file and the compiler makes use of llvm tools that might need to be aliased in the shell.


--------------
llvm-config-14

llc-14

llvm-14

-----------------


To compile, use `make all` on the root directory of the project. This will produce an executable called `comp.bin`.

To run the compiler without the bounds-checks insertion, use the following command:
`./comp.bin <filename.c> `

To run the compiler with the bounds-checks insertion, use the following command:
`./comp.bin <filename.c> -bc`


To run the compiler with the bounds-checks elimination optimization, use the following command:
`./comp.bin <filename.c> -bc -bce`


---------------------

These commands will generate a file with the same file name as the input file.


The compiler makes use of bash scripts for some of its functionality. Upon downloading this repo, your OS might remove the execution privelidge from these files. You might therefore need to run `chmod +X <bashscriptname.sh>


--------------------

# Example:

`./comp examples/simpleLoop.c -bc -bce`

This command will create a binary file called `simpleLoop.bin` and an LLVM IR file called `simpleLoop.ll`.

This binary will have its bounds-cehcks optimized due to the flags used for the compiler. 