#include "optionswindow.h"
#include "ui_optionswindow.h"
#include "user.h"

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
