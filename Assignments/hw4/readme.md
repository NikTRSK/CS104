- **Name**: Nikica Trajkovski
- **USC ID**: 1559186096
- **Email**: trajkovs@usc.edu

#Homework 4: Project, Part 1 (Inheritance, Maps)

To compile:
`make facile`

To run:
`./facile`

To compile and run with valgrind:
`make grind_facile`

####Notes on behavior:
* calling `PRINT` on an undeclared variable will print out `0`
* `PRINTALL` prints out only declared variables
**EX:**
```
PRINT A
PRINTALL
.
```
Outputs:
`0`

* Reasigning variables: Calling `LET` multiple times on the same variable reassignes the last value
**EX:**
```
LET A 5
LET A 2
LET A 9
PRINTALL
.
```
Outputs:
`A 9`

* As per the assignment, referencing an undeclared variable has a default value. However the variable doesn't get inserted into the variables list.
Example
```
LET A 5
PRINT B
PRINT ALL
.
```
Outputs:
```
0
A 5
```

Similarly, in math operations an undeclared variable is used as 0
Example:
```
LET A 10
ADD A B
PRINT ALL
.
```
Outputs:
`A 10`. Notice how B is not printed since it has not been declared, but it is considered to be 0 implicitly.

On the other hand, if used as the first variable in math operations the undeclared variable is stored in the variable list.
Example:
```
LET A 10
ADD B A
PRINT ALL
.
```
Outputs:
```
A 10
B 10
```
Notice how B is printed since it has been used as the left-hand operator and is considered to be 0 implicitly.