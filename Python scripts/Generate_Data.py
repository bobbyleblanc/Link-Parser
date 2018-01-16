from bs4 import BeautifulSoup
from urllib.request import urlopen
import csv

with open('ListofWebsites.csv','rU') as infile:
    reader = csv.reader(infile, delimiter= ',',quotechar='"')
    List_of_Websites = list(reader)

content = urlopen(List_of_Websites[0][0]).read()
soup = BeautifulSoup(content)
f = open('VintageOutput.txt','w', encoding='utf-8')
f.write(soup.get_text())

content = urlopen(List_of_Websites[0][1]).read()
soup = BeautifulSoup(content)
f = open('CommanderOutput.txt','w', encoding='utf-8')
f.write(soup.get_text())

content = urlopen(List_of_Websites[0][2]).read()
soup = BeautifulSoup(content)
f = open('LegacyOutput.txt','w', encoding='utf-8')
f.write(soup.get_text())

content = urlopen(List_of_Websites[0][3]).read()
soup = BeautifulSoup(content)
f = open('PauperOutput.txt','w', encoding='utf-8')
f.write(soup.get_text())

content = urlopen(List_of_Websites[0][4]).read()
soup = BeautifulSoup(content)
f = open('ModernOutput.txt','w', encoding='utf-8')
f.write(soup.get_text())

content = urlopen(List_of_Websites[0][5]).read()
soup = BeautifulSoup(content)
f = open('StandardOutput.txt','w', encoding='utf-8')
f.write(soup.get_text())
