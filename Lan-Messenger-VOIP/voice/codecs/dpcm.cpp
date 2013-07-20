#include "dpcm.h"

DPCM::DPCM()
{
}

QByteArray DPCM::encode(QByteArray &src)
{
    const char *srcd = src.data();
    quint16 last = *((int*)srcd);

    QByteArray dest;
    dest.append(srcd, 2);

    for(int i=2; i<src.length(); i+=2)
    {
        quint16 current = *((int*)(srcd+i));
        qint8 diff = current - last;
        dest.append((char*)(&diff), 1);
    }

    return dest;
}

QByteArray DPCM::decode(QByteArray &src)
{
    const char *srcd = src.data();
    QByteArray dest;
    dest.append(srcd, 2);

    // TO DO

    return dest;
}
