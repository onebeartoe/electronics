
import board

from ApplicationScreen import ApplicationScreen

class MenuScreen(ApplicationScreen):
    """ documentation """

    def __init__(self, pyportal, logger, temperature_font, application):
		super().__init__(pyportal, logger)
		logger.debug("MenuScreen constuctor")
		self.previous_touch = None
		self.background = 'settings_background.bmp'
		self.pyportal = pyportal
		text_area_configs = [dict(x=88, y=40, size=15, color=0xFFFFFF, font=temperature_font),  # time
							dict(x=88, y=140, size=15, color=0xFFFFFF, font=temperature_font)]   # randomjuke

		self.text_areas = self.create_text_areas(text_area_configs)
		self.buttons = [dict(left=0, top=30, right=80, bottom=93),    # on
                        dict(left=0, top=98, right=80, bottom=152),   # return
                        dict(left=0, top=155, right=80, bottom=220),  # off
                        dict(left=88, top=40, right=320, bottom = 60),   # time
                        dict(left=88, top=140, right=320, bottom = 160)]   # randomjuke
		self.logger = logger
		self.application = application

    def touch(self, t, touched):
		global alarm_hour, alarm_minute, alarm_enabled
		if t:
			global states
			global current_state
#			states = self.application.states
			if self.touch_in_button(t, self.buttons[0]):   # on
				self.logger.debug('ON touched')
				alarm_enabled = True
				self.text_areas[0].text = '%02d:%02d' % (4, 22)
			elif self.touch_in_button(t, self.buttons[1]):   # return
				self.logger.debug('RETURN touched')
				self.application.change_to_state('menu')
			elif self.touch_in_button(t, self.buttons[2]): # off
				self.logger.debug('OFF touched')
				alarm_enabled = False
				self.text_areas[0].text = '     '
			elif self.touch_in_button(t, self.buttons[3]):   # time
				self.logger.debug('time touched')
				self.application.change_to_state('randomjuke')
			elif self.touch_in_button(t, self.buttons[4]):   # randomjuke
				self.logger.debug('randomjuke touched')
				self.application.change_to_state('randomjuke')
			board.DISPLAY.refresh_soon()
			board.DISPLAY.wait_for_frame()
		else:
			self.previous_touch = None
		return bool(t)


    def enter(self):
        global snooze_time
        snooze_time = None

        self.pyportal.set_background(self.background)
        for ta in self.text_areas:
            self.pyportal.splash.append(ta)

        self.text_areas[0].text = '%02d:%02d' % (4, 26) # set time textarea

        self.text_areas[1].text = 'randomjuke'
