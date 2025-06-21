# EP2 - Centralidade em Redes Sociais (ACH2024 - 1º Semestre de 2025)

## 📌 Descrição

Este repositório contém a implementação do **Segundo Exercício-Programa** da disciplina **ACH2024 - Algoritmos e Estruturas de Dados**, ministrada pelo Prof. Luciano Antonio Digiampietri, na Universidade de São Paulo (USP).

O objetivo do trabalho é implementar diferentes medidas de **centralidade em grafos direcionados e não ponderados**, com aplicação no contexto de **redes sociais**.

## 👨‍💻 Autor

- **Nome**: Kevin Rodrigues Nunes   
- **Turma**: ACH2024-2025104
- **Professor**: Luciano Digiampietri (reponsável por todos os códigos presentes no .c base "completeERenomeie.c")

## 🧠 Conceitos abordados

As medidas de centralidade implementadas são:

1. **Centralidade de Grau (Degree Centrality)**  
   Mede o número de conexões que um vértice recebe.

2. **Centralidade de Proximidade (Closeness Centrality)**  
   Mede a proximidade de um nó em relação aos outros da rede.

3. **Centralidade de Intermediação (Betweenness Centrality)**  
   Mede a frequência com que um vértice aparece nos caminhos mais curtos entre outros nós.

4. **PageRank**  
   Mede a importância de um nó com base na importância dos nós que apontam para ele, utilizando um algoritmo iterativo com fator de amortecimento.

## 🔍 Estrutura do Projeto

```plaintext
📁 ep2-aed-ii
├── ep2.c                        # Arquivo principal do projeto
├── saida_obtida.txt             # Saída gerada pela execução
├── README.md                    # Documentação do projeto
├── base_docs/                   # Arquivos fornecidos como base
│   ├── ep2.pdf                  # Enunciado do exercício-programa
│   ├── completeERenomeie.c      # Código base a ser completado
│   └── saida_esperada.txt       # Exemplo de saída esperada
```

> ⚠️ O código foi escrito respeitando as assinaturas e estruturas fornecidas.

## 🛠️ Como compilar e executar

```bash
gcc -o ep2 ep2.c
./ep2
