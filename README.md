
# Sudoku Solver

  

This Sudoku solver uses the fact that NP complete problems can be converted into one another in polynomial time, to convert Sudoku into the exact cover problem.

Once converted, it is solved using _Knuth's DLX algorithm_ (Dancing Links implementation of Algorithm X).

The general method of solving by conversion to exact cover usually goes

``Original Problem -> Convert to exact cover matrix -> Create the linked list required for DLX, using the matrix -> Solve -> Convert back``

However, an optimization we made was to skip the second step entirely.

`` Original Problem -> Create the linked list required for DLX -> Solve -> Convert back``

This optimization proved extremely beneficial to solving times for Sudokus with a smaller number of clues, reducing solving times by  ~30x for a 16x16 Sudoku with no clues (we believe the time savings grow with the size of the Sudoku).


This project was made by
| Name         | Roll No |
|--------------|---------|
| Abhinav Bitragunta        | 230001003     |
| Aman Gupta          | 230001006     |
| Srinidhi Sai Boorgu     | 230001072     |
| Ansh Jain     | 230004005     |

## Improvements over the standard backtracking algorithm
For 9x9 Sudokus, the solving times(all measured on the same computer) ranged between 600μs to 400ms.
For standard  9x9 Sudokus(~17 clues), the solving times were almost always 170-200ms.

The DLX implementation, however, is able to consistently solve any 9x9 Sudoku in ~120μs.

The solving time will only get exponentially worse for the standard backtracking algorithm.
For 16x16 Sudokus(Hexadoku) with 80 clues, the standard algorithm takes  1.65 seconds! for a single solution, whereas the DLX implementation can output 10 solutions for it in just 1.1ms.

The gains in speed only grow as the Sudoku size gets larger.

## Requirements
* g++ compiler, that supports C++23 (This project will not compile on any standard older than C++20 due to the use of the ``format`` library).

## Build Instructions

  If your g++ compiler supports C++20 but not C++23, you'll have to replace ``-std=c++23`` in build.bat with ``-std=c++20`` using an editor that is able to edit windows batch files(.bat).
  
  The instructions below only work on Windows. For any other OS you'll have copy the commands from the **_build.bat_** file and run them in a terminal.

#### 1. Directly from File Explorer

  

* Double-click the **_build.bat_** file in your File Explorer to automatically open the Terminal and execute the script.

This generates a **_Sudoku Solver.exe_** file and runs it immediately.

  

* If the **_Sudoku Solver.exe_** file has already been generated, double-click the file in your File Explorer to run it.

  

#### 2. Using Command Prompt

* Open Command Prompt and navigate to your directory using the `cd` command.

* Run the following command to execute the **_build.bat_** file.

```cmd

build.bat

```

This generates a **_Sudoku Solver.exe_** file and runs it immediately.

* If the **_Sudoku Solver.exe_** file has already been generated, execute the following command.

```cmd

"Sudoku Solver.exe"

```


#### 3. Using PowerShell

* Open PowerShell and navigate to your directory using the `cd` command.

* Run the following command to execute the **_build.bat_** file.

```powershell

.\build.bat

```

This generates a **_Sudoku Solver.exe_** file and runs it immediately.

* If the **_Sudoku Solver.exe_** file has already been generated, execute the following command.

```powershell

.\"Sudoku Solver.exe"

```

  

## Debug Mode

To enter debug mode, uncomment the following line in **_Headers/Libraries.hpp_**, and build the project again(as done previously).

Make sure to delete any previous instances of the `Sudoku Solver.exe`file before building again.

```c++

//#define  DEBUG

```

## References

 * Donald Knuth's [original paper](https://www.ocf.berkeley.edu/~jchu/publicportal/sudoku/0011047.pdf) on dancing links.
 
* Harrysson, Laestander - Degree [project paper](https://www.kth.se/social/files/58861771f276547fe1dbf8d1/HLaestanderMHarrysson_dkand14.pdf)
