#include "voicesocket.h"

VoiceSocket::VoiceSocket(QObject *parent) :
    QObject(parent)
{
    isEnabled = false;
    connect(&udp, SIGNAL(readyRead()), this, SLOT(udp_readyRead()));
}

void VoiceSocket::connectToHost(QHostAddress ip, quint16 port)
{
    peer_ip = ip;
    peer_port = port;
}

void VoiceSocket::startListen(quint16 port)
{
    udp.bind(QHostAddress::Any, port);
}

void VoiceSocket::writeData(QByteArray data)
{
    if(!isEnabled) return;
    QByteArray data2 = qCompress(data, 9);
    //qDebug() << "Sent  " << peer_ip;
    //qDebug() << "Sent1 " << data.length();
    //qDebug() << "Sent2 " << data2.length();
    udp.writeDatagram(data2, peer_ip, peer_port);
}

void VoiceSocket::udp_readyRead()
{
    int size = udp.pendingDatagramSize();
    QHostAddress host;
    quint16 port;
    QByteArray data;
    data.resize(size);
    udp.readDatagram(data.data(), size, &host, &port);
    //qDebug() << "Recd  " << host;
    if(!isEnabled) return;
    if(host != peer_ip) return;
    QByteArray data2 = qUncompress(data);
    //qDebug() << "Recd1 " << data.length();
    //qDebug() << "Recd2 " << data2.length();
    emit readData(data2);
}

void VoiceSocket::setEnabled(bool val)
{
    isEnabled = val;
}
