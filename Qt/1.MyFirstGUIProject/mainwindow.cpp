//
// Created by cfgxy on 2023/6/28.
//

// You may need to build the project (run Qt uic code generator) to get "ui_MainWindow.h" resolved

#include "mainwindow.h"
#include "ui_MainWindow.h"
#include <QTime>


MainWindow::MainWindow(QWidget *parent) :
        QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_btnTime1_clicked() {
    emit mySignal();
}

void MainWindow::on_btnTime2_clicked() {
    emit mySignal();
}

void MainWindow::on_btnHello_clicked() {
    ui->label->setText("Hello World!");
}

void MainWindow::on_MainWindow_mySignal() {
    ui->label->setText(QTime::currentTime().toString());
}
