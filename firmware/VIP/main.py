import asyncio
import gc
from kb_module import kb_module_init
from screen import screen_init, get_screen
from screen_saver import screen_saver_init
import displayio
from leds import leds_init

from eye import eye_init, eye_deinit
    
async def _sleeper():
    while True:
        await asyncio.sleep_ms(5000)
        gc.collect()

async def main():
    displayio.release_displays()
    kb_module_init()
    screen_init()
    leds_init()
    screen_saver_init()
    await _sleeper()

def main_run():
    asyncio.run(main())

if __name__ == "__main__":
    asyncio.run(main())