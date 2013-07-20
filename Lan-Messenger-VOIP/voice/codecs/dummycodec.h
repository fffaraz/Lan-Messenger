#ifndef DUMMYCODEC_H
#define DUMMYCODEC_H

#include "voice/codec.h"

class DummyCodec : public Codec
{
public:
    DummyCodec();
    virtual QByteArray encode(QByteArray &src);
    virtual QByteArray decode(QByteArray &src);
};

#endif // DUMMYCODEC_H
