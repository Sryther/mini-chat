#include "mainwindow.h"
#include "application.h"
#include "message.h"
#include <QApplication>
#include <QMessageBox>
#include <QString>
#include <QStringList>
#include <iostream>

int main(int argc, char *argv[]) try
{
        Application a(argc, argv);
        MainWindow w;
        w.show();
        return a.exec();
} catch (std::exception &e) {
    QMessageBox box;
    box.setText(e.what());
    box.show();
}
