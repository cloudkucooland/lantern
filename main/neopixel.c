#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include "esp_log.h"
#include "driver/gpio.h"
#include "neopixel.h"
#include "esp_random.h"

#include "sdkconfig.h"
#include "lantern.h"


static const char *TAG = "neopixel";

static inline int min(int a, int b) {
  if (a < b) return a;
  return b;
}

static uint32_t brightness = 1;

void start_neopixel(void *unused) {
   int32_t rnd;
   tNeopixelContext ctx;
   tNeopixel pixel[PIXEL_COUNT];

   ESP_LOGI(TAG, "starting neopixel");
   ctx = neopixel_Init_RGBW(PIXEL_COUNT, NEOPIXEL_PIN);
   assert(ctx);

   for(int i = 0; i < PIXEL_COUNT; i++) {
     pixel[i].index = i;
     pixel[i].rgb = NP_RGBW(0,0,0,0);
   }
   neopixel_SetPixel(ctx, pixel, PIXEL_COUNT);

   while (brightness != 0) {
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
   ESP_LOGI(TAG, "stopping neopixel");
   for(int i = 0; i < PIXEL_COUNT; i++) {
      pixel[i].rgb = NP_RGBW(0,0,0,0);
   }
   neopixel_SetPixel(ctx, pixel, PIXEL_COUNT);
   neopixel_Deinit(ctx);
   vTaskDelete(NULL);
}

void set_brightness(int b) {
  if (brightness == 0 && b != 0) {
    brightness = b;
    xTaskCreate(start_neopixel, "start_neopixel", 2048, NULL, tskIDLE_PRIORITY, NULL);
  }

  brightness = b; // if == 0 will shut down the loop
}

int get_brightness(void) {
  return brightness;
}
