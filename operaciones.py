#-*-coding:utf-8-*-
print "Selecciona una opción de las siguientes"
print "1.- Suma 2.- Resta 3.- Multiplicación 4.- División "
opcion=input()
if (opcion==1):
	a = input("Ingresa el primer número: ")
	b = input("Ingresa el segundo número: ")
	suma = int(a+b)
	print (a, "+", b, "=", suma)

if (opcion==2):
	a = input("Ingresa el primer número: ")
	b = input("Ingresa el segundo numero: ")
	resta = int(a-b)
	print (a, "-", b, "=", resta)

if (opcion==3):
	a = input("Ingresa el primer número: ")
	b = input("Ingresa el segundo número: ")
	multip = int(a*b)
	print (a, "x", b, "=", multip)

if (opcion==4):
	a = input("Ingresa el primer número: ")
	b = input("Ingresa el segundo número: ")
	div = int(a/b)
	print (a, "/", b, "=", div)
