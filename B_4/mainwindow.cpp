#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtGui>
#include<math.h>

QImage image(500,500,QImage::Format_RGB888);
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    draw();
    dda(0,250,500,250);
    dda(250,0,250,500);
}
MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow:: draw()
{
    for(int i=0;i<500;i++)
    {
        for(int j=0;j<500;j++)
        {
            image.setPixel(i,j,qRgb(255,255,255));
        }
    }
}
int MainWindow::sign(float x)
{
    if(x>0)
        return 1;
    else
        return -1;
}

void MainWindow::dda(float x1,float y1,float x2,float y2)
{
    float len,dx,dy;
    if(abs(x2-x1)>abs(y2-y1))
    {
        len=abs(x2-x1);
    }
    else
    {
        len=abs(y2-y1);
    }
    dx=(x2-x1)/len;
    dy=(y2-y1)/len;
    float x,y;
    x=x1 + 0.5*sign(dx);
    y=y1 + 0.5*sign(dy);
    int i=0;
    while(i<len)
    {
        image.setPixel(x,y,qRgb(0,0,0));
        x=x+dx;
        y=y+dy;
        i++;
    }
    ui->l->setPixmap(QPixmap::fromImage(image));
}

void MainWindow::on_pushButton_clicked()
{
    dda(250+60,250-60,250+200,250-60);
    dda(250+60,250-60,250+130,250-136.28);
    dda(250+130,250-136.28,250+200,250-60);
}


void MainWindow::on_pushButton_2_clicked()
{
    float x1=60,y1=60,x2=200,y2=60,x3=130,y3=136.82;
    float a[3][3]={{x1,y1,1},{x2,y2,1},{x3,y3,1}};
    float b[3][3]={{1,0,0},{0,-1,0},{0,0,1}};
    float r[3][3]={0};
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<3;j++)
        {
            r[i][j]=0;
            for(int k=0;k<3;k++)
            {
                r[i][j]+=a[i][k]*b[k][j];
            }
        }
    }
    dda(250+r[0][0],250-r[0][1],250+r[1][0],250-r[1][1]);
    dda(250+r[0][0],250-r[0][1],250+r[2][0],250-r[2][1]);
    dda(250+r[1][0],250-r[1][1],250+r[2][0],250-r[2][1]);
}

void MainWindow::on_pushButton_3_clicked()
{
    float x1=60,y1=60,x2=200,y2=60,x3=130,y3=136.82;
    float a[3][3]={{x1,y1,1},{x2,y2,1},{x3,y3,1}};
    float b[3][3]={{-1,0,0},{0,1,0},{0,0,1}};
    float r[3][3]={0};
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<3;j++)
        {
            r[i][j]=0;
            for(int k=0;k<3;k++)
            {
                r[i][j]+=a[i][k]*b[k][j];
            }
        }
    }
    dda(250+r[0][0],250-r[0][1],250+r[1][0],250-r[1][1]);
    dda(250+r[0][0],250-r[0][1],250+r[2][0],250-r[2][1]);
    dda(250+r[1][0],250-r[1][1],250+r[2][0],250-r[2][1]);
}

void MainWindow::on_pushButton_4_clicked()
{
    float x1=60,y1=60,x2=200,y2=60,x3=130,y3=136.82;
    float a[3][3]={{x1,y1,1},{x2,y2,1},{x3,y3,1}};
    float b[3][3]={{0,1,0},{1,0,0},{0,0,1}};
    float r[3][3]={0};
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<3;j++)
        {
            r[i][j]=0;
            for(int k=0;k<3;k++)
            {
                r[i][j]+=a[i][k]*b[k][j];
            }
        }
    }
    dda(250+r[0][0],250-r[0][1],250+r[1][0],250-r[1][1]);
    dda(250+r[0][0],250-r[0][1],250+r[2][0],250-r[2][1]);
    dda(250+r[1][0],250-r[1][1],250+r[2][0],250-r[2][1]);
}

void MainWindow::on_pushButton_5_clicked()
{
    float x,y,ang;
    float x1=60,y1=60,x2=200,y2=60,x3=130,y3=136.82;
    x=ui->x->text().toFloat();
    y=ui->y->text().toFloat();
    ang=ui->ang->text().toFloat();
    ang=ang*3.14/180;
    //translate to origin
    float t1[3][3]={{cos(ang),sin(ang),0},{-sin(ang),cos(ang),0},{-x*cos(ang)+y*sin(ang)+x,-x*sin(ang)-y*cos(ang)-y,1}};
    float a[3][3]={{x1,y1,1},{x2,y2,1},{x3,y3,1}};
    float r[3][3]={0};
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<3;j++)
        {
            r[i][j]=0;
            for(int k=0;k<3;k++)
            {
                r[i][j]+=a[i][k]*t1[k][j];
            }
        }
    }
    dda(250+r[0][0],250-r[0][1],250+r[1][0],250-r[1][1]);
    dda(250+r[0][0],250-r[0][1],250+r[2][0],250-r[2][1]);
    dda(250+r[1][0],250-r[1][1],250+r[2][0],250-r[2][1]);
}
