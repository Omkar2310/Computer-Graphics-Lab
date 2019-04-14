#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "math.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}
int sign(float a)
{
    if(a>0)
    {
        return 1;
    }
    else if(a<0)
    {
        return -1;
    }
    else
    {
        return 0;
    }
}
void MainWindow::dda(float x1,float y1,float x2,float y2)
{
    QImage image(300,300, QImage::Format_RGB888);
    float len;
    if(abs(x2-x1)>abs(y2-y1))
    len=abs(x2-x1);
    else
        len=abs(y2-y1);
    float dx,dy;
    dx=(x2-x1)/len;
    dy=(y2-y1)/len;
    float x,y;
    x=x1 + 0.5*sign(dx);
    y=y1 + 0.5*sign(dy);
    int i=1;
    while(i<=len)
    {
        image.setPixel(floor(x),floor(y),qRgb(0,255,0));
        x=x+dx;
        y=y+dy;
        i++;
        ui->l->setPixmap(QPixmap::fromImage(image));
    }
}

void MainWindow::on_pushButton_clicked()
{
    float x1,y1,x2,y2;
    x1=ui->l1->text().toFloat();
    y1=ui->l2->text().toFloat();
    x2=ui->l3->text().toFloat();
    y2=ui->l4->text().toFloat();
    dda(x1,y1,x2,y2);
    float x3,y3;
    x3=(x1+x2)/2;
    y3=(y1+y2)/2;
    dda(x1,y1,x3,(y3+sqrt(3)*(x3-x1)));
   dda(x2,y2,x3,(y3+sqrt(3)*(x3-x1)));
}

void MainWindow::on_pushButton_2_clicked()
{
    ui->l->clear();
}
