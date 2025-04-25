# Projeto de Integração de Estradas em Wakanda

Este projeto foi desenvolvido como parte de uma atividade avaliativa da disciplina de Estruturas de Dados da Universidade Católica de Brasília (UCB). O objetivo é determinar a menor vizinhança de estrada entre cidades ao longo de uma rodovia reta, conforme as especificações do Rei T'Challa de Wakanda.

---

## Funcionalidades

1. **Leitura de Dados**: Processa um arquivo de entrada contendo o comprimento total da estrada e as posições/nomes das cidades.
2. **Validação de Restrições**:
   - Comprimento da estrada (`T`): `3 ≤ T ≤ 10^6`.
   - Número de cidades (`N`): `2 ≤ N ≤ 10^4`.
   - Posições das cidades: `0 < Xi < T` e únicas.
3. **Cálculo da Menor Vizinhança**:
   - Determina o menor trecho da estrada que é mais próximo de uma cidade do que de qualquer outra.
4. **Identificação da Cidade com Menor Vizinhança**:
   - Retorna o nome da cidade associada à menor vizinhança.

---

## Estrutura do Projeto

### Arquivos Principais:
- `cidades.h`: Define os Tipos Abstratos de Dados (TADs) `Cidade` e `Estrada`.
- `cidades.c`: Implementa as funções de leitura, validação e cálculo.
- `main.c` (exemplo): Demonstra a utilização das funções.

### Funções Implementadas:
- `Estrada *getEstrada(const char *nomeArquivo)`: Carrega e valida os dados do arquivo.
- `double calcularMenorVizinhanca(const char *nomeArquivo)`: Retorna a menor vizinhança.
- `char *cidadeMenorVizinhanca(const char *nomeArquivo)`: Retorna o nome da cidade com a menor vizinhança.

---

## Pré-requisitos:
- Compilador C (ex: GCC).
- Sistema operacional Windows/Linux/macOS.
