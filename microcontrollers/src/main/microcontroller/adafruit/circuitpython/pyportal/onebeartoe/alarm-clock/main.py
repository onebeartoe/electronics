"""
	documentation
"""

import adafruit_logging as logging
import board

from secrets import secrets
from adafruit_pyportal import PyPortal
from adafruit_bitmap_font import bitmap_font
import time

import adafruit_esp32spi.adafruit_esp32spi_requests as requests

from onebeartoe.gui.components import Application
from onebeartoe.gui.components import ApplicationScreen

from RandomJukeScreen import RandomJukeScreen

logger = logging.getLogger('alarm_clock')
logger.setLevel(logging.DEBUG)

touched = False



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




# touch_in_button






class Menu_State(ApplicationScreen):
#class Menu_State(State):
    """This state lets the user enable/disable the alarm and set its time.
    Swiping up/down adjusts the hours & miniutes separately."""

    def __init__(self, pyportal):
        super().__init__(pyportal)
        self.previous_touch = None
        self.background = 'settings_background.bmp'
        text_area_configs = [dict(x=88, y=40, size=15, color=0xFFFFFF, font=temperature_font),  # time
							dict(x=88, y=140, size=15, color=0xFFFFFF, font=temperature_font)]   # randomjuke

        self.text_areas = self.create_text_areas(text_area_configs)
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
            if self.touch_in_button(t, self.buttons[0]):   # on
                logger.debug('ON touched')
                alarm_enabled = True
                self.text_areas[0].text = '%02d:%02d' % (alarm_hour, alarm_minute)
            elif self.touch_in_button(t, self.buttons[1]):   # return
                logger.debug('RETURN touched')
                change_to_state('randomjuke')
            elif self.touch_in_button(t, self.buttons[2]): # off
                logger.debug('OFF touched')
                alarm_enabled = False
                self.text_areas[0].text = '     '
            elif self.touch_in_button(t, self.buttons[3]):   # time
                logger.debug('time touched')
                change_to_state('randomjuke')
            elif self.touch_in_button(t, self.buttons[4]):   # randomjuke
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




menuState = Menu_State(pyportal)

current_state = menuState
#current_state = None

states = {'menu' : menuState,
          'randomjuke' : RandomJukeScreen(pyportal, time_font, temperature_font)}


def change_to_state(state_name):
    global current_state
    if current_state:
        logger.debug('Exiting %s', current_state.name)
        current_state.exit()
    current_state = states[state_name]
    logger.debug('Entering %s', current_state.name)
    current_state.enter()



screen = ApplicationScreen(pyportal)
screen.clear_splash()
#clear_splash()

change_to_state("menu")

while True:
    touched = current_state.touch(pyportal.touchscreen.touch_point, touched)
    current_state.tick(time.monotonic())
