#include "optionswindow.h"
#include "ui_optionswindow.h"
#include "userpersistent.h"
#include "mainwindow.h"


OptionsWindow::OptionsWindow(QWidget *parent, QLineEdit *placeholder) :
    QFrame(parent),
    ui(new Ui::OptionsWindow),
    usernamePlaceholder (placeholder)
{
    ui->setupUi(this);
    UserPersistent::getInstance()->loadPersistent();
    updateFields();
}

OptionsWindow::~OptionsWindow()
{
    delete ui;
}

void OptionsWindow::updateFields() {
    ui->usernameField->setText(UserPersistent::getInstance()->getUsername());
    ui->portField->setText(QString::number(UserPersistent::getInstance()->getPort()));
}

void OptionsWindow::on_loadButton_clicked() {
    UserPersistent::getInstance()->loadPersistent();
    updateFields();
}

void OptionsWindow::on_saveButton_clicked() {
    UserPersistent::getInstance()->savePersistent();
    this->close();
    usernamePlaceholder->setPlaceholderText(UserPersistent::getInstance()->getUsername() + "> ");
}

void OptionsWindow::on_usernameField_textChanged(const QString &arg1) {
    UserPersistent::getInstance()->setUsername(ui->usernameField->text());
}

void OptionsWindow::on_portField_textChanged(const QString &arg1) {
    UserPersistent::getInstance()->setPort(ui->portField->text().toInt());
}
