#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "userpersistent.h"
#include "server.h"
#include <QDateTime>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    this->setAttribute(Qt::WA_QuitOnClose);
    ui->setupUi(this);
    ui->inputText->setPlaceholderText(UserPersistent::getUsername() + "> ");

    // SystemTray Icon
    QIcon icon(":/icons/sms-call.png");
    trayIcon = new QSystemTrayIcon(this);
    trayIcon->setToolTip("Mini-Chat");
    trayIcon->setIcon(icon);
    trayIcon->show();

    options = new OptionsWindow(0,ui->inputText);

    Message msg = Message(UserPersistent::getUsername(), UserPersistent::getColor(),
                          "127.0.0.1", "*connecté*", "255.255.255.255");
    Server::create(this);
    Server::sendMessage(msg);
}

MainWindow::~MainWindow()
{
    Message msg = Message(UserPersistent::getUsername(), UserPersistent::getColor(),
                          "127.0.0.1", "*déconnecté*", "255.255.255.255");
    Server::sendMessage(msg);
    UserPersistent::delInstance();
    Server::delInstance();
    if (options) delete options;
    options = nullptr;
    if (trayIcon) delete trayIcon;
    trayIcon = nullptr;
    if (ui) delete ui;
    ui = nullptr;
}

void MainWindow::on_actionFermer_triggered()
{
    this->close();
}

void MainWindow::on_actionOptions_triggered()
{
    options->updateFields();
    options->show();
}

void MainWindow::on_inputText_returnPressed()
{
    if (ui->inputText->text() == "") return;
    Message msg = Message(UserPersistent::getUsername(), UserPersistent::getColor(),
                          "127.0.0.1", ui->inputText->text(), "255.255.255.255");
//    this->appendMessage(msg);
    Server::sendMessage(msg);
    ui->inputText->clear();
}

void MainWindow::appendMessage(Message msg){
    QDateTime time = QDateTime::fromTime_t(msg.getTimestamp());
    ui->incomingText->append("<span style='font-weight:bold; color:" + msg.getColor() +
                             "' title='from " +
                             msg.getSender() + " at " + time.toString("hh'h'mm:ss") + "'>" +
                             msg.getUsername() + "></span> " + msg.getContent());

    // Show System Tray Icon if minimized
    if (this->isMinimized()) {
        trayIcon->showMessage(msg.getUsername(), msg.getContent(), QSystemTrayIcon::Information, 151000);
    }
}
