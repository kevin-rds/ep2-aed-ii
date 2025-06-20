# EP2 - Centralidade em Redes Sociais (ACH2024 - 1º Semestre de 2025)

## 📌 Descrição

Este repositório contém a implementação do **Segundo Exercício-Programa** da disciplina **ACH2024 - Estruturas de Dados**, ministrada pelo Prof. Luciano Antonio Digiampietri, na Universidade de São Paulo (USP).

O objetivo do trabalho é implementar diferentes medidas de **centralidade em grafos direcionados e não ponderados**, com aplicação no contexto de **redes sociais**.

## 👨‍💻 Autor

- **Nome**: Kevin Rodrigues Nunes   
- **Turma**: ACH2024-2025104
- Professor: Luciano Digiampietri (reponsável por todos os códigos presentes no .c base "completeERenomeie.c")

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

## 📂 Estrutura do projeto

- `completeERenomeie.c` – Arquivo base disponibilizado pela disciplina.
- `ep2.c` – Arquivo final com todas as funções implementadas, pronto para submissão.
- `saida.txt` – Arquivo com os resultados gerados pelos testes fornecidos no enunciado.

> ⚠️ O código foi escrito respeitando as assinaturas e estruturas fornecidas.

## 🛠️ Como compilar e executar

```bash
gcc -o ep2 ep2.c
./ep2
