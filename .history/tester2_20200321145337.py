import os
import subprocess
import re
from datetime import datetime
import time


process = subprocess.Popen(['./algo_tabou.exe', '1000', '1000', '50', 'distances_entre_villes_50.txt'],stdout=subprocess.PIPE,stderr=subprocess.PIPE)
stdout, stderr = process.communicate()



result = stdout


print(result)

