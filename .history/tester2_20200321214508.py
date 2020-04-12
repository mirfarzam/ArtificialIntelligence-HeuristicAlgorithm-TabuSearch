import os
import subprocess
import re
from datetime import datetime
import time
from statistics import mean 


numberOfTests = 10

tabuIteration = '5'
tabuDuration = '0'
numberOfCities = '10'

final_solution = []
list_coverage = []

print(f"\n\nTest for Tabu Search with this config: \n\tIterations : {tabuIteration} \n\tDuration(Tabu Memory): {tabuDuration} \n\tNumber of Cities: {numberOfCities}")
for i in range(0, numberOfTests):
    process = subprocess.Popen(['./algo_tabou.exe', tabuIteration, tabuDuration, numberOfCities, 'distances_entre_villes_{}.txt'.format(numberOfCities)],stdout=subprocess.PIPE,stderr=subprocess.PIPE)
    stdout, stderr = process.communicate()
    result = stdout
    result = re.sub(r'\s', ' ', str(result))
    solution = (re.findall(r'([0-9]{4}) km', result))[-1]
    final_solution.append(int(solution))
    coverage = re.findall(r'On est dans un minimum local a l\'iteration ([0-9]+) ->', result)
    if coverage != []:
        coverage = int(coverage[0])+ 1
    else:
        coverage = 5
    number_of_solution_before_coverage = coverage
    list_coverage.append(coverage)
    print('best found solution is {} and found in interation {}, number of solutions before coverage : {}'.format(solution, coverage, number_of_solution_before_coverage))
    time.sleep( 1 )

print("Summery:")

optimum_result = len(list(filter(lambda x: x == 3473, final_solution)))

print(f'number of optimum solution found is {optimum_result}, so in {numberOfTests} iteration we faced {(optimum_result/numberOfTests)*100}% coverage')
print(f'in average this test shows that we found the global optimum solution in iteration {mean(list_coverage)}\nand in worst we found it in iteration {max(list_coverage)} \nand in best case in iteration {max(list_coverage)}')
print(f'in tot') 