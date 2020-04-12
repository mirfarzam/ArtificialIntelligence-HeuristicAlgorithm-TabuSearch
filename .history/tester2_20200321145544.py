import os
import subprocess
import re
from datetime import datetime
import time


process = subprocess.Popen(['./algo_tabou.exe', '5', '0', '10', 'distances_entre_villes_50.txt'],stdout=subprocess.PIPE,stderr=subprocess.PIPE)
stdout, stderr = process.communicate()



result = stdout


print(result)

