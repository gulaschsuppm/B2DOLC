#pragma once
#include "olcPixelGameEngine.h"
#include "box2d/box2d.h"

//class b2Body;
//class b2Vec2;

namespace B2DOLC
{
    class Renderer
    {
    public:
        void Draw(b2Body* b);

        olc::vf2d ToScreen(const b2Vec2& vec) const;
        b2Vec2 ToWorld(const olc::vf2d& vec) const;

        void SetPGE(olc::PixelGameEngine* pge) { _pge = pge; }
        void SetOrigin(const olc::vf2d& origin) { _world_origin = origin; _b2vec_wo.Set(origin.x, origin.y); }
        void SetProjection(const olc::vf2d& projection) { _world_projection = projection; _b2vec_pro.Set(projection.x, projection.y); }
    private:
        void DrawPolygon(b2Body* body, b2PolygonShape* shape);
        void DrawCircle(b2Body* body, b2CircleShape* circle);

        olc::vf2d _world_origin;
        olc::vf2d _world_projection;
        b2Vec2 _b2vec_wo;
        b2Vec2 _b2vec_pro;
        olc::PixelGameEngine* _pge;
    };
}