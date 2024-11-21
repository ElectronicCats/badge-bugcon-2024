import board
import random
import time
import pwmio
from digitalio import DigitalInOut, Direction
import microcontroller

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
        self.init()
    
    def init(self, pin_red=board.IO5, pin_green=board.IO3, pin_blue=microcontroller.pin.GPIO11, pin_com_list=[microcontroller.pin.GPIO15, board.IO10, microcontroller.pin.GPIO23, board.IO1, microcontroller.pin.GPIO22]):
        
        self.red = pwmio.PWMOut(pin_red, frequency=1000, duty_cycle=0)
        self.green = pwmio.PWMOut(pin_green, frequency=1000, duty_cycle=0)
        self.blue = pwmio.PWMOut(pin_blue, frequency=1000, duty_cycle=0)

        self.com = [DigitalInOut(pin) for pin in pin_com_list]
        for pin in self.com:
            pin.direction = Direction.OUTPUT
            pin.value = False

        self.set_color([0, 0, 0])
        self.turn_off_all()

    def set_color(self, rgb):
        self.red.duty_cycle = 65535 - rgb[0]
        self.green.duty_cycle = 65535 - rgb[1]
        self.blue.duty_cycle = 65535 - rgb[2]

    def turn_off(self, led):
        if 0 <= led < len(self.com):
            self.com[led].value = False

    def turn_on(self, led):
        if 0 <= led < len(self.com):
            self.com[led].value = True

    def turn_on_all(self):
        for pin in self.com:
            pin.value = True
    
    def turn_off_all(self):
        for pin in self.com:
            pin.value = False
            
    def get_random_color(self):
        r = random.randint(45000, 50000)
        g = random.randint(0, r // 12)
        b = random.randint(0, g // 2) 
        return [r, g, b]
    
    def launch_particles(self, num, delay):
        for _ in range(num):
            for j in range(5):
                self.turn_off_all()
                self.set_color(self.get_random_color())
                self.turn_on(j)
                time.sleep(delay)
        self.turn_off_all()
    
    def launch_animation(self):
        self.launch_particles(1, 0.04)
        time.sleep(0.4)
        self.launch_particles(2, 0.03)
        time.sleep(0.3)
        self.launch_particles(5, 0.03)
        time.sleep(0.3)
        self.launch_particles(15, 0.02)
        self.turn_off_all()

def get_leds_obj():
    global leds_obj
    return leds_obj

def leds_init():
    global leds_obj
    leds_obj = RGBLEDS()
    leds_obj.launch_animation()

if __name__ == "__main__":
    leds_init()
