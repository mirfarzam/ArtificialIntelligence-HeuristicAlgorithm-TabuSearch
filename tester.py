import os
import subprocess
import re
from datetime import datetime
import time


# Print iterations progress
def printProgressBar (iteration, total, prefix = '', suffix = '', decimals = 1, length = 100, fill = '█', printEnd = "\r"):
    """
    Call in a loop to create terminal progress bar
    @params:
        iteration   - Required  : current iteration (Int)
        total       - Required  : total iterations (Int)
        prefix      - Optional  : prefix string (Str)
        suffix      - Optional  : suffix string (Str)
        decimals    - Optional  : positive number of decimals in percent complete (Int)
        length      - Optional  : character length of bar (Int)
        fill        - Optional  : bar fill character (Str)
        printEnd    - Optional  : end character (e.g. "\r", "\r\n") (Str)
    """
    percent = ("{0:." + str(decimals) + "f}").format(100 * (iteration / float(total)))
    filledLength = int(length * iteration // total)
    bar = fill * filledLength + '-' * (length - filledLength)
    print('\r%s |%s| %s%% %s' % (prefix, bar, percent, suffix), end = printEnd)
    # Print New Line on Complete
    if iteration == total:
        print()

class Route():
    def __init__(self, route, distance, time):
        self.route = route
        self.distance = distance
        self.time = time

routes = []

# printProgressBar(0, 10, prefix = 'Progress:', suffix = 'Complete', length = 50)
for i in range(0, 5):
    startTime = datetime.now()
    process = subprocess.Popen(['./algo_tabou.exe', '1000', '1000', '50', 'distances_entre_villes_50.txt'],stdout=subprocess.PIPE,stderr=subprocess.PIPE)
    stdout, stderr = process.communicate()
    # print(stdout)
    endTime = datetime.now() - startTime
    result = re.findall(r'[0-9\-]+\-\-> [0-9]{4}', str(stdout))
    bestRoute = (list(map(lambda x: re.sub('\-{3}>', '', x), result))[1]).split(" ")
    print(bestRoute)
    routes.append(Route(bestRoute[0], int(bestRoute[1]), endTime.microseconds))
    process.terminate()
    time.sleep( 1 )
    # printProgressBar(i + 1, 10, prefix = 'Progress:', suffix = 'Complete', length = 50)

# Routes Information
justRoutes = list(map(lambda x : x.route, routes))
uniqueRoutes = len(list(dict.fromkeys(justRoutes)))
print("Number of unique Routes : {}".format(uniqueRoutes))

# Distance Information
distances = list(map(lambda x : x.distance, routes))
minimumDistance = min(distances)
AverageDistance = sum(distances) / len(distances)
print("Minimum Distance : {}".format(minimumDistance))
print("Average Distance : {}".format(AverageDistance))

# Time Consuming Information
times = list(map(lambda x : x.time, routes))
AverageTimes = sum(times) / len(times)
print("Average Time it took to find a best route : {} microseconds".format(AverageTimes))

sorted_routes = sorted(routes, key=lambda student: student.distance)
print(f"best route is {sorted_routes[0].route} and distance is {sorted_routes[0].distance} and takes {sorted_routes[0].time} microseconds")
