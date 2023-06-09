#ifndef HITTABLE_H
#define HITTABLE_H

#include "rtweekend.h"

class material; 

struct hit_record { 
    point3 p; //intersection point
    vec3 normal;
    double t; //position along the ray
    shared_ptr <material> mat_ptr; 
    bool front_face;

    inline void set_face_normal(const ray& r, const vec3& outward_normal) {
        front_face = (dot (r.direction(), outward_normal) < 0); //true if ray hits front face 
        normal = front_face ? outward_normal :-outward_normal; //finds direction of normal
    }
};

class hittable {
    public:
        virtual bool hit (const ray& r, double t_min, double t_max, hit_record& rec) const = 0;
};

#endif