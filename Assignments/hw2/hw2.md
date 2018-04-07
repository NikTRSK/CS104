##PROBLEM 1:
###a)
The status of README.md is:
**Unmodified**
* Since we just pulled from the repository, the state of the file is the same as in the repository.

###b)
The status of README.md is: 
**Modified**
* Since we appended "Markdown is easy" to README.md the status now changed to Modified.

The status of fun_problem.txt is:
**Untracked**
* This is because fun_problem.txt is a new file and it still hasn't been added to the list of tracked files with the add command.

###c)
The status of README.md is:
**Staged**
* This is because the add command was called which caused the file to be staged.

The status of fun_problem.txt is:
**Staged**
* Since fun_problem.txt was a new file, after the add command was called the file was Staged to be commited.

###d)
The status of README.md is:
**Modified**
* This is because after the file was stagged in the previous step it was moved to the Unmodified state. Then we appended "Markdown is too easy" which changed the status to modified.

The status of fun_problem.txt is:
**Modified**
* Similarly as with README.md after staging the file it was moved to the Unmodified state. Then we appended "So far, so good", which changed the status of fun_problem.txt to Modified.

###e)
The status of README.md is:
**Staged**
* Since we run the add command on README.md the status changed from Modified to Staged (to be commited).

The status of fun_problem.txt is:
**Untracked** and the contents is **EMPTY**
* The file was Modified but running checkout overwrites the current file with from the previous commit.
* The file is empty since git pulled the file from the last commit, which was empty.

###f)
The status of README.md is:
Both **Staged** and **Unstaged**
* This is because git commits the version of the file when add was last ran. To commit the changes that we made we would have to run add once again.

##PROBLEM 3:
###a)
**Θ(nlogn)**
* The innerloop runs logn times since we through each iteration we multiply j by 2, until it reaches n. The outer loop runs n times. Therefore we can conclude that for each n the inner loop runs logn times, making this a nlogn algorithm.

###b)
**Θ(n<sup>2</sup>)**
* As in __part a)__ the inner loop will run *logn* times. Since the condition to trigger this loop is j%i, the loop itself will run n/i times. The middle loop will run i times in Θ(1) since we have the condition j%i. The outer loop runs n times, no matter what. All of this makes the sum as follows:

![alt text](https://github.com/NikTRSK/CS104/blob/master/MD_graphics/HW2/3-b1.png)

LATEX: ```\sum_{i=0}^{n-1}\frac{n}{i}logn+\sum_{i=0}^{n-1}(n-i)```

which simplifies to:

![alt text](https://github.com/NikTRSK/CS104/blob/master/MD_graphics/HW2/3-b2.png)

LATEX: ```\sum_{i=0}^{n-1}\frac{n}{i}logn+\sum_{i=0}^{n-1}(i) = nlog^2n+n-n^2 = \theta(n^2)```


###c)
**Θ(n<sup>2</sup>)**
* The outer loop runs n times but the condition of the inside the loop will cause the second for loop to run every 10i times and the inner part of the first loop will run Θ(1) rest of the time. Once we carry the sum we get n + 10n<sup>2</sup> (by the arithmetic series). Therefore the algorithm is Θ(n<sup>2</sup>).

###d)
**Θ(n)**
* The algorithm is similar to part c but instead instead of increasing the size by 10, it doubles the size. This in turn causes the if statement to trigger (and conversely for the inner loop to run) logi times. If we setup a sum for the times the inside of the loop is Θ(1) and when it's not we get the following:

![alt text](https://github.com/NikTRSK/CS104/blob/master/MD_graphics/HW2/3-d1.png)

LATEX: ```n+\sum_{i=0}^{logn}2^{i-1}=n+\sum_{i=0}^{logn}2^{i}=n+2^{logn}=n+n=\Theta (n)```

##PROBLEM 4:
1. A **list** of strings with the president names. Additionally we can add int data types for the terms of presidency if we wanted to provide more information. Since we need order a list is a natural choise since of the 3 ADT (list, map, set) is the only one that is ordered.

2. A **map** of ints (ints for zip, ints (potentially a larger capacity data type but an int should be sufficient since we are looking at zip codes) for the estimate). We can then use the zip code as the key to which we map the population estimates.

3. A **set** of strings with student names. A set is appropriate since we do not care for order or we need to look up names by key. We only care whether a student is in the set or not (whether they've solved the problem).

4. A **map** with ints for student ID (provided it's numerical as at USC) and ints for the assignment number. Additionally, we can use ints for the numeric grade (or floats if we decided to use decimal grades). We can then use a key pair of ID, assignemnt number to lookup the grade. The need to lookup based on a criteria (key) makes a map an appropriate choise.

##PROBLEM 5:
The code reverses a linked list. The resulting list is: 5,4,3,2,1. funcA will keep calling itself until the passed in list reaches NULL. The last call assignes the last node to out. Then funcB is called with the in (4) from the previous call and the last returned value from funcA (4 in this case) as the second parameter. funcB then recurses until the second parameter reaches NULL after which it appends the first parameter to the end of the list. All of the instances of funcB calls return. Now in->next is set to NULL and the list is 5,4 which is what funcA returns when it terminates the instance. Now it performes the similar operations for the previous function call.
An example of the trace of few of the function calls can be found here:

![alt text](https://github.com/NikTRSK/CS104/blob/master/MD_graphics/HW2/5.jpg)

**NOTE:** The trace doesn't show all steps but is enough to illustrate the trend and the final result. 