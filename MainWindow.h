#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
signals:
    void originChanged(double x, double y);

private slots:
    void onUpdatedOriginCoords();

    void on_actionOpen_image_triggered();

    void on_actionFit_triggered();

private:
    Ui::MainWindow *ui;

    void setUpAreaBoundItems();
};

#endif // MAINWINDOW_H
