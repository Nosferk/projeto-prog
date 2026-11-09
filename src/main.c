#include "raylib.h"

int main(void) {
    InitWindow(800, 600, "Olá, Raylib!");
    SetTargetFPS(60);
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawPixel(350, 340, RED);
        DrawLine(150, 350, 550, 350, BLUE);
        EndDrawing();
    }
    CloseWindow();
    return 0;
}
