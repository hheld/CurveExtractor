#ifndef CEGRAPHICSVIEW_H
#define CEGRAPHICSVIEW_H

#include <QGraphicsView>

class CEGraphicsScene;

class CEGraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit CEGraphicsView(QWidget *parent = 0);
    ~CEGraphicsView();
    
    void setBackgroundImage(const QString &img);
    void fitBgImgInView();

signals:
    
public slots:
    
private:
    CEGraphicsScene *theScene;
    QString backgroundImgPath;
    QPixmap bgPixmap;

    void drawBackground(QPainter *painter, const QRectF &rect);

    void wheelEvent(QWheelEvent *event);
};

#endif // CEGRAPHICSVIEW_H
