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

OptionsWindow::OptionsWindow(QWidget *parent, QLineEdit *placeholder) :
    QFrame(parent),
    ui(new Ui::OptionsWindow),
    usernamePlaceholder (placeholder)
{
    ui->setupUi(this);
    if (! UserPersistent::hasInstance()) UserPersistent::getInstance()->loadPersistent();
    updateFields();
}

OptionsWindow::~OptionsWindow()
{
    usernamePlaceholder = nullptr;
    delete ui;
}

void OptionsWindow::updateFields() {
    ui->usernameField->setText(UserPersistent::getInstance()->getUsername());
    ui->portField->setText(QString::number(UserPersistent::getInstance()->getPort()));
    ui->label_3->setStyleSheet("QLabel { background-color : "+ UserPersistent::getInstance()->getColor() +"; }");
}

void OptionsWindow::on_loadButton_clicked() {
    UserPersistent::getInstance()->loadPersistent();
    updateFields();
}

void OptionsWindow::on_saveButton_clicked() {
    if (UserPersistent::getInstance()->getUsername().length() == 0)
        throw std::ios_base::failure("Username cannot be empty");
    if(UserPersistent::getInstance()->getPort() > 65565 ||
            UserPersistent::getInstance()->getPort() < 1024)
        throw std::ios_base::failure("Port must be between 1024 and 65565");
    UserPersistent::getInstance()->savePersistent();
    usernamePlaceholder->setPlaceholderText(UserPersistent::getInstance()->getUsername() + ">");
    if (Server::hasInstance()) Server::getInstance(NULL)->changePort(UserPersistent::getInstance()->getPort());
    this->close();
}

void OptionsWindow::on_usernameField_textChanged(const QString &arg1) {
    UserPersistent::getInstance()->setUsername(ui->usernameField->text());
}

void OptionsWindow::on_portField_textChanged(const QString &arg1) {
    UserPersistent::getInstance()->setPort(ui->portField->text().toInt());
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
    QColor color = QColorDialog::getColor(UserPersistent::getInstance()->getColor(), this);

    UserPersistent::getInstance()->setColor(convertColor(color));
    updateFields();
}


