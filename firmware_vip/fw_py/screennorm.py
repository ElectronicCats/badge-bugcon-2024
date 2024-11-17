import gc9a01
from machine import Pin, SPI
import vga1_16x32 as font
import gc
import romant as deffont
import italict as font2
import math

class ScreenNorm:
    """
    A light wrapper around the gc9a01 screen.

    Attributes:
        _spi (SPI): The SPI interface.
        tft (gc9a01.GC9A01): The TFT display.
    """
    
    def _spi_init(self):
        self._spi = SPI(1, baudrate=40000000, sck=Pin(21), mosi=Pin(19))

    def __init__(self):
        """
        The constructor for ScreenNorm class.
        """
        
        self._spi_init()
        self.wake()

    def get_font(self):
        """
        Get the normal font
        
        Returns:
            font object
        """
        return font
    
    def get_vfont(self):
        """
        Get the default vector font (romans)
        """
        return deffont
    
    def wake(self):
        """
        Method to wake up the display.
        """
        self._spi_init()
        self.tft = gc9a01.GC9A01(self._spi, 240, 240,cs=Pin(4, Pin.OUT),dc=Pin(2, Pin.OUT),rotation=3)
        
        self.tft.init()
        self.tft.fill(0)
        self.text_auto_scale_center(font2,"launching...",120)

    def idle(self):
        """
        Method to get the display out of the way for another screen helper.
        """
        
        self._spi.deinit()
        self.spi=None
        self.tft=None
        gc.collect()

    def jpg(self,filename):
        """
        Method to show a jpg on the display.

        Args:
            filename (str): The name of the jpg file.
        """
        
        if self.tft!=None:
            #gc.collect()   
            self.tft.jpg(filename,0,0,1)

    def text(self,x,y,txt,fg_color=gc9a01.color565(45, 217, 80),bg_color=gc9a01.color565(0,25,10)):
        """
        Method to draw text on the display.

        Args:
            x (int): The x-coordinate of the top left corner of the text.
            y (int): The y-coordinate of the top left corner of the text.
            txt (str): The text to draw.
            fg_color (int): The foreground color. Default is gc9a01.color565(243,191,16).
            bg_color (int): The background color. Default is gc9a01.color565(26,26,26).
        """
        
        if self.tft!=None:
            self.tft.text(font,txt,x,y,fg_color,bg_color)

    def text_font(self,font,x,y,txt,fg_color=gc9a01.color565(45, 217, 80),scale=1.0):
        """
        Method to draw text with a font.
        
        Args:
            font (font or None): The font to use (or use default font)
            x,y (int): X and Y coordinate
            txt (str): String
            fg_color (int) Foreground color (note: no background color -- always transparent)
        """
        gc.collect()
        if self.tft!=None:
            if font==None:
                font=deffont
            self.tft.draw(font,txt,x,y,fg_color,scale)

    def clear(self,color=0):
        """
        Method to clear the display with a color.

        Args:
            color (int): The background color. Default is 0.
        """
        
        if self.tft!=None:
            self.tft.fill_rect(0,0,240,240,color)

    def pixel(self,x,y,color):
        """
        Method to set a pixel on the display.

        Args:
            x (int): The x-coordinate of the pixel.
            y (int): The y-coordinate of the pixel.
            color (int): The color of the pixel.
        """
        
        if self.tft!=None:
             self.tft.pixel(x,y,color)
    
    def get_tft(self):
        return self.tft
    
    def draw_len(self,font,txt,scale=1):
        return self.tft.draw_len(font,txt,scale)
        
    def get_max_text_width(self,y, center=(120, 120), radio=120):
        d_y = y - center[1]
        
        if abs(d_y) > radio:
            return 0
        
        width = 2 * math.sqrt(radio**2 - d_y**2)
        
        return width
        
    def get_txt_scale(self, font,txt,max_width = 230):
        txt_px_len = self.draw_len(font,txt,1)
        scale =  max_width / txt_px_len
        return min(max(scale,0.5),1)
    
    def get_x_txt_center(self,font,txt,scale=1):
        txt_px_len = self.draw_len(font,txt,scale)
        return int(120 - txt_px_len/2)

    def text_auto_scale_center(self,font, txt, y = 120, color = 0xffff):
        max_width = int(self.get_max_text_width(y)) - 20
        scale = self.get_txt_scale(font,txt,max_width)
        x = self.get_x_txt_center(font,txt,scale)
        self.text_font(font,x,y,txt,color,scale = scale)
    
def get_screen():
    """
    Function to get the one screen object.

    Returns:
        ScreenNorm: The screen object.
    """
    
    global _screen
    return _screen

def screen_init():
    global _screen
    _screen=ScreenNorm()