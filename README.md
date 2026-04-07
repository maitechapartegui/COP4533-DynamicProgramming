# COP4533-DynamicProgramming
**Students:**

Heiryn Hernandez Rojas - 90988659

Maite Chapartegui - 54536135

## Files
Within src folder:
* `opt.cpp` - has the input and opt dynamic programming algorithm which basically finds the common substring that maximizes total value of characters within said substring

Within data folder:
* `examplen.txt`: Different input files with a variety of input numbers and capacities
* `examplen.out`: the output with the misses for each function
## Compilation
Our program is written in C++
To compile the code,

1. Clone the repo on your device:
* git clone https://github.com/maitechapartegui/COP4533-DynamicProgramming.git

2. Compile in VSCode (or IDE of your choosing) terminal
* g++ -std=c++17 ./src/opt.cpp -o opt
* ./opt ./data/example100.in
- to change input file, just edit the path in the second command

## Assumptions

## Written Component

### Question 1: Empirical Comparison
Using the C++ <chrono> library:
- We placed the timers immediately before and after the core function for loop to capture only the execution time of the dp algorithm, specifically excluding the time spent on file I/O (input/output).
  This was done with code like:
    - `auto start = chrono::high_resolution_clock::now();`
    - `auto end = chrono::high_resolution_clock::now();`
    - `auto duration = chrono::duration_cast<chrono::nanoseconds>(end - start);`
      *As you can see with the graph: our algorithm follows the theta(mxm) trend. This means that it is correctly aligned with the expected trend. As we are going through two for loops that each run all m and all n times*
      ![Question 1 Runtime Graph](newRuntimeGraph.png)

### Question 2: Recurrence Equation
Assumptions:
- A and B are input string
- v(x) is value of character x
- M[i][j] = maximum value of common subsequence, where i ranges from (0,m) and j ranges from (0,n)

Base Cases:
- If i = 0, then M[0][j] = 0
- If j = 0, then M[i][0] = 0

Recurrence:
- M[i][j] = v(A[i]) + M[i - 1][j - 1]       if A[i] == B[j]
- M[i][j] = max(M[i - 1][j], M[i][j - 1])   if A[i] != B[j]

Explanation:
This recurrence is correct because for each cell M[i][j] we are solving the most optimal value for the first i letters of A and the first j letters of B. We check for two cases, either the last characters match, so we can take that character in our subsequence and add its value or the last characters do not match, so we cannot take both of them as a matched pair, meaning the optimal subsequence must skip one side, so we take the maximum value between the two max(M[i-1][j], M[i][j-1])).

### Question 3: Big-Oh
    HVLCSLength(A, B, v):
    
    m = length(A)
    n = length(B)
   
    create 2d array M of size (m+1) x (n+1) where M[i][j] is the max total value

    // base cases
    for i = 0 to m:
        M[i][0] = 0
    for j = 0 to n:
        M[0][j] = 0

    // fill table in bottom up
    for i = 1 to m:
        for j = 1 to n:
            if A[i-1] == B[j-1]:
                M[i][j] = M[i-1][j-1] + v(A[i-1])
            else:
                M[i][j] = max(M[i-1][j], M[i][j-1])
    for i = 1 to m:
        for j = 1 to n:
            if A[i-1] == B[j-1]:
                M[i][j] = M[i-1][j-1] + v(A[i-1])
            else:
                M[i][j] = max(M[i-1][j], M[i][j-1])
    
     return M[m][n]


- Runtime:
  - Our array has size m x m, so filling up the table takes O(mn) time.


