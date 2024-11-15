from machine import Pin, PWM
import time

class LEDS:
    LED1 = 0
    LED2 = 1
    LED3 = 2
    LED4 = 3
    LED5 = 4

class RGBLEDS:
    def __init__(self):
        self.red = None
        self.green = None
        self.blue = None
        self.com = []
    
    def init(self, pin_red=5, pin_green=3, pin_blue=11, pin_com_list=[15, 23, 10, 1, 22]):
        self.red = PWM(Pin(pin_red))
        self.green = PWM(Pin(pin_green))
        self.blue = PWM(Pin(pin_blue))
        
        self.com = [Pin(pin, Pin.OUT) for pin in pin_com_list]

        self.red.freq(1000)
        self.green.freq(1000)
        self.blue.freq(1000)

        self.set_color(0, 0, 0)
        
        for com_pin in self.com:
            com_pin.value(0)

    def set_color(self, red_value, green_value, blue_value):
        self.red.duty(1023 - red_value)
        self.green.duty(1023 - green_value)
        self.blue.duty(1023 - blue_value)

    def turn_off(self, led):
        if 0 <= led < len(self.com):
            self.com[led].value(0)

    def turn_on(self, led):
        if 0 <= led < len(self.com):
            self.com[led].value(1)

    def turn_on_all(self):
        for pin in self.com:
            pin.value(1)



    
