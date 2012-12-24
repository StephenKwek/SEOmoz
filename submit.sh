rm *.sw? .*.sw? templates/*.sw? templates/.*.sw?
git add .
git commit -m init
heroku create -s cedar
git push heroku master

