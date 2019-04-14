#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "math.h"
QImage image(700,700,QImage::Format_RGB888);

int sign(float a)
{
   if(a<0)
   {
       return(-1);
   }
   else if(a>0)
   {
       return(1);
   }
   else
   {
       return 0;
   }
}
void bresenhams(float x1,float y1,float x2,float y2)
{
   QRgb value;
   value=qRgb(255,255,255);
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
void seedfill(int x,int y,QRgb old,QRgb col)
{
    if(x<=0||x>=700||y>=700||y<=0)
    {
        return;
    }
    QRgb curr=image.pixel(x,y);
   if(curr==old)
   {

        image.setPixel(x,y,col);
        seedfill(x,y+1,old,col);
        seedfill(x-1,y,old,col);
        seedfill(x,y-1,old,col);
        seedfill(x+1,y,old,col);
    }
}
void draw()
{
    bresenhams(100,200,300,200);
    bresenhams(100,200,100,400);
    bresenhams(300,200,300,400);
    bresenhams(100,400,300,400);

    bresenhams(150,200,150,400);
    bresenhams(200,200,200,400);
    bresenhams(250,200,250,400);
    bresenhams(300,200,300,400);

    bresenhams(100,250,300,250);
    bresenhams(100,300,300,300);
    bresenhams(100,350,300,350);

    QRgb old=qRgb(0,0,0);
    QRgb new1=qRgb(255,255,255);

   //    image.setPixel(75,225,qRgb(255,255,255));
   seedfill(175,225,old,new1);
   seedfill(275,225,old,new1);
   seedfill(125,275,old,new1);
   seedfill(225,275,old,new1);

   seedfill(175,325,old,new1);
   seedfill(275,325,old,new1);
   seedfill(125,375,old,new1);
   seedfill(225,375,old,new1);

}
int* rotate(int x1,int y1)
{
    float theta=3.14/4;
    int *c1=new int [2];
    int newx,newy,x,y;
    x=x1-350;
    y=350-y1;
    newx=x*cos(theta)  - y*sin(theta);
    newy=y*cos(theta)  + x*sin(theta);
    c1[0]=newx +350;
    c1[1]=-newy + 350;
    return (c1);
}
void MainWindow::on_pushButton_clicked()
{
    for(int i=0;i<700;i++)
    {
        for(int j=0;j<700;j++)
        {
            image.setPixel(i,j,qRgb(0,0,0));
        }
    }
    int *newa=new int[2];
    int *newb=new int[2];
    newa=rotate(100,200);
    newb=rotate(300,200);
    bresenhams(newa[0],newa[1],newb[0],newb[1]);

    newb=rotate(100,400);
    bresenhams(newa[0],newa[1],newb[0],newb[1]);

    newa=rotate(300,200);
    newb=rotate(300,400);
    bresenhams(newa[0],newa[1],newb[0],newb[1]);

    newa=rotate(100,400);
    bresenhams(newa[0],newa[1],newb[0],newb[1]);
//inner lines
    newa=rotate(150,200);
    newb=rotate(150,400);
    bresenhams(newa[0],newa[1],newb[0],newb[1]);


    newa=rotate(200,200);
    newb=rotate(200,400);
    bresenhams(newa[0],newa[1],newb[0],newb[1]);

    newa=rotate(250,200);
    newb=rotate(250,400);
    bresenhams(newa[0],newa[1],newb[0],newb[1]);

    newa=rotate(300,200);
    newb=rotate(300,400);
    bresenhams(newa[0],newa[1],newb[0],newb[1]);

    newa=rotate(100,250);
    newb=rotate(300,250);
    bresenhams(newa[0],newa[1],newb[0],newb[1]);

    newa=rotate(100,300);
    newb=rotate(300,300);
    bresenhams(newa[0],newa[1],newb[0],newb[1]);


    newa=rotate(100,350);
    newb=rotate(300,350);
    bresenhams(newa[0],newa[1],newb[0],newb[1]);


    QRgb old=qRgb(0,0,0);
    QRgb new1=qRgb(255,255,255);

    newa=rotate(175,225);
    newb=rotate(275,225);
    seedfill(newa[0],newa[1],old,new1);
    seedfill(newb[0],newb[1],old,new1);

    newa=rotate(125,275);
    newb=rotate(225,275);
    seedfill(newa[0],newa[1],old,new1);
    seedfill(newb[0],newb[1],old,new1);

      newa=rotate(175,325);
      newb=rotate(275,325);
      seedfill(newa[0],newa[1],old,new1);
      seedfill(newb[0],newb[1],old,new1);

      newa=rotate(125,375);
      newb=rotate(225,375);
      seedfill(newa[0],newa[1],old,new1);
      seedfill(newb[0],newb[1],old,new1);


    ui->label->setPixmap(QPixmap::fromImage(image));
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    draw();
    ui->label->setPixmap(QPixmap::fromImage(image));

}

MainWindow::~MainWindow()
{
    delete ui;
}

