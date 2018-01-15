from bs4 import BeautifulSoup
from urllib.request import urlopen

url = "https://magic.wizards.com/en/articles/archive/mtgo-standings/competitive-vintage-constructed-league-2018-01-11"

content = urlopen(url).read()

soup = BeautifulSoup(content)

f = open('testfile.txt','w', encoding='utf-8')
f.write(soup.get_text())
