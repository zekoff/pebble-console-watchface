#include <pebble.h>
#include "main.h"
#define KEY_LOCATION 0

// BEGIN AUTO-GENERATED UI CODE; DO NOT MODIFY
static Window *s_window;
static GFont s_res_roboto_condensed_21;
static GFont s_res_bitham_42_medium_numbers;
static GFont s_res_gothic_18_bold;
static GFont s_res_gothic_14;
static TextLayer *s_textlayer_gmt_day;
static TextLayer *s_textlayer_gmt_time;
static TextLayer *s_textlayer_hsv_time;
static TextLayer *s_textlayer_iss_location;

static void initialise_ui(void) {
  s_window = window_create();
  #ifndef PBL_SDK_3
    window_set_fullscreen(s_window, true);
  #endif
  
  s_res_roboto_condensed_21 = fonts_get_system_font(FONT_KEY_ROBOTO_CONDENSED_21);
  s_res_bitham_42_medium_numbers = fonts_get_system_font(FONT_KEY_BITHAM_42_MEDIUM_NUMBERS);
  s_res_gothic_18_bold = fonts_get_system_font(FONT_KEY_GOTHIC_18_BOLD);
  s_res_gothic_14 = fonts_get_system_font(FONT_KEY_GOTHIC_14);
  // s_textlayer_gmt_day
  s_textlayer_gmt_day = text_layer_create(GRect(21, 7, 100, 30));
  text_layer_set_background_color(s_textlayer_gmt_day, GColorClear);
  text_layer_set_text(s_textlayer_gmt_day, "GMT 123");
  text_layer_set_text_alignment(s_textlayer_gmt_day, GTextAlignmentCenter);
  text_layer_set_font(s_textlayer_gmt_day, s_res_roboto_condensed_21);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_textlayer_gmt_day);
  
  // s_textlayer_gmt_time
  s_textlayer_gmt_time = text_layer_create(GRect(11, 26, 120, 54));
  text_layer_set_background_color(s_textlayer_gmt_time, GColorClear);
  text_layer_set_text(s_textlayer_gmt_time, "00:00");
  text_layer_set_text_alignment(s_textlayer_gmt_time, GTextAlignmentCenter);
  text_layer_set_font(s_textlayer_gmt_time, s_res_bitham_42_medium_numbers);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_textlayer_gmt_time);
  
  // s_textlayer_hsv_time
  s_textlayer_hsv_time = text_layer_create(GRect(20, 89, 100, 34));
  text_layer_set_background_color(s_textlayer_hsv_time, GColorClear);
  text_layer_set_text(s_textlayer_hsv_time, "HSV 00:00");
  text_layer_set_text_alignment(s_textlayer_hsv_time, GTextAlignmentCenter);
  text_layer_set_font(s_textlayer_hsv_time, s_res_gothic_18_bold);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_textlayer_hsv_time);
  
  // s_textlayer_iss_location
  s_textlayer_iss_location = text_layer_create(GRect(6, 142, 131, 20));
  text_layer_set_text(s_textlayer_iss_location, "ISS Location");
  text_layer_set_text_alignment(s_textlayer_iss_location, GTextAlignmentCenter);
  text_layer_set_font(s_textlayer_iss_location, s_res_gothic_14);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_textlayer_iss_location);
}

static void destroy_ui(void) {
  window_destroy(s_window);
  text_layer_destroy(s_textlayer_gmt_day);
  text_layer_destroy(s_textlayer_gmt_time);
  text_layer_destroy(s_textlayer_hsv_time);
  text_layer_destroy(s_textlayer_iss_location);
}
// END AUTO-GENERATED UI CODE

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
  static char hsv_buffer[12];
  strftime(hsv_buffer, sizeof(hsv_buffer), "HSV %I:%M", tick_time);
  text_layer_set_text(s_textlayer_hsv_time, hsv_buffer);
  static char day_buffer[10];
  snprintf(day_buffer, sizeof(day_buffer), "GMT %d", tick_time->tm_yday + 1);
  text_layer_set_text(s_textlayer_gmt_day, day_buffer);
}

static void tick_handler(struct tm *tick_time, TimeUnits units_changed) {
  update_time();
  if (tick_time->tm_min % 5 == 0)
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