# Sokoban em C++

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

## Controles

| Tecla | Ação            |
|-------|-----------------|
| `W`   | Mover para cima |
| `S`   | Mover para baixo|
| `A`   | Mover para esquerda |
| `D`   | Mover para direita  |

> Não é necessário pressionar Enter — o jogo lê a tecla instantaneamente.

---

## Legenda do mapa

| Símbolo | Significado                        |
|---------|------------------------------------|
| `@`     | Jogador                            |
| `?`     | Jogador sobre um alvo              |
| `$`     | Caixa                              |
| `%`     | Caixa posicionada no alvo (correta)|
| `-`     | Alvo (destino de uma caixa)        |
| `&`     | Parede                             |
| ` `     | Espaço vazio / área externa        |

---

## Orientações do jogo

**Objetivo:** posicione todas as caixas (`$`) sobre os alvos (`-`).
Quando uma caixa chega ao alvo ela vira `%`. O nível está completo quando não houver mais `$` no mapa.

**Regras fundamentais:**

- O jogador só consegue **empurrar** caixas, nunca puxá-las.
- Só é possível empurrar uma caixa se o espaço atrás dela estiver **livre** (vazio ou alvo).
- Não é possível empurrar **duas caixas ao mesmo tempo**.
- Caixas não podem atravessar paredes.

**Dicas de estratégia:**

- Planeje antes de agir — um movimento errado pode deixar o nível sem solução.
- Caixas encostadas em cantos ou ao longo de paredes sem alvo próximo ficam travadas para sempre.
- Observe a posição dos alvos e tente traçar o caminho inverso: de onde a caixa precisa vir para chegar lá.
- Se travar, reinicie o nível e tente uma abordagem diferente.

---

## Estrutura do código

```
boxxle.cpp
├── getch()          — leitura de tecla sem buffer (sem precisar de Enter)
├── SetCursorPos()   — posicionamento do cursor no terminal via ANSI
└── main()
    ├── Matriz do mapa (boxxle[15][15])
    ├── Loop principal
    │   ├── Renderização do mapa
    │   ├── Leitura de tecla
    │   └── Lógica de movimento (W/A/S/D)
    └── system("clear") — limpa o terminal a cada frame
```

### Estados internos da matriz

O mapa é representado por uma matriz de inteiros onde cada valor é um estado:

| Constante   | Valor | Descrição                    |
|-------------|-------|------------------------------|
| `hollow`    | 0     | Espaço vazio                 |
| `wall`      | 1     | Parede                       |
| `rightPlace`| 2     | Alvo                         |
| `afterWall` | 3     | Área externa ao mapa         |
| `box`       | 4     | Caixa                        |
| `player`    | 5     | Jogador                      |
| `boxIn`     | 6     | Caixa sobre o alvo           |
| `playerIn`  | 7     | Jogador sobre o alvo         |

---

## Autores

Código base por **Thiago Felski Pereira**.
Adaptações e correções de lógica (`playerIn`, `boxIn`, movimentação) realizadas durante o desenvolvimento.

---

## Observações técnicas

- A função `getch()` usa `termios.h` para desativar o modo canônico do terminal,
  permitindo leitura de tecla imediata sem buffer.
- O cursor do terminal é ocultado no início com `\033[?25l` para evitar piscadas visuais.
- Compatível com **OnlineGDB** e terminais Linux padrão.