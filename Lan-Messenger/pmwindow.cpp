// Lan Messenger
// Copyright (C) 2012 Faraz Fallahi <fffaraz@gmail.com>
// Copyright (C) 2017 Sebastian Martin Dicke <Sebastianmartindicke@gmx.de>
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

PMWindow::PMWindow(const QString &title, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PMWindow)
{
	setWindowTitle(title);
    ui->setupUi(this);
    ui->txtInput->setFocus();
	ui->txtChat->append("You chat now with " + title);
	ui->txtChat->append("Please note that this chat is unencrypted.");
	ui->txtChat->append("Anybody in your network can read all data sent in this conversation.");
	ui->txtChat->append("Have a nice time!\n");
}

PMWindow::~PMWindow()
{
    delete ui;
}

void PMWindow::on_btnSend_clicked()
{
	//Send only a message, if a text is typed to avoid spam the chat window with empty messages
	if (ui->txtInput->text() != "") {
		emit enteredText(ui->txtInput->text());
		ui->txtChat->append("Me: " + ui->txtInput->text());
		ui->txtInput->clear();
		ui->txtInput->setFocus();
	}
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
