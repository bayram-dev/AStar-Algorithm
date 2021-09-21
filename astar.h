#ifndef ASTAR_H
#define ASTAR_H
#include "input.h"
#include <chrono>

class AStar
{   ClosedList cl;
    OpenList ol;
public:
    AStar() {}
    SearchResult findPath(Input input);
    std::list<Node> reconstructPath(Node current);

    double getHValue(Node current, Node goal, bool dma);
};

#endif // ASTAR_H
