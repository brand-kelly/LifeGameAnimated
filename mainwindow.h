#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <vector>
#include <QTableWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

signals:
    void gridUpdateRequested(const std::vector<std::vector<int>>& grid);

private slots:
    void onTickButtonClicked();
    void updateGrid(const std::vector<std::vector<int>>& grid);

private:
    Ui::MainWindow *ui;
    QTableWidget* tableWidget;

    // You can add other private member functions if needed
    QColor calculateCellColor(int cellValue);

    // Define any other private members as needed
};

#endif // MAINWINDOW_H
