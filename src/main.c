#include "raylib.h"
#include <stdlib.h>
#include <stdio.h>
#include "cores.h"

#define LARGURA_BASE 1920.0f
#define ALTURA_BASE 1080.0f

float largura_tela = 0;
float altura_tela = 0;
Font Fo;

void fundo_base(int *menu, float *loja_barra);
void loja(int menu, float *loja_barra);
void barra_lateral_scroll(Vector2 pos1, Vector2 pos2, float *agora, Color C, Color C2, Color C3);
void Texto(const char *texto, int x, int y, int tam, Color C);
bool botao(const char *texto, int tam, float x, float y, float x2, float y2, Color C, Color C2);


float map(float valor, float entrada_min, float entrada_max, float saida_min, float saida_max);
float X(float valor);
float Y(float valor);
float S(float valor);

int main(void) {
    InitWindow(500, 500, "Steam IFSC");
    largura_tela = GetMonitorWidth(0);
    altura_tela = GetMonitorHeight(0);
    SetWindowSize(largura_tela, altura_tela);
    ToggleFullscreen();

    Fo = LoadFont("assets/fonts/Roboto-Condensed.ttf");

    if (!IsFontValid(Fo)) {
        TraceLog(LOG_ERROR, "Nao foi possivel carregar a fonte!");
    }

    SetTargetFPS(60);

    int menu = 0;
    float loja_barra = 0;
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(VERDE_SUPER_IPER_MEGA_ESCURO);
        loja(menu, &loja_barra);
        fundo_base(&menu, &loja_barra);
        EndDrawing();
    }
    UnloadFont(Fo);
    CloseWindow();
    return 0;
}



void loja(int menu, float *loja_barra){
    if (menu != 0) return;
    int desce = (*loja_barra) * 50; 
    barra_lateral_scroll((Vector2){largura_tela - X(20), Y(70)}, (Vector2){X(20), altura_tela - Y(100)}, loja_barra, VERDE_SUPER_ESCURO, VERDE_SUPER_IPER_ESCURO, VERDE_SUPER_IPER_QUASE_MEGA_ESCURO);
    DrawRectangleLines(largura_tela - X(20), Y(70), X(20), altura_tela - Y(100), VERDE_SUPER_IPER_QUASE_MEGA_ESCURO);
    //DrawLine(largura_tela - 20, 60, largura_tela - 20, altura_tela - 30, VERDE_SUPER_IPER_QUASE_MEGA_ESCURO);
    //Base
    DrawRectangleRounded((Rectangle){X(200), Y(170) - desce, X(1520), Y(500)}, 0.1f, 1, VERDE_SUPER_ESCURO);
    DrawRectangleRounded((Rectangle){X(230), Y(105) - desce, X(40) + MeasureTextEx(Fo, "Jogos em destaque:", S(40), 2).x, Y(50)}, 0.1, 1, VERDE_SUPER_IPER_ESCURO);
    Texto("Jogos em destaque:", X(250), Y(110) - desce, S(40), WHITE);
    DrawLineEx((Vector2){X(960), Y(180) - desce}, (Vector2){X(960), Y(660) - desce}, S(5), VERDE_SUPER_IPER_ESCURO);

    //Lado Esquerdo
    DrawRectangleRoundedLinesEx((Rectangle){X(220), Y(295) - desce, X(500), Y(250)}, 0.1f, 1, S(5), VERDE_SUPER_IPER_ESCURO);
    Texto("Vampire Survivors", X(230), Y(250) - desce, S(30), WHITE);
    Texto("Desenvolvido por Felipe", X(230), Y(560) - desce, S(20), WHITE);
    Texto("Jogo baseado no classico\nVampire Survivors, onde\nvoce precisa se protejer \nde inimigos que vem em\nordas te atacar", X(730), Y(300) - desce, S(20), WHITE);

    //Lado Direito
    DrawRectangleRoundedLinesEx((Rectangle){X(980), Y(295) - desce, X(500), Y(250)}, 0.1f, 1, S(5), VERDE_SUPER_IPER_ESCURO);
    Texto("Lacucaracha", X(990), Y(250) - desce, S(30), WHITE);
    Texto("Desenvolvido por Vicky", X(990), Y(560) - desce, S(20), WHITE);
    Texto("Melhor jogo do mundo\nfeita pela pessoa mais\ngostosa que existe", X(1490), Y(300) - desce, S(20), WHITE);

}

