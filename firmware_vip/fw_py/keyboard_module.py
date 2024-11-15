import time
import machine
from machine import Timer

BUTTON_PINS = [0, 8, 18, 20]  # UP,RIGHT,DOWN,LEFT
ACTIVE_LEVEL = 0  # PULLUP
DEBOUNCE_TIME_MS = 50
TICKS_INTERVAL = 100

button_states = [None] * len(BUTTON_PINS)
last_button_states = [None] * len(BUTTON_PINS)
last_press_times = [0] * len(BUTTON_PINS)

buttons = [machine.Pin(pin, machine.Pin.IN, pull=machine.Pin.PULL_UP if ACTIVE_LEVEL == 0 else machine.Pin.PULL_DOWN) for pin in BUTTON_PINS]

button_cb = None

class btn:
    BUTTON_UP = 0
    BUTTON_RIGHT = 1
    BUTTON_DOWN = 2
    BUTTON_LEFT = 3

def register_button_cb(callback):
    global button_cb
    button_cb = callback

def button_press_down(button_index):
    global last_press_times

    current_time = time.ticks_ms()
    
    if time.ticks_diff(current_time, last_press_times[button_index]) > DEBOUNCE_TIME_MS:
        if button_cb:
            button_cb(button_index)
        last_press_times[button_index] = current_time

def timer_callback(timer):
    global button_states, last_button_states

    for i in range(len(BUTTON_PINS)):
        current_button_state = buttons[i].value()

        if current_button_state == ACTIVE_LEVEL and last_button_states[i] != ACTIVE_LEVEL:
            button_press_down(i)
            
        last_button_states[i] = current_button_state

def init():
    timer = Timer(0)
    timer.init(period=TICKS_INTERVAL, mode=Timer.PERIODIC, callback=timer_callback)
    return timer
