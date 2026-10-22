# -itp-avaliacao2
 Identificação: Caywan Cleyton Silva Rodrigues 
 
 Descrição: O programa registra três notas de cada estudante de uma turma e gera um resumo dos resultados.
 
 Funcionalidades implementadas:
 Solicita a quantidade de estudantes (entre 1 e 10) e o nome de cada um, recusando nomes vazios.
 Lê três notas por estudante, aceitando apenas valores entre 0 e 10 e pedindo a nota novamente quando ela é inválida.
 Armazena as notas em uma matriz: as linhas representam os estudantes e as colunas representam as avaliações.
 Calcula a média aritmética de cada estudante e a armazena em um vetor alocado dinamicamente (calloc), com uma posição por estudante.
 Exibe uma tabela com nome, notas, média e situação. A situação é "atingiu a meta" quando a média é maior ou igual a 6, e "abaixo da meta" nos demais casos.
 Exibe a média geral da turma e o nome de quem obteve a maior média. Em caso de empate, todos os nomes empatados são exibidos.
 
 Compilação e execução: 
 Requisito: compilador GCC.
 Para compilar:
 gcc -Wall -Wextra -o boletim_turma boletim_turma.c
 Para executar:
 ./boletim_turma
 
 Testes:
 ### Teste 1 – Funcionamento normal

**Entradas:**

| Campo | Valor |
|---|---|
| Quantidade de estudantes | 3 |
| Nomes | Ana, Bruno, Carla |
| Notas de Ana | 5, 6, 7 |
| Notas de Bruno | 8, 8, 8 |
| Notas de Carla | 4, 4, 4 |

**Saída esperada:**

Nome                            Nota 1  Nota 2  Nota 3   Media  Situacao
Ana                               5.00    6.00    7.00    6.00  atingiu a meta
Bruno                             8.00    8.00    8.00    8.00  atingiu a meta
Carla                             4.00    4.00    4.00    4.00  abaixo da meta

Media geral da turma: 6.00
Maior media: 8.00
Estudante(s) com a maior media:
  - Bruno
Para as notas 5, 6 e 7, a média é 6,00 e a situação é "atingiu a meta".

### Teste 2 – Entrada inválida

**Entradas:** 1 estudante chamado Ana. Na primeira nota, é digitado `11`. Depois são digitadas as notas 5, 6 e 7.

**Saída esperada:** o programa rejeita o valor 11 e solicita a nota novamente.

Ana - nota 1 (0 a 10): Nota invalida. A nota deve estar entre 0 e 10.
Ana - nota 1 (0 a 10):

Em seguida, com as notas 5, 6 e 7, o resultado é média 6,00 e "atingiu a meta".

### Teste 3 – Empate na maior média

**Entradas:** 2 estudantes, Ana e Bia, com todas as notas iguais a 9.

**Saída esperada:** a maior média é 9,00 e os dois nomes são exibidos:

Maior media: 9.00
Estudante(s) com a maior media:
  - Ana
  - Bia
 
 Vídeo: https://www.youtube.com/watch?v=jZlgpppoO8k
 
 Referências: Usei como base as vídeo aulas e documentos disponibilizados pelo professor
