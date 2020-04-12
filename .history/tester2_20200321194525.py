import os
import subprocess
import re
from datetime import datetime
import time



final_solution = []

print("Test for 5 0 10")
for i in range(0, 10):
    process = subprocess.Popen(['./algo_tabou.exe', '20', '0', '10', 'distances_entre_villes_10.txt'],stdout=subprocess.PIPE,stderr=subprocess.PIPE)
    stdout, stderr = process.communicate()
    result = stdout
    result = re.sub(r'\s', ' ', result)
    solution = (re.findall(r'([0-9]{4}) km', result))[-1]
    final_solution.append(optimum)

    coverage = re.findall(r'On est dans un minimum local a l\'iteration ([0-9]+) ->', result)
    if coverage != []:
        coverage = int(coverage[0])+ 1
    else:
        coverage = 5
    print('best found solution is {} and found in interation {}'.format(optimum[-1], coverage))
    time.sleep( 1 )
    

