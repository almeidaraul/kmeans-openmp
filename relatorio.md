# Relatório de mudanças
Serve só para eu registrar tudo que fiz e como impactou o programa

# Modelo de entrada:
## Descrição do objetivo (ex: paralelizar for de leitura)
### Mudanças no código
Descrição de mudanças no código
### Tempo
Comparou com o que (paralelo ou sequencial)? Qual foi o tempo exato de cada?
### Resultado
Alterou o resultado?
### Por que funcionou/não funcionou
Explicação
### Observações

## Paralelizar for:n cluster[i] = 0
**Linha no código sequencial:** 19
### Mudanças no código
`pragma omp parallel for` simplérrimo
### Tempo
Comparação entre paralelo e sequencial. 0.1003s (sequencial) vs 0.1012s (paralelo).

Em geral ficaram os dois num tempo semelhante.
### Resultado
OK
### Por que funcionou/não funcionou
Não melhorou por conta de falso compartilhamento em `int *cluster`.
### Observações
Tentar resolver esse falso compartilhamento depois
