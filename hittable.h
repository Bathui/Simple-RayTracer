#pragma once

#include "ray.h"

class Hit_record {
    public:
        point3 p;
        vec3 normal;
        double t;
};

class Hittable{
    public:
        virtual ~Hittable() = default;

        virtual bool hit(const ray& r, double ray_tmin, double ray_tmax, Hit_record& rec) const = 0;
};