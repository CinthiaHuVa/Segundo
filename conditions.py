#!/usr/bin/python

import threading
from threading import Condition
import time
from random import randint

NTHREADS=20

# Bloqueo de un recurso mientras se usa
sem=Condition()

def bebe(i):
	s=randint(1,10)
	print "[+] Bebiendo hilo %d.. esperate %d secs" % (i,s)
	time.sleep(s)
	sem.notify(1)
	print "[-] estaba de muerte, hilos --%d--" % i
	sem.release()

def hilo(i):
	"""
	:param i: numero de hilo a efectos ilustrativos
	:return: nada
	"""
	print "[+] En hilo %d" % i
	time.sleep(1)
	while not sem.acquire():
		sem.wait(0.5)
	else:
		bebe(i)
	print "[-] hilo %d finalizado" % i

simplethread=[]
for i in range(NTHREADS):
	# arranque y comienzo de hilo num i+1
	simplethread.append(threading.Thread(target=hilo, args=[i+1]))
	simplethread[-1].start()

for i in range(NTHREADS):
	# esperamos que acabe el hilo num i
	simplethread[i].join()

print "[*] all threads finished"

