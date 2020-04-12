
process = subprocess.Popen(['./algo_tabou.exe', '1000', '1000', '50', 'distances_entre_villes_50.txt'],stdout=subprocess.PIPE,stderr=subprocess.PIPE)
stdout, stderr = process.communicate()

