#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <vector> // Include the vector header
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QColor>
#include <QVBoxLayout>
#include "life.h"
using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Create a central widget and set it as the main window's central widget
    QWidget* centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    // Create a vertical layout for the central widget
    QVBoxLayout* centralLayout = new QVBoxLayout(centralWidget);

    // Create and add the QTableWidget to the layout with stretch factor 1
    tableWidget = new QTableWidget(centralWidget);
    centralLayout->addWidget(tableWidget, 1); // Set stretch factor to 1

    // Set the tableWidget to stretch with the window
    tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    tableWidget->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    // Set a fixed size for each cell

    // Create a horizontal layout for the buttons
    QHBoxLayout* buttonLayout = new QHBoxLayout();

    // Create and add the buttons to the button layout
    QPushButton* tickButton = new QPushButton("Tick");
    buttonLayout->addWidget(tickButton);

    QPushButton* slowButton = new QPushButton("Slow");
    buttonLayout->addWidget(slowButton);

    QPushButton* pauseButton = new QPushButton("Pause");
    buttonLayout->addWidget(pauseButton);

    QPushButton* fastButton = new QPushButton("Fast");
    buttonLayout->addWidget(fastButton);

    QPushButton* quitButton = new QPushButton("Quit");
    buttonLayout->addWidget(quitButton);

    // Add a spacer item to push the buttons to the bottom
    buttonLayout->addStretch();

    // Add the button layout to the central layout
    centralLayout->addLayout(buttonLayout);

    // Connect the buttons to their respective slots
    connect(this, &MainWindow::gridUpdateRequested, this, &MainWindow::updateGrid);
    connect(tickButton, &QPushButton::clicked, this, &MainWindow::onTickButtonClicked);

    // Connect the Quit button to exit the application
    connect(quitButton, &QPushButton::clicked, this, &QCoreApplication::quit);
}



MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateGrid(const std::vector<std::vector<int>>& grid) {
    // Implement your grid update logic here
    // You can access the grid data using the 'grid' parameter
    // This function will be called whenever the grid needs to be updated

    int numRows = grid.size();
    int numCols = grid[0].size();

    tableWidget->setRowCount(numRows);
    tableWidget->setColumnCount(numCols);

    for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < numCols; j++) {
            QTableWidgetItem* item = new QTableWidgetItem();
            int cellValue = grid[i][j];

            // Set the background color based on cellValue
            QColor cellColor = calculateCellColor(cellValue);

            item->setBackground(cellColor);
            tableWidget->setItem(i, j, item);
        }
    }
}

QColor MainWindow::calculateCellColor(int cellValue) {
    // Calculate the cell color based on the cellValue (0-10)
    // Customize this function to determine the colors you want
    if (cellValue == 0) {
        return Qt::white;
    } else {
        // Calculate a shade of blue based on cellValue
        int blueValue = 255 - (cellValue * 10);
        return QColor(0, 0, blueValue);
    }
}

// Define the slot function for the "Tick" button click event
void MainWindow::onTickButtonClicked() {
    // Call tickGrid() to update the grid
    tickGrid(grid); // Assuming you also have tickGrid function in MainWindow

    // Access the grid from life.cpp using the getGrid function
    const std::vector<std::vector<int>>& lifeGrid = getGrid();

    // Update the widget with the new grid
    emit gridUpdateRequested(lifeGrid);
}
