#include "about_form.h"
#include "ui_about_form.h"

About_Form::About_Form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::About_Form)
{
    ui->setupUi(this);
}

About_Form::~About_Form()
{
    delete ui;
}

void About_Form::on_pushButton_clicked()
{
    this->close();
}
