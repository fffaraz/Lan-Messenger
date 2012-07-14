#include "dialognickname.h"
#include "ui_dialognickname.h"

DialogNickName::DialogNickName(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogNickName)
{
    ui->setupUi(this);
}

DialogNickName::~DialogNickName()
{
    delete ui;
}

void DialogNickName::on_btnOk_clicked()
{
    emit setName(ui->txtName->text());
    this->deleteLater();
}
