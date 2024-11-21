import time
import board
import math
import busio
import displayio
import gc9a01

class screen:
    def __init__(self):
        displayio.release_displays()
        
        tft0_clk  = board.IO21
        tft0_mosi = board.IO19
        tft_L0_dc   = board.IO2
        tft_L0_cs   = board.IO4
        spi = busio.SPI(clock=tft0_clk, MOSI=tft0_mosi)

        display_bus = displayio.FourWire(spi, command=tft_L0_dc, chip_select=tft_L0_cs)
        self.display = gc9a01.GC9A01(display_bus, width=240, height=240, rotation=270)

def get_screen():
    global _screen
    return _screen.display

def screen_init():
    global _screen
    _screen=screen()