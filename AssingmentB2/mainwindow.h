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
    bool start;
    int a[20],b[20];
    int ver=0;
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    int sign(float);
    void dda(float x1,float y1,float x2,float y2);
    void mousePressEvent(QMouseEvent *ev);
    void mouseDoubleClickEvent(QMouseEvent *ev);
    void seedfill(int,int,QRgb,QRgb);
private slots:
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
