#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<math.h>
#include<QMouseEvent>
#include<QColorDialog>
QColor c;
QImage image(800,450,QImage::Format_RGB888);
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ver=0;
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::dda(int x1,int y1,int x2,int y2)
{
    float len,dx,dy,x,y;
    len=(abs(x2-x1)>abs(y2-y1))?abs(x2-x1):abs(y2-y1);
    dx=(x2-x1)/len;
    dy=(y2-y1)/len;
    x=x1+0.5f;
    y=y1+0.5f;
    int i=1;
    while(i<len)
    {
        image.setPixel(static_cast<int>(x),static_cast<int>(y),c.rgb());
        x=x+dx;
        y=y+dy;
       i++;
    }
    ui->label->setPixmap(QPixmap::fromImage(image));
}

void MainWindow::mousePressEvent(QMouseEvent *ev)
{
    int p,q;
    p=ev->pos().x();
    q=ev->pos().y();
    a[ver]=p;
    b[ver]=q;
    ver++;
    if(ver%2==0)
    {
        cohensutherland(a[ver-1],b[ver-1],a[ver-2],b[ver-2]);
    }
}

void MainWindow::on_pushButton_clicked()
{
    dda(100,350,600,350);
    dda(100,350,100,150);
    dda(100,150,600,150);
    dda(600,350,600,150);
}

void MainWindow::on_pushButton_2_clicked()
{
    c=QColorDialog::getColor();
}
void MainWindow::cohensutherland(int x1,int y1,int x2,int y2)
{
    int code1,code2;
    code1=computecode(x1,y1);
    code2=computecode(x2,y2);
    bool accept=false;
    while(true)
    {
        if(code1==0 && code2==0)
        {
            //both endpts inside
            accept=true;
            break;
        }
        if(code1 && code2)
        {
            //completely outside
            break;
        }
        else
        {
            int codeout;
            double x,y;
            if(code1!=0)
            {
                codeout=code1;
            }
            else
            {
                codeout=code2;
            }
            if(codeout & top)
            {
                //above
                x=x1+(x2-x1)*(Ymax-y1)/(y2-y1);
                y=Ymax;
            }
            else if(codeout & bottom)
            {
                x=x1+(x2-x1)*(Ymin-y1)/(y2-y1);
                y=Ymin;
            }
            else if(codeout & right)
            {
                x=Xmax;
                y=y1+(y2-y1)*(Xmax-x1)/(x2-x1);
            }
            else if(codeout & left)
            {
                x=Xmin;
                y=y1+(y2-y1)*(Xmin-x1)/(x2-x1);
            }
            if(codeout==code1)
            {
                x1=x;
                y1=y;
                code1=computecode(x1,y1);
            }
            else if(codeout==code2)
            {
                x2=x;
                y2=y;
                code2=computecode(x2,y2);
            }
        }
    }
    if(accept)
    {
        dda(x1,y1,x2,y2);
    }
}

int MainWindow::computecode(int x, int y)
{
    int code=in;
    if(x<Xmin)
    {
        code|=left;
    }
    else if(x>Xmax)
    {
        code|=right;
    }
    if(y<Ymin)
    {
        code|=bottom;
    }
    else if(y>Ymax)
    {
        code|=top;
    }
    return code;
}
