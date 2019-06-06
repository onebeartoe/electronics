
#import analogio
import board
import displayio
import gc
import neopixel
import time

from adafruit_bitmap_font import bitmap_font
from adafruit_button import Button
from adafruit_pyportal import PyPortal

from MemoryCardsGame import MemoryCardsGame
from MemoryCardsGameCannedData import MemoryCardsGameCannedData
from MemoryCardsGameResponse import MemoryCardsGameResponse


class Application(object):
    """ documentation """

    def __init__(self):
        self.BACKGROUND_COLOR = 0x443355

        # Setup PyPortal without networking
        self.pyportal = PyPortal(default_bg=self.BACKGROUND_COLOR)

        self.initializeButtons()

        # Set the NeoPixel brightness
        BRIGHTNESS = 0.3

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
        self.game.startGame()

        self.interval = 5.5
        self.previousTime = time.monotonic()  # Time in seconds since power on


    def flipCard(self, buttonIndex, sprintIndex):
        print("card sprite index: ", sprintIndex)
        self.buttonAttributes[buttonIndex]['iconGroup'].pop()
        self.buttonAttributes[buttonIndex]['iconGroup'].append(self.cardSprites[sprintIndex])

    def handleButtonPress(self, button):
        print("Touched", button.name)

        buttonValue = int(button.name)

        response = self.selectCard(buttonValue)

        buttonIndex = buttonValue - 1

        sprintIndex = self.cards[buttonIndex].value - 1

        if(response == MemoryCardsGameResponse.GUESS_ONE_ACCEPTED):
            self.flipCard(buttonIndex, sprintIndex)
        elif response == MemoryCardsGameResponse.GUESS_TWO_ACCEPTED_MATCH:
            self.flipCard(buttonIndex, sprintIndex)
            self.pyportal.play_file('Coin.wav')
        elif response == MemoryCardsGameResponse.GUESS_REJECTED_CARD_ALREADY_REVEALED:
            self.pyportal.play_file('resources/sounds/invalid-guess.wav')
        else:
            message = "unknown response: " + str(response)
            raise Exception(message)


        button.label = self.buttonAttributes[buttonIndex]['label']

        # neopixel updates
        if self.mode == 0:
            self.strip_1.fill(button.fill_color)
        elif self.mode == 1:
            self.strip_2.fill(button.fill_color)
        elif self.mode == 2:
            self.strip_1.fill(button.fill_color)
            self.strip_2.fill(button.fill_color)


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


        self.pyportal.splash.append(self.icon1Group)



    def launch(self):

        while True:

            touch = self.pyportal.touchscreen.touch_point
            if touch:
                for button in self.buttons:
                    if button.contains(touch):
                        self.handleButtonPress(button)

                        break

            #TODO is this needed?
            time.sleep(0.05)

            now = time.monotonic()
            if now - self.previousTime >= 10.333:  # If 10.333 seconds elapses
                print("free memory: ", gc.mem_free() )
                self.previousTime = now


    def selectCard(self, cardValue):
        response = None

        if(cardValue == 1):
            response = self.game.selectCard1()
        elif(cardValue == 2):
            response = self.game.selectCard2()
        elif(cardValue == 3):
            response = self.game.selectCard3()
        elif(cardValue == 4):
            response = self.game.selectCard4()
        elif(cardValue == 5):
            response = self.game.selectCard5()
        elif(cardValue == 6):
            response = self.game.selectCard6()
        elif(cardValue == 7):
            response = self.game.selectCard7()
        elif(cardValue == 8):
            response = self.game.selectCard8()
        elif(cardValue == 9):
            response = self.game.selectCard9()
        elif(cardValue == 10):
            response = self.game.selectCard10()
        elif(cardValue == 11):
            response = self.game.selectCard11()
        elif(cardValue == 12):
            response = self.game.selectCard12()
        else:
            print("invalid card value: ")
            print(cardValue)
            raise Exception()

        return response
