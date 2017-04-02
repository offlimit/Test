#ifndef COSTUMSCENE_H
#define COSTUMSCENE_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsSceneEvent>
#include <QKeyEvent>
#include <QTimer>
#include <QXmlStreamWriter>
#include <QFile>
#include <QDebug>

#include "object.h"


class CostumScene : public QGraphicsScene
{
    Q_OBJECT
private:

    Block * m_curentObject;
    bool m_mousePresButton;
    QTimer m_timerPaint;
    bool  m_up,m_down,m_left,m_right,m_space;
    int m_keySpeed;



public:
    CostumScene();
    ~CostumScene();
    QGraphicsItem* CostumScene::Collides(QGraphicsItem * item);
    void SaveXMLFunc();



protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);

signals:
    void InfoCoord( const QString & );

public slots:

    void slotButtonClicked();
    void slotPresKey();
    void slotPaintFunc();



};

#endif // COSTUMSCENE_H
