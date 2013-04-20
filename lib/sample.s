In elif parser...
Parsing done..
Hello there...
(allocate, 12, NULL, NULL)

(mov, 1, , %eax)

(mov, 1, , %ecx)

(cmp %eax, %ecx)

je L0

(mov, 2, , %eax)

(mov, 2, , %ecx)

(cmp %eax, %ecx)

je L1

(mov, 13, , %eax)

(mov, %eax, , c)

jmp L2

L1:

(mov, 12, , %eax)

(mov, %eax, , d)

L2:

