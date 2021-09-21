#include <iostream>
#include "astar.h"
#include "structures.h"

int main(int argc, const char *argv[])
{
    AStar planner;
    bool dma = true;
    //AStar planner;
    std::string input_name = "Data/0.map";
    if(argc > 1)
        input_name = argv[1];
    Input input(input_name, dma);
    SearchResult result = planner.findPath(input);
    if(result.pathfound)
    {
        for(auto it = result.path.begin(); it != --result.path.end(); it++)
            std::cout<<"("<<it->x<<","<<it->y<<")->";
        std::cout<<"("<<(--result.path.end())->x<<","<<(--result.path.end())->y<<")";
    }
    else
        std::cout<<"PATH NOT FOUND!";

    std::cout<<"\nCost:"<<result.cost
             <<"\nRuntime: "<<result.runtime
             <<"\nSteps: "<<result.steps
             <<"\nNodes Created: "<<result.createdNodes
             <<"\nTrue Cardinal Cost:"<<input.true_cardinal_cost
             <<"\nTrue Diagonal Cost:"<<input.true_diagonal_cost<<"\n";

    std::cout<<"\ndma:"<<dma;
    if(dma) {
        std::cout<<"Does costs equal?"<<std::endl;
        if(result.cost == input.true_diagonal_cost) {
            std::cout<<"Yes"<<std::endl;
        }else {
            std::cout<<"No"<<std::endl;
        }
    }else {
        std::cout<<"Does costs equal?"<<std::endl;
        if(result.cost == input.true_cardinal_cost) {
            std::cout<<"Yes"<<std::endl;
        }else {
            std::cout<<"No"<<std::endl;
        }
    }
    return 0;
}
