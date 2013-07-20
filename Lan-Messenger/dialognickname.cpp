// Lan Messenger
// Copyright (C) 2012 Faraz Fallahi <fffaraz@gmail.com>
// 
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Affero General Public License as
// published by the Free Software Foundation, either version 3 of the
// License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Affero General Public License for more details.
//
// You should have received a copy of the GNU Affero General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
// 

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
