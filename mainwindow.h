#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtCore>
#include <QMainWindow>
#include <QLineEdit>
#include "peer.h"
#include "dialognickname.h"
#include "messenger.h"
#include "pmwindow.h"
#include "roomwindow.h"
#include "dialogroom.h"
#include "dialogabout.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void onSetName(QString name);
    void onUpdateList();
    void onRoomListUpdated(QString room, QString msg);
    void onPMSend(QString text);
    void onPMClosed();
    void onRoomSend(QString text);
    void onRoomClosed();
    void onRoomPM(QString id);
    void on_listUsers_doubleClicked(const QModelIndex &index);
    void onReceivedPM(QString from, QString text);
    void onReceivedRoom(QString room, QString from, QString text);
    void onJoinRoom(QString room);
    void onMenu(QAction* action);

private:
    Ui::MainWindow *ui;
    Messenger* msgr;
    QMap<QString, PMWindow*> pms;
    QMap<PMWindow*, QString> pmr;
    QMap<QString, RoomWindow*> rms;
    QMap<RoomWindow*, QString> rmr;
    PMWindow* makePMWindow(QString title);
    RoomWindow* makeRoomWindow(QString title);
};

#endif // MAINWINDOW_H
