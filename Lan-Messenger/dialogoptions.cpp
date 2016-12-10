#include "dialogoptions.hpp"
#include "ui_dialogoptions.h"

DialogOptions::DialogOptions(QWidget *parent) :
    QTabWidget(parent),
    ui(new Ui::DialogOptions)
{
    ui->setupUi(this);
}

DialogOptions::~DialogOptions()
{
    delete ui;
}
