#include <fstream>
#include <iostream>
#include <string>
#include <cctype>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include "util.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mainwindow.h"
#include <QCoreApplication>

using namespace std;

/*
1. A location that has zero or one neighbors will be empty in the next generation. If a cell was there,
it dies.
2. A location with two neighbors is stable. If it had a cell, it still contains a cell. If it was empty, it's still
empty.
3. A   location   with   three   neighbors   will   contain   a   cell   in   the   next   generation.   If   it   was   unoccupied
before, a new cell is born. If it currently contains a cell, the cell remains.
4. A location with four or more neighbors will be empty in the next generation. If there was a cell in
that location, it dies of overcrowding.
5. A cell that ages more than 10 generations dies, and will be empty the next generation, regardless
of how many neighbors it has.
*/

std::vector<std::vector<int>> grid;

const vector<vector<int>>& getGrid() {
    return grid;
}

int countNeighbors(const vector<vector<int>> &grid, int row, int col) {
    int count = 0;

    // Define valid neighboring directions (up, down, left, right, and diagonals)
    const int dr[] = {-1, 1, 0, 0, -1, -1, 1, 1};
    const int dc[] = {0, 0, -1, 1, -1, 1, -1, 1};

    // Get the number of rows and columns in the grid
    int numRows = grid.size();
    int numCols = grid[0].size();

    // Iterate through neighboring directions
    for (int i = 0; i < 8; i++) {
        int newRow = row + dr[i];
        int newCol = col + dc[i];

        // Check if the neighbor is within bounds
        if (newRow >= 0 && newRow < numRows && newCol >= 0 && newCol < numCols) {
            // Check the value of the neighbor and count it if it's 1 or greater
            if (grid[newRow][newCol] >= 1) {
                count++;
            }
        }
    }

    return count;
}

bool openFile(ifstream &infile, const string &filename) {
    infile.open(filename);
    return infile.is_open();
}

bool readInt(ifstream &infile, int &value) {
    string line;

    if (getline(infile, line)) {
        try {
            value = stoi(line);
            return true;
        } catch (const invalid_argument& e) {
            cerr << "Error: Invalid integer in the file." << endl;
        }
    }
    return false;
}

int createGrid(vector<vector<int>> &grid, ifstream &infile, int &rows, int &columns) {
    string line;
    grid.resize(rows, std::vector<int>(columns, 0));

    for (int i = 0; i < rows; i++) {
        if (!getline(infile, line)) {
            cerr << "Error: Insufficient data in file." << endl;
            return 1;
        }

        if (line.length() < columns) {
            cerr << "Error: Line " << i + 3 << " has insufficient data." << endl;
            return 1;
        }

        for (int j = 0; j < columns; j++) {
            if (line[j] == 'X') {
                grid[i][j] = 1;
            } else if (line[j] != '-') {
                cerr << "Error: Invalid character in the file." << endl;
                return 1;
            }
        }
    }
    return 0;
}

void printGrid(const vector<vector<int>> &grid) {
    string cell;
    for (const auto &row : grid) {
        for (int value : row) {
            if (value == 0) {
                cell = "-";
            } else {
                cell = "X";
            }
            cout << cell << " ";
        }
        cout << endl;
    }
}

int lifeRules(int neighbors) {
    if (neighbors <= 1 || neighbors >= 4) {
        // If empty remains empty, if cell here it dies
        return 0;
    } else if (neighbors == 2)    {
        return 1;
    } else {
        return 2;
    }
}

void tickGrid(vector<vector<int>> &grid) {
    vector<vector<int>> copiedGrid = grid;
    int neighbors = 0, rules = 0;
    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid[0].size(); j++) {
            neighbors = countNeighbors(grid, i, j);

            rules = lifeRules(neighbors);

            if (rules == 0) {
                copiedGrid[i][j] = 0;
            } else if (rules == 1 && grid[i][j] >= 1) {
                copiedGrid[i][j] = 1 + copiedGrid[i][j];
            } else if (rules == 2) {
                copiedGrid[i][j] = 1 + copiedGrid[i][j];
            } else if (grid[i][j] >= 10) {
                copiedGrid[i][j] = 0;
            }
        }
    }
    grid = copiedGrid;
}

int play(ifstream& infile, MainWindow& mainWindow) {
    int rows = 0, columns = 0;
    // Get first two values from file for rows and columns
    if (!readInt(infile, rows) || !readInt(infile, columns)) {
        return 1;
    }



    if (createGrid(grid, infile, rows, columns) == 1) {
        return 1;
    }

    cout << "got rows and columns" << endl;
    // Define a delay interval (in milliseconds) for animation
    emit mainWindow.gridUpdateRequested(grid);


    infile.close();

    return 0;
}
