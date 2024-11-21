import time
import board
import math
import busio
import terminalio
import displayio
import adafruit_imageload
import asyncio

from screen import get_screen
from kb_module import set_input_cb

# A list of all the BMP images you want displayed, in order
#
# https://cloudconvert.com/png-to-bmp
# convert to bmp -resize 240x240
img_filenames = ( "/imgs/BADGE-BUGCON-02.bmp",
                  "/imgs/BADGE-BUGCON-03.bmp",
                  "/imgs/BADGE-BUGCON-07.bmp",
                  "/imgs/BADGE-BUGCON-01.bmp",
                  "/imgs/BADGE-BUGCON-06.bmp",
                  "/imgs/BADGE-BUGCON-04.bmp",             
                  "/imgs/BADGE-BUGCON-05.bmp",
                  )

img_time = 5
menu_cb = None
task = None

class Gallery:
    def __init__(self,img_time = 5):
        self.display = get_screen()
        self.img_filenames = img_filenames
        self.idx = 0
        self.img_filename = img_filenames[self.idx]
        self.img_bitmap = displayio.OnDiskBitmap(open(self.img_filename, "rb"))
        self.img_palette = displayio.ColorConverter()
        self.img_tilegrid = displayio.TileGrid(self.img_bitmap, pixel_shader=self.img_palette)
        self.main = displayio.Group()
        self.display.root_group = self.main
        self.img_time = img_time
        self.main.append(self.img_tilegrid)
        
    def next_image(self):
        self.main.pop()
        self.img_filename = self.img_filenames[self.idx]
        self.img_bitmap = displayio.OnDiskBitmap(open(self.img_filename, "rb"))
        self.img_palette = displayio.ColorConverter()
        self.img_tilegrid = displayio.TileGrid(self.img_bitmap, pixel_shader=self.img_palette)
        self.main.append(self.img_tilegrid)
        self.idx = 0 if self.idx >= len(img_filenames)-1 else self.idx + 1

async def gallery_task():
    gallery = Gallery(img_time)
    while True:
        await asyncio.sleep(gallery.img_time)
        gallery.next_image()

def gallery_init(cb):
    global task,menu_cb
    menu_cb = cb
    set_input_cb(input_cb)
    if task == None:
        task = asyncio.create_task(gallery_task())

def gallery_deinit():
    global task,menu_cb
    if task:
        task.cancel()
    task = None
    if menu_cb:
        menu_cb()
        
def input_cb(event):
    if event.pressed:
        if event.key_number == 0: # LEFT
            gallery_deinit()
        elif event.key_number == 1:# RIGHT
            pass
        elif event.key_number == 2:# UP
            pass
        elif event.key_number == 3:# DOWN
            pass
