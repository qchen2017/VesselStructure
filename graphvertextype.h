#ifndef GRAPHVERTEXTYPE_H
#define GRAPHVERTEXTYPE_H

#include "common.h"
#include "swcnodetype.h"

class GraphVertexType
{
public:
    GraphVertexType();
    uintmax_t node_level;
    SWCNodeType node;
    AdjListType AdjList;

    //Methods
    bool isRoot;
    bool isBranch;
    bool isTerminal;
    bool isIsolated;
    bool isConnecting;

    //Adjacent Branches
    AdjListType SubBranches;
};

#endif // GRAPHVERTEXTYPE_H
