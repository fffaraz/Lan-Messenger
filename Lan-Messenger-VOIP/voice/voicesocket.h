#ifndef VOICESOCKET_H
#define VOICESOCKET_H

#include <QObject>
#include <QUdpSocket>

class VoiceSocket : public QObject
{
    Q_OBJECT
public:
    explicit VoiceSocket(QObject *parent = 0);
    void connectToHost(QHostAddress ip, quint16 port = 30011);
    void startListen(quint16 port = 30011);
    void setEnabled(bool val);
    
signals:
    void readData(QByteArray data);
    
public slots:
    void writeData(QByteArray data);

private slots:
    void udp_readyRead();

private:
    QUdpSocket udp;
    QHostAddress peer_ip;
    quint16 peer_port;
    bool isEnabled;
};

#endif // VOICESOCKET_H