void fundo_base(int *menu, float *loja_barra) {
    

    //Barra de Cima
    DrawRectangle(0, 0, largura_tela, Y(20), VERDE_SUPER_IPER_ESCURO);
    Texto("Steam - IFSC   by Felipe e Vicky", X(5), Y(5), S(10), GRAY);
    //Botões
    if (botao("-", S(20), largura_tela - X(40), 0, X(20), Y(20), VERDE_SUPER_ESCURO, WHITE)){
        MinimizeWindow();
    }
    if (botao("X", S(20), largura_tela - X(20), 0, X(20), Y(20), RED, WHITE)){
        exit(1);
    }

    //Menus
    if(*menu == 0){
        if (botao("Loja", S(30), 0, Y(20), X(200), Y(40), VERDE_NAO_SUPER_ESCURO, WHITE)) *loja_barra = 0.0f;
    } else if(botao("Loja", S(30), 0, Y(20), X(200), Y(40), VERDE_SUPER_ESCURO, WHITE)){
        *menu = 0;
        *loja_barra = 0.0f;
    }
    if(*menu == 1){
        botao("Biblioteca", S(30), X(200), Y(20), X(200), Y(40), VERDE_NAO_SUPER_ESCURO, WHITE);
    } else if(botao("Biblioteca", S(30), X(200), Y(20), X(200), Y(40), VERDE_SUPER_ESCURO, WHITE)){
        *menu = 1;
    }
    if(*menu == 2){
        botao("Perfil", S(30), X(400), Y(20), X(200), Y(40), VERDE_NAO_SUPER_ESCURO, WHITE);
    } else if(botao("Perfil", S(30), X(400), Y(20), X(200), Y(40), VERDE_SUPER_ESCURO, WHITE)){
        *menu = 2;
    }
    DrawLine(X(200), Y(20), X(200), Y(60), VERDE_SUPER_IPER_ESCURO);
    DrawLine(X(400), Y(20), X(400), Y(60), VERDE_SUPER_IPER_ESCURO);
    DrawRectangle(X(600), Y(20), largura_tela - X(600), Y(40), VERDE_SUPER_ESCURO);
    DrawLine(X(600), Y(20), X(600), Y(60), VERDE_SUPER_IPER_ESCURO);
    DrawLineEx((Vector2){0, Y(65)},(Vector2){largura_tela, Y(65)}, S(10), VERDE_SUPER_IPER_ESCURO);

    //Fundo

    DrawRectangle(0, altura_tela - Y(30), largura_tela, altura_tela, VERDE_SUPER_IPER_ESCURO);
}

void barra_lateral_scroll(Vector2 pos1, Vector2 pos2, float *agora, Color C, Color C2, Color C3){
    DrawRectangle(pos1.x, pos1.y, pos2.x, pos2.y, C2);
    *agora -= GetMouseWheelMove();
    if (*agora < 0) *agora = 0.0f;
    if (*agora > 100) *agora = 100.0f;
    float real_agora = map(*agora, 0.0f, 100.0f, pos1.y, pos1.y + pos2.y - Y(50.0f));
    
    DrawRectangle(pos1.x, real_agora, pos2.x, Y(50), C);
    DrawRectangleLines(pos1.x, real_agora, pos2.x, Y(50), C3);
}

void Texto(const char *texto, int x, int y, int tam, Color C){
    DrawTextEx(Fo, texto, (Vector2){x, y}, tam, S(2), C);
}

bool botao(const char *texto, int tam, float x, float y, float x2, float y2, Color C, Color C2){
    Vector2 mouse = (Vector2){GetMouseX(),GetMouseY()};
    DrawRectangle(x, y, x2, y2, C);
    Texto(texto, (x + x + x2)/2 - (MeasureTextEx(Fo, texto, tam, 2).x/2.0), (y + y + y2)/2 - (tam/2), tam, C2);
    if(mouse.x > x && mouse.x < x + x2 && mouse.y > y && mouse.y < y + y2 && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) return true;
    else return false;
}


    ///////   FUNÇÕES   ///////


float map(float valor, float entrada_min, float entrada_max, float saida_min, float saida_max) {
    return (valor - entrada_min) * (saida_max - saida_min) / (entrada_max - entrada_min) + saida_min;
}

float X(float valor) {
    return valor * ((float)GetScreenWidth() / LARGURA_BASE);
}

float Y(float valor) {
    return valor * ((float)GetScreenHeight() / ALTURA_BASE);
}

float S(float valor) {
    float escalaX = (float)GetScreenWidth() / LARGURA_BASE;
    float escalaY = (float)GetScreenHeight() / ALTURA_BASE;

    // Usa a menor escala para manter as proporções
    float escala = (escalaX < escalaY) ? escalaX : escalaY;

    return valor * escala;
}