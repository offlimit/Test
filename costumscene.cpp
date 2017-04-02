#include "costumscene.h"


CostumScene::CostumScene()
{
    m_curentObject=nullptr;
    m_mousePresButton=false;
    connect(&m_timerPaint,SIGNAL(timeout()),SLOT(slotPaintFunc()));
    connect(&m_timerPaint,SIGNAL(timeout()),SLOT(slotPresKey()));

    m_up=m_down=m_left=m_right=m_space=false;
    m_keySpeed=2;

}

CostumScene::~CostumScene()
{
    delete  m_curentObject;

}

void CostumScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(event->button()==Qt::LeftButton)
    {
        m_mousePresButton=true;
        m_timerPaint.start(10);
    }


    //Удаление объекта по правому щелчку
    if(event->button()==Qt::RightButton)

    {
        QGraphicsItem *temp=Collides(m_curentObject);
        if(temp)
            removeItem(temp);
        else if(m_curentObject)
        {
            delete m_curentObject;
            m_curentObject=nullptr;
        }
        else
        {
            QList<QGraphicsItem *>item=items(event->scenePos());
            if(!item.empty())
                removeItem(item[0]);
        }


    }



}

void CostumScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    m_mousePresButton=false;
    m_timerPaint.stop();
    Q_UNUSED(event);

}

void CostumScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if(m_curentObject)
    {

        m_curentObject->setPos(event->scenePos());


       emit InfoCoord("x: "+QString::number(m_curentObject->scenePos().x())+"\ny: "+QString::number(m_curentObject->scenePos().y()));
    }
}

QGraphicsItem* CostumScene::Collides(QGraphicsItem * item)

{

    QList<QGraphicsItem *> collisions = collidingItems(item);//возвращаем  список елементов с
    // которым столкнулся объект

    foreach (QGraphicsItem * it, collisions)
    {

        if (it == item||it ==m_curentObject)
            continue;

        return it;

    }
    return NULL;

}

void CostumScene::SaveXMLFunc()
{
    bool saccesfull=false;
    QFile *file=new QFile("C:/ProjectQT/MapRedactor/Image/map1.xml");


        if(!file->open(QIODevice::WriteOnly|QIODevice::Text))
        {
          qDebug()<<"Eror!"<<endl;
          emit InfoCoord("Error Cannot \nopen file ");
        }
        else
        {
           qDebug()<<"File created!"<<endl;
           saccesfull=true;

        }


    QXmlStreamWriter stream(file);

    stream.setAutoFormatting(true);
    stream.writeStartDocument();
    stream.writeStartElement("map1");

    QList<QGraphicsItem *>ListItems;
    ListItems=items();

    foreach (QGraphicsItem *item, ListItems)
    {
        Block* block= dynamic_cast<Block*> (item);

        stream.writeStartElement("Block");
        //stream.writeAttribute("id","1");

        //позиция на сцене
        stream.writeTextElement("coord_inScene.X",QString::number(item->scenePos().x()));
        stream.writeTextElement("coord_inScene.Y",QString::number(item->scenePos().y()));

        //позиция блока в своей системе
        stream.writeTextElement("coord_inItem.X",QString::number(block->getCoordBlock().x()));
        stream.writeTextElement("coord_inItem.Y",QString::number(block->getCoordBlock().y()));

        //размеры блока
        stream.writeTextElement("Size.width",QString::number(block->getSizeBlock().width()));
        stream.writeTextElement("Size.height",QString::number(block->getSizeBlock().height()));

        //Тип блока
        stream.writeTextElement("Type_Block",item->data(0).toString());

        stream.writeEndElement();

    }


    stream.writeEndElement();
    stream.writeEndDocument();


    file->close();
    if(saccesfull)
    {
        qDebug()<<"File save"<<endl;
        emit InfoCoord("File save ");
    }




}

void CostumScene::slotPaintFunc()
{

    if(m_mousePresButton||m_space)

    {
        if(m_curentObject)
        {

            Block* tempObject=new Block();  //временный
            *tempObject=*m_curentObject; //копирование текущего обьекта

            if( m_curentObject->data(0)=="Brick")
            {
                tempObject->setData(0,"Brick");
                tempObject->setPos(m_curentObject->scenePos());

            }
            else if(m_curentObject->data(0)=="QuadBrick")
            {
                tempObject->setData(0,"Brick");
                tempObject->setPos(m_curentObject->scenePos());



                QVector<Block *>temp;
                for(int i=0;i<3;i++)
                    temp.push_back(new Block(Block::QUADBRICK));


                temp[0]->setPos(tempObject->scenePos().x()+SIZE_BLOCK,
                                tempObject->scenePos().y());
                temp[0]->setData(0,"Brick");

                temp[1]->setPos(tempObject->scenePos().x(),
                                tempObject->scenePos().y()+SIZE_BLOCK);
                temp[1]->setData(0,"Brick");

                temp[2]->setPos(tempObject->scenePos().x()+SIZE_BLOCK,
                                tempObject->scenePos().y()+SIZE_BLOCK);
                temp[2]->setData(0,"Brick");

                for(int i=0;i<3;i++)
                    addItem(temp[i]);
//усли один из 4 елементов сталкиваются уничтожаются все
                    for(int i=0;i<3;i++)
                        if(Collides(temp[i]))
                        {
                            for(int j=0;j<3;j++)
                            {
                                removeItem(temp[j]);
                            }
                            removeItem(tempObject);
                            return ;
                        }
                }


            else if(m_curentObject->data(0)=="Armored")
            {
                tempObject->setData(0,"Armored");
                tempObject->setPos(m_curentObject->scenePos());
            }
            else if(m_curentObject->data(0)=="Net")
            {
                tempObject->setData(0,"Net");
                tempObject->setPos(m_curentObject->scenePos());
            }
            else if(m_curentObject->data(0)=="Shtab")
            {
                tempObject->setData(0,"Shtab");
                tempObject->setPos(m_curentObject->scenePos());
            }

            addItem(tempObject);

            //проверка сталкивается текущий объект с уже нарисовваным
            if(Collides(tempObject))
            {
                removeItem(tempObject);
            }

        }
    }
}

