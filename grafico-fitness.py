#!/usr/bin/env python3
import matplotlib.pyplot as plt
import sys

if len(sys.argv) != 3:
    print('Uso: %s salida titulo < <resultados>' % (sys.argv[0],))
    exit()

lines = (line.split() for line in sys.stdin.readlines())
lines = [(line[1], line[2], line[3]) for line in lines if line[0] == "mejor"]

gen = [line[0] for line in lines]
avg = [float(line[1]) for line in lines]
stddev = [float(line[2]) for line in lines]

salida = sys.argv[1]
titulo = sys.argv[2]

plt.xticks(range(0, len(gen), 5), fontsize=8)
plt.errorbar(gen, avg, yerr=stddev, label='Fitness Promedio')
plt.xlabel('Generacion')
plt.ylabel('Fitness')
plt.title(titulo)
plt.legend()
plt.savefig(fname=salida, format='pdf')
