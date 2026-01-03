#pragma once
#include "vec3.h"
#include "rtweekend.h"

using color = vec3;

inline double linear_to_gamma(double linear_component);
void write_color(std::ostream& out, const color& pixel_color);

