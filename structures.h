#ifndef STRUCTURES_H
#define STRUCTURES_H
#include <list>
#include <map>
#include <vector>

struct Node
{
    Node(int x_=-1, int y_=-1, double g_=-1, double f_=-1, Node* parent_ = nullptr):x(x_), y(y_), g(g_), f(f_), parent(parent_) {}
    int x, y;
    double g;
    double f;
    Node* parent;
};

class OpenList
{
private:
    std::list<Node> elements;
public:
    Node getMin()
    {
        return elements.front();
    }
    void popMin()
    {
        elements.pop_front();
    }

    int getSize()
    {
        return elements.size();
    }

    void addNode(Node node)
    {
        if(elements.empty())
        {
            elements.push_back(node);
            return;
        }
        auto pos = elements.end();
        bool posFound = false;
        for (auto iter = elements.begin(); iter != elements.end(); ++iter)
        {
            if (!posFound && iter->f >= node.f)
            {
                pos = iter;
                posFound = true;
            }
            if (iter->x == node.x && iter->y == node.y)
            {
                if (node.f >= iter->f)
                    return;
                else
                {
                    if (pos == iter)
                    {
                        iter->f = node.f;
                        iter->g = node.g;
                        iter->parent = node.parent;
                        return;
                    }
                    elements.erase(iter);
                    break;
                }
            }
        }
        elements.insert(pos, node);
    }
};

class ClosedList
{
private:
    std::map<std::pair<int, int>, Node> elements;
public:
    bool inClose(int x, int y)
    {
        return elements.find(std::make_pair(x,y)) != elements.end();
    }
    Node* getPointer(int x, int y)
    {
        return &elements.find(std::make_pair(x,y))->second;
    }
    void addClose(Node node)
    {
        elements.insert({std::make_pair(node.x, node.y), node});
    }
    int getSize()
    {
        return elements.size();
    }
};

struct SearchResult
{
    SearchResult():cost(0), pathfound(false), runtime(0), steps(0), createdNodes(0){}
    std::list<Node> path;
    double cost;
    int steps;
    int createdNodes;
    double runtime;
    bool pathfound;
};

#endif // STRUCTURES_H
