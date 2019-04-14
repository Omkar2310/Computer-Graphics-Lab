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
void MainWindow::dda(float x1,float y1,float x2,float y2,QImage image)
{
    QRgb value;
    value=qRgb(0,255,0);
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
        i++;
    }
    ui->l->setPixmap(QPixmap::fromImage(image));
}

void MainWindow::on_pushButton_clicked()
{
    QImage image(500,500, QImage::Format_RGB888);
    float x1=(ui->x1->text().toFloat());
    float y1=(ui->y1->text().toFloat());
    float x2=(ui->x2->text().toFloat());
    float y2=(ui->y2->text().toFloat());
    dda(x1,y1,x2,y2,image);

}

void MainWindow::on_pushButton_7_clicked()
{
    ui->l->clear();
}

void MainWindow::on_pushButton_2_clicked()
{
    //dashed
    QImage image(500,500, QImage::Format_RGB888);
    float x1=(ui->x1->text().toFloat());
    float y1=(ui->y1->text().toFloat());
    float x2=(ui->x2->text().toFloat());
    float y2=(ui->y2->text().toFloat());
    QRgb value;
    value=qRgb(0,255,0);
    int length=(abs(x2-x1)<abs(y2-y1))?(y2-y1):abs(x2-x1);
    float dx = (x2-x1)/length;
    float dy=(y2-y1)/length;
    float x=x1+.5*sign(dx);
    float y=y1+.5*sign(dy);
    int i=1;
    int cnt=10;
    while(i<length)
    {
        if(cnt!=0)
        {
        image.setPixel(floor(x),floor(y),value);
        x=x+dx;
        y=y+dy;
        i++;
        cnt--;
        }
        else
        {
            image.setPixel(floor(x),floor(y),qRgb(0,0,0));
            cnt=10;
            i++;
            x=x+dx;
            y=y+dy;

        }

    }
    ui->l->setPixmap(QPixmap::fromImage(image));
}

void MainWindow::on_pushButton_4_clicked()
{
    //dotted
    QImage image(500,500, QImage::Format_RGB888);
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
    //float len=sqrt(pow(x2-x1,2) + pow(y2-y1,2));
    int cnt=0;
    while(i<length)
    {
        if(cnt!=0)
        {
        image.setPixel(floor(x),floor(y),qRgb(0,0,0));
        x=x+dx;
        y=y+dy;
        i++;
        cnt--;
        }
        else
        {
            image.setPixel(floor(x),floor(y),qRgb(0,255,0));
            cnt=3;
            i++;
            x=x+dx;
            y=y+dy;

        }

    }
    ui->l->setPixmap(QPixmap::fromImage(image));
}

void MainWindow::on_pushButton_5_clicked()
{
    //dassheddot
    QImage image(500,500, QImage::Format_RGB888);
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
    int cnt=5;
    while(i<length)
    {
        if(cnt!=0)
        {
        image.setPixel(floor(x),floor(y),qRgb(0,255,0));
        x=x+dx;
        y=y+dy;
        i++;
        cnt--;
        }
        else
        {
            for(int j=0;j<7;j++)
            {
                if(j%4==0)
                {
                image.setPixel(floor(x),floor(y),qRgb(0,255,0));
                i++;
                x=x+dx;
                y=y+dy;
                cnt=5;
                }
                  else
                {
                    i++;
                    x=x+dx;
                    y=y+dy;
                }
            }

        }
         cnt=5;
    }
    ui->l->setPixmap(QPixmap::fromImage(image));
}
