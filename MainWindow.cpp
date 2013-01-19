#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QFileDialog>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionOpen_image_triggered()
{
    QString imgFileName = QFileDialog::getOpenFileName(this, tr("Choose image file to open"), "", tr("Image files (*.png *.jpg *.tif)"));

    if(!imgFileName.isEmpty())
    {
        ui->graphicsView->setBackgroundImage(imgFileName);
    }
}

void MainWindow::on_actionFit_triggered()
{
    ui->graphicsView->fitBgImgInView();
}
