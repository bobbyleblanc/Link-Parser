import os
import datetime
import shutil

date = str(datetime.date.today())

directoryVintage = date + '/VintageOutput.txt'
directoryCommander = date + '/CommanderOutput.txt'
directoryLegacy = date + '/LegacyOutput.txt'
directoryPauper = date + '/PauperOutput.txt'
directoryModern = date + '/ModernOutput.txt'
directoryStandard = date + '/StandardOutput.txt'


os.remove("date.txt")
os.remove("ListofWebsites.csv")
os.remove("links.csv")
os.remove(directoryVintage)
os.remove(directoryCommander)
os.remove(directoryLegacy)
os.remove(directoryPauper)
os.remove(directoryModern)
os.remove(directoryStandard)

#tempDir = date +'/temp/'
#shutil.rmtree(tempDir)