#include <pebble.h>
#include "main.h"

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
  window_set_background_color(s_window, GColorClear);
  #ifndef PBL_SDK_3
    window_set_fullscreen(s_window, true);
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
  app_event_loop();
  hide_main();
  return 0;
}