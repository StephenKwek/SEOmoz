import server 
import unittest

class ServerTest(unittest.TestCase):
	def testTextPage(self):
		for page in server.textPages:
			response = server.app.request("/" + page)
			self.assertEqual(response.status, '200 OK')
			self.assertEqual(response.data[:30], '<!DOCTYPE HTML PUBLIC "-//W3C/')
			self.assertEqual(response.data[-16:], '</BODY>\n</HTML>\n')

		for page in server.codePages:
			#page = 'nQueen'
			print page
			response = server.app.request("/" + page)
			self.assertEqual(response.status, '200 OK')
			self.assertEqual(response.data[:30], '<!doctype html 1.1>\n<html>\n<he')
			self.assertEqual(response.data[-16:], '</body>\n</html>\n')
	

if __name__ == "__main__":
	print server.urls
	unittest.main()
