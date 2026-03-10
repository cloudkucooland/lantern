#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
// #include "esp_log.h"
#include "driver/gpio.h"
#include "neopixel.h"
#include "esp_random.h"

#include "sdkconfig.h"
#include "lantern.h"

static inline int min(int a, int b) {
  if (a < b) return a;
  return b;
}

static uint32_t brightness = 1;

void start_neopixel(void *unused) {
   int32_t rnd;
   tNeopixelContext ctx;
   tNeopixel pixel[PIXEL_COUNT];

   ctx = neopixel_Init_RGBW(PIXEL_COUNT, NEOPIXEL_PIN);
   assert(ctx);

   for(int i = 0; i < PIXEL_COUNT; i++) {
     pixel[i].index = i;
     pixel[i].rgb = NP_RGBW(0,0,0,0);
   }
   neopixel_SetPixel(ctx, pixel, PIXEL_COUNT);

   while (1) {
     for(int i = 0; i < PIXEL_COUNT; i++) {
        rnd = esp_random();

        pixel[i].rgb = NP_RGBW(
          min((rnd & 0x0000000F), (rnd >> 8 & 0x0000000F)) * brightness, // green
          (rnd >> 8 & 0x0000003F) * brightness, // red
          min((rnd >> 16 & 0x0000000F), (rnd >> 8 & 0x0000000F)) * brightness, // blue
	  (rnd >> 24 & 0x00000001) * brightness // white
         );
     }

     neopixel_SetPixel(ctx, pixel, PIXEL_COUNT);
     vTaskDelay(pdMS_TO_TICKS(50 + (rnd >> 20 & 0x0000007F)));
   }
}

void set_brightness(int b) {
  brightness = b;
}

int get_brightness(void) {
  return brightness;
}
