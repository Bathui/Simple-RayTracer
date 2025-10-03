#include <iostream>
#include <cmath>
#include "color.h"
#include "ray.h"

bool hit_sphere(const point3& center, double radius, const ray& r){
    vec3 oc = center - r.origin();
    auto a = dot(r.direction(), r.direction());
    auto b = dot(-2.0 * r.direction(), oc);
    auto c = dot(oc, oc) - radius * radius;

    auto determinant = std::pow(b, 2) - 4 * a * c;
    return (determinant >= 0);
}

color ray_color (const ray& r) {
    if (hit_sphere(point3(0, 0, -1), 0.5, r))
        return color(0, 0, 1);

    vec3 unit_direction = unit_vector(r.direction());
    auto t = 0.5 * (unit_direction.y() - (-1));
    return (1.0 - t) * color(1.0, 1.0, 1.0) + t * color(0.5, 0.7, 1.0);
}

int main() {

    // Image
    auto aspect_ratio = 16.0 / 9.0;
    int image_width = 400;

    int image_height = int(image_width / aspect_ratio);
    // Height has to be at least 1 to make the image valid
    image_height = (image_height < 1) ? 1 : image_height;

    // Camera
    double focal_length = 1.0;
    double viewport_height = 2.0;
    auto viewport_width =  viewport_height * (double(image_width)/image_height);
    auto camera_center = point3(0, 0, 0);

    // Get the vectors across the horizontal and down the vertical viewport edges
    auto viewport_u = vec3(viewport_width, 0, 0);
    auto viewport_v = vec3(0, -viewport_height, 0);
    
    // Get the delta vectors from pixel to piexel
    auto pixel_delta_u = viewport_u / image_width;
    auto pixel_delta_v = viewport_v / image_height;
    
    // Get the location of the upper left pixel
    auto viewport_upper_left = camera_center - vec3(0, 0, focal_length) - viewport_u/2 - viewport_v/2;
    auto pixel00 = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);
    // Render

    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for (int j = 0; j < image_height; j++) {
        std::clog << "\rScanlines remaining: " << (image_height - j) << ' ' << std::flush;
        for (int i = 0; i < image_width; i++) {
            auto pixel_center = pixel00 + (i* pixel_delta_u) + (j * pixel_delta_v);
            auto ray_direction = pixel_center - camera_center;
            ray r(camera_center, ray_direction);
            
            auto pixel_color = ray_color(r);
            write_color(std::cout, pixel_color);
        }
    }

    std::clog << "\rDone.     \n";  
}