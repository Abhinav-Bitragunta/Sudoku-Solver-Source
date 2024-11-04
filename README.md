# Sudoku Solver
--------------------
Uses ***Dancing Links*** to implement ***Knuth's Algorithm X*** to convert Sudoku into the ***exact cover problem*** and solve it efficiently.

### Build instructions
---------------------
Compile with the following, and run the .exe from any terminal.
```bash
g++ -std=c++23 -O3 -march=native -flto -ffast-math -fomit-frame-pointer -o sudoku.exe sudoku.cpp

```



