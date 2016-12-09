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

#ifndef MESSENGER_H
#define MESSENGER_H

#include <QtCore>
#include <QtNetwork>
#include <QObject>
#include <QString>
#include "peer.h"

class Messenger : public QObject
{
    Q_OBJECT
public:
    typedef QList<Peer> PeerList;

    explicit Messenger(QObject *parent = 0);
    QString Name();
    QString ID();
    PeerList& getPeers();
    PeerList& getRoomPeers(QString room);
    void sendPM(QString text, QString to);
    void sendRoom(QString text, QString room);
    void joinRoom(QString room);
    void leaveRoom(QString room);
    
signals:
    void peersUpdated();
    void roomListUpdated(QString room, QString message);
    void receivedPM(QString from, QString text);
    void receivedRoom(QString room, QString from, QString text);
    
public slots:
    void setName(QString name);
    void start();

private slots:
    void onTimerdiscovery();
    void onReadyRead();


private:

	const QString PCK_HEADER {"288:0:"};
	static constexpr quint16 port = 2880;
    Peer _mypeer;
    PeerList _peers;
    QUdpSocket _udp;
    QTimer _timerdiscovery;
    QList<QHostAddress> _myips;
    QList<QString> _rooms;
    QMap<QString, PeerList> _roomslist;
    void log(const QString &data, const QString &dest, const bool isSent);
    void logSent(const QString &data, const QHostAddress &dest);
    void logReceived(const QString &data, const QHostAddress &dest);
    void processTheDatagram(const QByteArray &data, const QHostAddress &sender);
    void roomList(const QString &room);
};

#endif // MESSENGER_H
