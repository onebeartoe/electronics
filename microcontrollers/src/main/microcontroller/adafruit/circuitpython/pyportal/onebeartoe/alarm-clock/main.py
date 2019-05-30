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

from Application import Application
from ApplicationScreen import ApplicationScreen
from MenuScreen import MenuScreen
from RandomJukeScreen import RandomJukeScreen

logger = logging.getLogger('alarm_clock')
logger.setLevel(logging.DEBUG)

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

pyportal = PyPortal(url = DATA_SOURCE,
                    json_path = DATA_LOCATION,
                    status_neopixel = board.NEOPIXEL,
					debug = True)


application = Application(pyportal, logger, time_font, temperature_font)
application.change_to_state("menu")

touched = False

while True:
    touched = application.current_state.touch(pyportal.touchscreen.touch_point, touched)
    application.current_state.tick(time.monotonic())
