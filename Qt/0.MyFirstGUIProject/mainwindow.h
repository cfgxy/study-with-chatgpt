//
// Created by cfgxy on 2023/6/28.
//

#ifndef UNTITLED11_MAINWINDOW_H
#define UNTITLED11_MAINWINDOW_H

#include <QMainWindow>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

    ~MainWindow() override;

private:
    Ui::MainWindow *ui;

signals:
    void mySignal();

private slots:
    void on_btnTime1_clicked();
    void on_btnTime2_clicked();
    void on_btnHello_clicked();
    void on_MainWindow_mySignal();
};


#endif //UNTITLED11_MAINWINDOW_H
