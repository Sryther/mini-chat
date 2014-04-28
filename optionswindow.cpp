#include "optionswindow.h"
#include "ui_optionswindow.h"
#include "userpersistent.h"


OptionsWindow::OptionsWindow(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::OptionsWindow)
{
    ui->setupUi(this);
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
}

void OptionsWindow::on_usernameField_textChanged(const QString &arg1) {
    UserPersistent::getInstance()->setUsername(ui->usernameField->text());
}

void OptionsWindow::on_portField_textChanged(const QString &arg1) {
    UserPersistent::getInstance()->setPort(ui->portField->text().toInt());
}
