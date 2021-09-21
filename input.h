#ifndef INPUT_H
#define INPUT_H
#include "structures.h"
#include <vector>
#include <fstream>
#include <iostream>
#include <math.h>

struct Grid
{
    std::vector<std::vector<int>> elements;
    int width;
    int height;
    bool diagonal_moves_allowed;
    std::list<Node> getValidMoves(Node current);
    double getCost(Node current, Node neighbor);
};

class Input
{
public:
    Input(std::string fileName = "", bool dma = false);
    Node start;
    Node goal;
    Grid map;
    double true_cardinal_cost;
    double true_diagonal_cost;
    void loadInput(std::string fileName);
};

#endif // INPUT_H
