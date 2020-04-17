import os
import subprocess
import re
from datetime import datetime
import time
from statistics import mean
import csv

report =  open("report.txt", "a")

def test(tabuIt,cityNo,alphaT,constantT):
    numberOfTests = 10
    tabuIteration = tabuIt
    tabuDuration = '40'
    numberOfCities = cityNo
    alphaTabu = alphaT
    constantTabu = constantT
    final_solution = []
    list_coverage = []
    local_minimum = []
    headerCSV = [i+1 for i in range(int(numberOfCities))]
    rowList = []
    rowList.append(headerCSV)
    report.write(f"\n\nTest for Tabu Search with this config: \n\tIterations : {tabuIteration} \n\tNumber of Cities: {numberOfCities} \n\tAlpha For Tabu Duration = {alphaTabu} \n\tConstant For Tabu Duration = {constantTabu}")
    for i in range(0, numberOfTests):
        process = subprocess.Popen(['./algo_tabou.exe', tabuIteration , tabuDuration, numberOfCities, alphaTabu, constantTabu, 'distances_entre_villes_{}.txt'.format(numberOfCities)],stdout=subprocess.PIPE,stderr=subprocess.PIPE)
        stdout, stderr = process.communicate()
        result = stdout
        result = re.sub(r'\s', ' ', str(result))
        solution = (re.findall(r'([0-9]{4,7}) km', result))[-1]
        meanDuration = (re.findall(r'Mean Duration : ([0-9]+\.[0-9]+)', result))[0]
        meanDurationPerCity = re.findall(r'MDPC([0-9]+\.[0-9]+),', result)
        rowList.append([float(i) for i in meanDurationPerCity])
        final_solution.append(int(solution))
        coverage = re.findall(r'On est dans un minimum local a l\'iteration ([0-9]+) ->', result)
        if coverage != []:
            coverage = int(coverage[0])+ 1
            if int(solution) != 5644:
                local_minimum.append(int(solution))
        else:
            coverage = int(tabuIteration)
        number_of_solution_before_coverage = coverage
        list_coverage.append(coverage)
        report.write('{} : best found solution is {} and found in interation {}, number of solutions before coverage : {}, mean duration was : {}'.format(i, solution, coverage, number_of_solution_before_coverage, meanDuration))
        time.sleep( 1 )
    with open(f'{numberOfCities}-{tabuIteration}-{alphaTabu}-{constantTabu}.csv', 'w', newline='') as file:
        writer = csv.writer(file,delimiter=',')
        writer.writerows(rowList)
    report.write("Summary:")
    optimum_result = len(list(filter(lambda x: x == 5644, final_solution)))
    report.write(f'number of optimum solution found is {optimum_result}, so in {numberOfTests} runs of test we faced {(optimum_result/numberOfTests)*100}% coverage')
    report.write(f'in average this test shows that we found the global optimum solution in iteration {mean(list_coverage)}\nand in worst we found it in iteration {max(list_coverage)} \nand in best case in iteration {max(list_coverage)}')
    report.write(f'Totally, {sum(list_coverage)} cities visited before finding the global optimum in {numberOfTests} runs of this test\n')
    unique_local_minimum = list(dict.fromkeys(local_minimum))
    report.write(f'totally the algorithm was stuck in local optimum {len(local_minimum)} times \nthere are {len(unique_local_minimum)} unique local minimum \nthe best local optimum is {min(unique_local_minimum)} \nthe worst local optimum is {max(unique_local_minimum)}')



print("Thank you Sinan to Run this code! please wait ... it takes huge amount of time")
print("After finishing please send me the csv files and report.txt")


report.write("\n Test number one for 50 cities, 10000 iteration, alpha 1, with constant 10")
test("10000", "50", "1", "10")

report.write("\n Test number one for 50 cities, 10000 iteration, alpha 5, with constant 10")
test("10000", "50", "5", "10")

report.write("\n Test number one for 100 cities, 100000 iteration, alpha 1, with constant 10")
test("100000", "100", "1", "10")

report.write("\n Test number one for 100 cities, 100000 iteration, alpha 5, with constant 10")
test("100000", "100", "5", "10")





