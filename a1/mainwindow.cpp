#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "cmath"
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
    if(a<0)
    {
        return -1;
    }
    else if(a>0)
    {
        return 1;
    }
    else
        return 0;
}

void MainWindow::on_pushButton_clicked()
{
    QImage image(500,500, QImage::Format_RGB888);
    QRgb value;
    value=qRgb(0,255,0);
    float x1=(ui->x1->text().toFloat());
    float y1=(ui->y1->text().toFloat());
    float x2=(ui->x2->text().toFloat());
    float y2=(ui->y2->text().toFloat());

    int length=(abs(x2-x1)<abs(y2-y1))?(y2-y1):abs(x2-x1);
    float dx = (x2-x1)/length;
    float dy=(y2-y1)/length;
    float x=x1+.5*sign(dx);
    float y=y1+.5*sign(dy);
    int i=1;
    while(i<length)
    {
        image.setPixel(floor(x),floor(y),value);
        x=x+dx;
        y=y+dy;
        //qDebug()<<x<<" "<<y<<endl;

        i++;
    }
    ui->l->setPixmap(QPixmap::fromImage(image));
}
void bresenhams(float x1,float y1,float x2,float y2,QImage& image)
{
    QRgb value;
    value=qRgb(0,255,0);
    float x=x1;
    float y=y1;
    float dx=abs(x2-x1);
    float dy=abs(y2-y1);
    int s1=sign(x2-x1);
    int s2=sign(y2-y1);
    int interchange;
    if(dy>dx)
    {
        float temp=dx;
        dx=dy;
        dy=temp;
        interchange=1;
    }
    else
    {
        interchange=0;
    }
    float e=2*dy-dx;
    for(int i=0;i<=dx;i++)
    {
        image.setPixel(x,y,value);
        while(e>=0)
        {
            if(interchange==1)
            {
                x=x+s1;
            }
            else
            {
                y=y+s2;
            }
            e=e-2*dx;
        }
        if(interchange==1)
        {
            y=y+s2;
        }
        else
        {
            x=x+s1;
        }
        e=e+2*dy;
    }
}
void MainWindow::on_pushButton_2_clicked()
{
    float x1=ui->x1->text().toFloat();
    float x2=ui->x2->text().toFloat();
    float y1=ui->y1->text().toFloat();
    float y2=ui->y2->text().toFloat();
   QImage image1(300,300,QImage::Format_RGB888);
   bresenhams(x1,y1,x2,y2,image1);
   ui->l->setPixmap(QPixmap::fromImage(image1));

}
void drawline(float x1,float y1,float x2,float y2,QImage& image)
{
    QRgb value;
    value=qRgb(0,255,0);
    int length=(abs(x2-x1)<abs(y2-y1))?abs(y2-y1):abs(x2-x1);
    float dx = (x2-x1)/length;
    float dy=(y2-y1)/length;
    float x=x1+.5*sign(dx);
    float y=y1+.5*sign(dy);
    int i=1;
    while(i<length)
    {
        image.setPixel(floor(x),floor(y),value);
        x=x+dx;
        y=y+dy;
        //qDebug()<<x<<" "<<y<<endl;
        i++;
    }
}
void MainWindow::on_pushButton_3_clicked()
{
    float x1=ui->length->text().toFloat();
    float y1=ui->breadth->text().toFloat();
    QImage image1(300,300,QImage::Format_RGB888);

    drawline(0,0,x1,0,image1);
    drawline(0,0,0,y1,image1);
    drawline(0,y1,x1,y1,image1);
    drawline(x1,0,x1,y1,image1);
    drawline(0,y1/2,x1/2,0,image1);
    drawline(x1/2,0,x1,y1/2,image1);
    drawline(x1,y1/2,x1/2,y1,image1);
    drawline(x1/2,y1,0,y1/2,image1);
    drawline(x1/4,y1/4,3*x1/4,y1/4,image1);
    drawline(x1/4,y1/4,x1/4,3*y1/4,image1);
    drawline(x1/4,3*y1/4,3*x1/4,3*y1/4,image1);
    drawline(3*x1/4,y1/4,3*x1/4,3*y1/4,image1);
   // qDebug()<<x1<<y1;
    QRgb value;
    value=qRgb(0,255,0);
    image1.setPixel(x1,y1,value);




    ui->l->setPixmap(QPixmap::fromImage(image1));
}
