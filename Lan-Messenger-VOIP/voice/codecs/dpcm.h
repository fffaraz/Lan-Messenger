#ifndef DPCM_H
#define DPCM_H

#include "voice/codec.h"

class DPCM : public Codec
{
public:
    DPCM();
    virtual QByteArray encode(QByteArray &src);
    virtual QByteArray decode(QByteArray &src);
};

#endif // DPCM_H
