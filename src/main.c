#include "raylib.h"
#include <stdlib.h>
#include "cores.h"

int largura_tela;
int altura_tela;
void fundo_base(int *menu, Font Fo, float *loja_barra);
void loja(int menu, Font Fo, float *loja_barra);
void barra_lateral_scroll(Vector2 pos1, Vector2 pos2, float *agora, Color C, Color C2, Color C3);
bool botao(const char *texto, int tam, float x, float y, float x2, float y2, Color C, Color C2, Font Fo);
float map(float valor, float entrada_min, float entrada_max, float saida_min, float saida_max);

int main(void) {
    
    InitWindow(0, 0, "Steam IFSC");
    ToggleFullscreen();
    largura_tela = GetMonitorWidth(GetCurrentMonitor());
    altura_tela = GetMonitorHeight(GetCurrentMonitor());
    Font Fo = LoadFont("assets/fonts/Roboto-Condensed.ttf");

    if (!IsFontValid(Fo)) {
        TraceLog(LOG_ERROR, "Nao foi possivel carregar a fonte!");
    }

    SetTargetFPS(60);

    int menu = 0;
    float loja_barra = 0;
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(VERDE_SUPER_IPER_MEGA_ESCURO);
        loja(menu, Fo, &loja_barra);
        fundo_base(&menu, Fo, &loja_barra);
        EndDrawing();
    }
    UnloadFont(Fo);
    CloseWindow();
    return 0;
}

void barra_lateral_scroll(Vector2 pos1, Vector2 pos2, float *agora, Color C, Color C2, Color C3){
    DrawRectangle(pos1.x, pos1.y, pos2.x, pos2.y, C2);
    *agora -= GetMouseWheelMove();
    if (*agora < 0) *agora = 0.0f;
    if (*agora > 100) *agora = 100.0f;
    float real_agora = map(*agora, 0.0f, 100.0f, pos1.y, pos1.y + pos2.y - 50.0f);
    
    DrawRectangle(pos1.x, real_agora, pos2.x, 50, C);
    DrawRectangleLines(pos1.x, real_agora, pos2.x, 50, C3);

    // DrawText(TextFormat("%.2f", *agora), pos1.x - 100, pos1.y, 20, C3);
    // DrawText(TextFormat("%.2f", real_agora), pos1.x - 100, pos1.y + 50, 20, C3);
}

void loja(int menu, Font Fo, float *loja_barra){
    if (menu != 0) return;
    int desce = (*loja_barra) * 50; 
    barra_lateral_scroll((Vector2){largura_tela - 20, 70}, (Vector2){20, altura_tela - 100}, loja_barra, VERDE_SUPER_ESCURO, VERDE_SUPER_IPER_ESCURO, VERDE_SUPER_IPER_QUASE_MEGA_ESCURO);
    DrawRectangleLines(largura_tela - 20, 70, 20, altura_tela - 100, VERDE_SUPER_IPER_QUASE_MEGA_ESCURO);
    //DrawLine(largura_tela - 20, 60, largura_tela - 20, altura_tela - 30, VERDE_SUPER_IPER_QUASE_MEGA_ESCURO);
    //Base
    DrawRectangleRounded((Rectangle){200, 170 - desce, 1520, 500}, 0.1, 1, VERDE_SUPER_ESCURO);
    DrawRectangleRounded((Rectangle){230, 105 - desce, 40 + MeasureTextEx(Fo, "Jogos em destaque:", 40, 2).x, 50}, 0.1, 1, VERDE_SUPER_IPER_ESCURO);
    DrawTextEx(Fo, "Jogos em destaque:", (Vector2){250, 110 - desce}, 40, 2, WHITE);
    DrawLineEx((Vector2){960, 180 - desce}, (Vector2){960, 660 - desce}, 5, VERDE_SUPER_IPER_ESCURO);

    //Lado Esquerdo
    DrawRectangleRoundedLinesEx((Rectangle){220, 295 - desce, 500, 250}, 0.1, 1, 5, VERDE_SUPER_IPER_ESCURO);
    DrawTextEx(Fo, "Vampire Survivors", (Vector2){230, 250 - desce}, 30, 2, WHITE);
    DrawTextEx(Fo, "Desenvolvido por Felipe", (Vector2){230, 560 - desce}, 20, 2, WHITE);
    DrawTextEx(Fo, "Jogo baseado no classico\nVampire Survivors, onde\nvoce precisa se protejer \nde inimigos que vem em\nordas te atacar", (Vector2){730, 300 - desce}, 20, 2, WHITE);

    //Lado Direito
    DrawRectangleRoundedLinesEx((Rectangle){980, 295 - desce, 500, 250}, 0.1, 1, 5, VERDE_SUPER_IPER_ESCURO);
    DrawTextEx(Fo, "Lacucaracha", (Vector2){990, 250 - desce}, 30, 2, WHITE);
    DrawTextEx(Fo, "Desenvolvido por Vicky", (Vector2){990, 560 - desce}, 20, 2, WHITE);
    DrawTextEx(Fo, "Melhor jogo do mundo\nfeita pela pessoa mais\ngostosa que existe", (Vector2){1490, 300 - desce}, 20, 2, WHITE);

}

