
class ApplicationScreen(object):
	""" This is the interface for application screens """

	pyportal = None

	def __init__(self, pyportal):
		self.pyportal = pyportal

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
