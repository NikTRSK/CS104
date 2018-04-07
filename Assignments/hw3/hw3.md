##PROBLEM 2:
###a) Θ(n^2)
Since we are looking at the worst case, we take the worse of two functions, which is n^2.

###b) Θ(n)
Since foo() gets called 10 times the first time then bar() gets called then foo() gets called 20 times then bar() gets called once, we can conclude that foo runs n/2 times and bar() gets called every n+1 time. After setting up an equation and distributing over the number of calls, we can see that the cost per amortized operation is n.

![alt text](https://github.com/NikTRSK/CS104/blob/master/MD_graphics/HW3/2b.gif)

LATEX: ```\frac{\frac{n}{2}*foo() + bar()}{\frac{n}{2}}=\frac{\frac{n}{2}*logn +n^2}{\frac{n}{2}}=logn+2n=\Theta (n)```

###c) Θ(nlogn)
Similarly to b) we get nlogn since foo() is now Θ(nlogn).

![alt text](https://github.com/NikTRSK/CS104/blob/master/MD_graphics/HW3/2c.gif)

LATEX: ```\frac{\frac{n}{2}*foo() + bar()}{\frac{n}{2}}=\frac{\frac{n}{2}*nlogn +n^2}{\frac{n}{2}}=nlogn+2n=\Theta (nlogn)```

###d) Θ(n^2) for both worst and amortized.
By running the analisys on the algorithm we can see that foo() never gets called. Therefore we take the runtime of bar(), which is Θ(n^2).