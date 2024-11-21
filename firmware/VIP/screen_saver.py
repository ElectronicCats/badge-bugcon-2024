import asyncio
from eye import eye_init, eye_deinit
from scenes import scene_main_menu
from kb_module import set_afk_cb

enable_ss = True
timer = 0

def screen_saver_reset(event):
    global idle, timer
    consumed = False
    if event.pressed:
        if idle == True:
            eye_deinit()
            scene_main_menu()
            consumed = True
    idle = False
    timer = 0
    return consumed
                    
async def screen_saver_task():
    global timer, idle
    eye_init()
    idle = True
    while True:
        await asyncio.sleep(1)
        if enable_ss:
            timer +=1
            if timer >= 20:
                if idle == False:
                    idle = True
                    eye_init()
                timer = 0
            

def screen_saver_init():
    set_afk_cb(screen_saver_reset)
    asyncio.create_task(screen_saver_task())

def screen_saver_enable():
    global enable_ss
    enable_ss = True
    
def screen_saver_disable():
    global enable_ss,idle_time
    idle_time = 0
    enable_ss = False