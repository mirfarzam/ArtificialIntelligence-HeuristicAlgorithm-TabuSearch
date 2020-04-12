
process = subprocess.Popen(['./algo_tabou.exe', '1000', '1000', '50', 'distances_entre_villes_50.txt'],stdout=subprocess.PIPE,stderr=subprocess.PIPE)
stdout, stderr = process.communicate()


result = re.findall(r'[0-9\-]+\-\-> [0-9]{4}', str(stdout))
bestRoute = (list(map(lambda x: re.sub('\-{3}>', '', x), result))[1]).split(" ")
print(bestRoute)
routes.append(Route(bestRoute[0], int(bestRoute[1]), endTime.microseconds))
process.terminate()