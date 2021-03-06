/*  CurveExtractor A simple tool to extract data points from images.
 *  Copyright (c) 2013, Harald Held <harald.held@gmail.com>
 *  All rights reserved.
 *  https://bitbucket.org/hheld/curveextractor
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions are
 *  met:
 *
 *  (1) Redistributions of source code must retain the above copyright
 *      notice, this list of conditions and the following disclaimer.
 *
 *  (2) Redistributions in binary form must reproduce the above copyright
 *      notice, this list of conditions and the following disclaimer in
 *      the documentation and/or other materials provided with the
 *      distribution.
 *
 *  (3) The name of the author may not be used to
 *      endorse or promote products derived from this software without
 *      specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 *  IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 *  WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 *  DISCLAIMED. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT,
 *  INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 *  (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 *   SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 *  HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 *  STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
 *  IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 *  POSSIBILITY OF SUCH DAMAGE.
 */

#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "PointGraphicsItem.h"
#include "CEGraphicsScene.h"
#include "MeasurementAreaLineItem.h"
#include "SelectedPointsTableModel.h"
#include "CEGraphicsScene.h"
#include "CurveFitting/LeastSquaresSolver.h"
#include "CurveFitting/LeastSquareSolverFactory.h"
#include "FittedCurveGraphicsItem.h"

#include <QFileDialog>
#include <QMessageBox>
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
    model(new SelectedPointsTableModel(this)),
    originItem(0),
    topLeftItem(0),
    bottomRightItem(0),
    fcgi(0),
    doCurveFitting(false)
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

    connect(model, SIGNAL(itemDataRemoved(PointGraphicsItem*)), dynamic_cast<CEGraphicsScene*>(ui->graphicsView->scene()), SLOT(onDataPointRemoved(PointGraphicsItem*)));
    connect(model, SIGNAL(dataChanged(QModelIndex,QModelIndex)), this, SLOT(doCurveFit()));
    connect(model, SIGNAL(pointAdded()), this, SLOT(doCurveFit()));
    connect(model, SIGNAL(pointRemoved()), this, SLOT(doCurveFit()));

    connect(ui->comboBox_curveType, SIGNAL(currentIndexChanged(int)), this, SLOT(doCurveFit()));
    connect(ui->spinBox_numPointsCurve, SIGNAL(valueChanged(int)), this, SLOT(doCurveFit()));

    connect(ui->pushButton_saveCurveData, SIGNAL(clicked()), this, SLOT(saveCurveData()));
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
        ui->statusBar->showMessage(tr("Loaded image: %1").arg(imgFileName));
    }
}

void MainWindow::on_actionFit_triggered()
{
    ui->graphicsView->fitBgImgInView();
}

void MainWindow::setUpAreaBoundItems()
{
    QPointF origin(ui->lineEdit_originX->text().toDouble(), ui->lineEdit_originY->text().toDouble());

    originItem = new PointGraphicsItem(origin, tr("Origin"), true);
    topLeftItem = new PointGraphicsItem(origin, tr("Top left"), true, originItem);
    bottomRightItem = new PointGraphicsItem(origin, tr("Bottom right"), true, originItem);

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
    topLeftItem->setModel(model);
    bottomRightItem->setModel(model);

    model->setOriginItem(originItem);
    model->setTopLeftItem(topLeftItem);
    model->setBottomRightItem(bottomRightItem);

    model->onTopLeftChanged(0., ui->lineEdit_topLeftY->text().toDouble());
    model->onBottomrightChanged(ui->lineEdit_bottomRightX->text().toDouble(), 0.);
}

void MainWindow::on_actionSave_raw_data_triggered()
{
    if(model->rowCount() > 0)
    {
        QVector<double> x = model->getXData();
        QVector<double> y = model->getYData();

        QString csvFileName = QFileDialog::getSaveFileName(this, tr("Select file name"), "", tr("CSV files (*.csv)"));

        if(!csvFileName.endsWith(".csv"))
        {
            csvFileName += ".csv";
        }

        if(!csvFileName.isEmpty())
        {
            QFile file(csvFileName);

            file.open(QFile::WriteOnly);

            QTextStream out(&file);

            int numOfLines = x.size();

            Q_ASSERT(y.size() == numOfLines);

            for(int i=0; i<numOfLines; ++i)
            {
                out << x[i] << "," << y[i] << "\n";
            }

            file.close();
        }
    }
}

