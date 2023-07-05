// we have a 32kB transfer buffer for the LCD
// that means there can be a bitmap of
// the same area as 128x128 at 16-bit color
// but any rectangular shape

// the issue is normally the buffer
// will extend to the width of the
// display and be very short in height
// this causes controls to draw more
// than once because they have to render
// the top half, then again for the bottom
// half, or worse, there are more than 2
// divisions of the control.

// what I'd like to do is make my lib
// smart enough that it will only draw
// controls once, refreshing the screen
// around the controls. And then drawing
// each of the controls.

// what I currently have. A split()
// method that takes a rect and punches
// a rect shaped hole in it, returning
// up to 4 rects as a result. This could
// be used to cut out the control sections
// maybe.

// so I could run through the rects and
// split() them where there are controls
// and then draw around them on the first
// pass (draw the screen background)

// the issue with it is that I will 
// often be transfering less than 32kB
// at a time. With slow drawing controls
// like truetype labels and images from
// remote sites as below, this obviously
// pays for itself even with the extra
// overhead of sending small chunks.
// However, it may not be advantagous
// for certain controls, like a canvas
// with quick drawing.

// can anyone think of a better way?
// ideas to further optimize the above

#define GOOGLE_URL "http://www.google.com/images/branding/googlelogo/2x/googlelogo_color_160x56dp.png"

#include <Arduino.h>
#include <HTTPClient.h>
#include <Wifi.h>

#include <ui.hpp>
using namespace gfx;
using namespace uix;

HTTPClient http;
arduino_stream png_stream;
void setup() {
    Serial.begin(115200);
    display_init();
    main_screen_init();
    display_screen(main_screen);
    // this is necessary so that the main 
    // screen updates and clears all 
    // dirty rects. 
    display_update();
    WiFi.begin();
    Serial.print("Connecting");
    while (WiFi.status() != WL_CONNECTED) {
        Serial.print(".");
        delay(125);
    }
    Serial.println();
    Serial.println("Connected");
    // if we hadn't updated the screen
    // before this would have to load
    // more than once
    image2.stream(&png_stream);
    image2.on_load([](void* state) {
        http.begin(GOOGLE_URL);
        if(200==http.GET()) {
          png_stream.set(http.getStreamPtr());
        }
    });
}

void loop() {
    display_update();
}
