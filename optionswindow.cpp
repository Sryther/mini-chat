#include "optionswindow.h"
#include "ui_optionswindow.h"
#include "userpersistent.h"
#include "mainwindow.h"
#include <QColorDialog>
#include <QColor>
#include "server.h"
#include <exception>
#include <stdexcept>
#include <ios>
#include <QDateTime>

OptionsWindow::OptionsWindow(QWidget *parent, QLineEdit *placeholder) :
    QFrame(parent),
    ui(new Ui::OptionsWindow),
    usernamePlaceholder(placeholder)
{
    ui->setupUi(this);
    if (! UserPersistent::hasInstance()) UserPersistent::loadPersistent();
    updateFields();
}

OptionsWindow::OptionsWindow(const OptionsWindow &&other) :
    ui(other.ui),
    usernamePlaceholder(other.usernamePlaceholder)
{
    this->~OptionsWindow();
}

OptionsWindow::OptionsWindow(const OptionsWindow &other) :
    ui(other.ui),
    usernamePlaceholder(other.usernamePlaceholder)
{
}

OptionsWindow::~OptionsWindow()
{
    delete usernamePlaceholder;
    usernamePlaceholder = nullptr;
    delete ui;
    ui = nullptr;
}

void OptionsWindow::updateFields() {
    ui->usernameField->setText(UserPersistent::getUsername());
    ui->portField->setText(QString::number(UserPersistent::getPort()));
    ui->label_3->setStyleSheet("QLabel { background-color : "+ UserPersistent::getColor() +"; }");
}

void OptionsWindow::on_loadButton_clicked() {
    UserPersistent::loadPersistent();
    updateFields();
}

void OptionsWindow::on_saveButton_clicked() {
    if (ui->usernameField->text().length() == 0)
        throw std::ios_base::failure("Username cannot be empty");

    else {
        if (ui->usernameField->text() != UserPersistent::getUsername() || _newColor != UserPersistent::getColor()){
            Message nameChangedMsg = Message(UserPersistent::getUsername(), UserPersistent::getColor(),
                                             "127.0.0.1", Message::paint(UserPersistent::getUsername(), UserPersistent::getColor(),
                                                                         "from " + Message::getReplaceTag() + " at " + QDateTime::currentDateTime().toString("hh'h'mm:ss") )
                                             + " est maintenant <span style='font-weight:bold; color:" + _newColor + "'>" +
                                             ui->usernameField->text() + "</span>", "255.255.255.255");
            Server::sendMessage(nameChangedMsg, true);
            UserPersistent::setUsername(ui->usernameField->text());
            UserPersistent::setColor(_newColor);
        }
    }


    if(ui->portField->text().toInt() > 65565 ||
            ui->portField->text().toInt() < 1024)
        throw std::ios_base::failure("Port must be between 1024 and 65565");

    else {
        if (ui->portField->text().toInt() != UserPersistent::getPort()){
            Message portChangedMsg = Message(UserPersistent::getUsername(), UserPersistent::getColor(),
                                             "127.0.0.1", Message::paint(UserPersistent::getUsername(), UserPersistent::getColor(),
                                                                         "from " + Message::getReplaceTag() + " at " + QDateTime::currentDateTime().toString("hh'h'mm:ss") ) + " s'est déplacé", "255.255.255.255");
            Server::sendMessage(portChangedMsg, true);
        }
        UserPersistent::setPort(ui->portField->text().toInt());
    }


    UserPersistent::savePersistent();
    usernamePlaceholder->setPlaceholderText(UserPersistent::getUsername() + ">");
    if (Server::hasInstance()) Server::changePort();
    this->close();
}

QColor OptionsWindow::convertColor(QString color) {
    return QColor(color);
}

QString OptionsWindow::convertColor(QColor color) {
    QString red = QString::number( color.red(), 16 );
    QString green = QString::number( color.green(), 16 );
    QString blue = QString::number( color.blue(), 16 );

    if (red.length() == 1)
        red = "0" + red;
    if (green.length() == 1)
        green = "0" + green;
    if (blue.length() == 1)
        blue = "0" + blue;

    return "#" + red + green + blue;
}



void OptionsWindow::on_pushButton_clicked()
{
    QColor color = QColorDialog::getColor(UserPersistent::getColor(), this);
    _newColor = convertColor(color);
    ui->label_3->setStyleSheet("QLabel { background-color : "+ _newColor +"; }");
}


