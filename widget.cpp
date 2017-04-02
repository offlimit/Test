#include "widget.h"
#include "ui_widget.h"
#include <QKeyEvent>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    //установка размеров окна и граф представления
    setWindowState( Qt::WindowFullScreen);

    ui->graphicsView->resize(this->width(),this-> height());

    //создание сцены
    costumScene.setSceneRect(0,0,ui->graphicsView->width(),ui->graphicsView->height());

    //установка сцены в представление

    ui->graphicsView->setScene(&costumScene);


    ui->graphicsView->setRenderHint(QPainter::Antialiasing);					/// Устанавливаем сглаживание

    ui->graphicsView->setBackgroundBrush(QColor(100,100,16));
    ui->graphicsView->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);

    //подключение кнопок к сцене
    connect(ui->Armored,SIGNAL(clicked()),&costumScene,SLOT(slotButtonClicked()));
    connect(ui->brick,SIGNAL(clicked()),&costumScene,SLOT(slotButtonClicked()));
    connect(ui->net,SIGNAL(clicked()),&costumScene,SLOT(slotButtonClicked()));
    connect(ui->Quad,SIGNAL(clicked()),&costumScene,SLOT(slotButtonClicked()));
    connect(ui->Shtab,SIGNAL(clicked()),&costumScene,SLOT(slotButtonClicked()));
    connect(ui->save,SIGNAL(clicked()),&costumScene,SLOT(slotButtonClicked()));
    connect(ui->save_exit,SIGNAL(clicked()),&costumScene,SLOT(slotButtonClicked()));


// установка иконок на кнопки
    ui->brick->setIcon(QIcon(QPixmap("C:/ProjectQT/MapRedactor/Image/Brick2.png")));
    ui->brick->setIconSize(QSize(50,50));
    ui->Quad->setIcon(QIcon(QPixmap("C:/ProjectQT/MapRedactor/Image/Brick2.png")));
    ui->Quad->setIconSize(QSize(20,20));
    ui->Armored->setIcon(QIcon(QPixmap("C:/ProjectQT/MapRedactor/Image/Armored3.png")));
    ui->Armored->setIconSize(QSize(30,30));
    ui->net->setIcon(QIcon(QPixmap("C:/ProjectQT/MapRedactor/Image/Net.png")));
    ui->net->setIconSize(QSize(30,30));
    ui->net->setIcon(QIcon(QPixmap("C:/ProjectQT/MapRedactor/Image/Net.png")));
    ui->net->setIconSize(QSize(30,30));
    ui->Shtab->setIcon(QIcon(QPixmap("C:/ProjectQT/MapRedactor/Image/Pig.png")));
    ui->Shtab->setIconSize(QSize(30,30));

    //изменение информации по координатам текущего блока
    connect(&costumScene,SIGNAL(InfoCoord(QString)),ui->label,SLOT(setText(QString)));


    //разрешение на oтслеживание курсора мыши без нажатия кнопки
    ui->graphicsView->setMouseTracking(true);

}
Widget::~Widget()
{
    delete ui;
}


void Widget::keyPressEvent(QKeyEvent *event)
{
    if(event->key()==Qt::Key_Escape)
    {
        exit(0);
    }
    QWidget::keyPressEvent(event);
}

void Widget::on_label_linkActivated(const QString &link)
{

}
