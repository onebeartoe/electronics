
from MenuScreen import MenuScreen
from RandomJukeScreen import RandomJukeScreen

class Application(object):
	""" documentation """

	states = None

	current_state = None

	def __init__(self, pyportal, logger, time_font, temperature_font):
		logger.debug("Application constuctor")

		menuState = MenuScreen(pyportal, logger, temperature_font, self)

		self.current_state = menuState

		self.states = {'menu' : menuState,
		          'randomjuke' : RandomJukeScreen(pyportal, logger, time_font, temperature_font, self)}

		self.current_state.clear_splash()

		self.logger = logger



	def change_to_state(self, state_name):
#	    global current_state
	    if self.current_state:
	        self.logger.debug('Exiting %s', self.current_state.name)
	        self.current_state.exit()
	    self.current_state = self.states[state_name]
	    self.logger.debug('Entering %s', self.current_state.name)
	    self.current_state.enter()
