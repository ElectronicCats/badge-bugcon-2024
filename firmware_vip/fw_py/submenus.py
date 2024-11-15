import machine
import time
import keyboard_module
from keyboard_module import btn
import screennorm
import gc9a01

import romans as font6
import romant as font5
import romanc as font4
import italicc as font3
import italict as font2
import romand as font1

MAX_OPTIONS_NUM = 3
class GeneralSubMenu:
    def __init__(self, options, select_cb, exit_cb):
        self.screen = screennorm.get_screen()
        self.options = options
        self.options_count = len(options)
        self.selected_option = 0
        self.select_cb = select_cb
        self.exit_cb = exit_cb
        self.items_offset = 0
        keyboard_module.register_button_cb(self.handle_input)
        self.list_submenu_options()
        
    def list_submenu_options(self):                
        self.screen.clear(0)
        
        text = self.options[self.selected_option-1 if self.selected_option != 0 else self.options_count-1]
        self.screen.text_font(font4, 40, 40, text, fg_color = gc9a01.color565(45, 217, 80), scale =0.55)
        
        text = self.options[self.selected_option]
        self.screen.text_font(font2, 5, 116, text, fg_color = gc9a01.color565(120,247,180), scale = 0.75)
 
        text = self.options[self.selected_option+1 if self.selected_option != self.options_count-1 else 0]
        self.screen.text_font(font4, 40, 240-40-8, text, fg_color = gc9a01.color565(45, 217, 80), scale =0.55)
        

    def handle_input(self, btn_name):
        if btn_name == btn.BUTTON_LEFT:
            if self.exit_cb:
                self.exit_cb()
        elif btn_name == btn.BUTTON_RIGHT:
            if self.select_cb:
                self.select_cb(self.selected_option)
        elif btn_name == btn.BUTTON_UP:
            self.selected_option = self.selected_option - 1 if self.selected_option > 0 else self.options_count - 1
            self.list_submenu_options()
        elif btn_name == btn.BUTTON_DOWN:
            self.selected_option = self.selected_option + 1 if self.selected_option < self.options_count - 1 else 0
            self.list_submenu_options()