#ifndef PEER_H
#define PEER_H

#include <QtCore>
#include <QtNetwork>

class Peer
{
public:
    explicit Peer();
    QString Name;
    QString Domain;
    QHostAddress Host;
    QTime Lastseen;
    QString ID();
    
};

#endif // PEER_H
