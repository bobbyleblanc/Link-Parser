from bs4 import BeautifulSoup
from urllib.request import urlopen
import csv

import re
 
html_page = urlopen("https://magic.wizards.com/en/content/deck-lists-magic-online-products-game-info")
soup = BeautifulSoup(html_page,'html.parser')
links = []

for link in soup.find_all('a'):
    links.append(link.get('href'))

myFile = open('links.csv','w')

with myFile:
    writer = csv.writer(myFile)
    writer.writerows([links])
