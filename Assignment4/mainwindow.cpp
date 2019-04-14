
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMouseEvent>
#include <math.h>
#include<QDebug>
static QImage img(400,400,QImage::Format_RGB888);
static int a[10],b[10], ver=0,sx,sy;
static bool start;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    start = false;
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::dda(int x1,int y1,int x2,int y2)
{

    float x,y,dx,dy,l,i=1;
    QRgb value;
    value=qRgb(0,255,0);

    l=std::abs(x2-x1)>std::abs(y2-y1)?std::abs(x2-x1):std::abs(y2-y1);
    dx=(x2-x1)/l;
    dy=(y2-y1)/l;

    x=x1+0.5f;
    y=y1+0.5f;
    do
    {
       img.setPixel(static_cast<int>(x),static_cast<int>(y),value);
       x = x + dx;
       y = y + dy;
       i++;
      }while(i <= l);


ui->label->setPixmap(QPixmap::fromImage(img));

}
void MainWindow::mousePressEvent(QMouseEvent *ev)
{

    if(start==true)
    {
    int p=ev->pos().x();
    int q=ev->pos().y();
    qDebug()<<p<<'\t'<<q;

     if(ev->button()==Qt::RightButton)
     {
         a[ver]=p;
         b[ver]=q;
         dda(sx,sy,a[ver],b[ver]);
         dda(a[ver-1],b[ver-1],a[ver],b[ver]);
         start=false;
     }
     else {
         a[ver]=p;
         b[ver]=q;
         if(ver>0)
         {
             dda(a[ver],b[ver],a[ver-1],b[ver-1]);
         }else{
             sx=p;
             sy=q;
             dda(sx,sy,sx,sy);

         }

     }
     ver++;
    }
  }

void MainWindow::on_pushButton_clicked()
{
    start=true;
}

void MainWindow::mouseDoubleClickEvent(QMouseEvent *ev)
{
    int p=ev->pos().x();
     int q=ev->pos().y();
     //qDebug()<<p<<" "<<q;
     QRgb col=qRgb(255,0,0);
     QRgb old=qRgb(0,0,0);
     seedfill(p,q,old,col);
     ui->label->setPixmap(QPixmap::fromImage(img));
}
void MainWindow::seedfill(int x,int y,QRgb old,QRgb col)
{
     if(x<=0 || x>=400 || y<=0 || y>=400){
         return;
     }
    QRgb curr=img.pixel(x,y);

    if(curr==old)
    {
        img.setPixel(x,y,col);
        seedfill(x,y+1,old,col);
        seedfill(x-1,y,old,col);
        seedfill(x,y-1,old,col);
        seedfill(x+1,y,old,col);
    }
}

