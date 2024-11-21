last_selected = 0

from submenus import submenu
from gallery import gallery_init
from scrolling_text import ScrollingText

text = """Developed by Electronic Cats,with love from Mexico,Thanks
          -Roberto: @otrebor_671 -Francisco: @deimoshall -Lizeth"""

def scene_main_menu_cb(selection=0):
    global last_selected
    last_selected = selection
    if selection == 0:  #Galeria
        gallery_init(scene_main_menu)
    elif selection == 1:  #Animaciones
        ScrollingText(text,scene_main_menu)
    else:
        print("Opción no válida")

def scene_main_menu():
    global last_selected
    menu = submenu(["Galeria","Creditos"],last_selected, scene_main_menu_cb, None)