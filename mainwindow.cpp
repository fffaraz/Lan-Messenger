#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    msgr = new Messenger(this);
    DialogNickName *dlgName = new DialogNickName(this);
    connect(dlgName, SIGNAL(setName(QString)), this, SLOT(onSetName(QString)));
    connect(msgr, SIGNAL(peersUpdated()), this , SLOT(onUpdateList()));
    connect(msgr, SIGNAL(roomListUpdated(QString,QString)), this, SLOT(onRoomListUpdated(QString,QString)));
    connect(msgr, SIGNAL(receivedPM(QString,QString)), this, SLOT(onReceivedPM(QString,QString)));
    connect(msgr, SIGNAL(receivedRoom(QString,QString,QString)), this, SLOT(onReceivedRoom(QString,QString,QString)));
    dlgName->setModal(true);
    dlgName->setWindowTitle("You Nickname, Please");
    dlgName->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onSetName(QString name)
{
    msgr->setName(name);
    ui->lblWelcome->setText("Welcome " + msgr->Name());
    msgr->start();
}

void MainWindow::onUpdateList()
{
    ui->listUsers->clear();
    QList<Peer>& peers = msgr->getPeers();
    for(int i=0; i<peers.count(); i++)
        ui->listUsers->addItem(peers[i].ID());
}

void MainWindow::onRoomListUpdated(QString room, QString msg)
{
    QList<QString> ids;
    QList<Peer>& peers = msgr->getRoomPeers(room);
    for(int i=0; i<peers.count(); i++)
        ids.append(peers[i].ID());
    makeRoomWindow(room)->updateList(ids);
    makeRoomWindow(room)->receivedPM("", msg);
}


void MainWindow::on_listUsers_doubleClicked(const QModelIndex &index)
{
    QString userid = ui->listUsers->currentItem()->text();
    makePMWindow(userid);
}

PMWindow* MainWindow::makePMWindow(QString title)
{
    if(pms.keys().contains(title))
    {
        pms[title]->setFocus();
        return pms[title];
    }
    else
    {
        PMWindow* newpm = new PMWindow();
        pms.insert(title, newpm);
        pmr.insert(newpm, title);
        connect(newpm, SIGNAL(enteredText(QString)), this, SLOT(onPMSend(QString)));
        connect(newpm, SIGNAL(closedWindow()), this, SLOT(onPMClosed()));
        newpm->setWindowTitle(title);
        newpm->show();
        return newpm;
    }
}

RoomWindow* MainWindow::makeRoomWindow(QString title)
{
    if(rms.keys().contains(title))
    {
        rms[title]->setFocus();
        return rms[title];
    }
    else
    {
        RoomWindow* newrm = new RoomWindow();
        rms.insert(title, newrm);
        rmr.insert(newrm, title);
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
    msgr->sendPM(text, pmr[to]);
}

void MainWindow::onRoomSend(QString text)
{
    RoomWindow* room = qobject_cast<RoomWindow*>(sender());
    msgr->sendRoom(text, rmr[room]);
}

void MainWindow::onRoomClosed()
{
    RoomWindow* window = qobject_cast<RoomWindow*>(sender());
    msgr->leaveRoom(rmr[window]);
    rms.remove(rmr[window]);
    rmr.remove(window);
}

void MainWindow::onPMClosed()
{
    PMWindow* window = qobject_cast<PMWindow*>(sender());
    //msgr->sendPM("Closed chat window.", pmr[window]);
    pms.remove(pmr[window]);
    pmr.remove(window);
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
    if(action->text()=="About")
    {
        DialogAbout* about = new DialogAbout(this);
        about->setModal(true);
        about->setWindowTitle("About 288 L.M.");
        about->show();
    }
}

void MainWindow::onJoinRoom(QString room)
{
    makeRoomWindow(room)->setFocus();
    msgr->joinRoom(room);
}
