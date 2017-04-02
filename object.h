#ifndef OBJECT_H
#define OBJECT_H

#include <QGraphicsObject>
#include <QPainter>
#include <QPushButton>

#define POSITION_BLOCK -15
#define SIZE_BLOCK 30

class Block:public QGraphicsObject
{
    Q_OBJECT
public:
    enum state {BRICK,ARMORED, QUADBRICK,NET,SHTAB};
private:

    state m_mode;
    QSize m_size;
    QPoint m_topLeft;
    QPixmap m_pix;

public:
    Block(state mode=BRICK);
    Block(const Block& block);
    Block operator=(const Block& block);
    void setSizeAndPos(QPoint& pos,QSize& size);
    const QSize& getSizeBlock()const {return m_size;}
    const QPoint& getCoordBlock()const {return m_topLeft;}


    // QGraphicsItem interface
public:
    QRectF boundingRect() const;
    QPainterPath shape() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

#endif // OBJECT_H
