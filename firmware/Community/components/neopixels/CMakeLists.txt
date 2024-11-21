idf_component_register(SRCS "neopixels_module.c" "neopixels_events.c"
                       INCLUDE_DIRS "."
                       REQUIRES driver esp_timer led_strip)
