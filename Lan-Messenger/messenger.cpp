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

#include "messenger.h"

Messenger::Messenger(QObject *parent) :
    QObject(parent)
{
    connect(&_timerdiscovery, SIGNAL(timeout()), this, SLOT(onTimerdiscovery()));
    connect(&_udp, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
    _myips = QNetworkInterface::allAddresses();
    //qDebug() << _myips;
}

void Messenger::start()
{
    _udp.bind(2880, QUdpSocket::ReuseAddressHint);
    _timerdiscovery.start(5000);
}

void Messenger::setName(QString name)
{
    _mypeer.Name = name;
    _mypeer.Domain = QHostInfo::localHostName();
}

QString Messenger::Name()
{
    return _mypeer.ID();
}

void Messenger::onTimerdiscovery()
{
    QString packet = PCK_HEADER "DISCOVERY:" + _mypeer.ID();
    QHostAddress target = QHostAddress::Broadcast;
    logSent(packet, target);
    _udp.writeDatagram(packet.toUtf8(), target, 2880);

    // chekc for olds
    for(int i=0; i<_peers.count(); i++)
        if(_peers[i].Lastseen.secsTo(QTime::currentTime()) > 10)
        {
            _peers.removeAt(i);
            emit peersUpdated();
        }

    // room list
    for(int i=0; i<_rooms.count(); i++)
        roomList(_rooms[i]);

    for(int i=0; i<_rooms.count(); i++)
    {
        QString room = _rooms[i];
        if(!_roomslist.contains(room)) continue;
        for(int j=0; j<_roomslist[room].count(); j++)
            if(_roomslist[room].at(j).Lastseen.secsTo(QTime::currentTime()) > 10)
            {
                QString name = _roomslist[room][j].ID();
                _roomslist[room].removeAt(j);
                emit roomListUpdated(room, "*** " + name + " Left. ***");
            }
    }
}

void Messenger::onReadyRead()
{
    while (_udp.hasPendingDatagrams())
    {
        QByteArray datagram;
        datagram.resize(_udp.pendingDatagramSize());
        QHostAddress sender;
        quint16 senderPort;

        _udp.readDatagram(datagram.data(), datagram.size(), &sender, &senderPort);

        bool flag = true;
        for(int i=0; i < _myips.count(); ++i)
            if(sender.toString() == _myips[i].toString())
                flag = false;

        if (flag)
        {
            logReceived(datagram, sender);
            processTheDatagram(datagram, sender);
        }
    }
}

void Messenger::log(QString data, QString dest, bool isSent)
{
    QString msg;
    msg += isSent? "Sent     ":"Received ";
    msg += QString::number(data.length()) + " bytes";
    msg += isSent? " to   ":" from ";
    QString fill;
    fill.fill(' ', 15 - dest.size());
    msg += dest + fill + "  Data: ";
    msg += data;
    qDebug() << msg.toStdString().c_str();
    return;
}

void Messenger::logSent(QString data, QHostAddress dest)
{
    return log(data, dest.toString(), true);
}

void Messenger::logReceived(QString data, QHostAddress dest)
{
    return log(data, dest.toString(), false);
}

PeerList& Messenger::getPeers()
{
    return _peers;
}

PeerList& Messenger::getRoomPeers(QString room)
{
    return _roomslist[room];
}

void Messenger::processTheDatagram(QByteArray data, QHostAddress sender)
{
    QString str_packet = QString(data);
    QStringList packet = str_packet.split(':');
    if(packet.count()<4)
    {
        qWarning("Warning: Unknown Packet. ");
        return;
    }
    if(packet[0] != "288")
    {
        qWarning("Warning: Protocol Mismatch. ");
        return;
    }
    if(packet[1] != "0")
    {
        qWarning("Warning: Protocol Version Mismatch. ");
        return;
    }
    if(packet[2] == "DISCOVERY")
    {
        int found = -1;
        for(int i=0; i<_peers.count(); i++)
            if(_peers[i].ID() == packet[3]) found = i;
        if(found == -1)
        {
            Peer newpeer;
            QString peerid = packet[3];
            QStringList peerids = peerid.split('@');
            if(peerids.count() != 2)
            {
                qWarning("Warning: Wronge new Peer ID.");
                return;
            }
            newpeer.Name = peerids[0];
            newpeer.Domain = peerids[1];
            newpeer.Host = sender;
            newpeer.Lastseen = QTime::currentTime();
            _peers.append(newpeer);
            emit peersUpdated();
        }
        else
        {
            _peers[found].Lastseen = QTime::currentTime();
        }
    }

    if(packet[2] == "ROOMLIST")
    {
        QString room = packet[3];
        if(!_rooms.contains(room)) return;
        if(!_roomslist.contains(room))
            _roomslist.insert(room, PeerList());

        int found = -1;
        for(int i=0; i<_roomslist[room].count(); i++)
            if(_roomslist[room][i].ID() == packet[4]) found = i;

        if(found == -1)
        {
            Peer newpeer;
            QString peerid = packet[4];
            QStringList peerids = peerid.split('@');
            if(peerids.count() != 2)
            {
                qWarning("Warning: Wronge new Peer ID.");
                return;
            }
            newpeer.Name = peerids[0];
            newpeer.Domain = peerids[1];
            newpeer.Host = sender;
            newpeer.Lastseen = QTime::currentTime();
            _roomslist[room].append(newpeer);
            emit roomListUpdated(room, "***  " + newpeer.ID() + "  Joined. ***");
        }
        else
        {
            _roomslist[room][found].Lastseen = QTime::currentTime();
        }
    }


    if(packet[2] == "PM")
    {
        QString from = packet[3];
        QString text = packet[4];
        for(int i=5; i<packet.count(); i++)
            text += ":" + packet[i];
        emit receivedPM(from, text);
    }
    if(packet[2] == "ROOM")
    {
        QString room = packet[3];
        QString from = packet[4];
        QString text = packet[5];
        for(int i=6; i<packet.count(); i++)
            text += ":" + packet[i];

        bool found=false;
        for(int i=0;i<_rooms.count(); i++)
            if(_rooms[i] == room) found = true;

        if(found)
            emit receivedRoom(room, from, text);
    }
}

void Messenger::sendPM(QString text, QString to)
{
    QHostAddress adr;
    for(int i=0; i<_peers.count(); i++)
    {
        if(_peers[i].ID() == to)
            adr = _peers[i].Host;
    }
    QString packet = PCK_HEADER "PM:" + _mypeer.ID() + ":" + text;
    logSent(packet, adr);
    _udp.writeDatagram(packet.toUtf8(), adr, 2880);
}

void Messenger::sendRoom(QString text, QString room)
{
    QString packet = PCK_HEADER "ROOM:" + room + ":" + _mypeer.ID() + ":" + text;
    QHostAddress target = QHostAddress::Broadcast;
    logSent(packet, target);
    _udp.writeDatagram(packet.toUtf8(), target, 2880);
}

void Messenger::joinRoom(QString room)
{
    _rooms.append(room);
}

void Messenger::leaveRoom(QString room)
{
    _rooms.removeAll(room);
}

void Messenger::roomList(QString room)
{
    QString packet = PCK_HEADER "ROOMLIST:" + room + ":" + _mypeer.ID();
    QHostAddress target = QHostAddress::Broadcast;
    logSent(packet, target);
    _udp.writeDatagram(packet.toUtf8(), target, 2880);
}

