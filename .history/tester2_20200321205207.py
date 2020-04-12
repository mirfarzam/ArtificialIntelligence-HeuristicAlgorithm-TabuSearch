import os
import subprocess
import re
from datetime import datetime
import time


numberOfTests = 10

tabuIteration = '5'
tabuDuration = '0'
numberOfCities = '10'


final_solution = []

print(f"Test for Tabu S{tabuIteration} {tabuDuration} {numberOfCities}")
for i in range(0, numberOfTests):
    process = subprocess.Popen(['./algo_tabou.exe', tabuIteration, tabuDuration, numberOfCities, 'distances_entre_villes_{}.txt'.format(numberOfCities)],stdout=subprocess.PIPE,stderr=subprocess.PIPE)
    stdout, stderr = process.communicate()
    result = stdout
    result = re.sub(r'\s', ' ', result)
    solution = (re.findall(r'([0-9]{4}) km', result))[-1]
    final_solution.append(int(solution))
    coverage = re.findall(r'On est dans un minimum local a l\'iteration ([0-9]+) ->', result)
    if coverage != []:
        coverage = int(coverage[0])+ 1
    else:
        coverage = 5
    print('best found solution is {} and found in interation {}'.format(solution, coverage))
    time.sleep( 1 )
    

