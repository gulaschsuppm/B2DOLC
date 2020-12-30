#include "Renderer.h"
//#include "box2d/box2d.h"

namespace B2DOLC
{
    float ToRadians(float degree)
    {
        const float pi = 3.141592654f;
        return (degree * (pi / 180.0f));
    }

    olc::vf2d Rotate(const olc::vf2d& vec, float angle_deg, const olc::vf2d& origin)
    {
        // Move to world origin
        auto moved = vec - origin;

        float cosine = cosf(ToRadians(angle_deg));
        float sine = sinf(ToRadians(angle_deg));

        float x_prime = (moved.x * cosine) - (moved.y * sine);
        float y_prime = (moved.x * sine) + (moved.y * cosine);

        return (olc::vf2d(x_prime, y_prime) + origin);
    }

    b2Vec2 Rotate(const b2Vec2& vec, float angle_deg, const b2Vec2& origin = { 0,0 })
    {
        // Move to world origin
        auto moved = vec - origin;

        float cosine = cosf(ToRadians(angle_deg));
        float sine = sinf(ToRadians(angle_deg));

        float x_prime = (moved.x * cosine) - (moved.y * sine);
        float y_prime = (moved.x * sine) + (moved.y * cosine);

        return (b2Vec2(x_prime, y_prime) + origin);
    }

    olc::vf2d Renderer::ToScreen(const b2Vec2& vec) const
    {
        olc::vf2d world_vec(vec.x, vec.y);

        return (_world_origin + world_vec * _world_projection);
    }

    b2Vec2 Renderer::ToWorld(const olc::vf2d& vec) const
    {
        b2Vec2 screen_vec((vec.x - _world_origin.x) * _world_projection.x, (vec.y - _world_origin.y) * _world_projection.y);

        return screen_vec;
    }

    void Renderer::DrawPolygon(b2Body* body, b2PolygonShape* shape)
    {
        auto pos = body->GetPosition();
        auto angle = body->GetAngle();

        auto v0 = ToScreen(Rotate(pos + shape->m_vertices[0], angle));
        auto v1 = ToScreen(Rotate(pos + shape->m_vertices[1], angle));
        auto v2 = ToScreen(Rotate(pos + shape->m_vertices[2], angle));
        auto v3 = ToScreen(Rotate(pos + shape->m_vertices[3], angle));
        _pge->DrawLine(v0, v1);
        _pge->DrawLine(v1, v2);
        _pge->DrawLine(v2, v3);
        _pge->DrawLine(v3, v0);
    }

    void Renderer::DrawCircle(b2Body* body, b2CircleShape* circle)
    {
        auto pos = body->GetPosition();

        auto center = ToScreen(pos);
        _pge->DrawCircle(center, int(circle->m_radius), olc::GREEN);
    }

    void Renderer::Draw(b2Body* body)
    {
        auto fixture_list = body->GetFixtureList();
        for (b2Fixture* f = fixture_list; f; f = f->GetNext())
        {
            auto type = f->GetType();
            switch (type)
            {
            case b2Shape::e_polygon:
            {
                b2PolygonShape* poly = (b2PolygonShape*)f->GetShape();
                DrawPolygon(body, poly);
                break;
            }
            case b2Shape::e_circle:
            {
                b2CircleShape* circle = (b2CircleShape*)f->GetShape();
                DrawCircle(body, circle);
                break;
            }
            default:
                break;
            }
        }
    }
}