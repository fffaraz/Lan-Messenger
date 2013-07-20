#ifndef CODEC_H
#define CODEC_H

#include <QByteArray>

class Codec
{
public:
    Codec();
    virtual QByteArray encode(QByteArray &src) = 0;
    virtual QByteArray decode(QByteArray &src) = 0;
};

#endif // CODEC_H
