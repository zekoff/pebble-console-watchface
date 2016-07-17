#include <pebble.h>
#include "main.h"
#define KEY_LOCATION 0
#define KEY_VISIBILITY 1

// BEGIN AUTO-GENERATED UI CODE; DO NOT MODIFY
static Window *s_window;
static GBitmap *s_res_image_daytime_background;
static GBitmap *s_res_image_nighttime_background;
static GFont s_res_font_pragati_bold_24;
static GFont s_res_font_pragati_bold_72;
static GFont s_res_font_pragati_24;
static GFont s_res_font_teko_18;
static BitmapLayer *s_image_daytime;
static BitmapLayer *s_image_nighttime;
static TextLayer *s_textlayer_gmt_day;
static TextLayer *s_textlayer_gmt_time;
static TextLayer *s_textlayer_local_time;
static TextLayer *s_textlayer_iss_location;

static void initialise_ui(void) {
  s_window = window_create();
  #ifndef PBL_SDK_3
    window_set_fullscreen(s_window, true);
  #endif
  
  s_res_image_daytime_background = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_DAYTIME_BACKGROUND);
  s_res_image_nighttime_background = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_NIGHTTIME_BACKGROUND);
  s_res_font_pragati_bold_24 = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_PRAGATI_BOLD_24));
  s_res_font_pragati_bold_72 = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_PRAGATI_BOLD_72));
  s_res_font_pragati_24 = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_PRAGATI_24));
  s_res_font_teko_18 = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_TEKO_18));
  // s_image_daytime
  s_image_daytime = bitmap_layer_create(GRect(0, 0, 144, 168));
  bitmap_layer_set_bitmap(s_image_daytime, s_res_image_daytime_background);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_image_daytime);
  
  // s_image_nighttime
  s_image_nighttime = bitmap_layer_create(GRect(0, 0, 144, 168));
  bitmap_layer_set_bitmap(s_image_nighttime, s_res_image_nighttime_background);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_image_nighttime);
  
  // s_textlayer_gmt_day
  s_textlayer_gmt_day = text_layer_create(GRect(9, 0, 131, 30));
  text_layer_set_background_color(s_textlayer_gmt_day, GColorClear);
  text_layer_set_text(s_textlayer_gmt_day, "GMT 123");
  text_layer_set_text_alignment(s_textlayer_gmt_day, GTextAlignmentRight);
  text_layer_set_font(s_textlayer_gmt_day, s_res_font_pragati_bold_24);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_textlayer_gmt_day);
  
  // s_textlayer_gmt_time
  s_textlayer_gmt_time = text_layer_create(GRect(0, 2, 142, 74));
  text_layer_set_background_color(s_textlayer_gmt_time, GColorClear);
  text_layer_set_text(s_textlayer_gmt_time, "00:00");
  text_layer_set_text_alignment(s_textlayer_gmt_time, GTextAlignmentRight);
  text_layer_set_font(s_textlayer_gmt_time, s_res_font_pragati_bold_72);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_textlayer_gmt_time);
  
  // s_textlayer_local_time
  s_textlayer_local_time = text_layer_create(GRect(16, 71, 123, 25));
  text_layer_set_background_color(s_textlayer_local_time, GColorClear);
  text_layer_set_text(s_textlayer_local_time, "LOCAL 00:00");
  text_layer_set_text_alignment(s_textlayer_local_time, GTextAlignmentRight);
  text_layer_set_font(s_textlayer_local_time, s_res_font_pragati_24);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_textlayer_local_time);
  
  // s_textlayer_iss_location
  s_textlayer_iss_location = text_layer_create(GRect(2, 145, 140, 22));
  text_layer_set_background_color(s_textlayer_iss_location, GColorClear);
  text_layer_set_text(s_textlayer_iss_location, "ISS Location");
  text_layer_set_text_alignment(s_textlayer_iss_location, GTextAlignmentCenter);
  text_layer_set_font(s_textlayer_iss_location, s_res_font_teko_18);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_textlayer_iss_location);
}

