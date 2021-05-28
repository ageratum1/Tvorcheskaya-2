#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
 int length [7][7];
//62
 bool *checked=new bool [7];
 int min_path=1000;
 int *min_way=new int [10];
 int min_kol;
 int way[10];
 int startTown=0;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect (ui->pushButton_start, &QPushButton::clicked, this, &MainWindow::on_pushButton_start_clicked);
    for (int i=0;i<7;i++)
    {
        for (int j=0;j<7;j++)
        {
            length[i][j]=0;
        }
    }
    length[1][6]=21;
    length[1][5]=2;
    length[1][2]=34;
    length[1][3]=8;

    length[6][1]=21;
    length[6][5]=13;

    length[5][1]=2;
    length[5][6]=13;
    length[5][4]=3;
    length[5][2]=5;

    length[4][5]=3;
    length[4][2]=45;

    length[2][5]=5;
    length[2][4]=45;
    length[2][1]=34;
    length[2][3]=57;

    length[3][1]=8;
    length[3][2]=57;

    for (int i=1;i<7;i++)
    {
        checked[i]=false;
    }
    for (int i=0;i<10;i++)
    {
        min_way[i]=0;
        way[i]=0;
    }
    QPixmap pix("C:/Users/User/Documents/Komivaejor/graf.png");
    int w=ui->graf->width();
    int h=ui->graf->height();
    ui->graf->setPixmap(pix.scaled(w, h, Qt::KeepAspectRatio));
}

MainWindow::~MainWindow()
{
    delete ui;
    delete [] checked;
    delete [] min_way;
}

void find_path(int n,int path,int kol)
{

    checked[n]=true;
    kol++;
    way[kol]=n;
    length[0][1]=0;

    path+=length[way[kol-1]][n];

    for (int i=1;i<=6;i++)
    {
        if ((length[n][i]!=0) and(checked[i]==false))
        {
            find_path(i,path,kol);
        }
    }
    int x=0;
    for (int i=1;i<7;i++)
    {
        if (checked[i]==true) x++;
    }

    if (x==6 && length[n][startTown]!=0)
    {
        path+=length[n][startTown];
        kol++;
        way[kol]=startTown;



        if (path<=min_path)
        {

            min_path=path;
            min_kol=kol;
            int i=1;
            while (way[i]!=0)
            {
                min_way[i]=way[i];
                i++;
            }

        }

    }
    checked[n]=false;
    way[kol]=0;
    kol--;

}

void MainWindow::on_pushButton_start_clicked()
{
    ui->label_way->setText("");
    ui->label_path->setText("");
    if (ui->lineEdit->text()=="")
    {
        ui->label_way->setText("Error");
        ui->label_path->setText("Error");
    }
    else
    {

        startTown=(ui->lineEdit->text()).toInt();
        if (startTown>6 or startTown<1)
        {
          ui->label_way->setText("Error");
          ui->label_path->setText("Error");
        }
        else
        {
            checked[startTown]=true;
            find_path(startTown,0,0);
            int i=1;
            ui->label_path->setText(QString::number(min_path));
            while (min_way[i]!=0)
            {
                ui->label_way->setText(ui->label_way->text()+QString::number(min_way[i]));
                i++;
            }
        }
    }
}
