import random
import math

num_grids = 10
sudoku_size = 9
num_clues = 20

class SudokuGenerator:
    def __init__(self, size=9):
        self.size = size
        self.box_size = int(math.sqrt(size))
        self.grid = [[0 for _ in range(size)] for _ in range(size)]
        
    def is_valid(self, num, pos):
        row, col = pos
        
        for x in range(self.size):
            if self.grid[row][x] == num and col != x:
                return False
                
        for x in range(self.size):
            if self.grid[x][col] == num and row != x:
                return False

        box_x = col // self.box_size
        box_y = row // self.box_size
        for i in range(box_y * self.box_size, box_y * self.box_size + self.box_size):
            for j in range(box_x * self.box_size, box_x * self.box_size + self.box_size):
                if self.grid[i][j] == num and (i, j) != pos:
                    return False
                    
        return True
        
    def generate_puzzle(self, num_clues):
        max_clues = self.size * self.size
        if num_clues > max_clues:
            raise ValueError(f"Number of clues cannot exceed {max_clues}")
            
        positions = [(i, j) for i in range(self.size) for j in range(self.size)]
        selected_positions = random.sample(positions, num_clues)
        
        for pos in selected_positions:
            valid_numbers = list(range(1, self.size + 1))
            random.shuffle(valid_numbers)
            
            for num in valid_numbers:
                if self.is_valid(num, pos):
                    self.grid[pos[0]][pos[1]] = num
                    break
                    
        return self.grid
        
    def print_grid(self):
        for i in range(self.size):
            for j in range(self.size):
                print(self.grid[i][j], end=" ")
            print()

def generate_sudoku(size=9, num_clues=30):
    generator = SudokuGenerator(size)
    puzzle = generator.generate_puzzle(num_clues)
    return puzzle

if __name__ == "__main__":
    for i in range(1,num_grids+1):
        generator = SudokuGenerator(sudoku_size)
        puzzle = generator.generate_puzzle(num_clues)
        print(f"Grid {i}")
        generator.print_grid()
        print()