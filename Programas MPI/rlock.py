#!/usr/bin/python

import threading
from threading import RLock
import time

NTHREADS=20

# Bloqueo de un recurso mientras se usa
sem=RLock()

def hilo(i):
	"""
	:param i: numero de hilo a efectos ilustrativos
	:return: nada
	"""
	print "[+] En hilo %d" % i
	time.sleep(3)
	with sem:
	        print "[+] Bebiendo hilo %d..." % i
        time.sleep(1)
	print "[-] hilo %d satisfecho" % i

simplethread=[]
for i in range(NTHREADS):
	# arranque y comienzo de hilo num i+1
	simplethread.append(threading.Thread(target=hilo, args=[i+1]))
	simplethread[-1].start()

for i in range(NTHREADS):
	# esperamos que acabe el hilo num i
	simplethread[i].join()

print "[*] all threads finished"
