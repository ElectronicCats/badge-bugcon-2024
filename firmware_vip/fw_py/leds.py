from machine import Pin, PWM
import time

import random
import _thread

from micropython import const

LED1 = const(0)
LED2 = const(1)
LED3 = const(2)
LED4 = const(3)
LED5 = const(4)

class RGBLEDS:
    def __init__(self):
        self.red = None
        self.green = None
        self.blue = None
        self.com = []
        self.init()
    
    def init(self, pin_red=5, pin_green=3, pin_blue=11, pin_com_list=[15, 23, 10, 1, 22]):
        self.red = PWM(Pin(pin_red))
        self.green = PWM(Pin(pin_green))
        self.blue = PWM(Pin(pin_blue))
        
        self.com = [Pin(pin, Pin.OUT) for pin in pin_com_list]

        self.red.freq(1000)
        self.green.freq(1000)
        self.blue.freq(1000)

        self.set_color([0,0,0])
        
        for com_pin in self.com:
            com_pin.value(0)

    def set_color(self, rgb):
        self.red.duty(1023 - rgb[0])
        self.green.duty(1023 - rgb[1])
        self.blue.duty(1023 - rgb[2])

    def turn_off(self, led):
        if 0 <= led < len(self.com):
            self.com[led].value(0)

    def turn_on(self, led):
        if 0 <= led < len(self.com):
            self.com[led].value(1)

    def turn_on_all(self):
        for pin in self.com:
            pin.value(1)
    
    def turn_off_all(self):
        for pin in self.com:
            pin.value(0)
            
    def get_random_color(self):
        r = random.randint(600, 1023)
        g = random.randint(0, r//3)        
        b = random.randint(0, r // 4)
        return [r,g,b]
    
    def launch_particles(self, num, delay):
        for i in range(0,num):
            for j in range(0,5):
                    self.turn_off_all()
                    self.set_color(self.get_random_color())
                    self.turn_on(j)
                    time.sleep(delay)
        self.turn_off_all()
    
    def launch_animation(self):
        self.launch_particles(1,0.04)
        time.sleep(0.4)
        self.launch_particles(2,0.03)
        time.sleep(0.3)
        self.launch_particles(5,0.03)
        time.sleep(0.3)
        self.launch_particles(15,0.02)
        self.turn_off_all()
            
    def scanninig_animation(self):
        self.exit = False
        while self.exit == False:
            for i in range(0,5):
                self.turn_off_all()
                self.set_color(self.get_random_color())
                self.turn_on(i)
                time.sleep(0.5*(0 if self.exit else 1))
        self.turn_off_all()
        _thread.exit()
        
    def start_animation(self):
        _thread.start_new_thread(self.scanninig_animation,())
        
    def stop_animation(self):
        self.exit = True
    
def get_leds_obj():
    global leds_obj
    return leds_obj

def leds_init():
    global leds_obj
    leds_obj = RGBLEDS()
    leds_obj.launch_animation()

if __name__ == "__main__":
    leds_init()
    
