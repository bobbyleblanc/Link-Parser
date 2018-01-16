import subprocess
import Generate_Links
import os
import datetime
from time import sleep


curDir = os.getcwd()
curDir = curDir + '\Link-Parser.exe'

Generate_Links
subprocess.Popen([curDir])

sleep(5)

import Generate_Data
Generate_Data


sleep(5)

curDir = os.getcwd()
curDir = curDir + '\Website-Parser.exe'

sleep(5)
subprocess.Popen([curDir])
