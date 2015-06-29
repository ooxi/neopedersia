#include "PainterImpl.h"
#include <SDL2pp/Point.hh>
#include <SDL2pp/Renderer.hh>

void PainterImpl::draw(const Vec2 &pos, const Texture &picture) const
{
    std::string fileName = picture.getFileName();
    std::map<std::string, SDL2pp::Texture>::iterator it = textures.find(picture.getFileName());
    if (it == textures.end())
    {
        it = textures.emplace(fileName, SDL2pp::Texture(renderer, fileName)).first;
        it->second.SetBlendMode(SDL_BLENDMODE_BLEND);
    }

    renderer.Copy(it->second, SDL2pp::NullOpt, SDL2pp::Point(pos.x, pos.y));
}

Vec2 PainterImpl::getTextureSize(const Texture &picture) const
{
    std::map<std::string, SDL2pp::Texture>::iterator it = textures.find(picture.getFileName());
    if (it == textures.end())
        return Vec2();
    SDL2pp::Point size = it->second.GetSize();
    return Vec2(size.x, size.y);
}
