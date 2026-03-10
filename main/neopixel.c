#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include "esp_log.h"
#include "driver/gpio.h"
#include "neopixel.h"

#define PIXEL_COUNT 8 
#define NEOPIXEL_PIN GPIO_NUM_7

tNeopixelContext ctx;

static void np_alloff(void);

void start_neopixel(void) {
   ctx = neopixel_Init_RGBW(PIXEL_COUNT, NEOPIXEL_PIN);
   assert(ctx);

   // RGBW test on each pixel
   tNeopixel pixel[] =
   {
       { 0, NP_RGBW(50,0,0,0) }, /* red */
       { 0, NP_RGBW(0,50,0,0) }, /* green */
       { 0, NP_RGBW(0,0,50,0) }, /* blue */
       { 0, NP_RGBW(0,0,0,50) }, /* white */
       { 0, NP_RGBW(0,0,0,0) },  /* off */
   };

   for (int p = 0; p < PIXEL_COUNT; p++) {
      for(int j = 0; j < 5; j++) {
         neopixel_SetPixel(ctx, &pixel[j], 1);
         pixel[j].index++;
         vTaskDelay(pdMS_TO_TICKS(200));
      }
   }

   // pinwheel startup sequence
   for(int i = 0; i < 500 * PIXEL_COUNT; ++i) {
      tNeopixel pixel[] = {
          { (i)   % PIXEL_COUNT, NP_RGBW(0, 0, 0, 0) },
          { (i+3) % PIXEL_COUNT, NP_RGBW(0, 0, 0, 50) },
      };
      neopixel_SetPixel(ctx, pixel, 2);
      vTaskDelay(pdMS_TO_TICKS(50));
   }

   np_alloff();

   // neopixel_Deinit(ctx);
}

static void np_alloff(void) {
   for (int p = 0; p < PIXEL_COUNT; p++) {
     tNeopixel pixel = {p, NP_RGBW(0,0,0,0)};
     neopixel_SetPixel(ctx, &pixel, 1);
   }
}
