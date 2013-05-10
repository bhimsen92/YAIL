# YAIL : Yet Another Interpreted Language
A Functional Language Interpreter.

# How To Build
1. Download zip file from github.
2. Unzip it into any directory.
3. Go to YAIL-[master]/lib folder
4. execute <b>make</b> command. This will create bnK-lang executable in the <b>lib</b> directory.
5. Then go to <b>samples</b> folder which contains some simple programs.
6. Then execute the following command: <strong>../lib/bnK-lang &lt; file.yail [present in the <b>samples</b> directory.</strong>]


# Why I built It
1. To learn compiler design.
2. To understand how computer languages are designed and what it takes to build them.
3. To have experience with writing large code base and learn how to maintain it.
4. And finally to have fun. It`s really a humbling experience to see writing a simple program in your own language and see it executing 
   on your machine.


# What it can do
1. It is typed.
2. Supports basic arithmatic operations.
3. Supports basic types like Integers, Float, String and Arrays[only for Integers and Double]
4. Supports the creation of functions and nested functions.
5. Supports Closure and Currying.
6. Supports creation of Threads.

# How to use it

## Defining Variables

Creating variables in <i><b>yail</b></i> language is similar to <i><b>C or Java</b></i>. First you need to specify the type and then
the name of the variable. Since it is a functional language, all variables that you define must be initialized.
Example:

    Int num = 12; # statements must end with semicoln.
    # or
    Double d = 12.34; # To make value double, you need to write "." followed by some number.
    # or
    String str = "Hello world";
    # or
    Int[] num = [1, 2, 3, 4];
    # or
    Double[] num = [1.3, 2.3];
    # or
    Bool flag = false;
    
There is no restriction on creation of variables, you can create them where ever you want and whenever you want.

## Making Decisions
