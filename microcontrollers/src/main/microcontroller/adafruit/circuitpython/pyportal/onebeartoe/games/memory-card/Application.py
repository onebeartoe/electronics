
import analogio
import board
import displayio
import neopixel
import time

from adafruit_bitmap_font import bitmap_font
from adafruit_button import Button
from adafruit_pyportal import PyPortal

class Application(object):
    """ documentation """

    def __init__(self):
        self.BACKGROUND_COLOR = 0x443355

        # Setup PyPortal without networking
        self.pyportal = PyPortal(default_bg=self.BACKGROUND_COLOR)

        self.initializeButtons()

        # Set the NeoPixel brightness
        BRIGHTNESS = 0.3

        self.light_sensor = analogio.AnalogIn(board.LIGHT)

        self.strip_1 = neopixel.NeoPixel(board.D4, 30, brightness=BRIGHTNESS)
        self.strip_2 = neopixel.NeoPixel(board.D3, 30, brightness=BRIGHTNESS)

        # Turn off NeoPixels to start
        self.strip_1.fill(0)
        self.strip_2.fill(0)

        self.mode = 0
        self.mode_change = None

    def initializeButtons(self):
        
        self.icon1Group = displayio.Group()
        self.icon1Group.x = 20
        self.icon1Group.y = 20       
        
        # Button colors
        RED = (255, 0, 0)
        ORANGE = (255, 34, 0)
        YELLOW = (255, 170, 0)
        GREEN = (0, 255, 0)
        CYAN = (0, 255, 255)
        BLUE = (0, 0, 255)
        VIOLET = (153, 0, 255)
        MAGENTA = (255, 0, 51)
        PINK = (255, 51, 119)
        AQUA = (85, 125, 255)
        WHITE = (255, 255, 255)
        OFF = (0, 0, 0)

        buttonPositions = [
            {'pos1': (10, 10)},
		    {'pos2': (90, 10)},
            {'pos3': (170, 10)},
		    {'pos4': (250, 10)},
            {'pos5': (10, 90)},
		    {'pos6': (90, 90)},
		    {'pos7': (170, 90)},
		    {'pos8': (250, 90)},
		    {'pos9': (10, 170)},
		    {'pos10': (90, 170)},
		    {'pos11': (170, 170)},
		    {'pos12': (250, 170)}
            ]

        self.buttonAttributes = [
            {'label': "1", 'pos': (10, 10),    'size': (60, 60),         'color': WHITE, 'iconGroup' : None},
		    {'label': "2", 'pos': (90, 10),    'size': (60, 60), 'color': WHITE, 'iconGroup' : None},
            {'label': "3", 'pos': (170, 10),   'size': (60, 60),         'color': WHITE, 'iconGroup' : None},
		    {'label': "4", 'pos': (250, 10),   'size': (60, 60), 'color': WHITE, 'iconGroup' : None},
            {'label': "5", 'pos': (10, 90),    'size': (60, 60),         'color': WHITE, 'iconGroup' : None},
		    {'label': "6", 'pos': (90, 90),    'size': (60, 60), 'color': WHITE, 'iconGroup' : None},
		    {'label': "7", 'pos': (170, 90),   'size': (60, 60), 'color': WHITE, 'iconGroup' : None},
		    {'label': "8", 'pos': (250, 90),   'size': (60, 60), 'color': WHITE, 'iconGroup' : None},
		    {'label': "9", 'pos': (10, 170),   'size': (60, 60), 'color': WHITE, 'iconGroup' : None},
		    {'label': "10", 'pos': (90, 170),  'size': (60, 60), 'color': WHITE, 'iconGroup' : None},
		    {'label': "11", 'pos': (170, 170), 'size': (60, 60), 'color': WHITE, 'iconGroup' : None},
		    {'label': "12", 'pos': (250, 170), 'size': (60, 60), 'color': WHITE, 'iconGroup' : None}
            ]

        buttonFont = bitmap_font.load_font('/fonts/Arial-16.bdf')
        buttonFont.load_glyphs(b'0123456789CFabcdefghijklmnopqrstuvwxyz:')

        snooze_file = open('/resources/images/cards/1.bmp', "rb")
        icon = displayio.OnDiskBitmap(snooze_file)

        self.icon_sprite = displayio.TileGrid(icon,
                                         pixel_shader=displayio.ColorConverter(),
                                         x=0, y=0)

        self.buttons = []

        for spot in self.buttonAttributes:
            button = Button(x=spot['pos'][0],
                            y=spot['pos'][1],
                            width=spot['size'][0],
                            height=spot['size'][1],
                            style=Button.SHADOWROUNDRECT,
                            fill_color=spot['color'],
                            outline_color=0x222222,
                            name=spot['label'],
                            label_font=buttonFont)

            iconGroup = displayio.Group()
            iconGroup.x = spot['pos'][0]
            iconGroup.y = spot['pos'][1]
            iconGroup.append(self.icon_sprite)

            spot['iconGroup'] = iconGroup

            button.group.append(iconGroup)

            self.pyportal.splash.append(button.group)
            self.buttons.append(button)




# TODO: should we close the snooze_file?
#        snooze_file.close()

#        self.icon1Group.append(icon_sprite)
        self.pyportal.splash.append(self.icon1Group)



    def launch(self):
        # Calibrate light sensor on start to deal with different lighting situations
        # If the self.mode change isn't responding properly, reset your PyPortal to recalibrate
        initial_light_value = self.light_sensor.value
        while True:
            if self.light_sensor.value < (initial_light_value * 0.3) and self.mode_change is None:
		        self.mode_change = "mode_change"
            if self.light_sensor.value > (initial_light_value * 0.5) and self.mode_change == "mode_change":
                self.mode += 1
                self.mode_change = None
                if self.mode > 2:
                    self.mode = 0
                print(self.mode)
            touch = self.pyportal.touchscreen.touch_point
            if touch:
                for button in self.buttons:
                    if button.contains(touch):
                        spotIndex = int(button.name) - 1

                        button.label = self.buttonAttributes[spotIndex]['label']

                        self.pyportal.play_file('Coin.wav')
                        self.icon1Group.append(self.icon_sprite)

                        print("Touched", button.name)

                        if self.mode == 0:
                            self.strip_1.fill(button.fill_color)
                        elif self.mode == 1:
                            self.strip_2.fill(button.fill_color)
                        elif self.mode == 2:
                            self.strip_1.fill(button.fill_color)
                            self.strip_2.fill(button.fill_color)
                        break

            time.sleep(0.05)