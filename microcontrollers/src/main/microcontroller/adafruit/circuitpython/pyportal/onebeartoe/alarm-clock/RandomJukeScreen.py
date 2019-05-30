
import board
import displayio

from onebeartoe.gui.components import ApplicationScreen

class RandomJukeScreen(ApplicationScreen):
	"""This state manages the primary time display screen/mode"""

	def __init__(self, pyportal, logger, time_font, temperature_font):
		super().__init__(pyportal, logger)
		self.background_day = 'main_background_day.bmp'
		self.background_night = 'main_background_night.bmp'
		self.refresh_time = None
		self.update_time = None
		self.weather_refresh = None
		self.pyportal = pyportal
		text_area_configs = [dict(x=110, y=100, size=16, color=0xFFFFFF, font=time_font),   # Next lable
                             dict(x=110, y=150, size=16, color=0xFFFFFF, font=temperature_font)]  # response lable
		areas = self.create_text_areas(text_area_configs)
		self.text_areas = areas
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
				if self.touch_in_button(t, b):
					self.change_to_state(b['next_state'])
					break
			if self.touch_in_button(t, self.buttons[2]): # next button
				logger.debug('NEXT song touched')

#TODO: Make this a call to requests.post()
#      Docs: https://circuitpython.readthedocs.io/projects/esp32spi/en/latest/api.html#adafruit_esp32spi.adafruit_esp32spi_requests.post
#				response = requests.get('http://192.168.1.82:8080/onebeartoe-jukebox-ee/controls/song/next')
#                response = requests.get('http://192.168.1.80:1978/?action=next')
#                response = requests.get('http://192.168.1.80:8080/continuous/')
				response = 'new data'
				self.text_areas[1].text = 'ploop'
				print('lalal')
				print(response)
				print('lalal')
#                logger.debug(response)
		return bool(t)


	def enter(self):
		for ta in self.text_areas:
			self.pyportal.splash.append(ta)
		self.text_areas[0].text = 'Next'
		self.text_areas[1].text = '::::'
		board.DISPLAY.refresh_soon()
		board.DISPLAY.wait_for_frame()


	def exit(self):
		super().exit()
		for _ in range(len(self.snooze_icon)):
			self.snooze_icon.pop()
