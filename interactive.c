#include <stdio.h>
#include <stdlib.h>
#include "imageprocessing.h"
#include "bmp.h"
#include "string.h"
#define MAX_ims 100
#define MAX_flts 1000
#define MAX_ACTION_LENGTH 1000
#define MAX_DIM_PATH 100
#define MAX_FIL_DIM 1000

typedef struct {
    int ***data, rows, cols;
} Imagine;

typedef struct {
    float **val;
    int size;
} Filtru;

float** create_flt(int size, float values[MAX_FIL_DIM][MAX_FIL_DIM]) {
    float** flt = (float**)malloc(sizeof(float*) * size);
    if (!flt) return NULL;
    for (int i = 0; i < size; i++) {
        flt[i] = (float*)malloc(sizeof(float) * size);
        if (!flt[i]) {
            for (int j = 0; j < i; j++) {
                free(flt[j]); }
            free(flt);
            return NULL; }
        for (int j = 0; j < size; j++) {
            flt[i][j] = values[i][j]; } }
    return flt; }

void delete_filter(Filtru *flts, int *fil_nr, int idx_flt) {
    for (int i = 0; i < flts[idx_flt].size; i++) {
        free(flts[idx_flt].val[i]); }
    free(flts[idx_flt].val);
    for (int i = idx_flt; i < *fil_nr - 1; i++) {
        flts[i] = flts[i + 1]; }
    (*fil_nr)--; }

void delete_image(Imagine *ims, int *dim_imagini, int idx_img) {
    for (int i = 0; i < ims[idx_img].rows; i++) {
        for (int j = 0; j < ims[idx_img].cols; j++) {
            free(ims[idx_img].data[i][j]); }
        free(ims[idx_img].data[i]); }
    free(ims[idx_img].data);
    for (int i = idx_img; i < *dim_imagini - 1; i++) {
        ims[i] = ims[i + 1]; }
    (*dim_imagini)--; }

int main() {
    // TODO(loredana.stirbu) Task 7
    Imagine ims[MAX_ims];
    Filtru flts[MAX_flts];
    char actiune[MAX_ACTION_LENGTH], path[MAX_DIM_PATH];
    int idx = 0, N = 0, M = 0, x = 0, y = 0, w = 0, h = 0, rows = 0 , cols = 0;
    int R = 0, G = 0, B = 0, idx_dst = 0, idx_src = 0, flt_size = 0;
    int idx_img = 0, idx_flt = 0, dim_imagini = 0, fil_nr = 0;
    while (1) {
        scanf(" %s", actiune);
        if (strcmp(actiune, "e") == 0) {
            for (int s = dim_imagini - 1; s >= 0; s--) {
                delete_image(ims, &dim_imagini, s); }
            for (int s = fil_nr - 1; s >= 0; s--) {
                delete_filter(flts, &fil_nr, s); }
            break;
        } else if (strcmp(actiune, "l") == 0) {
            scanf(" %d %d %s", &N, &M, path);
            ims[dim_imagini].data = (int ***)malloc(N * sizeof(int **));
            for (int i = 0; i < N; i++) {
                ims[dim_imagini].data[i] = (int **)malloc(M * sizeof(int *));
                for (int j = 0; j < M; j++) {
                    ims[dim_imagini].data[i][j] = (int *)malloc(3 * sizeof(int)); } }
            read_from_bmp(ims[dim_imagini].data, N, M, path);
            ims[dim_imagini].rows = N;
            ims[dim_imagini].cols = M;
            dim_imagini++;
        }  else if (strcmp(actiune, "s") == 0) {
            scanf("%d %s", &idx, path);
            write_to_bmp(ims[idx].data, ims[idx].rows, ims[idx].cols, path);
        } else if (strcmp(actiune, "ah") == 0) {
            scanf("%d", &idx);
            ims[idx].data = flip_horizontal(ims[idx].data, ims[idx].rows, ims[idx].cols);
        } else if (strcmp(actiune, "ar") == 0) {
            scanf("%d", &idx);
            ims[idx].data = rotate_left(ims[idx].data, ims[idx].rows, ims[idx].cols);
            int temp = ims[idx].rows;
            ims[idx].rows = ims[idx].cols;
            ims[idx].cols = temp;
        } else if (strcmp(actiune, "ac") == 0) {
            scanf("%d %d %d %d %d", &idx, &x, &y, &w, &h);
            ims[idx].data = crop(ims[idx].data, ims[idx].rows, ims[idx].cols, x, y, h, w);
            ims[idx].rows = h;
            ims[idx].cols = w;
        } else if (strcmp(actiune, "ae") == 0) {
            scanf("%d %d %d %d %d %d", &idx, &rows, &cols, &R, &G, &B);
            ims[idx].data = extend(ims[idx].data, ims[idx].rows, ims[idx].cols, rows, cols, R, G, B);
            ims[idx].rows = ims[idx].rows + (2*rows);
            ims[idx].cols = ims[idx].cols + (2*cols);
        } else if (strcmp(actiune, "ap") == 0) {
            scanf("%d %d %d %d", &idx_dst, &idx_src, &x, &y);
            int iDs_r = ims[idx_dst].rows;
            int iDs_c = ims[idx_dst].cols;
            paste(ims[idx_dst].data, iDs_r, iDs_c, ims[idx_src].data, ims[idx_src].rows, ims[idx_src].cols, x, y);
        }  else if (strcmp(actiune, "cf") == 0) {
            float flt_values[MAX_FIL_DIM][MAX_FIL_DIM];
            scanf("%d", &flt_size);
            for (int i = 0; i < flt_size; i++) {
                for (int j = 0; j < flt_size; j++) {
                    scanf("%f", &flt_values[i][j]); } }
            flts[fil_nr].size = flt_size;
            flts[fil_nr].val = create_flt(flt_size, flt_values);
            fil_nr++;
        } else if (strcmp(actiune, "af") == 0) {
            scanf("%d %d", &idx_img, &idx_flt);
            int i_r = ims[idx_img].rows;
            int i_c = ims[idx_img].cols;
            ims[idx_img].data = apply_filter(ims[idx_img].data, i_r, i_c, flts[idx_flt].val, flts[idx_flt].size);
        } else if (strcmp(actiune, "df") == 0) {
            int idx_flt = 0;
            scanf("%d", &idx_flt);
            delete_filter(flts, &fil_nr, idx_flt);
        } else if (strcmp(actiune, "di") == 0) {
            int idx_img = 0;
            scanf("%d", &idx_img);
            delete_image(ims, &dim_imagini, idx_img);} }
    return 0; }
