#include "dialogroom.h"
#include "ui_dialogroom.h"

DialogRoom::DialogRoom(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogRoom)
{
    ui->setupUi(this);
}

DialogRoom::~DialogRoom()
{
    delete ui;
}

void DialogRoom::on_btnJoin_clicked()
{
    emit joinRoom(ui->txtRoom->text());
    this->deleteLater();
}
