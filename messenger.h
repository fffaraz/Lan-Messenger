#ifndef MESSENGER_H
#define MESSENGER_H

#include <QtCore>
#include <QtNetwork>
#include <QObject>
#include "peer.h"


#define PCK_HEADER "288:0:"
typedef QList<Peer> PeerList;

class Messenger : public QObject
{
    Q_OBJECT
public:
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
    Peer _mypeer;
    PeerList _peers;
    QUdpSocket _udp;
    QTimer _timerdiscovery;
    QList<QHostAddress> _myips;
    QList<QString> _rooms;
    QMap<QString, PeerList> _roomslist;
    void log(QString data, QString dest, bool isSent);
    void logSent(QString data, QHostAddress dest);
    void logReceived(QString data, QHostAddress dest);
    void processTheDatagram(QByteArray data, QHostAddress sender);
    void roomList(QString room);
};

#endif // MESSENGER_H