void MainWindow::doCurveFit()
{
    if(!doCurveFitting) return;

    if(fcgi)
    {
        ui->graphicsView->scene()->removeItem(fcgi);
    }

    delete fcgi; fcgi = 0;

    int curveTypeIndex = ui->comboBox_curveType->currentIndex();

    LeastSquaresSolver *solver = 0;

    switch(curveTypeIndex)
    {
    case 0:
        solver = LeastSquareSolverFactory::getSolver(LeastSquareSolverFactory::PolyQuadratic);
        break;
    case 1:
        solver = LeastSquareSolverFactory::getSolver(LeastSquareSolverFactory::PolyCubic);
        break;
    case 2:
        solver = LeastSquareSolverFactory::getSolver(LeastSquareSolverFactory::Exp);
        break;
    }

    if(!solver)
    {
        qDebug() << tr("Could not create a least square solver instance.");
        return;
    }

    QVector<double> dataX = model->getXData();
    QVector<double> dataY = model->getYData();

    solver->setDataPoints(dataX, dataY);
    solver->solve();

    if(dataX.size() > 0)
    {
        currentCurveAsString = "y = " + solver->toString();
        ui->textBrowser_currentCurve->setText(currentCurveAsString);
    }

    // plot the resulting curve ###############################################

    int numOfPoints = ui->spinBox_numPointsCurve->value();

    double minX = *std::min_element(dataX.begin(), dataX.end());
    double maxX = *std::max_element(dataX.begin(), dataX.end());

    QVector<double> cdX(numOfPoints);
    QVector<double> cdY(numOfPoints);

    Q_ASSERT(numOfPoints>1);
    double deltaX = 1. / (static_cast<double>(numOfPoints)-1.) * (maxX - minX);

    double originX = ui->lineEdit_originX->text().toDouble();
    double originY = ui->lineEdit_originY->text().toDouble();
    double topLeftY = ui->lineEdit_topLeftY->text().toDouble();
    double bottomRightX = ui->lineEdit_bottomRightX->text().toDouble();
    QPointF origItemCoords = originItem->scenePos();
    QPointF tlItemCoords = topLeftItem->scenePos();
    QPointF brItemCoords = bottomRightItem->scenePos();

    for(int i=0; i<numOfPoints; ++i)
    {
        cdX[i] = minX + i*deltaX;
        cdY[i] = (*solver)(cdX[i]);

        cdX[i] = origItemCoords.x() + (cdX[i]-originX)/(bottomRightX-originX)*(brItemCoords.x()-origItemCoords.x());
        cdY[i] = origItemCoords.y() + (cdY[i]-originY)/(topLeftY-originY)*(tlItemCoords.y()-origItemCoords.y());
    }

    fcgi = new FittedCurveGraphicsItem(cdX, cdY);
    ui->graphicsView->scene()->addItem(fcgi);

    delete solver;
}

void MainWindow::saveCurveData()
{
    if(fcgi)
    {
        QPolygonF points = fcgi->getPoints();

        QString csvFileName = QFileDialog::getSaveFileName(this, tr("Select file name"), "", tr("CSV files (*.csv)"));

        if(!csvFileName.endsWith(".csv"))
        {
            csvFileName += ".csv";
        }

        if(!csvFileName.isEmpty())
        {
            QFile file(csvFileName);

            file.open(QFile::WriteOnly);

            QTextStream out(&file);

            int numOfPoints = points.size();

            double originX = ui->lineEdit_originX->text().toDouble();
            double originY = ui->lineEdit_originY->text().toDouble();
            double topLeftY = ui->lineEdit_topLeftY->text().toDouble();
            double bottomRightX = ui->lineEdit_bottomRightX->text().toDouble();
            QPointF origItemCoords = originItem->scenePos();
            QPointF tlItemCoords = topLeftItem->scenePos();
            QPointF brItemCoords = bottomRightItem->scenePos();

            out << "# curve: " << currentCurveAsString << "\n";

            for(int i=0; i<numOfPoints; ++i)
            {
                out << originX + (points[i].x()-origItemCoords.x()) / (brItemCoords.x()-origItemCoords.x()) * (bottomRightX-originX)
                    << ","
                    << originY + (points[i].y()-origItemCoords.y()) / (tlItemCoords.y()-origItemCoords.y()) * (topLeftY-originY)
                    << "\n";
            }

            file.close();
        }
    }
}

void MainWindow::on_actionAbout_triggered()
{
    QString msg = tr("<p>CurveExtractor A simple tool to extract data points from images.</p>"
                     "<p>Copyright (c) 2013, Harald Held (harald.held@gmail.com)<br>"
                     "All rights reserved.</p>"
                     "<p><a href=\"https://bitbucket.org/hheld/curveextractor\">https://bitbucket.org/hheld/curveextractor</a></p>");

    QMessageBox::about(this, tr("About CurveExtractor"), msg);
}

void MainWindow::on_groupBox_curveFitting_toggled(bool checked)
{
    if(!doCurveFitting && checked)
    {
        doCurveFitting = checked;
        doCurveFit();
    }

    if(doCurveFitting && !checked)
    {
        ui->textBrowser_currentCurve->clear();

        if(fcgi)
        {
            ui->graphicsView->scene()->removeItem(fcgi);
            delete fcgi; fcgi = 0;
        }

        doCurveFitting = checked;
    }
}
