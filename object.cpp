#include "object.h"


Block::Block(state mode)
{
    m_mode=mode;
    m_topLeft={POSITION_BLOCK,POSITION_BLOCK};
    m_size={SIZE_BLOCK,SIZE_BLOCK};

    switch (mode)
    {
    case BRICK:
    {
        m_pix.load(":/Image/Brick2.png");

    }
        break;
    case QUADBRICK:
    {
        m_pix.load(":/Image/Brick2.png");
         }
      break;
    case ARMORED:
    {
         m_pix.load(":/Image/Armored3.png");

    }
      break;
    case NET:
    {
        m_pix.load(":/Image/Net.png");
        m_topLeft={-30,-30};
        m_size={60,60};
        setOpacity(0.5);
    }
      break;
    case SHTAB:
    {
        m_pix.load(":/Image/Pig.png");
        m_topLeft={-60,-60};
        m_size={120,120};
    }
    default:
        break;
    }
}

Block::Block(const Block &block)
{
    m_mode=block.m_mode;
    m_size=block.m_size;
    m_topLeft=block.m_topLeft;
    m_pix=block.m_pix;
}

Block Block::operator=(const Block &block)
{
    m_mode=block.m_mode;
    m_size=block.m_size;
    m_topLeft=block.m_topLeft;
    m_pix=block.m_pix;
    return *this;
}

void Block::setSizeAndPos(QPoint& pos, QSize& size)
{
    m_size=size;
    m_topLeft=pos;
}



QRectF Block::boundingRect() const
{
    return QRectF(m_topLeft.x(),m_topLeft.y(),m_size.height(),m_size.width());
}

QPainterPath Block::shape() const
{
    QPainterPath path;
    path.addRect(boundingRect());

   return path;
}

void Block::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(Qt::red);
   // painter->drawRect(m_topLeft.x(),m_topLeft.y(),m_size.height(),m_size.width());
    painter->drawPixmap(m_topLeft.x(),m_topLeft.y(),m_size.height(),m_size.width(),m_pix);
    Q_UNUSED(option);
    Q_UNUSED(widget);
}

