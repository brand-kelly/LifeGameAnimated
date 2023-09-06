#ifndef LIFE_H
#define LIFE_H

#include <vector>
#include <fstream>
#include "mainwindow.h"

// Declare the grid as a global variable in life.cpp
extern std::vector<std::vector<int>> grid;

// Function to get the grid from life.cpp
const std::vector<std::vector<int>>& getGrid();

// Function to count neighbors of a cell
int countNeighbors(const std::vector<std::vector<int>> &grid, int row, int col);

// Function to open a file for processing
bool openFile(std::ifstream &infile, const std::string &filename);

// Function to read an integer from a file
bool readInt(std::ifstream &infile, int &value);

// Function to create a grid from a file
int createGrid(std::vector<std::vector<int>> &grid, std::ifstream &infile, int &rows, int &columns);

// Function to print the grid to the console
void printGrid(const std::vector<std::vector<int>> &grid);

// Function to apply the rules of life to a cell
int lifeRules(int neighbors);

// Function to tick the grid to the next generation
void tickGrid(std::vector<std::vector<int>> &grid);

// Function to play the game of life
int play(std::ifstream &infile, MainWindow &mainWindow);

#endif // LIFE_H
