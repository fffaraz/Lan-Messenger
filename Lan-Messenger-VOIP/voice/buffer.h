#ifndef BUFFER_H
#define BUFFER_H

#include <QObject>
#include <QByteArray>

class Buffer : public QObject
{
    Q_OBJECT
public:
    explicit Buffer(quint16 size, QObject *parent = 0);
    
signals:
    void output(QByteArray data);
    
public slots:
    void input(QByteArray data);

private:
    QByteArray buffer;
    quint16 size;
};

#endif // BUFFER_H
