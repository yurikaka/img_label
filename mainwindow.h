#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#define LEN 15712

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QImage>
#include <QLineEdit>
#include <QPainter>
#include <QPen>
#include <QMessageBox>
#include <bits/stdc++.h>

using namespace std;

class MainWindow : public QMainWindow
{
    Q_OBJECT

    QLabel* lab;
    QImage* img;
    QLineEdit* cur;
    QPushButton *last, *next, *go;
    int num;
    unordered_map<int,QString> name;
    unordered_map<string,int> id;
    unordered_map<int,vector<vector<int>>> mp;
    unordered_map<int,vector<vector<int>>> mp2;

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void show_img();

public slots:
    void on_clicked_next();
    void on_clicked_last();
    void on_clicked_go();
};

#endif // MAINWINDOW_H
