#pragma once

#include "hittable.h"

class Sphere : public Hittable{
    public:
        Sphere (const point3& center, double radius): center(center), radius(std::fmax(0, radius)) {}
        bool hit (const ray& r, double ray_tmin, double ray_tmax, Hit_record& rec) const override;
    private:
       point3 center;
       double radius; 
};