# YAIL : Yet Another Interpreted Language
A Functional Language Interpreter.

# What Do You Need To Build It ?
1. flex[lex] tool
2. bison[yacc] tool
3. g++ compiler[latest version will be good]
4. Linux OS.

# How To Build
1. Download zip file from github.
2. Unzip it into any directory.
3. Go to YAIL-[master]/lib folder
4. execute <b>make</b> command. This will create bnK-lang executable in the <b>lib</b> directory.
5. Then go to <b>samples</b> folder which contains some simple programs.
6. Then execute the following command: <strong>../lib/bnK-lang &lt; file.yail [present in the <b>samples</b> directory.</strong>]


# Why I built It ?
1. To learn compiler design.
2. To understand how computer languages are designed and what it takes to build them.
3. To have experience with writing large code base and learn how to maintain it.
4. And finally to have fun. It`s really a humbling experience to see writing a simple program in your own language and see it executing 
   on your own machine.


# What it can do
1. It is typed.
2. Supports basic arithmatic operations.
3. Supports basic types like Integers, Float, String, Function and Arrays[only for Integers and Double]
4. Supports the creation of functions and nested functions.
5. Supports Closure and Currying.
6. Supports creation of Threads.

# How to use it

## Defining Variables

Creating variables in <i><b>yail</b></i> language is similar to <i><b>C or Java</b></i>. First you need to specify the type and then
the name of the variable. Since it is a functional language, all variables that you define must be initialized.

### Example:

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

Multiple assignments are not allowed. So following code snippet will through an error and is in accordance with Functional language.

    Int a = 12;
    a = 34; # error


## Making Decisions
You can control the flow of your program using good old if, else or elif structure. As in <i><b>Java</b></i> the coditional
expression must result in boolean value otherwise error will be thrown.

### if Example:

    Int a = 12, b = 10;
    if(a > b){
      print("a is grater\n");
    }
    else{
      print("b is greater\n");
    }
<b>else</b> block is compulsory whenever you write <b>if</b> or <b>elif</b>.

### elif Example:

    Int a = 10, b = 23, c = 25;
    if(a > b){
      if(a > c){
        print("a is greater\n");
      }
      else{
        print("c is greater\n");
      }
    }
    elif(b > c){
      print("b is greater\n");
    }
    else{
      print("c is greater\n");
    }

# Arrays
<i><b>yail</b></i> has only one container object, Arrays. In this language arrays are fixed length and homogeneous, meaning
they contain values of the specified type. 

Arrays support following operations:

1. Indexing
2. Concatenation
3. Slicing

### Array examples

    # array creation
    Int[] a = [1, 2, 3, 4, 5];
    
    # concatenation
    Int[] b = a + [123, 34];
    
    # slicing
    Int[] c = b[1:4];


# Creating Functions
In <i><b>yail</b></i> functions are basic way of creating abstractions. Function block are created using <i>function</i> keyword,
followed by <i>name</i> of the function, then optional arguments and the return type followed by statements which you want to execute 
once the function is called.
### syntax for creating a function.

    function funct_name([Type var,[Type var...]): ReturnType{
         # list of statements.
    }

### Some Examples

    # finding square.
    function square(Int n):Int{
        return n * n;
    }

    # finding factorial
    function fact(Int n):Int{
       if(n == 0)
         return 1;
       else
         return n * fact(n - 1);
    }
    
    # iterating through an array.
    function printArray(Int[] arr):Nothing{
      if(arr.length > 0){
         print(arr[0], " ");
         printArray(arr[1:]);
      }
      else{
         print("\n");
      }
    }
    
    # simple map implementation.
    function map(Int[] arr, Int index, Function f):Int[]{
      if(index < arr.length){
         return [f(arr[index])] + map(arr, index + 1, f);
      }
      else{
         return [];
      }
    }

### Calling syntax for functions
    
    funct_name([arg,[arg..]]);


# Creating Nested Functions and Closure
<i><b>yail</b></i> supports nesting functions within function and supports closure to

### Nested function example:

    function outer():Nothing{
      function inner():Nothing{
         print("Hello world\n");
      }
      inner();
    }
    outer();

### Closure example:

    function nC(Int n):Function{
      Int factN = fact(n);
      function Cr(Int r):Int{
         return factN/(fact(n - r) * fact(r));
      }
      return Cr;
    }
    
    Function _5c = nC(5);
    print("5C2: ", _5c(2));


# Currying
Currying is a technique in which a function is called with few parameters then it officially takes. After this <i>partial</i>
application, a new Function object is returned which you can use it to pass left over arguments so that the function finally gets
called.

### currying example:

    function addThreeNumbers(Int a, Int b, Int c):Int{
         return a + b + c;
    }
    
    Function add1 = addThreeNumbers(1); # new function object gets returned which is ready to take 'b' and 'c'.
    Function add5 = add1(5);
    Int result = add5(10); # result = 16
    print("Result: ", result);
    
The samples directory contains a quicksort example, which uses currying concept.

# What Needs To Be Done Yet
Lots of things needs to be implemented in this project but i believe following are really important which i want to concentrate
on.

1. Implementing error module.[right now, if you get any error, interpreter just exits or a segmentation fault is thrown]
2. Thread scheduling.
3. Testing.

I am still working on this project. Comments are really appreciated.

Following People helped me a lot during my project.

1. Ajey Bharadwaj A

2. Gourav H Dhelaria 

3. Prof. N S Kumar [our Project Guide]


