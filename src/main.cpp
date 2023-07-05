#define WIFI_SSID "Communism_Will_Win"
#define WIFI_PASS "mypalkarl"
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
    display_update();
    WiFi.begin(WIFI_SSID, WIFI_PASS);
    Serial.print("Connecting");
    while (WiFi.status() != WL_CONNECTED) {
        Serial.print(".");
        delay(125);
    }
    Serial.println();
    Serial.println("Connected");
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
