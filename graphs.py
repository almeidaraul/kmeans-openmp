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
pdf = pdf.groupby(group_by).mean()
print("Parallel time")
print(pdf)

sdf = df[df['Type'] == 'sequential']
del sdf['Type']
del sdf['CPUs']
sdf = sdf.groupby('Input Size').mean()
print("\n\nSequential time")
print(sdf)
