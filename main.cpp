#include "mainwindow.h"
#include <QApplication>
#include "life.h"
#include <iostream>
#include <QDebug>
#include <QTimer> // Include QTimer for animation delay
#include <fstream>
#include <QFileDialog>

using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    // Create a file dialog to get the filename from the user
    QString filename = QFileDialog::getOpenFileName(&w, "Open File", QDir::currentPath(), "Text Files (*.txt);;All Files (*)");

    if (filename.isEmpty()) {
        cerr << "No file selected. Exiting." << endl;
        return 1;
    }

    const string filenameUtf8 = filename.toUtf8().constData();

    ifstream infile;

    if (!openFile(infile, filenameUtf8)) {
        cerr << "Error: Could not open file " << filenameUtf8 << endl;
        return 1;
    }

    int consoleResult = play(infile, w);

    if (consoleResult != 0) {
        qDebug() << "Error: Console-based logic failed with code " << consoleResult;
        return consoleResult; // Exit with the error code from console-based logic
    }

    w.show();
    return a.exec();
}

