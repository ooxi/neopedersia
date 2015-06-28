#pragma once

#include "Texture.h"
#include "Point.h"

class WorldPainter
{
public:
    virtual void draw(const Point& pos, const Texture & picture) const = 0;
};
