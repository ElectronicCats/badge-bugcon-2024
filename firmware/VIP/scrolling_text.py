from kb_module import set_input_cb
from screen import get_screen

import displayio
from adafruit_display_text import label
import terminalio

class ScrollingText:
    def __init__(self, text, exit_cb, max_char_num = 12):
        set_input_cb(self.input_cb)
        self.exit_cb = exit_cb
        self.max_char_num = max_char_num
        self.text_arr = self.split_text(text)
        self.lines_num = len(self.text_arr)
        self.display = get_screen()
        self.main = displayio.Group()
        self.main.append(displayio.Group())
        self.display.root_group = self.main
        self.current_line = 0
        self.display_text()
    
    def split_text(self, text):
        words = text.split()
        lines = []
        current_line = ""
        
        for word in words:
            if len(current_line) + len(word) + 1 > self.max_char_num:
                if current_line:
                    lines.append(current_line)
                current_line = word
            else:
                if current_line:
                    current_line += " " + word
                else:
                    current_line = word
        if current_line:
            lines.append(current_line)
        
        return lines
    
    def display_text(self):
        text_group = displayio.Group()
        self.main.pop(0)
        
        for i in range(0,9):
            if(i-4+self.current_line < 0 or i-4+self.current_line >= self.lines_num):
                continue
            text = self.text_arr[i-4+self.current_line]
            sc = (i//2) + 1 if i < 4 else (8-i)//2+1
            y = (i*32) + 8
            text_area = label.Label(terminalio.FONT, text=text, color=0xFFFFFF,anchor_point = (0.5, 0.5),anchored_position = (120,y),scale = sc)
            text_group.append(text_area)
            
        self.main.append(text_group)
        
    def input_cb(self, event):
        if event.pressed:
            if event.key_number == 0: # LEFT
                if self.exit_cb:
                    self.exit_cb()
            elif event.key_number == 1:# RIGHT
                pass
            elif event.key_number == 2:# UP
                self.current_line = self.current_line - 1 if self.current_line > 0 else self.lines_num - 1
                self.display_text()
            elif event.key_number == 3:# DOWN
                self.current_line = self.current_line + 1 if self.current_line < self.lines_num - 1 else 0
                self.display_text()
