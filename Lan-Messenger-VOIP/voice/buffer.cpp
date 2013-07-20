#include "buffer.h"

Buffer::Buffer(quint16 size, QObject *parent) :
    QObject(parent)
{
    this->size = size;
}

void Buffer::input(QByteArray data)
{
    buffer.append(data);
    if(buffer.length() >= size)
    {
        emit output(buffer);
        buffer.clear();
    }
}
