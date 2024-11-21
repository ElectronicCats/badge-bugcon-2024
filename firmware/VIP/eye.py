import time, math, random
import displayio
import adafruit_imageload
import asyncio

from screen import get_screen

displayio.release_displays()

dw, dh = 240,240

eyeball_bitmap, eyeball_pal = adafruit_imageload.load("imgs/eye0_ball2.bmp")
iris_bitmap, iris_pal = adafruit_imageload.load("imgs/eye0_iris0.bmp")
iris_pal.make_transparent(0)

iris_w, iris_h = iris_bitmap.width, iris_bitmap.height
iris_cx, iris_cy = dw//2 - iris_w//2, dh//2 - iris_h//2
r = 20
task = None

class Eye:
    def __init__(self):
        self.display = get_screen()
        main = displayio.Group()
        self.display.root_group = main
        self.eyeball = displayio.TileGrid(eyeball_bitmap, pixel_shader=eyeball_pal)
        self.iris = displayio.TileGrid(iris_bitmap, pixel_shader=iris_pal, x=iris_cx,y=iris_cy)
        main.append(self.eyeball)
        main.append(self.iris)
        self.x, self.y = iris_cx, iris_cy
        self.tx, self.ty = self.x, self.y
        self.next_time = time.monotonic()
        self.eye_speed = 0.25
        self.twitch = 2

    def update(self):
        self.x = self.x * (1-self.eye_speed) + self.tx * self.eye_speed
        self.y = self.y * (1-self.eye_speed) + self.ty * self.eye_speed
        self.iris.x = int( self.x )
        self.iris.y = int( self.y )
        if time.monotonic() > self.next_time:
            t = random.uniform(0.25,self.twitch)
            self.next_time = time.monotonic() + t
            self.tx = iris_cx + random.uniform(-r,r)
            self.ty = iris_cy + random.uniform(-r,r)
        self.display.refresh()

async def eye_task():
    eye = Eye()
    while True:
        eye.update()
        await asyncio.sleep(0)

def eye_init():
    global task
    if task == None:
        task = asyncio.create_task(eye_task())

def eye_deinit():
    global task
    if task:
        task.cancel()
    task = None