#include <iostream>
#include "rose.h"
#include "CallGraph.h"


using namespace std;
using namespace SageInterface;
using namespace SageBuilder;

/** This filter determines which function declarations get processed in the analysis. */
class CGFilter {
public:
  bool operator()(SgFunctionDeclaration * funcDecl) {
    ROSE_ASSERT(funcDecl != NULL);
    Sg_File_Info* finfo = funcDecl->get_file_info();
    //Exclude compiler generated functions, but keep template instantiations
    if (finfo->isCompilerGenerated()) {
	return false;
    }
    //We don't process functions that don't have definitions
    if (funcDecl->get_definingDeclaration() == NULL) {
	return false;
    }
    
//     SgSourceFile* sf = isSgSourceFile(getEnclosingFileNode(funcDecl));
//     if(NULL == sf) {
//       return false;
//     }
//     
//     if (sf->get_file_info()->get_filenameString().compare(finfo->get_filenameString()) != 0) {
//       return false;
//     }
    
//     cout << funcDecl->get_name().getString() << ", " << isSgSourceFile(getEnclosingFileNode(funcDecl))->get_file_info()->get_filenameString() << endl;
    return true;
  }
};

int main(int argc, char* argv[]) {
  SgProject* project = frontend(argc, argv);
  
  // build the call graph
  CallGraphBuilder cgb(project);
  cgb.buildCallGraph(CGFilter());
  
//   cgb.buildCallGraph();
  SgIncidenceDirectedGraph* graph = cgb.getGraph();
  
  set<SgGraphNode *> nodes = graph->computeNodeSet();
  for (set<SgGraphNode *>::iterator itr = nodes.begin(); itr != nodes.end(); itr++) {
    SgNode* n = (*itr)->get_SgNode();
    cout << getVariantName(n->variantT()) << ", " << isSgFunctionDeclaration(n)->get_name().getString() << endl;
  }

  // This ROSE API method is not implemented and should not be used as the linker will complain
//   GenerateDotGraph();
  
  // writing the entire graph to a dot file; to be visualized with tools like xdot
  AstDOTGeneration g;
  g.writeIncidenceGraphToDOTFile(graph, "callgraph.dot");
  
  return backend(project);
}
