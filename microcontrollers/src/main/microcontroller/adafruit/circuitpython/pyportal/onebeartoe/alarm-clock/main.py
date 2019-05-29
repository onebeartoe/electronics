"""
	documentation
"""



import adafruit_logging as logging
import board
from adafruit_display_text.label import Label
from secrets import secrets
from adafruit_pyportal import PyPortal
from adafruit_bitmap_font import bitmap_font
import time
import displayio
import adafruit_esp32spi.adafruit_esp32spi_requests as requests


logger = logging.getLogger('alarm_clock')
logger.setLevel(logging.DEBUG)

touched = False

current_state = None

# fonts
temperature_font = bitmap_font.load_font('/fonts/Arial-16.bdf')
temperature_font.load_glyphs(b'0123456789CFabcdefghijklmnopqrstuvwxyz:')

time_font = bitmap_font.load_font('/fonts/Anton-Regular-104.bdf')
time_font.load_glyphs(b'0123456789:Next') # pre-load glyphs for fast printing

# HTTP configuration
# Set up where we'll be fetching data from
DATA_SOURCE = 'http://api.openweathermap.org/data/2.5/weather?zip='+secrets['city_zip']
#DATA_SOURCE = 'http://api.openweathermap.org/data/2.5/weather?id='+secrets['city_id']

DATA_SOURCE += '&appid='+secrets['openweather_token']
# You'll need to get a token from openweather.org, looks like 'b6907d289e10d714a6e88b30761fae22'

DATA_LOCATION = []



# alarm state support
alarm_background = 'red_alert.bmp'
alarm_file = 'alarm.wav'
alarm_enabled = True
alarm_armed = True
alarm_interval = 10.0
alarm_hour = 9
alarm_minute = 45
snooze_time = None
snooze_interval = 600.0


####################
# setup hardware

pyportal = PyPortal(url = DATA_SOURCE,
                    json_path = DATA_LOCATION,
                    status_neopixel = board.NEOPIXEL,
					debug = True)


def touch_in_button(t, b):
    in_horizontal = b['left'] <= t[0] <= b['right']
    in_vertical = b['top'] <= t[1] <= b['bottom']
    return in_horizontal and in_vertical




def create_text_areas(configs):
    """Given a list of area specifications, create and return test areas."""
    text_areas = []
    for cfg in configs:
        textarea = Label(cfg['font'], text=' '*cfg['size'])
        textarea.x = cfg['x']
        textarea.y = cfg['y']
        textarea.color = cfg['color']
        text_areas.append(textarea)
    return text_areas

class ApplicationScreen(object):
	""" This is the interface for application screens """

	def tick(self, now):
		""" handle one pass of the main loop """
		pass


	def exit(self):
		""" exit and clear splash """
		clear_splash()

#    def __init__(self):
#		pass

#    @property
#    def name(self):
#        """Return the name of teh state"""
#        return ''




class Menu_State(ApplicationScreen):
#class Menu_State(State):
    """This state lets the user enable/disable the alarm and set its time.
    Swiping up/down adjusts the hours & miniutes separately."""

    def __init__(self):
        super().__init__()
        self.previous_touch = None
        self.background = 'settings_background.bmp'
        text_area_configs = [dict(x=88, y=40, size=15, color=0xFFFFFF, font=temperature_font),  # time
							dict(x=88, y=140, size=15, color=0xFFFFFF, font=temperature_font)]   # randomjuke

        self.text_areas = create_text_areas(text_area_configs)
        self.buttons = [dict(left=0, top=30, right=80, bottom=93),    # on
                        dict(left=0, top=98, right=80, bottom=152),   # return
                        dict(left=0, top=155, right=80, bottom=220),  # off
                        dict(left=88, top=40, right=320, bottom = 60),   # time
                        dict(left=88, top=140, right=320, bottom = 160)]   # randomjuke


    @property
    def name(self):
        return 'menu'



    def touch(self, t, touched):
        global alarm_hour, alarm_minute, alarm_enabled
        if t:
            if touch_in_button(t, self.buttons[0]):   # on
                logger.debug('ON touched')
                alarm_enabled = True
                self.text_areas[0].text = '%02d:%02d' % (alarm_hour, alarm_minute)
            elif touch_in_button(t, self.buttons[1]):   # return
                logger.debug('RETURN touched')
                change_to_state('time')
            elif touch_in_button(t, self.buttons[2]): # off
                logger.debug('OFF touched')
                alarm_enabled = False
                self.text_areas[0].text = '     '
            elif touch_in_button(t, self.buttons[3]):   # time
                logger.debug('time touched')
                change_to_state('time')
            elif touch_in_button(t, self.buttons[4]):   # randomjuke
                logger.debug('randomjuke touched')
                change_to_state('randomjuke')
            board.DISPLAY.refresh_soon()
            board.DISPLAY.wait_for_frame()
        else:
            self.previous_touch = None
        return bool(t)


    def enter(self):
        global snooze_time
        snooze_time = None

        pyportal.set_background(self.background)
        for ta in self.text_areas:
            pyportal.splash.append(ta)

        self.text_areas[0].text = '%02d:%02d' % (alarm_hour, alarm_minute) # set time textarea

        self.text_areas[1].text = 'randomjuke'





