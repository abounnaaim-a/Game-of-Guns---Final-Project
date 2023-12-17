//Game of Guns - Final Project. Four Gosper Glider Guns firing at each other to create an infinite loop of cells.

#include <iostream>
#include <vector>
#include <windows.h>

const int rows = 40;
const int cols = 120;

void initializeGrid(std::vector<std::vector<char>>& grid) {
    grid.assign(rows, std::vector<char>(cols, ' '));
}

void printGrid(const std::vector<std::vector<char>>& grid) {
    system("cls");
    for (const auto& row : grid) {
        for (char cell : row) {
            std::cout << cell << ' ';
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void placeGosperGliderGun(std::vector<std::vector<char>>& grid, int startRow, int startCol) {
    std::vector<std::string> gunPattern = {
        "                        O",
        "                      O O",
        "            OO      OO           OO",
        "           O   O    OO           OO",
        "OO         O     O   OO",
        "OO         O   O OO    O O",
        "           O     O        O",
        "            O   O",
        "             OO"
    };

    for (int i = 0; i < gunPattern.size(); ++i) {
        for (int j = 0; j < gunPattern[i].size(); ++j) {
            grid[startRow + i][startCol + j] = gunPattern[i][j];
        }
    }
}

void updateGrid(std::vector<std::vector<char>>& grid) {
    std::vector<std::vector<char>> newGrid = grid;

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            int liveNeighbors = 0;

            for (int x = -1; x <= 1; ++x) {
                for (int y = -1; y <= 1; ++y) {
                    int newRow = (i + x + rows) % rows;
                    int newCol = (j + y + cols) % cols;

                    if (grid[newRow][newCol] == 'O') {
                        liveNeighbors++;
                    }
                }
            }

            if (grid[i][j] == ' ' && liveNeighbors == 3) {
                newGrid[i][j] = 'O';
            } else if (grid[i][j] == 'O' && (liveNeighbors < 3 || liveNeighbors > 4)) {
                newGrid[i][j] = ' ';
            }
        }
    }

    grid = newGrid;
}

int main() {
    std::vector<std::vector<char>> grid;

    initializeGrid(grid);

    placeGosperGliderGun(grid, 1, 1);
    placeGosperGliderGun(grid, 1, 50);
    placeGosperGliderGun(grid, 20, 1);
    placeGosperGliderGun(grid, 20, 50);

    for (int generation = 0; generation < 100; ++generation) {
        printGrid(grid);
        updateGrid(grid);
        Sleep(1000);
    }

    return 0;
}
