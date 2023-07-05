#include <display.hpp>
#include <uix.hpp>
#include <gfx.hpp>
#include "uix_image.hpp"

using surface_t = typename screen_t::control_surface_type;
using label_t = uix::label<surface_t>; 
using canvas_t = uix::canvas<surface_t>;
using svg_box_t = uix::svg_box<surface_t>;
using image_t = uix::image<surface_t>;

using color_t = gfx::color<typename screen_t::pixel_type>;
using color32_t = gfx::color<gfx::rgba_pixel<32>>;

extern screen_t main_screen;

extern image_t image1;
extern image_t image2;

extern void main_screen_init();