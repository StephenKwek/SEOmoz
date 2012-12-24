from server import app
import unittest

class ServerTest(unittest.TestCase):
	def testServer(self):
		for page in ("index", "cover", "resume", "code"):
			response = app.request("/" + page)
			'''
			print "|" + response.status + "|"
			print response.status == '200 OK'
			print "|"+response.data[:30]+"|"
			print response.data[:30] == '<!DOCTYPE HTML PUBLIC "-//W3C/'
			'''
		 	print "|"+response.data[-30:]+"|"
			print response.data[-30:] == 'TBD</P>\n</OL>\n</BODY>\n</HTML>\n'

if __name__ == "__main__":
	unittest.main()
