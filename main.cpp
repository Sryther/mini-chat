#include "mainwindow.h"
#include "application.h"
#include "message.h"
#include <QApplication>
#include <QMessageBox>
#include <QString>
#include <QStringList>
#include <iostream>
#include <QDir>

int main(int argc, char *argv[]) {
        Application a(argc, argv);
        MainWindow w;
        w.show();
        return a.exec();
}
