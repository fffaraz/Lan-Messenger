#include "dummycodec.h"

DummyCodec::DummyCodec()
{
}

QByteArray DummyCodec::encode(QByteArray &src)
{
    return src;
}

QByteArray DummyCodec::decode(QByteArray &src)
{
    return src;
}
