#!/bin/python3
import sys
import pandas as pd
import numpy as np
# execution: graphs.py a.csv b.csv (a = parallel results, b = sequential)

pdf = pd.read_csv(sys.argv[1], delimiter=';')
pdf['Type'] = 'parallel'
sdf = pd.read_csv(sys.argv[2], delimiter=';')
sdf['Type'] = 'sequential'

df = pd.concat([pdf, sdf]).reset_index()

input_dict = {'10x1M.txt': '10',
              '10x2M.txt': '20',
              '10x5M.txt': '50'}

df = df.replace({'Input Size': input_dict})
df['Output'] = df['Output'].apply(lambda x: x == 'y')
df = df[df['Output']]
#df = df[df['CPUs'] < 16]
del df['Output']
del df['index']

group_by = ['CPUs', 'Input Size']

pdf = df[df['Type'] == 'parallel']
del pdf['Type']
print("Parallel time")
print(pdf.groupby(group_by).mean())
print("Std dev")
print(pdf.groupby(group_by)['Time'].std())

sdf = df[df['Type'] == 'sequential']
del sdf['Type']
del sdf['CPUs']
print("\n\nSequential time")
print(sdf.groupby('Input Size').mean())
print("Std dev")
print(sdf.groupby('Input Size')['Time'].std())

def isFloat(s):
    try:
        float(s)
        return True
    except ValueError:
        return False

filepaths = ['resultado_sequencial28nov.txt', 'resultado_paralelo28nov.txt']
for filepath in filepaths:
    print(filepath)
    entrada = '10x1M.txt'
    entradas = {'10x1M.txt': {
                    1: {'total': [], 'seq': []},
                    2: {'total': [], 'seq': []},
                    4: {'total': [], 'seq': []},
                    8: {'total': [], 'seq': []}
                   },
                '10x2M.txt': {
                    1: {'total': [], 'seq': []},
                    2: {'total': [], 'seq': []},
                    4: {'total': [], 'seq': []},
                    8: {'total': [], 'seq': []}
                   },
                 '10x5M.txt': {
                    1: {'total': [], 'seq': []},
                    2: {'total': [], 'seq': []},
                    4: {'total': [], 'seq': []},
                    8: {'total': [], 'seq': []}
                   }}
    cpu = 1
    with open(filepath) as fp:
        line = fp.readline()
        cnt = 1
        while line:
            if isFloat(line[:-1]):
                if len(entradas[entrada][cpu]['total']) > len(entradas[entrada][cpu]['seq']):
                    entradas[entrada][cpu]['seq'].append(float(line))
                else:
                    entradas[entrada][cpu]['total'].append(float(line))
            elif "cpu" in line:
                cpu = int(line[:-1].split('=')[1])
            elif "entrada" in line:
                entrada = line[:-1].split('=')[1]
            line = fp.readline()
    for entrada in entradas:
        print("Entrada={}".format(entrada))
        for c in entradas[entrada]:
            avgp = 0
            stdp = 0
            print("CPU={}".format(c))
            total = entradas[entrada][c]['total']
            seq = entradas[entrada][c]['seq']
            for i in range(len(total)):
                avgp += seq[i]/total[i]
            avgp /= len(total)
            for i in range(len(total)):
                stdp += (seq[i]/total[i] - avgp)**2
            stdp /= len(total)
            print("Avg: {}\n".format(avgp*100))
