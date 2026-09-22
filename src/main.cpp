

#include "Arduino_GFX_Library.h"
#include "HWCDC.h"
#include "SensorPCF85063.hpp"
#include "TouchDrvGT911.hpp"
#include "WS_CH32_IO.h"
#include "lvgl.h"
#include <SPI.h>

#include "canbus.h"
#include "driver/twai.h"

#include "ui/actions.h"
#include "ui/ui.h"
#include "ui/vars.h"

#include "main.h"

#define TOUCHSCREEN_LOG 0

void tick_en_cours_logic(void);
void application_service(void);

#define FOREVER 1

#define EXAMPLE_LVGL_TICK_PERIOD_MS 2
#define SCREEN_WIDTH 480
#define SCREEN_HEIGHT 480
#define DEFAULT_I2C_SDA (WS_CH32_IO::DEFAULT_I2C_SDA)
#define DEFAULT_I2C_SCL (WS_CH32_IO::DEFAULT_I2C_SCL)

HWCDC USBSerial;
SensorPCF85063 rtc;
TouchDrvGT911 GT911;

uint8_t gt911_i2c_addr = 0;
uint32_t screen_width;
uint32_t screen_height;
lv_obj_t *label; // Global label object
uint32_t lastMillis;

static lv_disp_draw_buf_t draw_buf;
static lv_color_t buf[SCREEN_WIDTH * SCREEN_HEIGHT / 10];

Arduino_DataBus *bus =
    new Arduino_SWSPI(GFX_NOT_DEFINED /* DC */, 42 /* CS */, 2 /* SCK */,
                      1 /* MOSI */, GFX_NOT_DEFINED /* MISO */);

Arduino_ESP32RGBPanel *rgbpanel = new Arduino_ESP32RGBPanel(
    40 /* DE */, 39 /* VSYNC */, 38 /* HSYNC */, 41 /* PCLK */, 46 /* R0 */,
    3 /* R1 */, 8 /* R2 */, 18 /* R3 */, 17 /* R4 */, 14 /* G0 */, 13 /* G1 */,
    12 /* G2 */, 11 /* G3 */, 10 /* G4 */, 9 /* G5 */, 5 /* B0 */, 45 /* B1 */,
    48 /* B2 */, 47 /* B3 */, 21 /* B4 */, 1 /* hsync_polarity */,
    10 /* hsync_front_porch */, 8 /* hsync_pulse_width */,
    50 /* hsync_back_porch */, 1 /* vsync_polarity */,
    10 /* vsync_front_porch */, 8 /* vsync_pulse_width */,
    20 /* vsync_back_porch */);

Arduino_RGB_Display *gfx = new Arduino_RGB_Display(
    SCREEN_WIDTH, SCREEN_HEIGHT, rgbpanel, 2 /* rotation */,
    true /* auto_flush */, bus, GFX_NOT_DEFINED /* RST */,
    st7701_type1_init_operations, sizeof(st7701_type1_init_operations));

#if LV_USE_LOG != 0
/* Serial debugging */
void my_print(const char *buf) {
  Serial.printf(buf);
  Serial.flush();
}
#endif

/* Display flushing */
void my_disp_flush(lv_disp_drv_t *disp, const lv_area_t *area,
                   lv_color_t *color_p) {
  uint32_t w = (area->x2 - area->x1 + 1);
  uint32_t h = (area->y2 - area->y1 + 1);

#if (LV_COLOR_16_SWAP != 0)
  gfx->draw16bitBeRGBBitmap(area->x1, area->y1, (uint16_t *)&color_p->full, w,
                            h);
#else
  gfx->draw16bitRGBBitmap(area->x1, area->y1, (uint16_t *)&color_p->full, w, h);
#endif

  lv_disp_flush_ready(disp);
}

/**
 *
 */
