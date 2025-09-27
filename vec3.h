#pragma once

#include <iostream>
#include <cmath>

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









