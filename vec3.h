#pragma once

#include <cmath>
#include <random>
inline double random_double(){
    // Return a random real in [0, 1)
    static std::uniform_real_distribution<double> distribution(0.0, 1.0);
    static std::mt19937 generator;
    return distribution(generator);
}

inline double random_double(double min, double max){
    return min + (max - min) * random_double();
}


class vec3{
    public:
        double e[3];
        
        //  Constructors
        vec3() : e{0, 0, 0}{}
        vec3(double e0, double e1, double e2):e{e0, e1, e2}{}

        double x() const {  return e[0]; }
        double y() const {  return e[1]; }
        double z() const {  return e[2]; }

        //const obj access
        double operator[](int i)const {return e[i];}
        // regular obj access
        double& operator[](int i) {return e[i];}

        vec3 operator-() const {   return vec3{-e[0], -e[1], -e[2]};   };
        
        vec3& operator+= (const vec3& v);
        vec3& operator*= (const vec3& v);
        vec3& operator/= (const vec3& v);

        double length() const{  return std::sqrt(length_squared()); }
        double length_squared() const { return std::pow(e[0], 2) + std::pow(e[1], 2) + std::pow (e[2], 2);  }
        
        bool near_zero() const {
            auto s = 1e-8;
            return (std::fabs(e[0]) < s) && (std::fabs(e[1]) < s) && (std::fabs(e[2]) < s);
        }

        static vec3 random() {
            return vec3(random_double(), random_double(), random_double());
        }

        static vec3 random(double min, double max) {
            return vec3(random_double(min,max), random_double(min,max), random_double(min,max));
        }
};

using point3 = vec3; //give vec3 an alias

// Utility functions

inline vec3 operator+ (const vec3& u, const vec3& v){
    return vec3(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]);
}

inline vec3 operator- (const vec3& u, const vec3& v){
    return vec3(u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2]);
}

inline vec3 operator* (const vec3& u, const vec3& v){
    return vec3(u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]); 
}

inline vec3 operator* (double t, const vec3& v){
    return vec3(t * v.e[0], t * v[1], t * v[2]);
}

inline vec3 operator* (const vec3& v, double t){
    return t * v;
}

inline vec3 operator/ (const vec3& v, double t){
    return (1/t) * v;
}

inline double dot (const vec3& u, const vec3& v){
    return u.e[0] * v.e[0] + u.e[1] * v.e[1] + u.e[2] * v.e[2];
}

inline vec3 cross (const vec3& u, const vec3& v) {
    return vec3(u.e[1] * v.e[2] - u.e[2] * v.e[1],
                u.e[2] * v.e[0] - u.e[0] * v.e[2],
                u.e[0] * v.e[1] - u.e[1] * v.e[0]);
}

inline vec3 unit_vector (const vec3& v){
    return v / v.length();
}

inline vec3 random_unit_vector(){
    while (true) {
        auto p = vec3::random(-1, 1);
        auto lensq = p.length_squared();
        if (lensq <= 1) // inside the unit sphere
            return p / sqrt(lensq); // get the unit vector 
    }
}

inline vec3 random_on_hemisphere (const vec3& normal) {
    vec3 on_unit_sphere = random_unit_vector();
    if (dot(on_unit_sphere, normal) > 0.0) 
        return on_unit_sphere;
    return -on_unit_sphere;
}

inline vec3 reflect (const vec3& v, const vec3& n) {
    return v - 2*dot(v, n) * n;
}






