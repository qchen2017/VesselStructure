#include "common.h"
#include "graphvertextype.h"
#include "swcnodetype.h"

//Reference: https://www.youtube.com/watch?v=zVrPdF7f4-I

typedef QMap<unsigned long long,GraphVertexType> GraphType;
typedef GraphType VesselTreeType;
bool read_swc(VesselTreeType *outTree,const QString inFileName);

int main(int argc, char *argv[])
{
    VesselTreeType VesselTree;
    read_swc(&VesselTree,"C:/Users/Shruthi/Desktop/test_swc.swc");
    qDebug() << "Done Reading. Fingers Crossed";
    qDebug() << "BreakPoint!!!!";
    return EXIT_SUCCESS;
}

 bool read_swc(VesselTreeType *outTree,const QString inFileName){
     QFile file(inFileName);
     if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){
         qDebug() << "Could not open the file in Read Only mode";
         return false;
     }
     QTextStream in(&file);

     while(!in.atEnd())
     {
         GraphVertexType vertex;
         SWCNodeType node;
         QString line = in.readLine();
         QStringList linelist = line.split(' ', QString::SkipEmptyParts);
         if(linelist.isEmpty()) continue;
         if(line[0] == '#') continue;

         //Read Current Node
         unsigned long long node_id = linelist[0].toULongLong();
         node.type = linelist[1].toUInt();
         node.x = linelist[2].toDouble();
         node.y = linelist[3].toDouble();
         node.z = linelist[4].toDouble();
         node.r = linelist[5].toDouble();
         node.pnum = linelist[6].toULongLong();

         //Put it into the vertex
         vertex.node = node;

         //Put the Vertex into the outTree
         outTree->insert(node_id,vertex);
     }
     if(outTree->isEmpty()){
         qDebug() << "Nothing was read from the SWC File";
         qDebug() << "The tree is empty";
         return false;
     }

     QMutableMapIterator<unsigned long long, GraphVertexType> tree_it1(*outTree);
     QMutableMapIterator<unsigned long long, GraphVertexType> tree_it2(*outTree);
     while (tree_it1.hasNext()) {
         tree_it1.next();
         //Populate the Adjacency List for the node
         while (tree_it2.hasNext()) {
             tree_it2.next();
             if(tree_it1.key() == tree_it2.key()) continue;
             GraphVertexType vertex = tree_it2.value();
             if(vertex.node.pnum == tree_it1.key()){
                 vertex.AdjList.append(&vertex.node);
             }
             tree_it2.setValue(vertex);/*Debug Point*/
         }
         GraphVertexType vertex = tree_it1.value();
         //Node Type Elements Updation
         if(vertex.node.pnum < 0){
             vertex.isRoot = true;
         }
         if(vertex.AdjList.size()==0){
             vertex.isTerminal = true;
             //the following is if you want to prune these, future!
             if(vertex.isRoot) vertex.isIsolated=true;
         }
         if(vertex.AdjList.size() == 1){
             vertex.isConnecting = true;
         }
         if(vertex.AdjList.size() > 1){
             vertex.isBranch = true;
         }
         tree_it1.setValue(vertex);/*Debug Point*/
     }
     return true;
}
