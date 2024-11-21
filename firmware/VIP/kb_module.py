import asyncio
import board
import keypad

afk_cb = None
input_cb = None
# LEFT = 0
# RIGHT = 1
# UP = 2
# DOWN = 3

def set_afk_cb(cb):
    global afk_cb
    afk_cb = cb
    
def set_input_cb(cb):
    global input_cb
    input_cb = cb

async def kb_module_task():
    global input_cb,afk_cb
    with keypad.Keys((board.IO20, board.IO8, board.IO0, board.IO18), value_when_pressed=False) as keys:
        while True:
            event = keys.events.get()
            if event:
                if afk_cb:
                    consumed = afk_cb(event)
                if input_cb and not consumed:
                    input_cb(event)
            await asyncio.sleep(0)

def kb_module_init():
    asyncio.create_task(kb_module_task())