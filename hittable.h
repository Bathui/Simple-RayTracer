#pragma once
#include "vec3.h"

#include "rtweekend.h"


class Hit_record {
    public:
        point3 p;
        vec3 normal;
        double t;
        bool front_face;

        void set_face_normal (const ray& r, const vec3& outward_normal) {
            // use normal vector as the hit record
            // outward_normal is assumed to be a unit vector

            front_face = dot(r.direction(), outward_normal) < 0;
            normal = front_face ? outward_normal : -outward_normal;
        }
};

class Hittable{
    public:
        virtual ~Hittable() = default;

        virtual bool hit(const ray& r, interval ray_t, Hit_record& rec) const = 0;
};