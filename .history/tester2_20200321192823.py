import os
import subprocess
import re
from datetime import datetime
import time


print("Test for 5 0 10")
for i in range(0, 10):
    process = subprocess.Popen(['./algo_tabou.exe', '5', '0', '10', 'distances_entre_villes_10.txt'],stdout=subprocess.PIPE,stderr=subprocess.PIPE)
    stdout, stderr = process.communicate()
    result = stdout
    result = re.sub(r'\s', ' ', result)
    optimum = (re.findall(r'([0-9]{4}) km', result))[-1]
    coverage = re.findall(r'On est dans un minimum local a l\'iteration ([0-9]+) ->', result)
    if coverage != []:
        coverage = coverage[0] 
    else:
        coverage = 5
    print(f"best found solution is {result} and found in interation {coverage}")
    time.sleep( 1 )
    

