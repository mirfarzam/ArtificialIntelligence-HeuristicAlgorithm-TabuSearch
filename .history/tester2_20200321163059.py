import os
import subprocess
import re
from datetime import datetime
import time


print("Test for ")
for in in range(0, 10):
    print(f"Test {i+1} : ===============================")
    process = subprocess.Popen(['./algo_tabou.exe', '5', '0', '10', 'distances_entre_villes_10.txt'],stdout=subprocess.PIPE,stderr=subprocess.PIPE)
    stdout, stderr = process.communicate()
    result = stdout
    print(result)
    

