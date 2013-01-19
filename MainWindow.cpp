#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "PointGraphicsItem.h"
#include "CEGraphicsScene.h"

#include <QFileDialog>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QPointF origin(ui->doubleSpinBox_originX->value(), ui->doubleSpinBox_originY->value());

    ui->graphicsView->scene()->addItem(new PointGraphicsItem(origin, tr("Origin")));

    connect(ui->doubleSpinBox_originX, SIGNAL(valueChanged(double)), this, SLOT(onUpdatedOriginCoords()));
    connect(ui->doubleSpinBox_originY, SIGNAL(valueChanged(double)), this, SLOT(onUpdatedOriginCoords()));

    connect(this, SIGNAL(originChanged(double,double)), dynamic_cast<CEGraphicsScene*>(ui->graphicsView->scene()), SLOT(onUpdateOriginCoords(double,double)));

    connect(ui->checkBox_showImg, SIGNAL(clicked(bool)), ui->graphicsView, SLOT(onShowImgChanged(bool)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onUpdatedOriginCoords()
{
    double x = ui->doubleSpinBox_originX->value();
    double y = ui->doubleSpinBox_originY->value();

    emit originChanged(x, y);
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
