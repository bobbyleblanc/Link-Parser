from bs4 import BeautifulSoup
from urllib.request import urlopen
import csv
import os
import datetime

with open('ListofWebsites.csv','rU') as infile:
    reader = csv.reader(infile, delimiter= ',',quotechar='"')
    List_of_Websites = list(reader)

date = str(datetime.date.today())
#datetemp = date + '/temp'
DoesntExist = 1

if os.path.isdir(date):
    DoesntExist = 0
if DoesntExist: 
    os.mkdir(date)

#os.mkdir(datetemp)
date = str(datetime.date.today())
f = open('date.txt', 'w', encoding='utf-8')
f.write(date)

content = urlopen(List_of_Websites[0][0]).read()
soup = BeautifulSoup(content, "html.parser")
directoryVintage = date + '/VintageOutput.txt'
f = open(directoryVintage,'w', encoding='utf-8')
f.write(soup.get_text())

content = urlopen(List_of_Websites[0][1]).read()
soup = BeautifulSoup(content, "html.parser")
directoryCommander = date + '/CommanderOutput.txt'
f = open(directoryCommander,'w', encoding='utf-8')
f.write(soup.get_text())

content = urlopen(List_of_Websites[0][2]).read()
soup = BeautifulSoup(content, "html.parser")
directoryLegacy = date + '/LegacyOutput.txt'
f = open(directoryLegacy,'w', encoding='utf-8')
f.write(soup.get_text())

content = urlopen(List_of_Websites[0][3]).read()
soup = BeautifulSoup(content, "html.parser")
directoryPauper = date + '/PauperOutput.txt'
f = open(directoryPauper,'w', encoding='utf-8')
f.write(soup.get_text())

content = urlopen(List_of_Websites[0][4]).read()
soup = BeautifulSoup(content, "html.parser")
directoryModern = date + '/ModernOutput.txt'
f = open(directoryModern,'w', encoding='utf-8')
f.write(soup.get_text())

content = urlopen(List_of_Websites[0][5]).read()
soup = BeautifulSoup(content, "html.parser")
directoryStandard = date + '/StandardOutput.txt'
f = open(directoryStandard,'w', encoding='utf-8')
f.write(soup.get_text())




#content = urlopen(List_of_Websites[0][0]).read()
#soup = BeautifulSoup(content, "html.parser")
#directoryVintage = datetemp + '/VintageOutput.txt'
#f = open(directoryVintage,'w', encoding='utf-8')
#f.write(soup.get_text())

#content = urlopen(List_of_Websites[0][1]).read()
#soup = BeautifulSoup(content, "html.parser")
#directoryCommander = datetemp + '/CommanderOutput.txt'
#f = open(directoryCommander,'w', encoding='utf-8')
#f.write(soup.get_text())

#content = urlopen(List_of_Websites[0][2]).read()
#soup = BeautifulSoup(content, "html.parser")
#directoryLegacy = datetemp + '/LegacyOutput.txt'
#f = open(directoryLegacy,'w', encoding='utf-8')
#f.write(soup.get_text())

#content = urlopen(List_of_Websites[0][3]).read()
#soup = BeautifulSoup(content, "html.parser")
#directoryPauper = datetemp + '/PauperOutput.txt'
#f = open(directoryPauper,'w', encoding='utf-8')
#f.write(soup.get_text())

#content = urlopen(List_of_Websites[0][4]).read()
#soup = BeautifulSoup(content, "html.parser")
#directoryModern = datetemp + '/ModernOutput.txt'
#f = open(directoryModern,'w', encoding='utf-8')
#f.write(soup.get_text())

#content = urlopen(List_of_Websites[0][5]).read()
#soup = BeautifulSoup(content, "html.parser")
#directoryStandard = datetemp + '/StandardOutput.txt'
#f = open(directoryStandard,'w', encoding='utf-8')
#f.write(soup.get_text())
f.close()
