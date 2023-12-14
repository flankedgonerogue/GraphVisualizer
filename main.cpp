#include <iostream>
#include "include/Graph.h"

int main()
{
    Flanky::Graph graph;
    graph.insertNode("A");
    graph.insertNode("B");
    graph.insertNode("C");
    graph.insertNode("D");
    graph.insertEdge("A", "B", 1);
    graph.insertEdge("B", "C", 3);
    graph.insertEdge("B", "A", 4);
    graph.insertEdge("B", "D", 9);

    std::cout << graph.getNodesAsString() << Flanky::Graph::getEdgesAsStringFromEdges(graph.findEdgesForNode("B")) << std::flush;

    return 0;
}