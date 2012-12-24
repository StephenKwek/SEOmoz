import web
web.config.debug = True
renderTextPage = web.template.render('textPages/')
renderCodePage = web.template.render('codePages/')

textPages = ['index', 'cover', 'resume', 'code']
codePages = ['checkBST', 'divide', 'dynamicProgramming', 'log2', 'matchPattern', 'nQueen', 'stock']
urls = ['/(.*)'] + textPages + codePages

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
            "dynamicProgramming" : renderCodePage.dynamicProgramming(),
            "log2" : renderCodePage.log2(),
            "matchPattern" : renderCodePage.matchPattern(),
            "nQueen" : renderCodePage.nQueen(),
            "stock" : renderCodePage.stock()
        }
        
        if action.has_key(name):
            return action[name]
        else: 
            return action["cover"]

    
if __name__ == "__main__":
    app.run()
