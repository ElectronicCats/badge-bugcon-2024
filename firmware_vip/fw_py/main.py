import screennorm
from keyboard_module import keyboard_module_init
from submenus import GeneralSubMenu
from about_me import about_me_init
from kevin_scan import kevin_scan_init
from leds import leds_init

last_selected = 0
leds_obj = None

def scene_main_menu_cb(selection=0):
    global last_selected, leds_obj
    last_selected = selection
    if selection == 0:  #Buscando a Kevin
       kevin_scan_init(scene_main_menu)
    elif selection == 1:  #Animaciones
        pass
    elif selection == 2:  #Osciloscopio
        pass
    elif selection == 3:  #Presentacion
        about_me_init(scene_main_menu)
    else:
        print("Opción no válida")

def scene_main_menu():
    global last_selected
    menu = GeneralSubMenu(["Buscando a Kevin","Animaciones","Osciloscopio","Presentacion"],last_selected, scene_main_menu_cb, None)

def get_leds_obj():
    print(type(leds_obj))

def setup():
    screennorm.screen_init()
    leds_init()
    keyboard_module_init()
    scene_main_menu()
 
if __name__ == "__main__":
    setup()
