#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    int a[20],b[20],ver=0;
    bool start;
    void dda(int x1,int y1,int x2,int y2);
    void mousePressEvent(QMouseEvent *ev);
    void cohensutherland(int x1,int y1,int x2,int y2);
    int computecode(int,int);
    const int in=0;
    const int left=1;
    const int right=2;
    const int top=8;
    const int bottom=4;
   int  Xmin=100;
   int  Xmax=600;
   int  Ymin=150;
   int  Ymax=350;
private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
