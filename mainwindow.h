#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "optionswindow.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionFermer_triggered();

    void on_actionOptions_triggered();

private:
    Ui::MainWindow *ui;

    OptionsWindow *options;
};

#endif // MAINWINDOW_H
