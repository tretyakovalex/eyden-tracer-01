#pragma once

#include "IPrim.h"
#include "ray.h"

// --- IMPLENET class CPrimDisc ---
// --- PUT YOUR CODE HERE ---


class CPrimDisc : public IPrim {
public:
    /**
     * @brief Constructor
     * @param origin Point on the plane
     * @param normal Normal to the plane
     * @param radius Radius of the Plane
     */
    
//    CPrimDisc();
    
//    CPrimDisc(const Vec3f& origin, const Vec3f& normal, const float radius)
//    : CPrimPlane(origin, normal)
//    , m_radius(radius)
//    {}

    CPrimDisc(const Vec3f& origin, const Vec3f& normal, const float radius)
    : IPrim()
    , m_origin(origin)
    , m_normal(normal)
    , m_radius(radius)
    {}
    
    virtual ~CPrimDisc(void) = default;
    
    virtual bool intersect(Ray& ray) const {
        float t = (m_origin - ray.org).dot(m_normal) / ray.dir.dot(m_normal);
        
        if(t < Epsilon || t > ray.t) return false;
        if(norm(ray.org + (ray.dir * t) - m_origin) > m_radius) return false;
        
        ray.t = t;
        return true;
    }
private:
    Vec3f m_origin; ///< Position of the center of the disc
    Vec3f m_normal; ///< Normal to the disc
    float m_radius; ///< Radius of the disc
};
