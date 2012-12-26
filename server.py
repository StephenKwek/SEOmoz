import web
web.config.debug = True
    
textPages = ['index', 'cover', 'resume', 'code']
textPages = ['index', 'cover', 'resume', 'code']
codePages = ['checkBST', 'divide', 'dynamicProgramming', 'log2', 'matchPattern', 'nQueen', 'stock']
reportPages = ['report']

urls = ['/(.*)'] + textPages + codePages + reportPages
app = web.application(urls, globals()) 


class index:
    renderTextPage = web.template.render('textPages/')
    renderCodePage = web.template.render('codePages/')
    renderReport = web.template.render('report/')
    count = dict.fromkeys(textPages + codePages + reportPages + [""], 0)

    def GET(self, name):
        if index.count.has_key(name):
            index.count[name] += 1

        action = {
            "report" : index.renderReport.report(index.count),
            "cover" : index.renderTextPage.cover(),
            "resume" : index.renderTextPage.resume(),
            "index" : index.renderTextPage.index(),
            "code" : index.renderTextPage.code(),

            "checkBST" : index.renderCodePage.checkBST(),
            "divide" : index.renderCodePage.divide(),
            "dynamicProgramming" : index.renderCodePage.dynamicProgramming(),
            "log2" : index.renderCodePage.log2(),
            "matchPattern" : index.renderCodePage.matchPattern(),
            "nQueen" : index.renderCodePage.nQueen(),
            "stock" : index.renderCodePage.stock()

        }
        
        if action.has_key(name):
            return action[name]
        else: 
            index.count["cover"] += 1
            return action["cover"]

            
    
if __name__ == "__main__":
    app.run()
