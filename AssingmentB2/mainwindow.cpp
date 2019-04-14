#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QMouseEvent>
#include<math.h>
#include<QColorDialog>
QColor c;
QImage image(700,400,QImage::Format_RGB888);
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    start=true;
    ver=0;
}

MainWindow::~MainWindow()
{
    delete ui;
}
int MainWindow::sign(float x)
{
    if(x>0)
        return 1;
    return -1;
}
void MainWindow::dda(float x1,float y1,float x2,float y2)
{
    float dx,dy,l,x,y,i=1;
    l=std::abs(x2-x1)>std::abs(y2-y1)?std::abs(x2-x1):std::abs(y2-y1);
    dx=(x2-x1)/l;
     dy=(y2-y1)/l;
     x=x1+0.5f;
     y=y1+0.5f;
     while(i<l)
     {
         image.setPixel(x,y,c.rgb());
         x=x+dx;
         y=y+dy;
         i++;
     }
ui->label->setPixmap(QPixmap::fromImage(image));
}
void MainWindow::mousePressEvent(QMouseEvent *ev)
{
    if(start==true)
    {
        int p,q;
        p=ev->pos().x();
        q=ev->pos().y();
        a[ver]=p;
        b[ver]=q;
        if(ev->button()==Qt::RightButton)
        {
            dda(0,0,a[ver-1],b[ver-1]);
            start=false;
        }
        else
        {
            if(ver>0)
            dda(a[ver],b[ver],a[ver-1],b[ver-1]);
        }
        ver++;
    }
}

void MainWindow::on_pushButton_clicked()
{
    c=QColorDialog::getColor();

}

void MainWindow::mouseDoubleClickEvent(QMouseEvent *ev)
{
    int p,q;
    p=ev->pos().x();
    q=ev->pos().y();
    QRgb old=qRgb(0,0,0);
    seedfill(p,q,old,c.rgb());
    ui->label->setPixmap(QPixmap::fromImage(image));
    ver--;
}
void MainWindow::seedfill(int x,int y,QRgb old,QRgb fill)
{
    QRgb curr=image.pixel(x,y);
    if(curr==old)
    {
        image.setPixel(x,y,fill);
        seedfill(x,y+1,old,fill);
        seedfill(x,y-1,old,fill);
        seedfill(x+1,y,old,fill);
        seedfill(x-1,y,old,fill);
    }
}
