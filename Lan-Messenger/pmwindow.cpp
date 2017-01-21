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

PMWindow::PMWindow(const QString &partner, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PMWindow)
{
	QString header("<p style=\"color:#33CC33\">");
	QString footer("</p>");
	QString breaker("<br />");
    ui->setupUi(this);
    ui->txtInput->setFocus();
	ui->txtChat->append(header + "You chat now with " + partner + breaker +
					 "Please note that this chat is unencrypted." +breaker  +						"Anybody in your network can read all data sent in this		conversation." + breaker + "Have a nice time!" + breaker + footer);
	connect(ui->btnSend, SIGNAL(clicked(bool)), ui->txtInput, SLOT(setFocus()));
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
