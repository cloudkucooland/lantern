void start_neopixel(void *);
void set_brightness(int);
int get_brightness(void);
void start_buttonread(void *);

#define PIXEL_COUNT 8 
#define NEOPIXEL_PIN GPIO_NUM_7

#define BUTTON_IO_NUM           GPIO_NUM_4 // GPIO number for the button
#define BUTTON_ACTIVE_LEVEL     0 // Active level for the button (0 for active low, 1 for active high)

