#pragma once

#include "hittable.h"

class Sphere : public Hittable{
    public:
        Sphere (const point3& center, double radius, shared_ptr<material> mat): center(center), radius(std::fmax(0, radius)), mat(mat) {}
        bool hit(const ray& r, interval ray_t, Hit_record& rec) const{
            vec3 oc = center - r.origin();
            auto a = r.direction().length_squared();
            auto h = dot(r.direction(), oc);
            auto c = oc.length_squared() - radius * radius;

            auto discriminant = std::pow(h, 2) - a * c;

            if (discriminant < 0)
                return false;

            auto sqrtd = std::sqrt(discriminant);

            auto root = (h-sqrtd) /a;
            if (!ray_t.surrounds(root)){
                root = (h + sqrtd) / a; // try the bigger one
                if (!ray_t.surrounds(root))
                    return false;  
            }
            
            rec.t = root;
            rec.p = r.at(rec.t);
            vec3 outward_normal = (rec.p - center) / radius;
            rec.set_face_normal(r, outward_normal);
            rec.mat = mat;

            return true;
        } 
       point3 center;
       double radius; 
       shared_ptr<material> mat;

};