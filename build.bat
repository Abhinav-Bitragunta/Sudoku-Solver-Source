@echo off

set optimizers=-Ofast -march=native -flto -funroll-loops -ffast-math -fno-math-errno -fno-trapping-math -fno-stack-protector -fno-exceptions -fno-rtti -funsafe-math-optimizations -fno-semantic-interposition -fomit-frame-pointer

g++ -std=c++23 %optimizers%  -I  Headers  -c  src\Board.cpp                -o  A.o
g++ -std=c++23 %optimizers%  -I  Headers  -c  src\Node.cpp                 -o  B.o
g++ -std=c++23 %optimizers%  -I  Headers  -c  src\ConstraintMatrix.cpp     -o  C.o
g++ -std=c++23 %optimizers%  -I  Headers  -c  src\ToroidalLinkedList.cpp   -o  D.o
g++ -std=c++23 %optimizers%  -I  Headers  -c  src\Solver.cpp               -o  E.o
g++ -std=c++23 %optimizers%  -I  Headers  -c      main.cpp                 -o  F.o

g++ -std=c++23 %optimizers% A.o B.o C.o D.o E.o F.o -o "Sudoku Solver.exe"

del *.o
echo Build Successful, opening Sudoku Solver.exe

"Sudoku Solver.exe"