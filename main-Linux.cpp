#include <iostream>
#include <termios.h>
#include <unistd.h>
#define line 15
#define collum 15
#define line2 9
#define collum2 12
#define hollow 0
#define wall 1
#define rightPlace 2
#define afterWall 3
#define box 4
#define player 5
#define boxIn 6
#define playerIn 7
using namespace std;

int getch(void) {
    int ch;
    struct termios oldt, newt;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
}

int main() {
    printf("\033[?25l");

    int pli, pco;
    int options = 0;
    int mapSelection = 0;
    char x;
    bool venceu = false;
    bool desistiu = false;
    int caixasSoltas = 0;

    int boxxle[line][collum] = {
        {3,3,1,1,1,1,1,3,3,3,3,3,3,3,3},
        {3,3,1,0,0,0,1,3,3,3,3,3,3,3,3},
        {3,3,1,0,0,0,1,1,1,1,1,1,3,3,3},
        {3,3,1,0,0,0,0,1,0,0,0,1,3,3,3},
        {3,3,1,1,0,0,0,1,0,0,0,1,3,3,3},
        {3,1,1,1,0,0,0,0,0,0,0,1,3,3,3},
        {1,1,1,1,0,0,1,1,1,0,0,1,3,3,3},
        {1,1,1,1,0,0,1,3,1,0,2,1,3,3,3},
        {1,0,0,4,0,0,1,3,1,0,2,1,3,3,3},
        {1,0,0,4,4,0,1,3,1,0,2,1,3,3,3},
        {1,0,5,0,0,0,1,3,1,1,1,1,3,3,3},
        {1,1,1,1,1,1,1,3,3,3,3,3,3,3,3},
        {3,3,3,3,3,3,3,3,3,3,3,3,3,3,3},
        {3,3,3,3,3,3,3,3,3,3,3,3,3,3,3},
        {3,3,3,3,3,3,3,3,3,3,3,3,3,3,3}
    };

    int boxxle_reset[line][collum] = {
        {3,3,1,1,1,1,1,3,3,3,3,3,3,3,3},
        {3,3,1,0,0,0,1,3,3,3,3,3,3,3,3},
        {3,3,1,0,0,0,1,1,1,1,1,1,3,3,3},
        {3,3,1,0,0,0,0,1,0,0,0,1,3,3,3},
        {3,3,1,1,0,0,0,1,0,0,0,1,3,3,3},
        {3,1,1,1,0,0,0,0,0,0,0,1,3,3,3},
        {1,1,1,1,0,0,1,1,1,0,0,1,3,3,3},
        {1,1,1,1,0,0,1,3,1,0,2,1,3,3,3},
        {1,0,0,4,0,0,1,3,1,0,2,1,3,3,3},
        {1,0,0,4,4,0,1,3,1,0,2,1,3,3,3},
        {1,0,5,0,0,0,1,3,1,1,1,1,3,3,3},
        {1,1,1,1,1,1,1,3,3,3,3,3,3,3,3},
        {3,3,3,3,3,3,3,3,3,3,3,3,3,3,3},
        {3,3,3,3,3,3,3,3,3,3,3,3,3,3,3},
        {3,3,3,3,3,3,3,3,3,3,3,3,3,3,3}
    };

    int boxxle2[line2][collum2] = {
        {3,1,1,1,1,1,3,3,3,3,3,3},
        {3,1,0,0,0,1,1,1,1,1,3,3},
        {3,1,0,4,0,1,0,0,0,1,3,3},
        {3,1,0,0,0,1,4,1,0,1,3,3},
        {3,1,1,1,4,0,0,1,0,1,3,3},
        {3,3,1,0,0,0,0,1,0,1,3,3},
        {3,3,1,0,0,0,0,1,0,1,3,3},
        {3,3,1,0,5,0,2,2,2,1,3,3},
        {3,3,1,1,1,1,1,1,1,1,3,3}
    };

    // copia de segurança do mapa 2 para reset
    int boxxle2_reset[line2][collum2] = {
        {3,1,1,1,1,1,3,3,3,3,3,3},
        {3,1,0,0,0,1,1,1,1,1,3,3},
        {3,1,0,4,0,1,0,0,0,1,3,3},
        {3,1,0,0,0,1,4,1,0,1,3,3},
        {3,1,1,1,4,0,0,1,0,1,3,3},
        {3,3,1,0,0,0,0,1,0,1,3,3},
        {3,3,1,0,0,0,0,1,0,1,3,3},
        {3,3,1,0,5,0,2,2,2,1,3,3},
        {3,3,1,1,1,1,1,1,1,1,3,3}
    };

    cout << "\n1-Autores  2-Orientacoes do jogo  3-Jogar\n";
    cin >> options;

    if (options == 1) {
        cout << "Autores: Isaac Estolano e Pedro Francisco\n";
        cout << "\nPressione qualquer tecla para continuar...";
        getch();
        cout << "\n1-Autores  2-Orientacoes do jogo  3-Jogar\n";
        cin >> options;
    }

    if (options == 2) {
        cout << "==================================================" << endl;
        cout << "              ORIENTACOES DO JOGO                " << endl;
        cout << "==================================================" << endl;
        cout << endl;
        cout << "OBJETIVO:" << endl;
        cout << "Posicione todas as caixas ($) sobre os alvos (-)." << endl;
        cout << "Quando uma caixa chega ao alvo ela vira %." << endl;
        cout << "O nivel esta completo quando nao houver mais $ no mapa." << endl;
        cout << endl;
        cout << "CONTROLES:" << endl;
        cout << "  W - Mover para cima" << endl;
        cout << "  S - Mover para baixo" << endl;
        cout << "  A - Mover para esquerda" << endl;
        cout << "  D - Mover para direita" << endl;
        cout << "  R - Reiniciar o mapa atual" << endl;
        cout << "Nao e necessario pressionar Enter." << endl;
        cout << endl;
        cout << "LEGENDA DO MAPA:" << endl;
        cout << "  @  Jogador" << endl;
        cout << "  ?  Jogador sobre um alvo" << endl;
        cout << "  $  Caixa" << endl;
        cout << "  %  Caixa posicionada no alvo (correta)" << endl;
        cout << "  -  Alvo (destino de uma caixa)" << endl;
        cout << "  &  Parede" << endl;
        cout << "     Espaco vazio / area externa" << endl;
        cout << endl;
        cout << "REGRAS FUNDAMENTAIS:" << endl;
        cout << "  - O jogador so consegue empurrar caixas, nunca puxa-las." << endl;
        cout << "  - So e possivel empurrar uma caixa se o espaco atras" << endl;
        cout << "    dela estiver livre (vazio ou alvo)." << endl;
        cout << "  - Nao e possivel empurrar duas caixas ao mesmo tempo." << endl;
        cout << "  - Caixas nao podem atravessar paredes." << endl;
        cout << endl;
        cout << "DICAS DE ESTRATEGIA:" << endl;
        cout << "  - Planeje antes de agir: um movimento errado pode" << endl;
        cout << "    deixar o nivel sem solucao." << endl;
        cout << "  - Caixas encostadas em cantos ou ao longo de paredes" << endl;
        cout << "    sem alvo proximo ficam travadas para sempre." << endl;
        cout << "  - Observe os alvos e trace o caminho inverso: de onde" << endl;
        cout << "    a caixa precisa vir para chegar la." << endl;
        cout << "  - Se travar, reinicie o nivel com R e tente outra abordagem." << endl;
        cout << endl;
        cout << "==================================================" << endl;
        cout << "        Pressione qualquer tecla para jogar...    " << endl;
        cout << "==================================================" << endl;
        getch();
        options = 3;
    }

    if (options == 3) {
        cout << "Digite 1 para o mapa Boxxle1 e 2 para Boxxle2: ";
        cin >> mapSelection;

        // define coordenadas 
        if (mapSelection == 1) {
            pli = 10;
            pco = 2;
        }
        if (mapSelection == 2) {
            pli = 7;
            pco = 4;
        }
    }

    while (options == 3 && venceu == false && desistiu == false) {

        system("clear");

        if (mapSelection == 1) {
            for (int i = 0; i < line; i++) {
                for (int j = 0; j < collum; j++) {
                    switch (boxxle[i][j]) {
                        case hollow:   
                          cout << " "; 
                          break;
                        case wall:     
                          cout << "&"; 
                          break;
                        case rightPlace: 
                        cout << "-";
                         break;
                        case afterWall: 
                         cout << " "; 
                         break;
                        case box:       
                         cout << "$"; 
                         break;
                        case player:    
                         cout << "@";
                          break;
                        case boxIn:     
                         cout << "%";
                          break;
                        case playerIn: 
                          cout << "?";
                           break;
                        default:   
                          cout << " "; 
                          break;
                    }
                }
                cout << endl;
            }
            cout << "\n[R] Reiniciar  [Q] Desistir" << endl;

            // VERIFICACAO  MAPA 1 
            caixasSoltas = 0;
            for (int i = 0; i < line; i++) {
                for (int j = 0; j < collum; j++) {
                    if (boxxle[i][j] == box) {
                        caixasSoltas = caixasSoltas + 1;
                    }
                }
            }
            if (caixasSoltas == 0) {
                venceu = true;
            }
        }

        if (mapSelection == 2) {
            for (int i = 0; i < line2; i++) {
                for (int j = 0; j < collum2; j++) {
                    switch (boxxle2[i][j]) {
                        case hollow:     
                        cout << " ";
                         break;
                        case wall:     
                          cout << "&"; 
                          break;
                        case rightPlace: 
                        cout << "-"; 
                        break;
                        case afterWall: 
                         cout << " "; 
                         break;
                        case box:     
                           cout << "$";
                            break;
                        case player:    
                         cout << "@";
                          break;
                        case boxIn:  
                            cout << "%";
                             break;
                        case playerIn:   
                            cout << "?"; 
                        break;
                        default:    
                             cout << " ";
                              break;
                    }
                }
                cout << endl;
            }
            cout << "\n[R] Reiniciar  [Q] Desistir" << endl;

            // VERIFICACAO MAPA 2
            caixasSoltas = 0;
            for (int i = 0; i < line2; i++) {
                for (int j = 0; j < collum2; j++) {
                    if (boxxle2[i][j] == box) {
                        caixasSoltas = caixasSoltas + 1;
                    }
                }
            }
            if (caixasSoltas == 0) {
                venceu = true;
            }
        }

        if (venceu == true) {
            cout << "\n==========================================" << endl;
            cout << "        PARABENS! Voce venceu!           " << endl;
            cout << "==========================================" << endl;
            break;
        }

      
        x = getch();

        // RESET
        if (x == 'r') {
            if (mapSelection == 1) {
                for (int i = 0; i < line; i++) {
                    for (int j = 0; j < collum; j++) {
                        boxxle[i][j] = boxxle_reset[i][j];
                    }
                }
                pli = 10;
                pco = 2;
            }
            if (mapSelection == 2) {
                for (int i = 0; i < line2; i++) {
                    for (int j = 0; j < collum2; j++) {
                        boxxle2[i][j] = boxxle2_reset[i][j];
                    }
                }
                pli = 7;
                pco = 4;
            }
        }

        if (x == 'q') {
            desistiu = true;
        }

        if (mapSelection == 1) {
            switch (x) {
            case 'w':
                if (boxxle[pli-1][pco] == wall) {
                    break;
                }
                if (boxxle[pli-1][pco] == box || boxxle[pli-1][pco] == boxIn) {
                    if (boxxle[pli-2][pco] == hollow || boxxle[pli-2][pco] == rightPlace) {
                        if (boxxle[pli-2][pco] == rightPlace) {
                            boxxle[pli-2][pco] = boxIn;
                        }
                        else {
                            boxxle[pli-2][pco] = box;
                        }
                        if (boxxle[pli-1][pco] == boxIn) {
                            boxxle[pli-1][pco] = playerIn;
                        }
                        else {
                            boxxle[pli-1][pco] = player;
                        }
                        if (boxxle[pli][pco] == playerIn) {
                            boxxle[pli][pco] = rightPlace;
                        }
                        else {
                            boxxle[pli][pco] = hollow;
                        }
                        pli--;
                    }
                    break;
                }
                if (boxxle[pli-1][pco] == rightPlace) {
                    boxxle[pli-1][pco] = playerIn;
                }
                else {
                    boxxle[pli-1][pco] = player;
                }
                if (boxxle[pli][pco] == playerIn) {
                    boxxle[pli][pco] = rightPlace;
                }
                else {
                    boxxle[pli][pco] = hollow;
                }
                pli--;
                break;

            case 's':
                if (boxxle[pli+1][pco] == wall) {
                    break;
                }
                if (boxxle[pli+1][pco] == box || boxxle[pli+1][pco] == boxIn) {
                    if (boxxle[pli+2][pco] == hollow || boxxle[pli+2][pco] == rightPlace) {
                        if (boxxle[pli+2][pco] == rightPlace) {
                            boxxle[pli+2][pco] = boxIn;
                        }
                        else {
                            boxxle[pli+2][pco] = box;
                        }
                        if (boxxle[pli+1][pco] == boxIn) {
                            boxxle[pli+1][pco] = playerIn;
                        }
                        else {
                            boxxle[pli+1][pco] = player;
                        }
                        if (boxxle[pli][pco] == playerIn) {
                            boxxle[pli][pco] = rightPlace;
                        }
                        else {
                            boxxle[pli][pco] = hollow;
                        }
                        pli++;
                    }
                    break;
                }
                if (boxxle[pli+1][pco] == rightPlace) {
                    boxxle[pli+1][pco] = playerIn;
                }
                else {
                    boxxle[pli+1][pco] = player;
                }
                if (boxxle[pli][pco] == playerIn) {
                    boxxle[pli][pco] = rightPlace;
                }
                else {
                    boxxle[pli][pco] = hollow;
                }
                pli++;
                break;

            case 'a':
                if (boxxle[pli][pco-1] == wall) {
                    break;
                }
                if (boxxle[pli][pco-1] == box || boxxle[pli][pco-1] == boxIn) {
                    if (boxxle[pli][pco-2] == hollow || boxxle[pli][pco-2] == rightPlace) {
                        if (boxxle[pli][pco-2] == rightPlace) {
                            boxxle[pli][pco-2] = boxIn;
                        }
                        else {
                            boxxle[pli][pco-2] = box;
                        }
                        if (boxxle[pli][pco-1] == boxIn) {
                            boxxle[pli][pco-1] = playerIn;
                        }
                        else {
                            boxxle[pli][pco-1] = player;
                        }
                        if (boxxle[pli][pco] == playerIn) {
                            boxxle[pli][pco] = rightPlace;
                        }
                        else {
                            boxxle[pli][pco] = hollow;
                        }
                        pco--;
                    }
                    break;
                }
                if (boxxle[pli][pco-1] == rightPlace) {
                    boxxle[pli][pco-1] = playerIn;
                }
                else {
                    boxxle[pli][pco-1] = player;
                }
                if (boxxle[pli][pco] == playerIn) {
                    boxxle[pli][pco] = rightPlace;
                }
                else {
                    boxxle[pli][pco] = hollow;
                }
                pco--;
                break;

            case 'd':
                if (boxxle[pli][pco+1] == wall) {
                    break;
                }
                if (boxxle[pli][pco+1] == box || boxxle[pli][pco+1] == boxIn) {
                    if (boxxle[pli][pco+2] == hollow || boxxle[pli][pco+2] == rightPlace) {
                        if (boxxle[pli][pco+2] == rightPlace) {
                            boxxle[pli][pco+2] = boxIn;
                        }
                        else {
                            boxxle[pli][pco+2] = box;
                        }
                        if (boxxle[pli][pco+1] == boxIn) {
                            boxxle[pli][pco+1] = playerIn;
                        }
                        else {
                            boxxle[pli][pco+1] = player;
                        }
                        if (boxxle[pli][pco] == playerIn) {
                            boxxle[pli][pco] = rightPlace;
                        }
                        else {
                            boxxle[pli][pco] = hollow;
                        }
                        pco++;
                    }
                    break;
                }
                if (boxxle[pli][pco+1] == rightPlace) {
                    boxxle[pli][pco+1] = playerIn;
                }
                else {
                    boxxle[pli][pco+1] = player;
                }
                if (boxxle[pli][pco] == playerIn) {
                    boxxle[pli][pco] = rightPlace;
                }
                else {
                    boxxle[pli][pco] = hollow;
                }
                pco++;
                break;
            }
        }

        if (mapSelection == 2) {
            switch (x) {
            case 'w':
                if (boxxle2[pli-1][pco] == wall) {
                    break;
                }
                if (boxxle2[pli-1][pco] == box || boxxle2[pli-1][pco] == boxIn) {
                    if (boxxle2[pli-2][pco] == hollow || boxxle2[pli-2][pco] == rightPlace) {
                        if (boxxle2[pli-2][pco] == rightPlace) {
                            boxxle2[pli-2][pco] = boxIn;
                        }
                        else {
                            boxxle2[pli-2][pco] = box;
                        }
                        if (boxxle2[pli-1][pco] == boxIn) {
                            boxxle2[pli-1][pco] = playerIn;
                        }
                        else {
                            boxxle2[pli-1][pco] = player;
                        }
                        if (boxxle2[pli][pco] == playerIn) {
                            boxxle2[pli][pco] = rightPlace;
                        }
                        else {
                            boxxle2[pli][pco] = hollow;
                        }
                        pli--;
                    }
                    break;
                }
                if (boxxle2[pli-1][pco] == rightPlace) {
                    boxxle2[pli-1][pco] = playerIn;
                }
                else {
                    boxxle2[pli-1][pco] = player;
                }
                if (boxxle2[pli][pco] == playerIn) {
                    boxxle2[pli][pco] = rightPlace;
                }
                else {
                    boxxle2[pli][pco] = hollow;
                }
                pli--;
                break;

            case 's':
                if (boxxle2[pli+1][pco] == wall) {
                    break;
                }
                if (boxxle2[pli+1][pco] == box || boxxle2[pli+1][pco] == boxIn) {
                    if (boxxle2[pli+2][pco] == hollow || boxxle2[pli+2][pco] == rightPlace) {
                        if (boxxle2[pli+2][pco] == rightPlace) {
                            boxxle2[pli+2][pco] = boxIn;
                        }
                        else {
                            boxxle2[pli+2][pco] = box;
                        }
                        if (boxxle2[pli+1][pco] == boxIn) {
                            boxxle2[pli+1][pco] = playerIn;
                        }
                        else {
                            boxxle2[pli+1][pco] = player;
                        }
                        if (boxxle2[pli][pco] == playerIn) {
                            boxxle2[pli][pco] = rightPlace;
                        }
                        else {
                            boxxle2[pli][pco] = hollow;
                        }
                        pli++;
                    }
                    break;
                }
                if (boxxle2[pli+1][pco] == rightPlace) {
                    boxxle2[pli+1][pco] = playerIn;
                }
                else {
                    boxxle2[pli+1][pco] = player;
                }
                if (boxxle2[pli][pco] == playerIn) {
                    boxxle2[pli][pco] = rightPlace;
                }
                else {
                    boxxle2[pli][pco] = hollow;
                }
                pli++;
                break;

            case 'a':
                if (boxxle2[pli][pco-1] == wall) {
                    break;
                }
                if (boxxle2[pli][pco-1] == box || boxxle2[pli][pco-1] == boxIn) {
                    if (boxxle2[pli][pco-2] == hollow || boxxle2[pli][pco-2] == rightPlace) {
                        if (boxxle2[pli][pco-2] == rightPlace) {
                            boxxle2[pli][pco-2] = boxIn;
                        }
                        else {
                            boxxle2[pli][pco-2] = box;
                        }
                        if (boxxle2[pli][pco-1] == boxIn) {
                            boxxle2[pli][pco-1] = playerIn;
                        }
                        else {
                            boxxle2[pli][pco-1] = player;
                        }
                        if (boxxle2[pli][pco] == playerIn) {
                            boxxle2[pli][pco] = rightPlace;
                        }
                        else {
                            boxxle2[pli][pco] = hollow;
                        }
                        pco--;
                    }
                    break;
                }
                if (boxxle2[pli][pco-1] == rightPlace) {
                    boxxle2[pli][pco-1] = playerIn;
                }
                else {
                    boxxle2[pli][pco-1] = player;
                }
                if (boxxle2[pli][pco] == playerIn) {
                    boxxle2[pli][pco] = rightPlace;
                }
                else {
                    boxxle2[pli][pco] = hollow;
                }
                pco--;
                break;

            case 'd':
                if (boxxle2[pli][pco+1] == wall) {
                    break;
                }
                if (boxxle2[pli][pco+1] == box || boxxle2[pli][pco+1] == boxIn) {
                    if (boxxle2[pli][pco+2] == hollow || boxxle2[pli][pco+2] == rightPlace) {
                        if (boxxle2[pli][pco+2] == rightPlace) {
                            boxxle2[pli][pco+2] = boxIn;
                        }
                        else {
                            boxxle2[pli][pco+2] = box;
                        }
                        if (boxxle2[pli][pco+1] == boxIn) {
                            boxxle2[pli][pco+1] = playerIn;
                        }
                        else {
                            boxxle2[pli][pco+1] = player;
                        }
                        if (boxxle2[pli][pco] == playerIn) {
                            boxxle2[pli][pco] = rightPlace;
                        }
                        else {
                            boxxle2[pli][pco] = hollow;
                        }
                        pco++;
                    }
                    break;
                }
                if (boxxle2[pli][pco+1] == rightPlace) {
                    boxxle2[pli][pco+1] = playerIn;
                }
                else {
                    boxxle2[pli][pco+1] = player;
                }
                if (boxxle2[pli][pco] == playerIn) {
                    boxxle2[pli][pco] = rightPlace;
                }
                else {
                    boxxle2[pli][pco] = hollow;
                }
                pco++;
                break;
            }
        }
    }

    if (desistiu == true) {
        system("clear");
        cout << "\n==========================================" << endl;
        cout << "     Voce desistiu. Ate a proxima!       " << endl;
        cout << "==========================================" << endl;
    }
    return 0;
}