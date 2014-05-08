#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "userpersistent.h"
#include <QDateTime>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    trayIcon(new QSystemTrayIcon(this))
{
    ui->setupUi(this);
    ui->inputText->setPlaceholderText(UserPersistent::getInstance()->getUsername() + "> ");
    QSystemTrayIcon* trayIcon = new QSystemTrayIcon(this);
    QIcon icon(":/icons/sms-call.png");
    trayIcon->setToolTip("Mini-Chat");
    trayIcon->show();
    trayIcon->setIcon(icon);
}

MainWindow::~MainWindow()
{
    if (options) {
        delete options;
    }
    delete ui;
}

void MainWindow::on_actionFermer_triggered()
{
    if (options) options->close();
    this->close();
}

void MainWindow::on_actionOptions_triggered()
{
    options = new OptionsWindow(0,ui->inputText);
    options->show();
}

void MainWindow::on_inputText_returnPressed()
{
    Message msg = Message(UserPersistent::getInstance()->getUsername(), "127.0.0.1", ui->inputText->text(), "0.0.0.0");
    this->appendMessage(msg);
    ui->inputText->clear();
}

void MainWindow::appendMessage(Message msg){
    QDateTime time = QDateTime::fromTime_t(msg.timestamp);
    ui->incomingText->append("<span style='font-weight:bold;' title='from " + msg.getSender() + " à " + time.toString() + "'>" + msg.getUsername() + "></span> " + msg.getContent());

    // Show System Tray Icon if minimized
    if (this->isMinimized()) {
        trayIcon->showMessage("Nouveau message !", msg.getUsername() + " > " + msg.getContent(), QSystemTrayIcon::Information, 151000);
    }
}
