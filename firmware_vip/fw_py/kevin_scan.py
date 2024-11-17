from ibeacon_scan import BLEScan
import time
from keyboard_module import register_button_cb
from keyboard_module import btn
import screennorm
from leds import get_leds_obj

import _thread

from micropython import const

import romans as font6
import romant as font5
import romanc as font4
import italicc as font3
import italict as font2
import romand as font1

import random

scanner = None
rssi = 0
exit_cb = None

GREEN_DARK = const(0x01E0)
GREEN_MEDIUM = const(0x03E0)

SCANNER_COLOR = GREEN_MEDIUM
SCANNER_BG_COLOR = GREEN_DARK

exit_flag=False

def draw_radar():
    global exit_flag
    exit_flag=False
    while exit_flag==False:
        global rssi
        screen = screennorm.get_screen()
        screen.clear(SCANNER_BG_COLOR)
        tft = screen.get_tft()
        
        for i in range(0,6):
            tft.vline((i+1)*40,0,240,0)
            tft.hline(0,(i+1)*40,240,0)
        
        for i in range(0,3):
            tft.vline(119+i,0,85,SCANNER_COLOR)
            tft.vline(119+i,155,85,SCANNER_COLOR)
            tft.hline(0,119+i,85,SCANNER_COLOR)
            tft.hline(155,119+i,85,SCANNER_COLOR)
        
        screen.text_auto_scale_center(font5, str(rssi) if rssi else "???", 120, 0xffff)
        
        for i in range(0,3):
            if exit_flag:
                break
            tft.circle(120,120,49+i,SCANNER_COLOR)
            
        for i in range(0,3):
            if exit_flag:
                break
            tft.circle(120,120,79+i,SCANNER_COLOR)
        
        for i in range(0,3):
            if exit_flag:
                break
            tft.circle(120,120,109+i,SCANNER_COLOR)
        
        time.sleep(0.1)
    _thread.exit()
        
def on_kevin_found_cb(_rssi):
    global rssi
    rssi = _rssi
    

def handle_input(btn_name):
    if btn_name == btn.BUTTON_LEFT:
        global exit_flag
        exit_flag=True
        kevin_scan_deinit()
        exit_cb()
    elif btn_name == btn.BUTTON_RIGHT:
        pass
    elif btn_name == btn.BUTTON_UP:
        pass
    elif btn_name == btn.BUTTON_DOWN:
        pass

def kevin_scan_init(cb):
    global scanner, rssi, exit_cb
    leds_obj = get_leds_obj()
    leds_obj.start_animation()
    register_button_cb(handle_input)
    exit_cb = cb
    rssi = 0
    scanner = BLEScan(on_kevin_found_cb)
    scanner.scan()
    _thread.start_new_thread(draw_radar,())
    
def kevin_scan_deinit():
    leds_obj = get_leds_obj()
    leds_obj.stop_animation()
    global scanner
    scanner.deinit()