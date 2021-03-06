#pragma once

#include "Ground.h"
#include "WorldPainterImpl.h"
#include "worldObjects/WorldObject.h"
#include "Rect.h"
#include <list>
#include <vector>
#include "PathFinder.h"

class World
{
public:
    World(Painter& painter) : worldPainter(painter) {}
    void fill();
    void update();
    void render();
    void moveMap(const Vec2& offset);
    void alignToWindowCenter(const Vec2& windowSize);
    int find(const Vec2& from, const Vec2& to, std::vector<Vec2>& path);
    WorldObjectId getBuilding(const Vec2& pos) const;
    void addWorldObject(WorldObject* worldObject, const Vec2& pos);
    void addWorldObject(WorldObject* worldObject);
    void removeWorldObject(WorldObject* worldObject);
    WorldObject* getNearestTarget(const Vec2& pos, int range);
    void massiveDamage(const Vec2& pos, int range, int damage);

private:
    void updatePathFinderMap();
    void putWallRect(const Rect &rect);
    void putWallLine(Vec2 from, const Vec2& direction, int len);
    void removeWallByPos(const Vec2& pos);
    void removeUnitByList();
    void renderHealthBars(const WorldPainter& worldPainter) const;

    WorldPainterImpl worldPainter;
    Ground ground;
    Vec2 offset;
    PathFinder pathFinder;

    //TODO: Delete items.
    std::list<WorldObject*> items;
    std::vector<WorldObject*> removeList;
};
