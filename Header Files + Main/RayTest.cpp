#include "rtweekend.h"

#include "color.h"
#include "hittable_list.h"
#include "sphere.h"
#include "camera.h"

#include <iostream>

using namespace std;

color ray_color (const ray& r, const hittable& world){
    hit_record rec;
    if (world.hit (r, 0, infinity, rec)){ //hit sphere
        return 0.5 * (rec.normal + color (1,1,1)); 
    }
    vec3 unit_direction = unit_vector (r.direction());
    auto t = 0.5 * (unit_direction.y() + 1.0);
    return (1.0 - t) * color (1.0, 1.0, 1.0) + t * color(0.5, 0.7, 1.0); //background
}

int main(){
    const auto aspect_ratio = 16.0 / 9.0;
    const int image_width = 400;
    const int image_height = static_cast<int>(image_width / aspect_ratio);

    // World
    hittable_list world;
    world.add(make_shared<sphere>(point3(0, 0, -1), 0.5));
    world.add(make_shared<sphere>(point3(0, -100.5, -1), 100));

    // Camera
    camera cam (point3 (0, 0, 0), point3(0, 0, -1), vec3(0, 1, 0), 90, aspect_ratio);

    // Render
    cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";
    for (int j = image_height-1; j >= 0; j--){
        cerr << "\rScanlines remaining: " << j << ' ' << flush;
        for (int i = 0; i < image_width; i++){
            auto u = double(i) / (image_width-1);
            auto v = double(j) / (image_height-1);
            ray r = cam.get_ray(u, v);
            color pixel_color = ray_color (r, world);
            write_color(cout, pixel_color);
        }
    }
    cerr << "\nDone.\n";
}