void example_increase_lvgl_tick(void *arg) {
  /* Tell LVGL how many milliseconds has elapsed */
  lv_tick_inc(EXAMPLE_LVGL_TICK_PERIOD_MS);
}

/**
 *
 */
static uint8_t count = 0;
void example_increase_reboot(void *arg) {
  count++;
  if (count == 30) {
    esp_restart();
  }
}

/**
 * @brief Read the touchpad
 *
 *
 */
void my_touchpad_read(lv_indev_drv_t *indev_driver, lv_indev_data_t *data) {
  TouchPoints points = GT911.getTouchPoints();
  uint8_t touched = points.getPointCount();

  if (touched > 0) {
    for (int i = 0; i < touched; ++i) {
      TouchPoint tp = points.getPoint(i);
      int16_t touchX = tp.x;
      int16_t touchY = tp.y;
      switch (gfx->getRotation()) {
      case 0:
        break;
      case 1:
        touchX = tp.y;
        touchY = gfx->height() - tp.x;
        break;
      case 2:
        touchX = gfx->width() - tp.x;
        touchY = gfx->height() - tp.y;
        break;
      case 3:
        touchX = gfx->width() - tp.y;
        touchY = tp.x;
        break;
      }
      data->state = LV_INDEV_STATE_PR;

      /*Set the coordinates*/
      data->point.x = touchX;
      data->point.y = touchY;

#if TOUCHSCREEN_LOG == 1
      USBSerial.print(millis());
      USBSerial.print(" ms, ");
      USBSerial.print("data X : ");
      USBSerial.print(touchX);
      USBSerial.print(" data Y : ");
      USBSerial.println(touchY);
      USBSerial.println();
#endif
      // gfx->fillCircle(touchX, touchY, 5, BLUE);
    }
  } else {
    data->state = LV_INDEV_STATE_REL;
  }
}

/**
 *
 */
void i2c_scan() {
  USBSerial.println("Scanning I2C bus...");
  byte error, address;
  int nDevices = 0;

  for (address = 1; address < 127; address++) {
    Wire.beginTransmission(address);
    error = Wire.endTransmission();

    if (error == 0) {
      USBSerial.print("I2C device found at address 0x");
      if (address < 16) {
        USBSerial.print("0");
      }
      USBSerial.println(address, HEX);
      nDevices++;

      if (address == GT911_SLAVE_ADDRESS_L ||
          address == GT911_SLAVE_ADDRESS_H) {
        gt911_i2c_addr = address;
        USBSerial.print("Found GT911 candidate address: 0x");
        USBSerial.println(address, HEX);
      }
    } else if (error == 4) {
    }
  }

  if (nDevices == 0) {
    USBSerial.println("No I2C devices found");
  } else {
    USBSerial.println("I2C scan completed");
  }
}

/**
 *
 */
bool init_gt911_with_probe(int sda_pin, int scl_pin) {
  Wire.begin(sda_pin, scl_pin);
  delay(100);

  i2c_scan();

  if (gt911_i2c_addr == 0) {
    USBSerial.println("GT911 not found in I2C scan");
    return false;
  }

  GT911.setPins(-1, -1);
  if (GT911.begin(Wire, gt911_i2c_addr, sda_pin, scl_pin)) {
    USBSerial.print("GT911 initialized successfully at address 0x");
    USBSerial.println(gt911_i2c_addr, HEX);
    return true;
  } else {
    USBSerial.print("Failed to initialize GT911 at address 0x");
    USBSerial.println(gt911_i2c_addr, HEX);
    return false;
  }
}

/**
 * @brief setup function
 *
 * no param, no return
 *
 */
