#include "raylib.h"
#include <stdlib.h>

#define N 20
#define MAX 300

typedef struct {
    int pontuacao;
} Placar;

// BUBBLE SORT
void bubbleSort(Placar *v, int n, long *comp, long *trocas) {
    *comp = 0;
    *trocas = 0;

    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1 - i; j++) {

            (*comp)++;

            if (v[j].pontuacao > v[j + 1].pontuacao) {

                Placar temp = v[j];
                v[j] = v[j + 1];
                v[j + 1] = temp;

                (*trocas)++;
            }
        }
    }
}

// INSERTION SORT
void insertionSort(Placar *v, int n, long *comp, long *trocas) {
    *comp = 0;
    *trocas = 0;

    for (int i = 1; i < n; i++) {

        Placar chave = v[i];
        int j = i - 1;

        while (j >= 0) {

            (*comp)++;

            if (v[j].pontuacao > chave.pontuacao) {
                v[j + 1] = v[j];
                (*trocas)++;
                j--;
            } else {
                break;
            }
        }

        v[j + 1] = chave;
    }
}

int main() {

    InitWindow(800, 500, "Atividade 7");

    Placar *v = malloc(N * sizeof(Placar));

    for (int i = 0; i < N; i++) {
        v[i].pontuacao = GetRandomValue(20, MAX);
    }

    long comparacoes = 0;
    long trocas = 0;

    double tempo = 0;

    while (!WindowShouldClose()) {

        // B = BUBBLE SORT
        if (IsKeyPressed(KEY_B)) {

            double inicio = GetTime();

            bubbleSort(v, N, &comparacoes, &trocas);

            double fim = GetTime();

            tempo = (fim - inicio) * 1000.0;
        }

        // I = INSERTION SORT
        if (IsKeyPressed(KEY_I)) {

            insertionSort(v, N, &comparacoes, &trocas);
        }

        BeginDrawing();

        ClearBackground(RAYWHITE);

        DrawText("B = Bubble Sort", 20, 20, 20, BLACK);
        DrawText("I = Insertion Sort", 20, 45, 20, BLACK);

        DrawText(
            TextFormat("Comparacoes: %ld", comparacoes),
            20, 75, 20, BLACK
        );

        DrawText(
            TextFormat("Trocas: %ld", trocas),
            20, 100, 20, BLACK
        );

        DrawText(
            TextFormat("Tempo Bubble: %.4f ms", tempo),
            20, 125, 20, BLACK
        );

        // DESENHA AS BARRAS
        for (int i = 0; i < N; i++) {

            DrawRectangle(
                30 + i * 35,
                450 - v[i].pontuacao,
                25,
                v[i].pontuacao,
                BLUE
            );
        }

        EndDrawing();
    }

    free(v);

    CloseWindow();

    return 0;
}