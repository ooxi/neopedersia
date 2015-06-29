#include <math.h>
#include "PathFinder.h"

void PathFinder::PrintStateInfo(void * /*state*/)
{
    // For debug purposes, for example write state to stdout.
}

Vec2 PathFinder::NodeToPoint(void *node)
{
    int index = (int) node;
    int y = index / MAP_WIDTH;
    int x = index - y * MAP_WIDTH;
    return Vec2(x, y);
}

void *PathFinder::PointToNode(const Vec2 &point)
{
    return (void *) (point.y * MAP_WIDTH + point.x);
}

void PathFinder::AdjacentCost(void *state, std::vector<micropather::StateCost> *adjacent)
{
    const int dx[8] = {1, 1, 0, -1, -1, -1, 0, 1};
    const int dy[8] = {0, 1, 1, 1, 0, -1, -1, -1};
    const float cost[8] = {1.0f, 1.41f, 1.0f, 1.41f, 1.0f, 1.41f, 1.0f, 1.41f};

    Vec2 p = NodeToPoint(state);

    for (int i = 0; i < 8; ++i)
    {
        //TODO: Use Vec2.
        int nx = p.x + dx[i];
        int ny = p.y + dy[i];

        if (passable(nx, ny))
        {
            micropather::StateCost nodeCost = {PointToNode(Vec2(nx, ny)), cost[i]};
            adjacent->push_back(nodeCost);
        }
    }
}

bool PathFinder::passable(int nx, int ny)
{
    if ((nx >= 0) && (nx < MAP_WIDTH) && (ny >= 0) && (ny < MAP_HEIGHT))
    {
        MapCell cell = cells[nx][ny];
        if (cell == 0)
            return true;
    }
    return false;
}

float PathFinder::LeastCostEstimate(void *stateStart, void *stateEnd)
{
    Vec2 start = NodeToPoint(stateStart);
    Vec2 end = NodeToPoint(stateEnd);

    //TODO: Use Vec2.
    int dx = start.x - end.x;
    int dy = start.y - end.y;
    return (float) sqrt((double) (dx * dx) + (double) (dy * dy));
}

int PathFinder::find(const Vec2 &from, const Vec2 &to, std::vector<Vec2> &path)
{
    path.clear();

    //TODO: Dont recreate MicroPather.
    micropather::MicroPather pather(this);
    std::vector<void *> p;
    float totalCost;
    int result = pather.Solve(PointToNode(from), PointToNode(to), &p, &totalCost);

    if (!result)
    {
        for (std::vector<void *>::iterator it = p.begin();
             it != p.end();
             ++it)
        {
            path.push_back(NodeToPoint(*it) * 8);
        }
    }

    return result;
}

//bool PathFinder::isPointEmpty(int x, int y) const
//{
//    //TODO: precision problem.
//    int col = x / 8;
//    int row = y / 8;
//
//    if ((col < 0) && (col >= MAP_WIDTH))
//        return false;
//
//    if ((row < 0) && (row >= MAP_HEIGHT))
//        return false;
//
//    if (cells[col][row])
//        return false;
//
//    return true;
//}
