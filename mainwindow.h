#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "optionswindow.h"
#include "message.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void appendMessage(Message msg);

private slots:
    void on_actionFermer_triggered();

    void on_actionOptions_triggered();

    void on_inputText_returnPressed();

private:
    Ui::MainWindow *ui;

    OptionsWindow *options;
};

#endif // MAINWINDOW_H
