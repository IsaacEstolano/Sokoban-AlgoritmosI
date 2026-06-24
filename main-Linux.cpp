/*
  Código criado por Thiago Felski Pereira
  Move um caractere na matriz sem testes
  Útil para implementação de jogos
  com movimentação de personagem.
  (Típicos de algoritmos 1)
  Versão para OnlineGDB / Linux usando termios.h
*/
#include <iostream>
#include <termios.h>
#include <unistd.h>
#define line 15
#define collum 15
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
  struct termios oldt;
  struct termios newt;
  tcgetattr(STDIN_FILENO, &oldt); // guarda as configurações antigas
  newt = oldt; // copia as configurações antigas para as novas
  newt.c_lflag &= ~(ICANON | ECHO); // faz uma mudança nas novas configurações
  tcsetattr(STDIN_FILENO, TCSANOW, &newt); // aplica as novas configurações
  ch = getchar();                          // pega a tecla
  tcsetattr(STDIN_FILENO, TCSANOW, &oldt); // restaura as configurações antigas
  return ch;                               // retorna o caractere lido
}
void SetCursorPos(int XPos, int YPos) {
  printf("\033[%d;%dH", YPos + 1, XPos + 1);
}
int main() {
  printf("\033[?25l"); //código para o desativar o cursor no console    
    
  int pli = 10, pco = 2; // pli e pco são a line e a collum do personagem na matriz
  int options=0;
  int mapSelection=0;
int boxxle[line][collum] =
{
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
int boxxle2[12][12] =
{
 {3,1,1,1,1,1,3,3,3,3,3,3},
 {3,1,0,0,0,1,1,1,1,1,3,3},
 {3,1,0,4,0,1,0,0,0,1,3,3},
 {3,1,0,0,0,1,4,1,0,1,3,3},
 {3,1,1,1,4,0,0,1,0,1,3,3},
 {3,3,1,0,0,0,0,1,0,1,3,3},
 {3,3,1,0,0,0,0,1,0,1,3,3},
 {3,3,1,0,5,0,2,2,2,1,3,3},
 {3,3,1,1,1,1,1,1,1,1,3,3},
 {3,3,3,3,3,3,3,3,3,3,3,3},
 {3,3,3,3,3,3,3,3,3,3,3,3},
 {3,3,3,3,3,3,3,3,3,3,3,3}
};
  char x;
  
  while (true) {
    if(options!=3){
      cout << "\n1-Autores 2-Orientações do jogo 3-Jogar;\n";
      cin>>options;

    }
    if(options==1){
      cout<<"Autores:Isaac Estolano e Pedro Francisco";
    }  
  if(options==2){
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
    cout << "  - Se travar, reinicie o nivel e tente outra abordagem." << endl;
    cout << endl;
    cout << "==================================================" << endl;
    cout << "        Pressione qualquer tecla para voltar...   " << endl;
    cout << "==================================================" << endl;
  }
      // imprime matriz
if(options==3){
  if(mapSelection!=1 || mapSelection!=2){
    cout<<"Digite 1 para o mapa Boxxle1 e 2 para Boxxle2";
    cin>>mapSelection;
  }
  if(mapSelection==1){
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
          cout<<"-";
          break;
          case afterWall:
          cout<<" ";
          break;
        case box:
          cout<<"$";
          break;
        case player:
          cout << "@";    
          break;
        case boxIn:
          cout<<"%";
          break;
        case playerIn:
          cout<<"?";
          break;
        default:
          cout << " ";
        }
      }
      cout << endl;
    }
    //cout << "texto depois da matriz\n";
    // atualiza jogador
    x = getch(); // pega a tecla
    switch (x) {
    case 'w':
    if (boxxle[pli-1][pco] == wall)
        break;
    
    // --- Empurrar caixa ---
    if (boxxle[pli-1][pco] == box || boxxle[pli-1][pco] == boxIn)
    {
        if (boxxle[pli-2][pco] == hollow || boxxle[pli-2][pco] == rightPlace)
        {
            // Destino da caixa
            if (boxxle[pli-2][pco] == rightPlace){
              boxxle[pli-2][pco] = boxIn;
            }
            else
                boxxle[pli-2][pco] = box;
    
            // Célula onde o player vai pisar (onde estava a caixa)
            if (boxxle[pli-1][pco] == boxIn)
                boxxle[pli-1][pco] = playerIn;
            else
                boxxle[pli-1][pco] = player;
    
            // Célula que o player deixa
            if (boxxle[pli][pco] == playerIn)
                boxxle[pli][pco] = rightPlace;
            else
                boxxle[pli][pco] = hollow;
    
            pli--;
        }
        break;
    }
    
    // --- Movimento simples ---
    if (boxxle[pli-1][pco] == rightPlace)
        boxxle[pli-1][pco] = playerIn;
    else
        boxxle[pli-1][pco] = player;
    
    if (boxxle[pli][pco] == playerIn)
        boxxle[pli][pco] = rightPlace;
    else
        boxxle[pli][pco] = hollow;
    
    pli--;
    break;
    
      
    case 's':
    
    if (boxxle[pli+1][pco] == wall)
        break;
    
    // --- Empurrar caixa ---
    if (boxxle[pli+1][pco] == box || boxxle[pli+1][pco] == boxIn)
    {
        if (boxxle[pli+2][pco] == hollow || boxxle[pli+2][pco] == rightPlace)
        {
            // Destino da caixa
            if (boxxle[pli+2][pco] == rightPlace){
              boxxle[pli+2][pco] = boxIn;
            }
            else{
              boxxle[pli+2][pco] = box;
            }
    
            // Célula onde o player vai pisar
            if (boxxle[pli+1][pco] == boxIn){
    
              boxxle[pli+1][pco] = playerIn;
            }
            else{
              boxxle[pli+1][pco] = player;
    
            }
    
            // Célula que o player deixa
            if (boxxle[pli][pco] == playerIn){
              boxxle[pli][pco] = rightPlace;
            }
            else{
              boxxle[pli][pco] = hollow;
    
            }
    
            pli+=1;
        }
        break;
    }
    
    // --- Movimento simples ---
    if (boxxle[pli+1][pco] == rightPlace)
        boxxle[pli+1][pco] = playerIn;
    else
        boxxle[pli+1][pco] = player;
    
    if (boxxle[pli][pco] == playerIn)
        boxxle[pli][pco] = rightPlace;
    else
        boxxle[pli][pco] = hollow;
    
    pli++;
    break;
    
    
    
    case 'a':
    if(boxxle[pli][pco-1] == wall){
        break;
    }
    
    if(boxxle[pli][pco-1] == box)
    {
        if(boxxle[pli][pco-2] == hollow ||boxxle[pli][pco-2] == rightPlace)
        {
            if(boxxle[pli][pco-2] == rightPlace)
            {
                boxxle[pli][pco-2] = boxIn;
            }
            else{
              boxxle[pli][pco-2]=box;
            }
    
            if(boxxle[pli][pco]== boxIn){
              boxxle[pli][pco]=playerIn;
            }
            else{
              boxxle[pli][pco]=player;
            }
    
            if(boxxle[pli][pco]==playerIn){
              boxxle[pli][pco]=rightPlace;
            }
            else{
              boxxle[pli][pco]=hollow;
            }
            pli-=1;
        }
        break;
    }
    if (boxxle[pli][pco-1] == rightPlace)
        boxxle[pli][pco-1] = playerIn;
    else
        boxxle[pli][pco-1] = player;
    
    if (boxxle[pli][pco] == playerIn)
        boxxle[pli][pco] = rightPlace;
    else
        boxxle[pli][pco] = hollow;
    
    pco--;
    break;
    
    
      
    break;
    
    
    case 'd':
    if (boxxle[pli][pco+1] == wall)
        break;
    
    // --- Empurrar caixa ---
    if (boxxle[pli][pco+1] == box || boxxle[pli][pco+1] == boxIn)
    {
        if (boxxle[pli][pco+2] == hollow || boxxle[pli][pco+2] == rightPlace)
        {
            // Destino da caixa
            if (boxxle[pli][pco+2] == rightPlace)
                boxxle[pli][pco+2] = boxIn;
            else
                boxxle[pli][pco+2] = box;
    
            // Célula onde o player vai pisar (onde estava a caixa)
            if (boxxle[pli][pco+1] == boxIn)
                boxxle[pli][pco+1] = playerIn;
            else
                boxxle[pli][pco+1] = player;
    
            // Célula que o player deixa
            if (boxxle[pli][pco] == playerIn)
                boxxle[pli][pco] = rightPlace;
            else
                boxxle[pli][pco] = hollow;
    
            pco++;
        }
        break;
    }
    
    // --- Movimento simples ---
    if (boxxle[pli][pco+1] == rightPlace)
        boxxle[pli][pco+1] = playerIn;
    else
        boxxle[pli][pco+1] = player;
    
    if (boxxle[pli][pco] == playerIn)
        boxxle[pli][pco] = rightPlace;
    else
        boxxle[pli][pco] = hollow;
    
    pco++;
    break;
    // coloca o cursor na posição inicial
    system("clear");
    }
  }
  if(mapSelection==2){
     for (int i = 0; i < line; i++) {
      for (int j = 0; j < collum; j++) {
        switch (boxxle2[i][j]) {
        case hollow:
          cout << " ";
          break;
        case wall:
          cout << "&";
          break;
        case rightPlace:
          cout<<"-";
          break;
          case afterWall:
          cout<<" ";
          break;
        case box:
          cout<<"$";
          break;
        case player:
          cout << "@";    
          break;
        case boxIn:
          cout<<"%";
          break;
        case playerIn:
          cout<<"?";
          break;
        default:
          cout << " ";
        }
      }
      cout << endl;
    }
    //cout << "texto depois da matriz\n";
    // atualiza jogador
    x = getch(); // pega a tecla
    switch (x) {
    case 'w':
    if (boxxle2[pli-1][pco] == wall)
        break;
    
    // --- Empurrar caixa ---
    if (boxxle2[pli-1][pco] == box || boxxle2[pli-1][pco] == boxIn)
    {
        if (boxxle2[pli-2][pco] == hollow || boxxle2[pli-2][pco] == rightPlace)
        {
            // Destino da caixa
            if (boxxle2[pli-2][pco] == rightPlace)
                boxxle2[pli-2][pco] = boxIn;
            else
                boxxle2[pli-2][pco] = box;
    
            // Célula onde o player vai pisar (onde estava a caixa)
            if (boxxle2[pli-1][pco] == boxIn)
                boxxle2[pli-1][pco] = playerIn;
            else
                boxxle2[pli-1][pco] = player;
    
            // Célula que o player deixa
            if (boxxle2[pli][pco] == playerIn)
                boxxle2[pli][pco] = rightPlace;
            else
                boxxle2[pli][pco] = hollow;
    
            pli--;
        }
        break;
    }
    
    // --- Movimento simples ---
    if (boxxle2[pli-1][pco] == rightPlace)
        boxxle2[pli-1][pco] = playerIn;
    else
        boxxle2[pli-1][pco] = player;
    
    if (boxxle2[pli][pco] == playerIn)
        boxxle2[pli][pco] = rightPlace;
    else
        boxxle2[pli][pco] = hollow;
    
    pli--;
    break;
    
      
    case 's':
    
    if (boxxle2[pli+1][pco] == wall)
        break;
    
    // --- Empurrar caixa ---
    if (boxxle2[pli+1][pco] == box || boxxle2[pli+1][pco] == boxIn)
    {
        if (boxxle2[pli+2][pco] == hollow || boxxle2[pli+2][pco] == rightPlace)
        {
            // Destino da caixa
            if (boxxle2[pli+2][pco] == rightPlace){
              boxxle2[pli+2][pco] = boxIn;
            }
            else{
              boxxle2[pli+2][pco] = box;
            }
    
            // Célula onde o player vai pisar
            if (boxxle2[pli+1][pco] == boxIn){
    
              boxxle2[pli+1][pco] = playerIn;
            }
            else{
              boxxle2[pli+1][pco] = player;
    
            }
    
            // Célula que o player deixa
            if (boxxle2[pli][pco] == playerIn){
              boxxle2[pli][pco] = rightPlace;
            }
            else{
              boxxle2[pli][pco] = hollow;
    
            }
    
            pli+=1;
        }
        break;
    }
    
    // --- Movimento simples ---
    if (boxxle2[pli+1][pco] == rightPlace)
        boxxle2[pli+1][pco] = playerIn;
    else
        boxxle2[pli+1][pco] = player;
    
    if (boxxle2[pli][pco] == playerIn)
        boxxle2[pli][pco] = rightPlace;
    else
        boxxle2[pli][pco] = hollow;
    
    pli++;
    break;
    
    case 'a':
    if(boxxle2[pli][pco-1] == wall){
        break;
    }
    
    if(boxxle2[pli][pco-1] == box)
    {
        if(boxxle2[pli][pco-2] == hollow ||boxxle2[pli][pco-2] == rightPlace)
        {
            if(boxxle2[pli][pco-2] == rightPlace)
            {
                boxxle2[pli][pco-2] = boxIn;
            }
            else{
              boxxle2[pli][pco-2]=box;
            }
    
            if(boxxle2[pli][pco]== boxIn){
              boxxle2[pli][pco]=playerIn;
            }
            else{
              boxxle2[pli][pco]=player;
            }
    
            if(boxxle2[pli][pco]==playerIn){
              boxxle2[pli][pco]=rightPlace;
            }
            else{
              boxxle2[pli][pco]=hollow;
            }
            pli-=1;
        }
        break;
    }
    if (boxxle2[pli][pco-1] == rightPlace)
        boxxle2[pli][pco-1] = playerIn;
    else
        boxxle2[pli][pco-1] = player;
    
    if (boxxle2[pli][pco] == playerIn)
        boxxle2[pli][pco] = rightPlace;
    else
        boxxle2[pli][pco] = hollow;
    
    pco--;
    break;
      
    break;
    case 'd':
    if (boxxle2[pli][pco+1] == wall)
        break;
    
    // --- Empurrar caixa ---
    if (boxxle2[pli][pco+1] == box || boxxle2[pli][pco+1] == boxIn)
    {
        if (boxxle2[pli][pco+2] == hollow || boxxle2[pli][pco+2] == rightPlace)
        {
            // Destino da caixa
            if (boxxle2[pli][pco+2] == rightPlace)
                boxxle2[pli][pco+2] = boxIn;
            else
                boxxle2[pli][pco+2] = box;
    
            // Célula onde o player vai pisar (onde estava a caixa)
            if (boxxle2[pli][pco+1] == boxIn)
                boxxle2[pli][pco+1] = playerIn;
            else
                boxxle2[pli][pco+1] = player;
    
            // Célula que o player deixa
            if (boxxle2[pli][pco] == playerIn)
                boxxle2[pli][pco] = rightPlace;
            else
                boxxle2[pli][pco] = hollow;
    
            pco++;
        }
        break;
    }
    
    // --- Movimento simples ---
    if (boxxle2[pli][pco+1] == rightPlace)
        boxxle2[pli][pco+1] = playerIn;
    else
        boxxle2[pli][pco+1] = player;
    
    if (boxxle2[pli][pco] == playerIn)
        boxxle2[pli][pco] = rightPlace;
    else
        boxxle2[pli][pco] = hollow;
    
    pco++;
    break;
    // coloca o cursor na posição inicial
    system("clear");
    }
  }
}
  }
return 0;
}

