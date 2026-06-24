# Boxxle — Sokoban em C++

Implementação do clássico puzzle **Sokoban** em terminal, desenvolvida em C++ para Linux.
O jogador empurra caixas pelos corredores até posicioná-las nos alvos marcados.

---

## Sobre o jogo

Sokoban (倉庫番) é um puzzle japonês criado em 1981. O nome significa *"guardião do armazém"*.
O objetivo é simples: empurre todas as caixas (`$`) até os alvos (`-`). A dificuldade está
no planejamento — uma caixa empurrada contra a parede errada pode travar o nível para sempre.

---

## Requisitos

- Sistema operacional Linux (ou OnlineGDB)
- Compilador g++ com suporte a C++11 ou superior
- Terminal com suporte a sequências ANSI (qualquer terminal moderno)

---

## Compilação e execução

```bash
g++ -o boxxle boxxle.cpp
./boxxle
```

---

## Menu inicial

Ao iniciar o jogo, o seguinte menu é exibido:

```
1-Autores  2-Orientacoes do jogo  3-Jogar
```

Digite o número da opção desejada e pressione Enter. Ao escolher a opção 1 (Autores) ou 2 (Orientações),
o jogo retorna automaticamente para a opção de jogar ao pressionar qualquer tecla.

---

## Seleção de mapa

Após escolher jogar, o jogo pergunta qual mapa carregar:

```
Digite 1 para o mapa Boxxle1 e 2 para Boxxle2
```

Cada mapa tem seu próprio layout, posição inicial do jogador e conjunto de caixas e alvos.

---

## Controles

| Tecla | Ação                        |
|-------|-----------------------------|
| `W`   | Mover para cima             |
| `S`   | Mover para baixo            |
| `A`   | Mover para esquerda         |
| `D`   | Mover para direita          |
| `R`   | Reiniciar o mapa atual      |
| `Q`   | Desistir e encerrar o jogo  |

Não é necessário pressionar Enter — o jogo lê a tecla instantaneamente.

---

## Legenda do mapa

| Símbolo | Significado                         |
|---------|-------------------------------------|
| `@`     | Jogador                             |
| `?`     | Jogador sobre um alvo               |
| `$`     | Caixa                               |
| `%`     | Caixa posicionada no alvo (correta) |
| `-`     | Alvo (destino de uma caixa)         |
| `&`     | Parede                              |
| ` `     | Espaço vazio / área externa         |

---

## Orientações do jogo

**Objetivo:** posicione todas as caixas (`$`) sobre os alvos (`-`).
Quando uma caixa chega ao alvo ela vira `%`. O nível está completo quando não houver mais `$` no mapa
e a mensagem de vitória é exibida.

**Regras fundamentais:**

- O jogador só consegue **empurrar** caixas, nunca puxá-las.
- Só é possível empurrar uma caixa se o espaço atrás dela estiver **livre** (vazio ou alvo).
- Não é possível empurrar **duas caixas ao mesmo tempo**.
- Caixas não podem atravessar paredes.

**Dicas de estratégia:**

- Planeje antes de agir — um movimento errado pode deixar o nível sem solução.
- Caixas encostadas em cantos ou ao longo de paredes sem alvo próximo ficam travadas para sempre.
- Observe a posição dos alvos e tente traçar o caminho inverso: de onde a caixa precisa vir para chegar lá.
- Se travar, pressione `R` para reiniciar o mapa e tente uma abordagem diferente.
- Se o nível estiver impossível de resolver, pressione `Q` para desistir.

---

## Estrutura do código

```
boxxle.cpp
├── getch()        — leitura de tecla sem buffer (sem precisar de Enter)
└── main()
    ├── Matrizes dos mapas
    │   ├── boxxle[15][15]        — mapa 1 (estado atual)
    │   ├── boxxle_reset[15][15]  — cópia do mapa 1 para reset
    │   ├── boxxle2[9][12]        — mapa 2 (estado atual)
    │   └── boxxle2_reset[9][12]  — cópia do mapa 2 para reset
    ├── Menu inicial (opções 1, 2, 3)
    ├── Seleção de mapa e inicialização de pli/pco
    └── Loop principal (while)
        ├── system("clear")
        ├── Renderização do mapa ativo
        ├── Verificação de vitória (contagem de caixas soltas)
        ├── getch() — leitura de tecla
        ├── Tratamento de R (reset) e Q (desistência)
        └── Lógica de movimento W/A/S/D para o mapa ativo
```

### Estados internos da matriz

O mapa é representado por uma matriz de inteiros onde cada valor é um estado:

| Constante    | Valor | Descrição              |
|--------------|-------|------------------------|
| `hollow`     | 0     | Espaço vazio           |
| `wall`       | 1     | Parede                 |
| `rightPlace` | 2     | Alvo                   |
| `afterWall`  | 3     | Área externa ao mapa   |
| `box`        | 4     | Caixa                  |
| `player`     | 5     | Jogador                |
| `boxIn`      | 6     | Caixa sobre o alvo     |
| `playerIn`   | 7     | Jogador sobre o alvo   |

### Lógica de movimento

Cada tecla de direção segue sempre a mesma sequência de verificações:

1. Se a célula à frente é parede, não faz nada.
2. Se a célula à frente é caixa (`box` ou `boxIn`), verifica se a célula seguinte está livre para empurrar.
3. Se pode empurrar, atualiza as três células envolvidas: destino da caixa, célula do meio (onde o player chega) e célula de origem (onde o player estava), preservando `rightPlace` quando necessário.
4. Se a célula à frente é livre, move o player diretamente, preservando `rightPlace` na célula de origem se o player estava em `playerIn`.

### Verificação de vitória

Após cada renderização, o jogo percorre a matriz inteira com dois `for` aninhados contando quantas células contêm `box`. Se o contador chegar a zero significa que todas as caixas estão em `boxIn` e o jogo exibe a mensagem de vitória encerrando o loop.

### Reset de mapa

Cada mapa possui uma matriz de backup (`boxxle_reset` e `boxxle2_reset`) com o estado inicial. Ao pressionar `R`, o jogo copia o backup de volta para a matriz ativa célula por célula e restaura as coordenadas `pli` e `pco` do jogador para a posição inicial do mapa.

---

## Autores

Código base por **Isaac Estolano**.
Desenvolvimento, correções de lógica e novas funcionalidades por **Isaac Estolano** e **Pedro Francisco**.

---

## Observações técnicas

- A função `getch()` usa `termios.h` para desativar o modo canônico do terminal, permitindo leitura de tecla imediata sem buffer e sem precisar pressionar Enter.
- O cursor do terminal é ocultado no início com `\033[?25l` para evitar piscadas visuais durante a renderização.
- Compatível com **OnlineGDB** e terminais Linux padrão.