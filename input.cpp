#include "input.h"

Input::Input(std::string fileName, bool dma)
{
    map.diagonal_moves_allowed = dma;
    if(fileName != "")
    {
        loadInput(fileName);
        return;
    }
    // Убрал псевдоданные, тк не имеют смысла, ибо у нас есть инпут файл
}

double Grid::getCost(Node current, Node neighbor)
{
    // по хорошему, тут надо учитывать также случай current=neighbor, но ожидается, что такого случая никогда не будет
    // /////////////////////////////////////////////////////////////////////////////////////////
    // диагональный переход дает нам корень из 2 (sqrt(1*1+1*1))
    // переход в cardinal дает лишь изменение 1 координаты, потому переход дает нам стоимость 1
    // /////////////////////////////////////////////////////////////////////////////////////////
    if ((current.x != neighbor.x) && (current.y != neighbor.y))
        return sqrt(2);
    else
        return 1;
}
std::list<Node> Grid::getValidMoves(Node current)
{
    std::list<Node> result;
    std::list<std::pair<int, int>> d1 = {{0 ,1}, {1, 0}, {-1, 0}, {0, -1}};
    for(auto d:d1)
        if(current.x + d.first < width-1 && current.x + d.first >= 0 && current.y + d.second < height-1 && current.y + d.second >= 0)
            if(elements[current.x + d.first][current.y + d.second] == 0)
                result.push_back(Node(current.x + d.first, current.y + d.second));
    if(diagonal_moves_allowed)
    {
        // просто добавляем дополнительные значения по диагоналям в наш result
        std::list<std::pair<int, int>> d2 = {{1, 1}, {-1, -1}, {1, -1},  {-1, 1}};
        for(auto d:d2)
            if(current.x + d.first < width-1 && current.x + d.first >= 0 && current.y + d.second < height-1 && current.y + d.second >= 0)
                if((elements[current.x + d.first][current.y + d.second] == 0)   // по диагонали 0
                        && (elements[current.x + d.first][current.y] == 0)      // с одной стороны 0
                        && (elements[current.x][current.y + d.second] == 0))    //с другой стороны 0
                {
                    // проверка выше нужна только для того, чтобы можно было пройти по диагонали ( вы упомянули об этой проверке во время занятия на 01:08:00)
                    result.push_back(Node(current.x + d.first, current.y + d.second));
                }
    }
    return result; // массив со всеми вершинами, к которым у нас есть прямой путь
}

void Input::loadInput(std::string fileName)
{
    std::ifstream in;
    in.open(fileName);
    if(!in.is_open())
    {
        std::cout<<"Error! Cannot load the file "<<fileName<<"\n";
        return;
    }
    char c;
    in>>map.height>>map.width;
    map.elements.resize(map.height, std::vector<int>(map.width, 0));
    for(int k=0; k<map.height; k++)
        for(int l=0; l<map.width; l++)
        {
            in>>c;
            if(c == '#')
                map.elements[k][l]=1;
        }
    in>>start.x>>start.y>>goal.x>>goal.y>>true_cardinal_cost>>true_diagonal_cost;
}
