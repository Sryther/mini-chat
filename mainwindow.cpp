#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionFermer_triggered()
{
    this->close();
}

void MainWindow::on_actionOptions_triggered()
{
    options = new OptionsWindow();
    options->show();
}

void MainWindow::on_inputText_returnPressed()
{
    ui->incomingText->appendPlainText(ui->inputText->text());
    ui->inputText->clear();
}