class Randomjuke_State(ApplicationScreen):
    """This state manages the primary time display screen/mode"""

    def __init__(self):
        super().__init__()
        self.background_day = 'main_background_day.bmp'
        self.background_night = 'main_background_night.bmp'
        self.refresh_time = None
        self.update_time = None
        self.weather_refresh = None
        text_area_configs = [dict(x=110, y=100, size=16, color=0xFFFFFF, font=time_font),   # Next lable
                             dict(x=110, y=140, size=16, color=0xFFFFFF, font=temperature_font)]  # response lable
        self.text_areas = create_text_areas(text_area_configs)

        self.icon_file = None

        self.snooze_icon = displayio.Group()
        self.snooze_icon.x = 260
        self.snooze_icon.y = 70
        self.snooze_file = None

        # each button has it's edges as well as the state to transition to when touched
        self.buttons = [dict(left=0, top=50, right=80, bottom=120, next_state='randomjuke'),
                        dict(left=0, top=155, right=80, bottom=220, next_state='menu'),
                        dict(left=88, top=120, right=320, bottom=220)]  # Next button


    @property
    def name(self):
        return 'randomjuke'


    def tick(self, now):
        """Handle a tick: one pass through the main loop"""
        pass


    def touch(self, t, touched):
        if t and not touched:             # only process the initial touch
            max = len(self.buttons) - 1  # only do state stuff with the first two buttons
            for button_index in range(max):
                b = self.buttons[button_index]
                if touch_in_button(t, b):
                    change_to_state(b['next_state'])
                    break
            if touch_in_button(t, self.buttons[2]): # next button
                logger.debug('NEXT song touched')

#TODO: Make this a call to requests.post()
#      Docs: https://circuitpython.readthedocs.io/projects/esp32spi/en/latest/api.html#adafruit_esp32spi.adafruit_esp32spi_requests.post
                response = requests.get('http://192.168.1.82:8080/onebeartoe-jukebox-ee/controls/song/next')
#                response = requests.get('http://192.168.1.80:1978/?action=next')
#                response = requests.get('http://192.168.1.80:8080/continuous/')
                self.text_areas[1].text = 'ploop'
                print('lalal')
                print(response)
                print('lalal')
#                logger.debug(response)
        return bool(t)


    def enter(self):
        for ta in self.text_areas:
            pyportal.splash.append(ta)
        self.text_areas[0].text = 'Next'
        self.text_areas[1].text = '::::'
        board.DISPLAY.refresh_soon()
        board.DISPLAY.wait_for_frame()


    def exit(self):
        super().exit()
        for _ in range(len(self.snooze_icon)):
            self.snooze_icon.pop()



states = {'menu' : Menu_State(),
          'randomjuke' : Randomjuke_State()}


def change_to_state(state_name):
    global current_state
    if current_state:
        logger.debug('Exiting %s', current_state.name)
        current_state.exit()
    current_state = states[state_name]
    logger.debug('Entering %s', current_state.name)
    current_state.enter()


def clear_splash():
    for _ in range(len(pyportal.splash) - 1):
        pyportal.splash.pop()


clear_splash()
change_to_state("menu")

while True:
    touched = current_state.touch(pyportal.touchscreen.touch_point, touched)
    current_state.tick(time.monotonic())
