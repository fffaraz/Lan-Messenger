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
