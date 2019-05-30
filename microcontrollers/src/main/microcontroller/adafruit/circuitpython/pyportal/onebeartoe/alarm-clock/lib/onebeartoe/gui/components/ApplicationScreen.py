
from adafruit_display_text.label import Label

class ApplicationScreen(object):
	""" This is the interface for application screens """

	pyportal = None

	logger = None



	def change_to_state(self, state_name, current_state, states):
#	    global current_state
	    if current_state:
	        self.logger.debug('Exiting %s', current_state.name)
	        current_state.exit()
	    current_state = states[state_name]
	    self.logger.debug('Entering %s', current_state.name)
	    current_state.enter()


	def touch_in_button(self, t, b):
		in_horizontal = b['left'] <= t[0] <= b['right']
		in_vertical = b['top'] <= t[1] <= b['bottom']
		return in_horizontal and in_vertical


	def create_text_areas(self, configs):
	    """Given a list of area specifications, create and return test areas."""
	    text_areas = []
	    for cfg in configs:
	        textarea = Label(cfg['font'], text=' '*cfg['size'])
	        textarea.x = cfg['x']
	        textarea.y = cfg['y']
	        textarea.color = cfg['color']
	        text_areas.append(textarea)
	    return text_areas


#TODO can we move this back up to the top?
	def __init__(self, pyportal, logger):
		self.pyportal = pyportal
		self.logger = logger




	def clear_splash(self):
		for _ in range(len(self.pyportal.splash) - 1):
			self.pyportal.splash.pop()





	def tick(self, now):
		""" handle one pass of the main loop """
		pass


	def exit(self):
		""" exit and clear splash """
		self.clear_splash()



#    @property
#    def name(self):
#        """Return the name of teh state"""
#        return ''
