#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "PointGraphicsItem.h"
#include "CEGraphicsScene.h"
#include "MeasurementAreaLineItem.h"
#include "SelectedPointsTableModel.h"
#include "CEGraphicsScene.h"

#include <QFileDialog>
#include <QDebug>

void MainWindow::setValidators()
{
    ui->lineEdit_originX->setValidator(dv);
    ui->lineEdit_originY->setValidator(dv);
    ui->lineEdit_topLeftY->setValidator(dv);
    ui->lineEdit_bottomRightX->setValidator(dv);
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    dv(new QDoubleValidator),
    model(new SelectedPointsTableModel(this))
{
    ui->setupUi(this);

    ui->tableView_points->setModel(model);
    dynamic_cast<CEGraphicsScene*>(ui->graphicsView->scene())->setModel(model);

    setValidators();

    setUpAreaBoundItems();

    connect(ui->lineEdit_originX, SIGNAL(textEdited(QString)), this, SLOT(onUpdatedOriginCoords()));
    connect(ui->lineEdit_originY, SIGNAL(textEdited(QString)), this, SLOT(onUpdatedOriginCoords()));

    connect(ui->lineEdit_topLeftY, SIGNAL(textEdited(QString)), this, SLOT(onUpdatedTopLeftCoords()));
    connect(ui->lineEdit_bottomRightX, SIGNAL(textEdited(QString)), this, SLOT(onUpdatedBottomRightCoords()));

    connect(ui->checkBox_showImg, SIGNAL(clicked(bool)), ui->graphicsView, SLOT(onShowImgChanged(bool)));

    connect(dynamic_cast<CEGraphicsScene*>(ui->graphicsView->scene()), SIGNAL(pointAdded(double,double,PointGraphicsItem*)), model, SLOT(onAddDataPoint(double,double,PointGraphicsItem*)));

    connect(this, SIGNAL(originChanged(double,double)), model, SLOT(onOriginChanged(double,double)));
    connect(this, SIGNAL(topLeftChanged(double,double)), model, SLOT(onTopLeftChanged(double,double)));
    connect(this, SIGNAL(bottomRightChanged(double,double)), model, SLOT(onBottomrightChanged(double,double)));
}

MainWindow::~MainWindow()
{
    delete ui;
    delete dv;
}

void MainWindow::onUpdatedOriginCoords()
{
    double x = ui->lineEdit_originX->text().toDouble();
    double y = ui->lineEdit_originY->text().toDouble();

    emit originChanged(x, y);
}

void MainWindow::onUpdatedTopLeftCoords()
{
    double y = ui->lineEdit_topLeftY->text().toDouble();

    emit topLeftChanged(0., y);
}

void MainWindow::onUpdatedBottomRightCoords()
{
    double x = ui->lineEdit_bottomRightX->text().toDouble();

    emit bottomRightChanged(x, 0.);
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

void MainWindow::setUpAreaBoundItems()
{
    QPointF origin(ui->lineEdit_originX->text().toDouble(), ui->lineEdit_originY->text().toDouble());

    PointGraphicsItem *originItem = new PointGraphicsItem(origin, tr("Origin"));
    PointGraphicsItem *topLeftItem = new PointGraphicsItem(origin, tr("Top left"), originItem);
    PointGraphicsItem *bottomRightItem = new PointGraphicsItem(origin, tr("Bottom right"), originItem);

    topLeftItem->moveBy(0., -100.);
    bottomRightItem->moveBy(100., 0.);

    MeasurementAreaLineItem *xLine = new MeasurementAreaLineItem(originItem, topLeftItem);
    MeasurementAreaLineItem *yLine = new MeasurementAreaLineItem(originItem, bottomRightItem);

    topLeftItem->setConnectedMeasurementLineItem(xLine);
    bottomRightItem->setConnectedMeasurementLineItem(yLine);

    xLine->setColor(originItem->getColor());
    yLine->setColor(originItem->getColor());

    ui->graphicsView->scene()->addItem(originItem);
    ui->graphicsView->scene()->addItem(xLine);
    ui->graphicsView->scene()->addItem(yLine);

    originItem->setModel(model);

    model->setOriginItem(originItem);
    model->setTopLeftItem(topLeftItem);
    model->setBottomRightItem(bottomRightItem);

    model->onTopLeftChanged(0., ui->lineEdit_topLeftY->text().toDouble());
    model->onBottomrightChanged(ui->lineEdit_bottomRightX->text().toDouble(), 0.);
}