void CostumScene::slotButtonClicked()
{
    QString str = ( (QPushButton*)sender())->text ( ) ;

    if(str=="Brick")
    {

        if(m_curentObject)
            delete m_curentObject;
        m_curentObject=new Block(Block::BRICK);
        m_curentObject->setData(0,"Brick");
        addItem(m_curentObject);
        m_curentObject->setPos(0,0);

    }
    else if(str=="Armored")
    {
        if(m_curentObject)
            delete m_curentObject;
        m_curentObject=new Block(Block::ARMORED);
        m_curentObject->setData(0,"Armored");
        addItem(m_curentObject);
        m_curentObject->setPos(0,0);
    }
    else  if(str=="Net")
    {
        if(m_curentObject)
            delete m_curentObject;
        m_curentObject=new Block(Block::NET);
        m_curentObject->setData(0,"Net");
        addItem(m_curentObject);
        m_curentObject->setPos(0,0);
    }
    else if(str=="QUAD brick")
    {
        if(m_curentObject)
            delete m_curentObject;
        m_curentObject=new Block(Block::QUADBRICK);
        m_curentObject->setData(0,"QuadBrick");
        addItem(m_curentObject);
        m_curentObject->setPos(0,0);
    }
    else if(str=="Save")
    {
        SaveXMLFunc();
    }
    else if(str=="EXIT")
    {
        exit(0);
    }
    else if(str=="Shtab")
    {
        if(m_curentObject)
            delete m_curentObject;
        m_curentObject=new Block(Block::SHTAB);
        m_curentObject->setData(0,"Shtab");
        addItem(m_curentObject);
        m_curentObject->setPos(0,0);
    }

}

void CostumScene::slotPresKey()
{
    if(m_curentObject)
    {
        emit InfoCoord("x: "+QString::number(m_curentObject->scenePos().x())+"\ny: "+QString::number(m_curentObject->scenePos().y()));
        if(m_up)
            m_curentObject->setY(m_curentObject->y()-m_keySpeed);
        else  if(m_down)
            m_curentObject->setY(m_curentObject->y()+m_keySpeed);
        else if(m_left)
            m_curentObject->setX(m_curentObject->x()-m_keySpeed);
        else if(m_right)
            m_curentObject->setX(m_curentObject->x()+m_keySpeed);
        if(m_space)
        {
            m_timerPaint.start(10);
             slotPaintFunc();
             m_keySpeed=4;
        }
    }
}

void CostumScene::keyPressEvent(QKeyEvent *event)
{

    switch (event->key())
    {
    case (Qt::Key_Down):
        {
            m_down=true;
            m_timerPaint.start(20);
         }
        break;

    case Qt::Key_Up:
        {
           m_up=true;
           m_timerPaint.start(20);
        }
        break;
    case Qt::Key_Left:
        {

           m_left=true;
           m_timerPaint.start(20);
        }
        break;
    case Qt::Key_Right:
        {

          m_right=true;
          m_timerPaint.start(20);
        }
        break;

   case Qt::Key_Space:
    {

          m_space=true;
          m_timerPaint.start(20);

    }
         break;
    case Qt::Key_Escape:
        exit(0);
        break;
    default:
        break;
    }


}

void CostumScene::keyReleaseEvent(QKeyEvent *event)
{

   switch (event->key())
   {
   case (Qt::Key_Down):
       {
           m_down=false;
           m_timerPaint.stop();
       }
       break;

   case Qt::Key_Up:
       {
           m_up=false;
            m_timerPaint.stop();
        }
       break;
   case Qt::Key_Left:
       {
           m_left=false;
            m_timerPaint.stop();
       }
       break;
   case Qt::Key_Right:
       {
           m_right=false;
            m_timerPaint.stop();
       }
       break;

  case Qt::Key_Space:
   {
       m_space=false;
       m_keySpeed=2;
       m_timerPaint.stop();

   }
        break;
   default:
     break;
   }
}
