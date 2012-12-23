import web
web.config.debug = True
render = web.template.render('templates/')

urls = (
    '/(.*)', 'index', 'cover', 'resume', 'code'
)

class index:
    def GET(self, name):
	if name == "cover":
		return render.cover()
	if name == "resume":
		return render.resume()
	if name == "index":
		return render.index()
	if name == "code":
		return render.code()
	else: 
		return render.index()
	
if __name__ == "__main__":
    app = web.application(urls, globals())
    app.run()
