# Questão 4 - Comparação AVL vs BST

## Descrição

Implementação que compara o desempenho entre Árvores AVL (auto-balanceadas) e Árvores Binárias de Pesquisa (BST) tradicionais.

### Especificações

- **Dataset**: 1.000.000 de elementos inteiros aleatórios
- **Execuções**: 10 árvores de cada tipo (AVL e BST)
- **Métricas comparadas**:
  - Tempo de criação (inserção de todos os elementos)
  - Altura da árvore resultante
  - Tempo médio de busca (30 consultas por árvore)

### Estruturas Implementadas

#### Árvore Binária de Pesquisa (BST)
- Inserção: O(log n) médio, O(n) pior caso
- Busca: O(log n) médio, O(n) pior caso
- Não garante balanceamento

#### Árvore AVL
- Inserção: O(log n) garantido (com rotações)
- Busca: O(log n) garantido
- Mantém balanceamento automático (fator de balanceamento ≤ 1)
- Altura máxima teórica: ~1.44 * log₂(n) ≈ 29 para 1M elementos

## Compilação

```bash
gcc -o programa main.c ../../shared/arvore.c ../../shared/stats.c -lm -Wall
```

## Execução

```bash
./programa
```

### Monitoramento de Memória

Para verificar o uso de memória:

```bash
/usr/bin/time -v ./programa
```

## Estrutura do Código

### Arquivos Modificados
- `shared/arvore.h` - Adicionadas declarações para AVL
- `shared/arvore.c` - Implementação completa de AVL com rotações

### Tipos Abstratos de Dados
- `Arvore` (BST) - Tipo opaco para árvore binária tradicional
- `ArvoreAVL` - Tipo opaco para árvore AVL balanceada

### Funções Principais (AVL)
- `criar_arvore_avl()` - Cria árvore vazia
- `inserir_avl()` - Insere com balanceamento automático
- `buscar_arvore_avl()` - Busca logarítmica
- `obter_altura()` - Retorna altura da árvore
- `liberar_arvore_avl()` - Libera memória

### Algoritmo de Balanceamento AVL
Implementa 4 casos de rotação:
1. **LL (Left-Left)**: Rotação simples à direita
2. **RR (Right-Right)**: Rotação simples à esquerda
3. **LR (Left-Right)**: Rotação dupla (esquerda + direita)
4. **RL (Right-Left)**: Rotação dupla (direita + esquerda)

## Resultados Esperados

### Tempo de Criação
- **AVL**: Mais lento devido às rotações de balanceamento
- **BST**: Mais rápido, apenas inserções simples

### Altura
- **AVL**: ~20-21 níveis (logarítmica garantida)
- **BST**: Variável, depende da ordem de inserção (pode chegar a centenas)

### Tempo de Busca
- **AVL**: Mais rápido e consistente (O(log n) garantido)
- **BST**: Mais lento se desbalanceada (pode degradar para O(n))

## Observações

- Seed fixa (42) para reprodutibilidade dos resultados
- Mesmo dataset usado para todas as 20 árvores (10 BST + 10 AVL)
- Chaves de busca: 15 garantidas presentes + 15 aleatórias
- Implementação segue princípios de TAD (encapsulamento total)
