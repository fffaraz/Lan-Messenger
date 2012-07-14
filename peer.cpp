#include "peer.h"

Peer::Peer()
{
}

QString Peer::ID()
{
    return Name + "@" + Domain;
}
