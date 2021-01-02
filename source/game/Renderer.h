#pragma once
#include "olcPixelGameEngine.h"
#include "box2d/box2d.h"
#include "GameResources.h"

namespace B2DOLC
{
    class Renderer
    {
    public:
        void Draw(GameObject* b);

        olc::vf2d ToScreen(const b2Vec2& vec) const;
        b2Vec2 ToWorld(const olc::vf2d& vec) const;

        void SetPGE(olc::PixelGameEngine* pge) { _pge = pge; }
        void SetOrigin(const olc::vf2d& origin) { _world_origin = origin; _b2vec_wo.Set(origin.x, origin.y); }
        void SetProjection(const olc::vf2d& projection) { _world_projection = projection; _b2vec_pro.Set(projection.x, projection.y); }
        void SetZoom(float zoom) { _world_zoom = zoom; }

    private:
        void DrawPolygon(GameObject* body, b2PolygonShape* shape);
        void DrawCircle(GameObject* body, b2CircleShape* circle);

        olc::vf2d _world_origin;
        olc::vf2d _world_projection;
        float _world_zoom;
        b2Vec2 _b2vec_wo;
        b2Vec2 _b2vec_pro;
        olc::PixelGameEngine* _pge;
    };
}