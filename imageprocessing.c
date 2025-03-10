#include <stdio.h>
#include <stdlib.h>
#include "imageprocessing.h"

// TODO(loredana.stirbu) Task 1
int ***flip_horizontal(int ***image, int N, int M) {
    int ***flipped = (int ***)malloc(N * sizeof(int **));
    for (int i = 0; i < N; i++) {
        flipped[i] = (int **)malloc(M * sizeof(int *));
        for (int j = 0; j < M; j++) {
            flipped[i][j] = (int *)malloc(3 * sizeof(int)); } }
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            flipped[i][M - j - 1][0] = image[i][j][0];
            flipped[i][M - j - 1][1] = image[i][j][1];
            flipped[i][M - j - 1][2] = image[i][j][2]; } }
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            free(image[i][j]); }
        free(image[i]); }
    free(image);
    return flipped; }

// TODO(loredana.stirbu) Task 2
int ***rotate_left(int ***image, int N, int M) {
    int ***rotleft = (int ***)malloc(M * sizeof(int **));
    for (int i = 0; i < M; i++) {
        rotleft[i] = (int **)malloc(N * sizeof(int *));
        for (int j = 0; j < N; j++) {
            rotleft[i][j] = (int *)malloc(3 * sizeof(int)); } }
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            rotleft[M - i - 1][j][0] = image[j][i][0];
            rotleft[M - i - 1][j][1] = image[j][i][1];
            rotleft[M - i - 1][j][2] = image[j][i][2]; } }
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            free(image[i][j]); }
        free(image[i]); }
    free(image);
    return rotleft; }

// TODO(loredana.stirbu) Task 3
int ***crop(int ***image, int N, int M, int x, int y, int h, int w) {
    int ***cropp = (int ***)malloc(h * sizeof(int **));
    for (int i = 0; i < h; i++) {
        cropp[i] = (int **)malloc(w * sizeof(int *));
        for (int j = 0; j < w; j++) {
            cropp[i][j] = (int *)malloc(3 * sizeof(int)); } }
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            cropp[i][j][0] = image[i + y][j + x][0];
            cropp[i][j][1] = image[i + y][j + x][1];
            cropp[i][j][2] = image[i + y][j + x][2]; } }
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            free(image[i][j]); }
        free(image[i]); }
    free(image);
    return cropp; }

// TODO(loredana.stirbu) Task 4
int ***extend(int ***image, int N, int M, int rows, int cols, int new_R, int new_G, int new_B) {
    int nN = N+(2*rows);
    int nM = M+(2*cols);
    int ***extended = (int ***)malloc(nN* sizeof(int **));
    for (int i = 0; i < nN; i++) {
        extended[i] = (int **)malloc(nM * sizeof(int *));
        for (int j = 0; j < nM; j++) {
            extended[i][j] = (int*)malloc(3*sizeof(int));
            if (i< rows || i >= N+rows || j < cols || j >= M+cols) {
                extended[i][j][0] = new_R;
                extended[i][j][1] = new_G;
                extended[i][j][2] = new_B;
            } else {
                extended[i][j][0] = image[i-rows][j-cols][0];
                extended[i][j][1] = image[i-rows][j-cols][1];
                extended[i][j][2] = image[i-rows][j-cols][2];
            } } }
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            free(image[i][j]); }
        free(image[i]); }
    free(image);
    return extended; }

// TODO(loredana.stirbu) Task 5
int ***paste(int ***image_dst, int N_dst, int M_dst, int ***image_src, int N_src, int M_src, int x, int y) {
    for (int i = 0; (i < N_src) && ((i + y) < N_dst); i++) {
        for (int j = 0; (j < M_src) && ((j + x) < M_dst); j++) {
            image_dst[i + y][j + x][0] = image_src[i][j][0];
            image_dst[i + y][j + x][1] = image_src[i][j][1];
            image_dst[i + y][j + x][2] = image_src[i][j][2]; } }
    return image_dst;}

// TODO(loredana.stirbu) Task 6
int ***apply_filter(int ***image, int N, int M, float **filter, int filter_size) {
    int centrul_filtr = filter_size / 2;
    const float CUL_MAX = 255.0f;
    int ***filtrat = (int ***)malloc(N * sizeof(int**));
    for (int i = 0; i < N; i++) {
        filtrat[i] = (int**)malloc(M * sizeof(int*));
        for (int j = 0; j < M; j++) {
            filtrat[i][j] = (int*)malloc(3 * sizeof(int));
            float sum_color[3] = {0.0f, 0.0f, 0.0f};
            for (int filtr_i = 0; filtr_i < filter_size; filtr_i++) {
                for (int filtr_j = 0; filtr_j < filter_size; filtr_j++) {
                    int pix_i_orig = i + filtr_i - centrul_filtr;
                    int pix_j_orig = j + filtr_j - centrul_filtr;
                    if (pix_i_orig >= 0 && pix_i_orig < N && pix_j_orig >= 0 && pix_j_orig < M) {
                        for (int k = 0; k <= 2; k++) {
                            sum_color[k] += (float)image[pix_i_orig][pix_j_orig][k] * filter[filtr_i][filtr_j]; } } } }
            for (int k = 0; k <= 2; k++) {
                if (sum_color[k] < (float)0.0f) {
                    filtrat[i][j][k] = 0;
                } else {
                    if (sum_color[k] > CUL_MAX) {
                        filtrat[i][j][k] = (int)CUL_MAX;
                    } else {
                        filtrat[i][j][k] = (int)sum_color[k]; } } } } }
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            free(image[i][j]); }
        free(image[i]); }
    free(image);
    return filtrat; }
