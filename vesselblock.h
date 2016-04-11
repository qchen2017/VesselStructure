#ifndef VESSELBLOCK_H
#define VESSELBLOCK_H

#include "common.h"
#include "graphvertextype.h"

typedef QMap<unsigned long long,GraphVertexType> GraphType;
class VesselBlock
{
public:
    VesselBlock();
    QVector<GraphType> VesselTrees;
};

#endif // VESSELBLOCK_H
