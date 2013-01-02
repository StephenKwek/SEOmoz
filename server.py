import web
web.config.debug = True
    
textPages = ['index', 'cover', 'resume', 'code']
textPages = ['index', 'cover', 'resume', 'code']
codePages = ['checkBST', 'divide', 'dynamicProgramming', 'log2', 'matchPattern', 'nQueen', 'stock']
reportPages = ['monitor']

urls = ['/(.*)'] + textPages + codePages + reportPages
app = web.application(urls, globals()) 


class index:
    _renderTextPage = web.template.render('textPages/')
    _renderCodePage = web.template.render('codePages/')
    _renderMonitor = web.template.render('monitor/')
    count = dict.fromkeys(textPages + codePages + reportPages + [""], 0)

    def GET(self, name):
        if index.count.has_key(name):
            index.count[name] += 1

        action = {
            "monitor" : index._renderMonitor.monitor(index.count),
            "cover" : index._renderTextPage.cover(),
            "resume" : index._renderTextPage.resume(),
            "index" : index._renderTextPage.index(),
            "code" : index._renderTextPage.code(),

            "checkBST" : index._renderCodePage.checkBST(),
            "divide" : index._renderCodePage.divide(),
            "dynamicProgramming" : index._renderCodePage.dynamicProgramming(),
            "log2" : index._renderCodePage.log2(),
            "matchPattern" : index._renderCodePage.matchPattern(),
            "nQueen" : index._renderCodePage.nQueen(),
            "stock" : index._renderCodePage.stock()

        }
        
        if action.has_key(name):
            return action[name]
        else: 
            index.count["cover"] += 1
            return action["cover"]

            
    
if __name__ == "__main__":
    app.run()
