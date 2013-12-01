'''
/*
 * Grupo 13:
 * 329550-Adriano Pais Rodrigues
 * 380075-Arthur Pessoa de Souza
 * 379980-Joao Eduardo Brandes Luiz
*/
'''

from random import uniform
import sys

def gera(tam, chance):
	print tam
	for i in range(0, tam):
		for j in range(0, tam):
			print 1 if uniform(0, 100) < chance and i != j else 0,
		print
	print 0

def geraMulti(tamini, tamfim, increment, chance):
	for g in range(tamini, tamfim, increment):
		print g
		for i in range(0, g):
			for j in range(0, g):
				print 1 if uniform(0, 100) < chance and i != j else 0,
			print
	print 0

if len(sys.argv) == 3:
	gera(int(sys.argv[1]), float(sys.argv[2]))
	exit()

if len(sys.argv) == 5:
	geraMulti(int(sys.argv[1]), int(sys.argv[2]), int(sys.argv[3]), float(sys.argv[4]))
	exit()

print "Usages:"
print "python adjacencia.py number_of_nodes prcentage_of_completion"
print "python adjacencia.py initial_number_of_nodes final_number_of_nodes increment prcentage_of_completion"
