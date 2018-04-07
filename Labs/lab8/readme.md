# Lab 08 - Templates

At this point in the course, we've created many simple data structures ourselves, as well as used a number of already-templated STL classes. The goal of this lab is to learn how to actually create these templated classes ourselves.

## 1 - Motivation

Recall that we've been creating data structure classes that look like `AListInt`, `StackInt`, etc. They are useful data structures, but they were limited to serving one type of data (`int`s and `double`s in this case).

What if, for example, a user wants to use a linked list, but for a series of `string`s? In order to use the same kind of data structure for different data types, we'll have to make a copy of the code, change every single mention of `int` to `string`. Doing so creates a lot of code that is repeated unnecsesarily, violating a software engineering principle called [**Don't Repeat Yourself (DRY)**](http://en.wikipedia.org/wiki/Don't_repeat_yourself). It's easy to setup, but comes with a heavy price: if you discover a bug in one set of code, you'll have to apply the patch across multiple files, making your project very prone to mistakes and errors.

Through templates, however, we could treat a type as a variable, and specify it at the time of object declaration. By the end of this lab, we'll convert one of the type-specific lists into a generic, templated one.

## 2 - Example

One of the simplest templated examples we've encountered so far is the `std::pair` class. It is declared with two "types", and values of the sepcified types are passed in to the constructor. In a templated class, functions signatures and parameters can be defined "programatically". For example:

```
Pair<double, string> student(1234567890, "Nikhil Bedi");
Pair<string, int> question("What is the answer to life, universe, and everything?", 42);
```

Similarly, the return values of its functions can be defined "programmatically" as well. For example:

```
double studentId = student.getFirst() // returns a double
string answer = question.getSecond(); // returns a string
```

Let's open the file `pair.h` and take a closer look.

### Declare the types with `template < >`

We list the number of programatically declared types that we'll use in a templated class with a simple `template < >` tag, right before the signature of anything related to the class - class declaration, function implementation, etc. This is important - technically, a templated `Pair` class with one dynamic type is an entirly different class from a non-templated `Pair` class, even if they share the same name. Therefore, every time we mention a templated class, we must refer to it with `template < >`.

Notice that with Pair, we are listing that two classes can be specified. We're going to name the first type `FirstType` and the second type `SecondType`. These names act as variable names - wherever in the class, `FirstType` and `SecondType` is referring to the specific types that the user of the templated class specified in declaration.

### Do not pre-compile!

Another thing you'll notice is that the class's implementations for all its methods are included in this header file. This is not a bad practice, but in fact, it is required for templated class to do so, since templated classes cannot be pre-compiled.

As we've mentioned from the Coding Guide,

> Each source file the compiler knows about is compiled in its own translation unit and it only knows about its own contents and the contents that other source files export. Source files export all globally visible variables and functions. Normally when you write some non templated code, it gets fully compiled since all the types are known and it can be exported to other translation units (other source files). When you have template code, that template is just a blueprint of what the compiler has to do when it gets a type. It is not until you instantiate your template by saying ”I want a List of strings” (List) that the compiler goes ahead and tries to actually generate the code where it replaces with `T = std::string`.

Therefore, since it is impossible for the compiler to know ahead of time what specific type of templated classes the program will need, we do not bother putting its method implementations in their own `cpp` file to be pre-compiled into a `.o` file before linking.

## 3 - Your turn

We have included a simplified version of LListInt in here - your job is to template it and make it usable with any class, not just int's. We have already changed the name from `LListInt` to a simple `LList`

What you need to do:

1. Copy the contents from `llist.cpp` into the bottom of `llist.h`, since we do not want templated class implementations in their own file.
2. Template the struct `Item`. It is setup to store an int variable, but that needs to change, too.
2. Template the class - include `template < >` tags wherever the class is mentioned. Since there is only one generic type - convention usually names it `T` (instead of `FirstType`, `SecondType`).
3. Change (almost) all mentions of `int` to `T`. Reference to the class `Item` needs to be changed as well - remember that it is not templated.
4. Make, and see if the main file works.
