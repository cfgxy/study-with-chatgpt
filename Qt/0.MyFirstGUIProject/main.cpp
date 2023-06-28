#include <QApplication>
#include <QPushButton>
#include "mainwindow.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    MainWindow win;
    win.setFixedSize(306, 239);
    win.setWindowFlags(
            Qt::WindowCloseButtonHint
    );
    win.show();


    return QApplication::exec();
}
