#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "userpersistent.h"
#include <QDateTime>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->inputText->setPlaceholderText(UserPersistent::getInstance()->getUsername() + "> ");
    QIcon icon(":/icons/sms-call.png");
    trayIcon = new QSystemTrayIcon(this);
    trayIcon->setToolTip("Mini-Chat");
    trayIcon->setIcon(icon);
    trayIcon->show();
}

MainWindow::~MainWindow()
{
    if (options) delete options;
    delete trayIcon;
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
    if (ui->inputText->text() == "") return;
    Message msg = Message(UserPersistent::getInstance()->getUsername(), "127.0.0.1", ui->inputText->text(), "0.0.0.0");
    this->appendMessage(msg);
    ui->inputText->clear();
}

void MainWindow::appendMessage(Message msg){
    QDateTime time = QDateTime::fromTime_t(msg.timestamp);
    ui->incomingText->append("<span style='font-weight:bold;' title='from " + msg.getSender() + " at " + time.toString("hh'h'mm:ss") + "'>" + msg.getUsername() + "></span> " + msg.getContent());

    // Show System Tray Icon if minimized
    if (this->isMinimized()) {
        trayIcon->showMessage(msg.getUsername(), msg.getContent(), QSystemTrayIcon::Information, 151000);
    }
}
