#include <pebble.h>
#include "main.h"
#define KEY_LOCATION 0

// BEGIN AUTO-GENERATED UI CODE; DO NOT MODIFY
static Window *s_window;
static GFont s_res_roboto_condensed_21;
static GFont s_res_bitham_42_medium_numbers;
static GFont s_res_gothic_14;
static TextLayer *s_textlayer_gmt_label;
static TextLayer *s_timelayer_gmt;
static TextLayer *s_timelayer_hsv;
static TextLayer *s_textlayer_hsv_label;
static TextLayer *s_textlayer_location;

static void initialise_ui(void) {
  s_window = window_create();
  #ifndef PBL_SDK_3
    window_set_fullscreen(s_window, 0);
  #endif
  
  s_res_roboto_condensed_21 = fonts_get_system_font(FONT_KEY_ROBOTO_CONDENSED_21);
  s_res_bitham_42_medium_numbers = fonts_get_system_font(FONT_KEY_BITHAM_42_MEDIUM_NUMBERS);
  s_res_gothic_14 = fonts_get_system_font(FONT_KEY_GOTHIC_14);
  // s_textlayer_gmt_label
  s_textlayer_gmt_label = text_layer_create(GRect(20, 5, 100, 30));
  text_layer_set_background_color(s_textlayer_gmt_label, GColorClear);
  text_layer_set_text(s_textlayer_gmt_label, "GMT");
  text_layer_set_text_alignment(s_textlayer_gmt_label, GTextAlignmentRight);
  text_layer_set_font(s_textlayer_gmt_label, s_res_roboto_condensed_21);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_textlayer_gmt_label);
  
  // s_timelayer_gmt
  s_timelayer_gmt = text_layer_create(GRect(10, 20, 120, 54));
  text_layer_set_background_color(s_timelayer_gmt, GColorClear);
  text_layer_set_text(s_timelayer_gmt, "00:00");
  text_layer_set_text_alignment(s_timelayer_gmt, GTextAlignmentCenter);
  text_layer_set_font(s_timelayer_gmt, s_res_bitham_42_medium_numbers);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_timelayer_gmt);
  
  // s_timelayer_hsv
  s_timelayer_hsv = text_layer_create(GRect(20, 89, 100, 34));
  text_layer_set_background_color(s_timelayer_hsv, GColorClear);
  text_layer_set_text(s_timelayer_hsv, "00:00");
  text_layer_set_text_alignment(s_timelayer_hsv, GTextAlignmentCenter);
  text_layer_set_font(s_timelayer_hsv, s_res_roboto_condensed_21);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_timelayer_hsv);
  
  // s_textlayer_hsv_label
  s_textlayer_hsv_label = text_layer_create(GRect(5, 89, 100, 21));
  text_layer_set_background_color(s_textlayer_hsv_label, GColorClear);
  text_layer_set_text(s_textlayer_hsv_label, "HSV");
  text_layer_set_font(s_textlayer_hsv_label, s_res_roboto_condensed_21);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_textlayer_hsv_label);
  
  // s_textlayer_location
  s_textlayer_location = text_layer_create(GRect(6, 142, 131, 20));
  text_layer_set_text(s_textlayer_location, "ISS Location");
  text_layer_set_text_alignment(s_textlayer_location, GTextAlignmentCenter);
  text_layer_set_font(s_textlayer_location, s_res_gothic_14);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_textlayer_location);
}

static void destroy_ui(void) {
  window_destroy(s_window);
  text_layer_destroy(s_textlayer_gmt_label);
  text_layer_destroy(s_timelayer_gmt);
  text_layer_destroy(s_timelayer_hsv);
  text_layer_destroy(s_textlayer_hsv_label);
  text_layer_destroy(s_textlayer_location);
}
// END AUTO-GENERATED UI CODE

static void handle_window_unload(Window* window) {
  destroy_ui();
}

static void inbox_received_callback(DictionaryIterator *iter, void *context) {
  APP_LOG(APP_LOG_LEVEL_INFO, "Message received from phone.");
  static char location_buffer[60];
  Tuple *location_tuple = dict_find(iter, KEY_LOCATION);
  if (location_tuple) {
    snprintf(location_buffer, sizeof(location_buffer), "%s", location_tuple->value->cstring);
    text_layer_set_text(s_textlayer_location, location_buffer);
  }
}

static void init_watchface(void) {
  app_message_register_inbox_received(inbox_received_callback);
  app_message_open(128, 128);
}

void show_main(void) {
  initialise_ui();
  window_set_window_handlers(s_window, (WindowHandlers) {
    .unload = handle_window_unload,
  });
  window_stack_push(s_window, true);
  init_watchface();
}

void hide_main(void) {
  window_stack_remove(s_window, true);
}

static void request_location_update(void) {
  DictionaryIterator *iter;
  app_message_outbox_begin(&iter);
  dict_write_uint8(iter, 0, 0);
  app_message_outbox_send();
}

int main(void) {
  show_main();
  app_event_loop();
  hide_main();
  return 0;
}