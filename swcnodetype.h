#ifndef ADJNODETYPE_H
#define ADJNODETYPE_H

#include "common.h"

class SWCNodeType
{
public:
    SWCNodeType();
    //unsigned long long node_id;
    unsigned int type;
    double x;
    double y;
    double z;
    double r;
    unsigned long long pnum; //parent node num
};

//Important Note: Call QDeleteAll(adjlist.begin(),adjlist.end()) to delete memory.
//Probable cause of a Memory leak in near future... *Sigh*
typedef QVector<SWCNodeType*> AdjListType;//Pointers to child nodes

#endif // ADJNODETYPE_H
