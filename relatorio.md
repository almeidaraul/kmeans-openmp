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

## Paralelizar `CLUSTER_ZERO`
**Linha no código sequencial:** 19
### Mudanças no código
`pragma omp parallel for` simplérrimo
### Tempo
Comparação entre paralelo e sequencial. 0.1003s (sequencial) vs 0.1012s (paralelo).

Em geral ficaram os dois num tempo semelhante.
### Resultado
OK
### Por que funcionou/não funcionou
**Não** melhorou por conta de falso compartilhamento em `int *cluster`.
### Observações
Tentar resolver esse falso compartilhamento depois

## Juntar `LE_N` e `CLUSTER_ZERO`
**Linha no código sequencial:** 19
### Mudanças no código
Juntar dois `for 0:n` em um só. Um faz `cluster[i] = 0` e outro faz `scanf` em `x`.

`pragma omp parallel for` em cima do for único.
### Tempo
Paralelo 0.0644s vs sequencial 0.0645s. Iguais
### Resultado
OK
### Por que funcionou/não funcionou
**Não** melhorou por conta do mesmo falso compartilhamento do `CLUSTER_ZERO`. **NÃO SEI PORQUE QUE JUNTAR OS DOIS FOR SEQUENCIALMENTE MSM NÃO MELHOROU**
### Observações
Entender isso
