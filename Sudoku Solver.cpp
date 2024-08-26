#include <iostream>
#include <vector>

class SudokuSolver {
private:
    std::vector<std::vector<int>> board;
    const int SIZE = 9;

public:
    SudokuSolver(const std::vector<std::vector<int>>& initial_board) : board(initial_board) {}

    bool solve() {
        int row, col;
        if (!findEmptyCell(row, col)) {
            return true; // Puzzle solved
        }

        for (int num = 1; num <= 9; num++) {
            if (isValid(row, col, num)) {
                board[row][col] = num;

                if (solve()) {
                    return true;
                }

                board[row][col] = 0; // Backtrack
            }
        }

        return false; // No solution found
    }

    void printBoard() {
        for (int i = 0; i < SIZE; i++) {
            if (i % 3 == 0 && i != 0) {
                std::cout << "---------------------\n";
            }
            for (int j = 0; j < SIZE; j++) {
                if (j % 3 == 0 && j != 0) {
                    std::cout << "| ";
                }
                std::cout << board[i][j] << " ";
            }
            std::cout << "\n";
        }
    }

private:
    bool findEmptyCell(int& row, int& col) {
        for (row = 0; row < SIZE; row++) {
            for (col = 0; col < SIZE; col++) {
                if (board[row][col] == 0) {
                    return true;
                }
            }
        }
        return false;
    }

    bool isValid(int row, int col, int num) {
        // Check row
        for (int x = 0; x < SIZE; x++) {
            if (board[row][x] == num) {
                return false;
            }
        }

        // Check column
        for (int x = 0; x < SIZE; x++) {
            if (board[x][col] == num) {
                return false;
            }
        }

        // Check 3x3 box
        int startRow = row - row % 3;
        int startCol = col - col % 3;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i + startRow][j + startCol] == num) {
                    return false;
                }
            }
        }

        return true;
    }
};

int main() {
    std::vector<std::vector<int>> puzzle = {
        {5, 3, 0, 0, 7, 0, 0, 0, 0},
        {6, 0, 0, 1, 9, 5, 0, 0, 0},
        {0, 9, 8, 0, 0, 0, 0, 6, 0},
        {8, 0, 0, 0, 6, 0, 0, 0, 3},
        {4, 0, 0, 8, 0, 3, 0, 0, 1}, //can change it according to your need
        {7, 0, 0, 0, 2, 0, 0, 0, 6},
        {0, 6, 0, 0, 0, 0, 2, 8, 0},
        {0, 0, 0, 4, 1, 9, 0, 0, 5},
        {0, 0, 0, 0, 8, 0, 0, 7, 9}
    };

    SudokuSolver solver(puzzle);

    std::cout << "Sudoku Puzzle:\n";
    solver.printBoard();

    if (solver.solve()) {
        std::cout << "\nSolved Sudoku:\n";
        solver.printBoard();
    } else {
        std::cout << "\nNo solution exists.\n";
    }

    return 0;
}