void fundo_base(int *menu, Font Fo, float *loja_barra) {
    

    //Barra de Cima
    DrawRectangle(0, 0, largura_tela, 20, VERDE_SUPER_IPER_ESCURO);
    DrawTextEx(Fo, "Steam - IFSC   by Felipe e Vicky", (Vector2){5, 5}, 10, 2, GRAY);
    //Botões
    if (botao("-", 20, largura_tela - 40, 0, 20, 20, VERDE_SUPER_ESCURO, WHITE, Fo)){
        MinimizeWindow();
    }
    if (botao("X", 20, largura_tela - 20, 0, 20, 20, RED, WHITE, Fo)){
        exit(1);
    }

    //Menus
    if(*menu == 0){
        if (botao("Loja", 30, 0, 20, 200, 40, VERDE_NAO_SUPER_ESCURO, WHITE, Fo)) *loja_barra = 0.0f;
    } else if(botao("Loja", 30, 0, 20, 200, 40, VERDE_SUPER_ESCURO, WHITE, Fo)){
        *menu = 0;
        *loja_barra = 0.0f;
    }
    if(*menu == 1){
        botao("Biblioteca", 30, 200, 20, 200, 40, VERDE_NAO_SUPER_ESCURO, WHITE, Fo);
    } else if(botao("Biblioteca", 30, 200, 20, 200, 40, VERDE_SUPER_ESCURO, WHITE, Fo)){
        *menu = 1;
    }
    if(*menu == 2){
        botao("Perfil", 30, 400, 20, 200, 40, VERDE_NAO_SUPER_ESCURO, WHITE, Fo);
    } else if(botao("Perfil", 30, 400, 20, 200, 40, VERDE_SUPER_ESCURO, WHITE, Fo)){
        *menu = 2;
    }
    DrawLine(200, 20, 200, 60, VERDE_SUPER_IPER_ESCURO);
    DrawLine(400, 20, 400, 60, VERDE_SUPER_IPER_ESCURO);
    DrawRectangle(600,20, largura_tela - 600, 40, VERDE_SUPER_ESCURO);
    DrawLine(600,20, 600, 60, VERDE_SUPER_IPER_ESCURO);
    DrawLineEx((Vector2){0, 65},(Vector2){largura_tela, 65}, 10, VERDE_SUPER_IPER_ESCURO);

    //Fundo

    DrawRectangle(0, altura_tela - 30, largura_tela, altura_tela, VERDE_SUPER_IPER_ESCURO);
}

bool botao(const char *texto, int tam, float x, float y, float x2, float y2, Color C, Color C2, Font Fo){
    Vector2 mouse = (Vector2){GetMouseX(),GetMouseY()};
    DrawRectangle(x, y, x2, y2, C);
    DrawTextEx(Fo, texto, (Vector2){(x + x + x2)/2 - (MeasureTextEx(Fo, texto, tam, 2).x/2.0), (y + y + y2)/2 - (tam/2)}, tam, 2, C2);
    if(mouse.x > x && mouse.x < x + x2 && mouse.y > y && mouse.y < y + y2 && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) return true;
    else return false;
}

float map(float valor, float entrada_min, float entrada_max, float saida_min, float saida_max) {
    return (valor - entrada_min) * (saida_max - saida_min) / (entrada_max - entrada_min) + saida_min;
}
