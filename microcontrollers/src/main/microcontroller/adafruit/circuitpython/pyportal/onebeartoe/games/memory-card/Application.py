
import analogio
import board
import displayio
import neopixel
import time

from adafruit_bitmap_font import bitmap_font
from adafruit_button import Button
from adafruit_pyportal import PyPortal

from MemoryCardsGame import MemoryCardsGame
from MemoryCardsGameCannedData import MemoryCardsGameCannedData

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

        self.game = MemoryCardsGame()
        cannedData = MemoryCardsGameCannedData()
        self.cards = cannedData.validCardSetCountOf2()
        self.game.setCards(self.cards)

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

        self.buttonAttributes = [
            {'label': "1", 'pos': (10, 10),    'size': (60, 60), 'color': WHITE, 'iconGroup' : None},
            {'label': "2", 'pos': (90, 10),    'size': (60, 60), 'color': WHITE, 'iconGroup' : None},
            {'label': "3", 'pos': (170, 10),   'size': (60, 60), 'color': WHITE, 'iconGroup' : None},
            {'label': "4", 'pos': (250, 10),   'size': (60, 60), 'color': WHITE, 'iconGroup' : None},
            {'label': "5", 'pos': (10, 90),    'size': (60, 60), 'color': WHITE, 'iconGroup' : None},
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

        cardBackFile = open('/resources/images/cards/back.bmp', "rb")
        icon = displayio.OnDiskBitmap(cardBackFile)
        self.cardBackSprite = displayio.TileGrid(icon,
                                         pixel_shader=displayio.ColorConverter(),
                                         x=0, y=0)

        cardFile1 = open('/resources/images/cards/1.bmp', "rb")
        cardFileIcon1 = displayio.OnDiskBitmap(cardFile1)
        self.cardSprite1 = displayio.TileGrid(cardFileIcon1,
                                         pixel_shader=displayio.ColorConverter(),
                                         x=0, y=0)

        cardFile2 = open('/resources/images/cards/2.bmp', "rb")
        cardFileIcon2 = displayio.OnDiskBitmap(cardFile2)
        self.cardSprite2 = displayio.TileGrid(cardFileIcon2,
                                         pixel_shader=displayio.ColorConverter(),
                                         x=0, y=0)

        cardFile3 = open('/resources/images/cards/3.bmp', "rb")
        cardFileIcon3 = displayio.OnDiskBitmap(cardFile3)
        self.cardSprite3 = displayio.TileGrid(cardFileIcon3,
                                             pixel_shader=displayio.ColorConverter(),
                                             x=0, y=0)

        cardFile4 = open('/resources/images/cards/4.bmp', "rb")
        cardFileIcon4 = displayio.OnDiskBitmap(cardFile4)
        self.cardSprite4 = displayio.TileGrid(cardFileIcon4,
                                          pixel_shader=displayio.ColorConverter(),
                                          x=0, y=0)


        cardFile5 = open('/resources/images/cards/5.bmp', "rb")
        cardFileIcon5 = displayio.OnDiskBitmap(cardFile5)
        self.cardSprite5 = displayio.TileGrid(cardFileIcon5,
                                           pixel_shader=displayio.ColorConverter(),
                                           x=0, y=0)


        cardFile6 = open('/resources/images/cards/6.bmp', "rb")
        cardFileIcon6 = displayio.OnDiskBitmap(cardFile6)
        self.cardSprite6 = displayio.TileGrid(cardFileIcon6,
                                           pixel_shader=displayio.ColorConverter(),
                                           x=0, y=0)

        """
        cardFile7 = open('/resources/images/cards/7.bmp', "rb")
        cardFileIcon7 = displayio.OnDiskBitmap(cardFile7)
        self.cardSprite7 = displayio.TileGrid(cardFileIcon7,
                                                pixel_shader=displayio.ColorConverter(),
                                                x=0, y=0)

        cardFile8 = open('/resources/images/cards/8.bmp', "rb")
        cardFileIcon8 = displayio.OnDiskBitmap(cardFile8)
        self.cardSprite8 = displayio.TileGrid(cardFileIcon8,
                                                pixel_shader=displayio.ColorConverter(),
                                                x=0, y=0)

        cardFile9 = open('/resources/images/cards/9.bmp', "rb")
        cardFileIcon9 = displayio.OnDiskBitmap(cardFile9)
        self.cardSprite9 = displayio.TileGrid(cardFileIcon9,
                                                pixel_shader=displayio.ColorConverter(),
                                                x=0, y=0)

        cardFile10 = open('/resources/images/cards/10.bmp', "rb")
        cardFileIcon10 = displayio.OnDiskBitmap(cardFile10)
        self.cardSprite10 = displayio.TileGrid(cardFileIcon10,
                                                pixel_shader=displayio.ColorConverter(),
                                                x=0, y=0)

        cardFile11 = open('/resources/images/cards/11.bmp', "rb")
        cardFileIcon11 = displayio.OnDiskBitmap(cardFile11)
        self.cardSprite11 = displayio.TileGrid(cardFileIcon11,
                                                pixel_shader=displayio.ColorConverter(),
                                                x=0, y=0)

        cardFile12 = open('/resources/images/cards/12.bmp', "rb")
        cardFileIcon12 = displayio.OnDiskBitmap(cardFile12)
        self.cardSprite12 = displayio.TileGrid(cardFileIcon12,
                                                pixel_shader=displayio.ColorConverter(),
                                                x=0, y=0)
        """

        self.cardSprites = [self.cardSprite1, self.cardSprite2, self.cardSprite3, self.cardSprite4, self.cardSprite5, self.cardSprite6]

        self.buttons = []

        for attributes in self.buttonAttributes:
            button = Button(x=attributes['pos'][0],
                            y=attributes['pos'][1],
                            width=attributes['size'][0],
                            height=attributes['size'][1],
                            style=Button.SHADOWROUNDRECT,
                            fill_color=attributes['color'],
                            outline_color=0x222222,
                            name=attributes['label'],
                            label_font=buttonFont)

            iconGroup = displayio.Group()
            iconGroup.x = attributes['pos'][0]
            iconGroup.y = attributes['pos'][1]
            iconGroup.append(self.cardBackSprite)

            attributes['iconGroup'] = iconGroup

            button.group.append(iconGroup)

            self.pyportal.splash.append(button.group)
            self.buttons.append(button)

# TODO: should we close the cardBackFile?
#        cardBackFile.close()

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
                        print("Touched", button.name)

                        buttonValue = int(button.name)
                        buttonIndex = buttonValue - 1

                        button.label = self.buttonAttributes[buttonIndex]['label']

                        self.pyportal.play_file('Coin.wav')

                        sprintIndex = self.cards[buttonIndex].value

                        print("sprint index: ", sprintIndex)
                        self.buttonAttributes[buttonIndex]['iconGroup'].pop()
                        self.buttonAttributes[buttonIndex]['iconGroup'].append(self.cardSprites[sprintIndex])



                        if self.mode == 0:
                            self.strip_1.fill(button.fill_color)
                        elif self.mode == 1:
                            self.strip_2.fill(button.fill_color)
                        elif self.mode == 2:
                            self.strip_1.fill(button.fill_color)
                            self.strip_2.fill(button.fill_color)
                        break

            time.sleep(0.05)
