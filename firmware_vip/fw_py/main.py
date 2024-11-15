import screennorm
import keyboard_module
import submenus
import about_me
from kevin_scan import kevin_scan_init

def scene_main_menu_cb(selection=0):
    if selection == 0:  #Buscando a Kevin
       kevin_scan_init()
    elif selection == 1:  #Animaciones
        print("2")
    elif selection == 2:  #Osciloscopio
        print("3")
    elif selection == 3:  #Acerca de mi
        about_me.init()
    else:
        print("Opción no válida")

def scene_main_menu():
    menu = submenus.GeneralSubMenu(["Buscando a Kevin","Animaciones","Osciloscopio","Acerca de mi"], scene_main_menu_cb, None)

if __name__ == "__main__":
    screennorm.screen_init()
    keyboard_module.init()
    scene_main_menu()
