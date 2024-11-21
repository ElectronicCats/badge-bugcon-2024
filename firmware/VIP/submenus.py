from kb_module import set_input_cb
from screen import get_screen

import displayio
from adafruit_display_text import label
import terminalio

MAX_OPTIONS_NUM = 3
class submenu:
    def __init__(self, options, selected_option,select_cb, exit_cb):
        self.display = get_screen()
        self.options = options
        self.options_count = len(options)
        self.selected_option = selected_option
        self.select_cb = select_cb
        self.exit_cb = exit_cb
        self.items_offset = 0
        set_input_cb(self.input_cb)
        self.list_submenu_options()
    
    def list_submenu_options(self):
        main = displayio.Group()
        self.display.root_group = main
        
        text = self.options[self.selected_option-1 if self.selected_option != 0 else self.options_count-1]
        text_area1 = label.Label(terminalio.FONT, text=text, color=0xFFFFFF)
        text_area1.anchor_point = (0.5, 0.5)
        text_area1.anchored_position = (120,60)
        text_area1.scale = 2
        text_group1 = displayio.Group()
        text_group1.append(text_area1)

        text = text = self.options[self.selected_option]
        text_area2 = label.Label(terminalio.FONT, text=text, color=0xFFFFFF)
        text_area2.anchor_point = (0.5, 0.5)
        text_area2.anchored_position = (120,120)
        text_area2.scale = 3
        text_group2 = displayio.Group()
        text_group2.append(text_area2)
        
        text = text = self.options[self.selected_option+1 if self.selected_option != self.options_count-1 else 0]
        text_area3 = label.Label(terminalio.FONT, text=text, color=0xFFFFFF)
        text_area3.anchor_point = (0.5, 0.5)
        text_area3.anchored_position = (120,180)
        text_area3.scale = 2
        text_group3 = displayio.Group()
        text_group3.append(text_area3) 
        
        main.append(text_group1)
        main.append(text_group2)
        main.append(text_group3)

    def input_cb(self, event):
        if event.pressed:
            if event.key_number == 0: # LEFT
                if self.exit_cb:
                    self.exit_cb()
            elif event.key_number == 1:# RIGHT
                if self.select_cb:
                    self.select_cb(self.selected_option)
            elif event.key_number == 2:# UP
                self.selected_option = self.selected_option - 1 if self.selected_option > 0 else self.options_count - 1
                self.list_submenu_options()
            elif event.key_number == 3:# DOWN
                self.selected_option = self.selected_option + 1 if self.selected_option < self.options_count - 1 else 0
                self.list_submenu_options()