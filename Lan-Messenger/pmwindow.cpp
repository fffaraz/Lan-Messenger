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

#include "pmwindow.h"
#include "ui_pmwindow.h"

PMWindow::PMWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PMWindow)
{
    ui->setupUi(this);
    ui->txtInput->setFocus();
}

PMWindow::~PMWindow()
{
    delete ui;
}

void PMWindow::on_btnSend_clicked()
{
    emit enteredText(ui->txtInput->text());
    ui->txtChat->append("Me: " + ui->txtInput->text());
    ui->txtInput->clear();
    ui->txtInput->setFocus();
}

void PMWindow::receivedPM(QString text)
{
    ui->txtChat->append(this->windowTitle() + " : " + text);
}

void PMWindow::on_txtInput_returnPressed()
{
    on_btnSend_clicked();
}

void PMWindow::closeEvent(QCloseEvent *event)
{
    emit closedWindow();
    event->accept();
    this->deleteLater();
}
