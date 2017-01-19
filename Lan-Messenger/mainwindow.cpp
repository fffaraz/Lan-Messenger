// Lan Messenger
// Copyright (C) 2012 Faraz Fallahi <fffaraz@gmail.com>
// 
// This program is free software: you can redistribute it and/or modify
// it under the tethis->rms of the GNU Affero General Public License as
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

#include <memory>
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	this->ui->setupUi(this);
	this->msgr = new Messenger(this);
	DialogNickName *dlgName = new DialogNickName(this);
	connect(dlgName, SIGNAL(setName(QString)), this, SLOT(onSetName(QString)));
	connect(this->msgr, SIGNAL(peersUpdated()), this , SLOT(onUpdateList()));
	connect(this->msgr, SIGNAL(roomListUpdated(QString,QString)), this, SLOT(onRoomListUpdated(QString,QString)));
	connect(this->msgr, SIGNAL(receivedPM(QString,QString)), this, SLOT(onReceivedPM(QString,QString)));
	connect(this->msgr, SIGNAL(receivedRoom(QString,QString,QString)), this, SLOT(onReceivedRoom(QString,QString,QString)));
	connect(this->ui->actionAbout, SIGNAL(triggered(bool)), this, SLOT(onAbout()));
	connect(this->ui->actionOptions, SIGNAL(triggered(bool)), this, SLOT(onOptions()));
	connect(this->ui->actionExit, SIGNAL(triggered(bool)), this, SLOT(onExit()));
	dlgName->setModal(true);
	dlgName->setWindowTitle("You Nickname, Please");
	dlgName->show();
}

MainWindow::~MainWindow()
{
	delete this->ui;
	delete this->msgr;
}

void MainWindow::onSetName(QString name)
{
	this->msgr->setName(name);
	this->ui->lblWelcome->setText("Welcome " + this->msgr->Name());
	this->msgr->start();
}

void MainWindow::onUpdateList()
{
	this->ui->listUsers->clear();
	for (Peer &current : this->msgr->getPeers()) {
		this->ui->listUsers->addItem(current.ID());
	}
}

void MainWindow::onRoomListUpdated(QString room, QString msg)
{
    QList<QString> ids;
	for (Peer &current : this->msgr->getRoomPeers(room)) {
		ids.append(current.ID());
	}
    makeRoomWindow(room)->updateList(ids);
    makeRoomWindow(room)->receivedPM("", msg);
}


void MainWindow::on_listUsers_doubleClicked(const QModelIndex &index)
{
	QString userid = this->ui->listUsers->currentItem()->text();
    makePMWindow(userid);
}

PMWindow* MainWindow::makePMWindow(const QString &title)
{
	if(this->pms.keys().contains(title))
    {
		this->pms[title]->setFocus();
		return this->pms[title];
    }
    else
    {
		PMWindow* newpm = new PMWindow(title);
		this->pms.insert(title, newpm);
		this->pmr.insert(newpm, title);
		connect(newpm, SIGNAL(enteredText(QString)), this, SLOT(onMmsend(QString)));
		connect(newpm, SIGNAL(closedWindow()), this, SLOT(onPMClosed()));
		newpm->setWindowTitle(title);
		newpm->show();
		return newpm;
    }
}

RoomWindow* MainWindow::makeRoomWindow(const QString &title)
{
	if(this->rms.keys().contains(title))
    {
		this->rms[title]->setFocus();
		return this->rms[title];
    }
    else
    {
		RoomWindow* newrm = new RoomWindow();
		this->rms.insert(title, newrm);
		this->rmr.insert(newrm, title);
		connect(newrm, SIGNAL(enteredText(QString)), this, SLOT(onRoomSend(QString)));
		connect(newrm, SIGNAL(closedWindow()), this, SLOT(onRoomClosed()));
		connect(newrm, SIGNAL(startPM(QString)), this, SLOT(onRoomPM(QString)));
		newrm->setWindowTitle(title);
		newrm->show();
		return newrm;
    }
}

void MainWindow::onRoomPM(QString id)
{
    makePMWindow(id);
}

void MainWindow::onPMSend(QString text)
{
    PMWindow* to = qobject_cast<PMWindow*>(sender());
	this->msgr->sendPM(text, this->pmr[to]);
}

void MainWindow::onRoomSend(QString text)
{
    RoomWindow* room = qobject_cast<RoomWindow*>(sender());
	this->msgr->sendRoom(text, this->rmr[room]);
}

void MainWindow::onRoomClosed()
{
    RoomWindow* window = qobject_cast<RoomWindow*>(sender());
	this->msgr->leaveRoom(this->rmr[window]);
	this->rms.remove(this->rmr[window]);
	this->rmr.remove(window);
}

void MainWindow::onPMClosed()
{
    PMWindow* window = qobject_cast<PMWindow*>(sender());
	//this->msgr->sendPM("Closed chat window.", this->pmr[window]);
	this->pms.remove(this->pmr[window]);
	this->pmr.remove(window);
}

void MainWindow::onReceivedPM(QString from, QString text)
{
    makePMWindow(from)->receivedPM(text);
}

void MainWindow::onReceivedRoom(QString room, QString from, QString text)
{
    makeRoomWindow(room)->receivedPM(from, text);
}

void MainWindow::onMenu(QAction *action)
{
    if(action->text()=="Join")
    {
        DialogRoom* joinroom = new DialogRoom(this);
        connect(joinroom, SIGNAL(joinRoom(QString)), this, SLOT(onJoinRoom(QString)));
        joinroom->setModal(true);
        joinroom->setWindowTitle("Room Name");
        joinroom->show();
    }
}

void MainWindow::onAbout()
{
    DialogAbout* about = new DialogAbout(this);
    about->setModal(true);
    about->setWindowTitle("About 288 L.M.");
    about->show();
}

void MainWindow::onOptions()
{
	DialogOptions* options = new DialogOptions(this->msgr);
    options->setWindowTitle("Options");
    options->show();
}

void MainWindow::onJoinRoom(QString room)
{
    makeRoomWindow(room)->setFocus();
	this->msgr->joinRoom(room);
}


void MainWindow::onExit()
{
	exit(0);
}
