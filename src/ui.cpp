#include <ui.hpp>
#define GOOGLE_IMPLEMENTATION
#include <assets/google.hpp>
using namespace uix;
using namespace gfx;

screen_t main_screen(lcd_buffer_size,lcd_buffer1,lcd_buffer2);

image_t image1(main_screen);
image_t image2(main_screen);

void main_screen_init() {
    main_screen.background_color(color_t::black);
    size16 sz;
    png_image::dimensions(&google,&sz);
    srect16 r(0,0,sz.width-1,sz.height-1);
    image1.bounds(r);
    image1.on_load([](void* state){((io::stream*)state)->seek(0);},&google);
    image1.stream(&google);
    main_screen.register_control(image1);
    image2.bounds(image1.bounds().offset(0,image1.dimensions().height));
    main_screen.register_control(image2);
    
}

