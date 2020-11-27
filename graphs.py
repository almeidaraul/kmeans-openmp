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
df = df[df['CPUs'] < 8]
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

filepath = 'sequential.txt'
total = []
seq = []
with open(filepath) as fp:
    line = fp.readline()
    cnt = 1
    while line:
        if isFloat(line[:-1]):
            if len(total) > len(seq):
                seq.append(float(line))
            else:
                total.append(float(line))
        line = fp.readline()
avgp = 0
stdp = 0
for i in range(len(total)):
    avgp += seq[i]/total[i]
avgp /= len(total)
for i in range(len(total)):
    stdp += (seq[i]/total[i] - avgp)**2
stdp /= len(total)
print("Avg: {}\nStd: {}\n".format(avgp*100, stdp*100))
