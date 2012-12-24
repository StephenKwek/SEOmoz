import web
web.config.debug = True
renderTextPage = web.template.render('textPages/')
renderCodePage = web.template.render('codePages/')

urls = (
    '/(.*)', 'index', 'cover', 'resume', 'code',
    'checkBST', 'divide', 'log2', 'matchPattern', 'nQueen', 'stock'
)

app = web.application(urls, globals())

class index:
    def GET(self, name):
        print name
        action = {
            "cover" : renderTextPage.cover(),
            "resume" : renderTextPage.resume(),
            "index" : renderTextPage.index(),
            "code" : renderTextPage.code(),

            "checkBST" : renderCodePage.checkBST(),
            "divide" : renderCodePage.divide(),
            "log2" : renderCodePage.log2(),
            "matchPattern" : renderCodePage.matchPattern(),
            "stock" : renderCodePage.stock()
        }
        
        if action.has_key(name):
            return action[name]
        else: 
            return action["index"]

    
if __name__ == "__main__":
    app.run()