static void destroy_ui(void) {
  window_destroy(s_window);
  bitmap_layer_destroy(s_image_daytime);
  bitmap_layer_destroy(s_image_nighttime);
  text_layer_destroy(s_textlayer_gmt_day);
  text_layer_destroy(s_textlayer_gmt_time);
  text_layer_destroy(s_textlayer_local_time);
  text_layer_destroy(s_textlayer_iss_location);
  gbitmap_destroy(s_res_image_daytime_background);
  gbitmap_destroy(s_res_image_nighttime_background);
  fonts_unload_custom_font(s_res_font_pragati_bold_24);
  fonts_unload_custom_font(s_res_font_pragati_bold_72);
  fonts_unload_custom_font(s_res_font_pragati_24);
  fonts_unload_custom_font(s_res_font_teko_18);
}
// END AUTO-GENERATED UI CODE

static void set_daytime() {
  layer_set_hidden(bitmap_layer_get_layer(s_image_nighttime), true);
  text_layer_set_text_color(s_textlayer_gmt_day, GColorBlack);
  text_layer_set_text_color(s_textlayer_gmt_time, GColorBlack);
  text_layer_set_text_color(s_textlayer_local_time, GColorBlack);
  APP_LOG(APP_LOG_LEVEL_INFO, "Set to daytime mode.");
}

static void set_nighttime() {
  layer_set_hidden(bitmap_layer_get_layer(s_image_nighttime), false);
  text_layer_set_text_color(s_textlayer_gmt_day, GColorWhite);
  text_layer_set_text_color(s_textlayer_gmt_time, GColorWhite);
  text_layer_set_text_color(s_textlayer_local_time, GColorWhite);
  APP_LOG(APP_LOG_LEVEL_INFO, "Set to nighttime mode.");
}

static void request_location_update(void) {
  DictionaryIterator *iter;
  app_message_outbox_begin(&iter);
  dict_write_uint8(iter, 0, 0);
  app_message_outbox_send();
}

static void update_time() {
  time_t temp = time(NULL);
  struct tm *tick_time = gmtime(&temp);
  static char gmt_buffer[8];
  strftime(gmt_buffer, sizeof(gmt_buffer), "%H:%M", tick_time);
  text_layer_set_text(s_textlayer_gmt_time, gmt_buffer);
  tick_time = localtime(&temp);
  static char local_buffer[12];
  strftime(local_buffer, sizeof(local_buffer), "LOCAL %H:%M", tick_time);
  text_layer_set_text(s_textlayer_local_time, local_buffer);
  static char day_buffer[10];
  snprintf(day_buffer, sizeof(day_buffer), "GMT %d", tick_time->tm_yday + 1);
  text_layer_set_text(s_textlayer_gmt_day, day_buffer);
}

static void tick_handler(struct tm *tick_time, TimeUnits units_changed) {
  update_time();
  request_location_update();
}

static void handle_window_unload(Window* window) {
  destroy_ui();
}

static void inbox_received_callback(DictionaryIterator *iter, void *context) {
  APP_LOG(APP_LOG_LEVEL_INFO, "Message received from phone.");
  static char location_buffer[24];
  Tuple *location_tuple = dict_find(iter, KEY_LOCATION);
  if (location_tuple) {
    snprintf(location_buffer, sizeof(location_buffer), "%s", location_tuple->value->cstring);
    text_layer_set_text(s_textlayer_iss_location, location_buffer);
  }
  Tuple *visibility_tuple = dict_find(iter, KEY_VISIBILITY);
  if (visibility_tuple) {
    if (strcmp("0", visibility_tuple->value->cstring) == 0)
      set_nighttime();
    else
      set_daytime();
  }
}

static void init_watchface(void) {
  tick_timer_service_subscribe(MINUTE_UNIT, tick_handler);
  update_time();
  app_message_register_inbox_received(inbox_received_callback);
  app_message_open(128, 128);
}

void show_main(void) {
  initialise_ui();
  window_set_window_handlers(s_window, (WindowHandlers) {
    .unload = handle_window_unload,
  });
  window_stack_push(s_window, true);
  set_nighttime();
}

void hide_main(void) {
  window_stack_remove(s_window, true);
}

int main(void) {
  show_main();
  init_watchface();
  app_event_loop();
  hide_main();
  return 0;
}