#include "astar.h"
#include "dijkstra.h"

SearchResult AStar::findPath(Input i)
{
    auto t = std::chrono::high_resolution_clock::now();
    SearchResult result;
    /*
     * start.g = 0
     * start.f = getHValue(start, goal, dma)
     * OPEN = {start}
     * CLOSED = {}
     * while OPEN is not empty
     *  current = node from OPEN with minimal g-value
     *  move current from OPEN to CLOSED
     *  if current is goal
     *      result.f = current.f
     *      return reconstructPath(current)
     *  neighbors = get neighbors of current node
     *  for each neighbor in neighbors:
     *      if neighbor in CLOSED:
     *          continue
     *      neighbor.g = current.g + cost(neighbor, current)
     *      neighbor.f = neighbor.g + getHValue(neighbor, goal, dma)
     *      neighbor.parent = current
     *      insert or update neighbor into OPEN
     * return path not found
     */
    i.start.g = 0;
    i.start.f = AStar::getHValue(i.start, i.goal, i.map.diagonal_moves_allowed);
    ol.addNode(i.start);
    while (ol.getSize() != 0)
    {
        Node current = ol.getMin();
        cl.addClose(current);
        ol.popMin();
        if ((current.x == i.goal.x) && (current.y == i.goal.y))
        {
            result.cost = current.f;
            result.pathfound = true;
            result.path = AStar::reconstructPath(current);
            break;
        }
        std::list<Node> neighbours = i.map.getValidMoves(current);
        for (auto n : neighbours)
        {
            if (cl.inClose(n.x, n.y))
                continue;
            n.g = current.g + i.map.getCost(n, current);
            n.f = n.g + AStar::getHValue(n, i.goal, i.map.diagonal_moves_allowed);
            n.parent = cl.getPointer(current.x, current.y);
            ol.addNode(n);
        }
    }
    result.createdNodes = cl.getSize() + ol.getSize();
    result.steps = cl.getSize();
    result.runtime = std::chrono::duration_cast<std::chrono::duration<double>>(std::chrono::high_resolution_clock::now() - t).count();
    return result;
}

double AStar::getHValue(Node current, Node goal, bool dma)
{
    if (dma)
        return abs(abs(goal.x - current.x) - abs(goal.y - current.y)) + sqrt(2) * fmin(abs(goal.x - current.x), abs(goal.y - current.y));
    else
        return abs(goal.x - current.x) + abs(goal.y - current.y);;
}

std::list<Node> AStar::reconstructPath(Node current)
{
    std::list<Node> path;
    while(current.parent != nullptr)
    {
        path.push_front(current);
        current = *current.parent;
    }
    path.push_front(current);
    return path;
}

