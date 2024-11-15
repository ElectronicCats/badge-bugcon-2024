import keyboard_module
from keyboard_module import btn
import screennorm
import time
from machine import Timer
import random

from main import scene_main_menu

import romans as font6
import romant as font5
import romanc as font4
import italicc as font3
import italict as font2
import romand as font1

NAME = "[NOMBRE]"
LAST_NAME = "[APELLIDO]"
MARITAL_STATUS = "[ESTADO CIVIL]"

CITY = "[CIUDAD]"
STATE = "[ESTADO]"
COUNTRY = "[PAIS]"

PERIOD = 20000

current_index=0
timer=None

def display_name():
    screen = screennorm.get_screen()
    screen.clear(0)
    tft = screen.get_tft()

    tft.fill_rect(0,0,240,50,0xF800)
    tft.fill_rect(0,190,240,50,0xF800)
    tft.fill_rect(0,50,240,50,0xFFFF)
    
    screen.text_auto_scale_center(font1, "HOLA", 25)
    screen.text_auto_scale_center(font2, "Mi Nombre es:" ,75, 0)
    screen.text_auto_scale_center(font2, NAME, 125)
    screen.text_auto_scale_center(font2, LAST_NAME, 165)
    screen.text_auto_scale_center(font1, MARITAL_STATUS, 215)

def display_origin():
    screen = screennorm.get_screen()
    screen.clear(0)
    tft = screen.get_tft()

    tft.fill_rect(0,0,240,50,0xF800)
    tft.fill_rect(0,190,240,50,0xF800)
    tft.fill_rect(0,50,240,50,0xFFFF)
    
    screen.text_auto_scale_center(font1, "ORIGEN", 25)
    screen.text_auto_scale_center(font5, "Vengo desde:" ,75,0)
    screen.text_auto_scale_center(font2, CITY, 125)
    screen.text_auto_scale_center(font2, STATE, 165)
    screen.text_auto_scale_center(font1, COUNTRY, 215)

def display_demo():
    screen = screennorm.get_screen()
    screen.clear(0)
    tft = screen.get_tft()
    
    tft.hline(0,50,240,0xffff)  #(x,y,len,color)
    tft.vline(120,45,10,0xffff)  #(x,y,len,color)
    tft.hline(0,190,240,0xffff)
    tft.vline(120,185,10,0xffff)
    
    tft.line(0,110,240,90,0xffff)  #(x1,y1,x2,y2,color)
    tft.line(240,160,0,140,0xffff)
    
    screen.text_auto_scale_center(font5, "Modifica el", 25, 0xfaaf)  #(screen,font,text,y,color)
    screen.text_auto_scale_center(font5, "archivo about_me" ,75, 0xcfa5)
    screen.text_auto_scale_center(font5, "con Thonny para", 125, 0xffff)
    screen.text_auto_scale_center(font5, "personalizar tu", 165, 0x3d89)
    screen.text_auto_scale_center(font5, "informacion", 215, 0x44f6)
    
def display_demo2():
    screen = screennorm.get_screen()
    screen.clear(0)
    tft = screen.get_tft()
    
    for i in range(500):
        x = random.randint(0,240)
        y = random.randint(0,240)
        color = random.randint(0,0xffff)
        tft.pixel(x,y,color)  #(x,y,color)
        
    screen.text_auto_scale_center(font1, "Tambien puedes", 25, 0xcfa5)
    screen.text_auto_scale_center(font2, "agregar nuevas" ,75, 0x44f6)
    screen.text_auto_scale_center(font3, "paginas para", 125, 0xffff)
    screen.text_auto_scale_center(font4, "compartir datos", 165, 0xfaaf)
    screen.text_auto_scale_center(font5, "interesantes", 215, 0x3d89)
    
###############################################################
### Create new display functions and add them to this list ###
###############################################################
display_functions = [display_name,display_origin,display_demo,display_demo2]

def handle_input(btn_name):
    global timer, current_index
    if btn_name == btn.BUTTON_LEFT:
        timer.deinit()
        scene_main_menu()
    elif btn_name == btn.BUTTON_RIGHT:
        next_function(None)
        timer_reset()
    elif btn_name == btn.BUTTON_UP:
        pass
    elif btn_name == btn.BUTTON_DOWN:
        pass

def timer_reset():
    global timer
    timer.deinit()
    timer.init(period=PERIOD, mode=Timer.PERIODIC, callback=next_function)
    
def next_function(timer):
    global current_index
    global display_functions
    display_functions[current_index]()
    current_index += 1
    if current_index >= len(display_functions):
        current_index = 0
          
def init():
    keyboard_module.register_button_cb(handle_input)
    global timer, current_index
    timer = Timer(2)
    timer.init(period=PERIOD, mode=Timer.PERIODIC, callback=next_function)
    next_function(None)