void setup(void) {
  USBSerial.begin(115200); /* prepare for possible serial debug */
  while (millis() < 5000)
    ; // pour permettre l'affichage sur l'USB

  // Wire.begin(DEFAULT_I2C_SDA, DEFAULT_I2C_SCL);
  if (!WS_CH32_IO::begin(Wire, DEFAULT_I2C_SDA, DEFAULT_I2C_SCL,
                         WS_CH32_IO::DEFAULT_I2C_FREQ, &USBSerial)) {
    USBSerial.println("CH32V003 IO expander init failed");
  } else {
    USBSerial.println("CH32V003 IO expander ==> Ok");
  }

  if (!init_gt911_with_probe(DEFAULT_I2C_SDA, DEFAULT_I2C_SCL)) {
    while (1) {
      USBSerial.println("Failed to find GT911 - check your wiring!");
      delay(1000);
    }
  }

  GT911.setHomeButtonCallback(
      [](void *user_data) { USBSerial.println("Home button pressed!"); }, NULL);
  // @todo phifo : à supprimer ?

  GT911.setMaxTouchPoint(1); // max is 5

  CANBUS_setup();

  USBSerial.println("End of hardware setup");

  gfx->begin();
  screen_width = gfx->width();
  screen_height = gfx->height();

  lv_init();
  lv_color_t *buf1 = (lv_color_t *)heap_caps_malloc(
      screen_width * screen_height / 4 * sizeof(lv_color_t), MALLOC_CAP_DMA);
  lv_color_t *buf2 = (lv_color_t *)heap_caps_malloc(
      screen_width * screen_height / 4 * sizeof(lv_color_t), MALLOC_CAP_DMA);

  String LVGL_Arduino = "LVGL version : ";
  LVGL_Arduino += String('V') + lv_version_major() + "." + lv_version_minor() +
                  "." + lv_version_patch();

  USBSerial.println(LVGL_Arduino);

#if LV_USE_LOG != 0
  lv_log_register_print_cb(
      my_print); /* register print function for debugging */
#endif

  lv_disp_draw_buf_init(&draw_buf, buf1, buf2,
                        screen_width * screen_height / 4);

  // Initialize the display
  static lv_disp_drv_t disp_drv;
  lv_disp_drv_init(&disp_drv);
  // Change the following line to your display resolution
  disp_drv.hor_res = screen_width;
  disp_drv.ver_res = screen_height;
  disp_drv.flush_cb = my_disp_flush;
  disp_drv.draw_buf = &draw_buf;
  disp_drv.sw_rotate = 1; // add for rotation
  // disp_drv.rotated = LV_DISP_ROT_90;
  lv_disp_drv_register(&disp_drv);

  // Initialize the input device driver
  static lv_indev_drv_t indev_drv;
  lv_indev_drv_init(&indev_drv);
  indev_drv.type = LV_INDEV_TYPE_POINTER;
  indev_drv.read_cb = my_touchpad_read;
  lv_indev_drv_register(&indev_drv);

  const esp_timer_create_args_t lvgl_tick_timer_args = {
      .callback = &example_increase_lvgl_tick, .name = "lvgl_tick"};

  const esp_timer_create_args_t reboot_timer_args = {
      .callback = &example_increase_reboot, .name = "reboot"};

  esp_timer_handle_t lvgl_tick_timer = NULL;
  esp_timer_create(&lvgl_tick_timer_args, &lvgl_tick_timer);
  esp_timer_start_periodic(lvgl_tick_timer, EXAMPLE_LVGL_TICK_PERIOD_MS * 1000);

  ui_init();

  // --- Charge l'historique depuis la mémoire Flash ---
  // @todo phifo charger_historique();
  USBSerial.println("----- Start application : Testeur de semelle ! -----\n");
}

/**
 * @brief main loop
 *
 * no params, never return
 *
 */
void loop(void) {
  while (FOREVER) {
    // moteur graphique LVGL (animations, clics)
    lv_timer_handler();

    // Application / machine à états
    application_service();

    // 2. Fait tourner la logique interne générée par EEZ Studio
    // ui_tick();

    // 3. Fait tourner TA logique (chronomètre, barre de progression, textes)
    // tick_en_cours_logic();

    delay(5);
  }
}