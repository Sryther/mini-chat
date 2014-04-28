#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "userpersistent.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->inputText->setPlaceholderText(UserPersistent::getInstance()->getUsername() + "> ");
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
    options = new OptionsWindow(0,ui->inputText);
    options->show();
}

void MainWindow::on_inputText_returnPressed()
{
    Message msg = Message(UserPersistent::getInstance()->getUsername(), "0.0.0.0", ui->inputText->text(), "0.0.0.0");
    this->appendMessage(msg);
    ui->inputText->clear();
}

void MainWindow::appendMessage(Message msg){
    ui->incomingText->appendPlainText(msg.getUsername() + " >> " + msg.getContent());
}
