/**
 * -----------------------------------------------------------------------------
 * Project: Fossil Logic
 *
 * This file is part of the Fossil Logic project, which aims to develop
 * high-performance, cross-platform applications and libraries. The code
 * contained herein is licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License. You may obtain
 * a copy of the License at:
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the
 * License for the specific language governing permissions and limitations
 * under the License.
 *
 * Author: Michael Gene Brockus (Dreamer)
 * Date: 04/05/2014
 *
 * Copyright (C) 2014-2025 Fossil Logic. All rights reserved.
 * -----------------------------------------------------------------------------
 */
#include "fossil/data/matrix.h"
#include <stdlib.h>
#include <string.h>

/* ============================================================================
 * Internal Structure
 * ============================================================================
 */
struct fossil_data_matrix {
    size_t rows;
    size_t cols;
    double *data;
};

/* ============================================================================
 * Helpers
 * ============================================================================
 */
static size_t
matrix_index(const fossil_data_matrix_t *m, size_t r, size_t c)
{
    return r * m->cols + c;
}

/* ============================================================================
 * Lifecycle
 * ============================================================================
 */
fossil_data_matrix_t *
fossil_data_matrix_create(size_t rows, size_t cols)
{
    fossil_data_matrix_t *m;

    if (rows == 0 || cols == 0) {
        return NULL;
    }

    m = (fossil_data_matrix_t *)malloc(sizeof(*m));
    if (!m) {
        return NULL;
    }

    m->rows = rows;
    m->cols = cols;
    m->data = (double *)calloc(rows * cols, sizeof(double));

    if (!m->data) {
        free(m);
        return NULL;
    }

    return m;
}

void
fossil_data_matrix_free(fossil_data_matrix_t *m)
{
    if (!m) {
        return;
    }

    free(m->data);
    free(m);
}

/* ============================================================================
 * Properties
 * ============================================================================
 */
size_t
fossil_data_matrix_rows(const fossil_data_matrix_t *m)
{
    return m ? m->rows : 0;
}

size_t
fossil_data_matrix_cols(const fossil_data_matrix_t *m)
{
    return m ? m->cols : 0;
}

/* ============================================================================
 * Element Access
 * ============================================================================
 */
fossil_data_matrix_status_t
fossil_data_matrix_get(
    const fossil_data_matrix_t *m,
    size_t row,
    size_t col,
    double *out_value
)
{
    if (!m || !out_value) {
        return FOSSIL_DATA_MATRIX_ERR_NULL;
    }

    if (row >= m->rows || col >= m->cols) {
        return FOSSIL_DATA_MATRIX_ERR_BOUNDS;
    }

    *out_value = m->data[matrix_index(m, row, col)];
    return FOSSIL_DATA_MATRIX_OK;
}

fossil_data_matrix_status_t
fossil_data_matrix_set(
    fossil_data_matrix_t *m,
    size_t row,
    size_t col,
    double value
)
{
    if (!m) {
        return FOSSIL_DATA_MATRIX_ERR_NULL;
    }

    if (row >= m->rows || col >= m->cols) {
        return FOSSIL_DATA_MATRIX_ERR_BOUNDS;
    }

    m->data[matrix_index(m, row, col)] = value;
    return FOSSIL_DATA_MATRIX_OK;
}

/* ============================================================================
 * Utilities
 * ============================================================================
 */
void
fossil_data_matrix_fill(
    fossil_data_matrix_t *m,
    double value
)
{
    size_t i, total;

    if (!m) {
        return;
    }

    total = m->rows * m->cols;
    for (i = 0; i < total; ++i) {
        m->data[i] = value;
    }
}

fossil_data_matrix_status_t
fossil_data_matrix_copy(
    const fossil_data_matrix_t *src,
    fossil_data_matrix_t **out
)
{
    fossil_data_matrix_t *dst;

    if (!src || !out) {
        return FOSSIL_DATA_MATRIX_ERR_NULL;
    }

    dst = fossil_data_matrix_create(src->rows, src->cols);
    if (!dst) {
        return FOSSIL_DATA_MATRIX_ERR_ALLOC;
    }

    memcpy(dst->data, src->data,
           src->rows * src->cols * sizeof(double));

    *out = dst;
    return FOSSIL_DATA_MATRIX_OK;
}

/* ============================================================================
 * Linear Algebra
 * ============================================================================
 */
fossil_data_matrix_status_t
fossil_data_matrix_add(
    const fossil_data_matrix_t *a,
    const fossil_data_matrix_t *b,
    fossil_data_matrix_t **out
)
{
    fossil_data_matrix_t *r;
    size_t i, total;

    if (!a || !b || !out) {
        return FOSSIL_DATA_MATRIX_ERR_NULL;
    }

    if (a->rows != b->rows || a->cols != b->cols) {
        return FOSSIL_DATA_MATRIX_ERR_DIM_MISMATCH;
    }

    r = fossil_data_matrix_create(a->rows, a->cols);
    if (!r) {
        return FOSSIL_DATA_MATRIX_ERR_ALLOC;
    }

    total = a->rows * a->cols;
    for (i = 0; i < total; ++i) {
        r->data[i] = a->data[i] + b->data[i];
    }

    *out = r;
    return FOSSIL_DATA_MATRIX_OK;
}

fossil_data_matrix_status_t
fossil_data_matrix_mul(
    const fossil_data_matrix_t *a,
    const fossil_data_matrix_t *b,
    fossil_data_matrix_t **out
)
{
    fossil_data_matrix_t *r;
    size_t i, j, k;

    if (!a || !b || !out) {
        return FOSSIL_DATA_MATRIX_ERR_NULL;
    }

    if (a->cols != b->rows) {
        return FOSSIL_DATA_MATRIX_ERR_DIM_MISMATCH;
    }

    r = fossil_data_matrix_create(a->rows, b->cols);
    if (!r) {
        return FOSSIL_DATA_MATRIX_ERR_ALLOC;
    }

    for (i = 0; i < a->rows; ++i) {
        for (j = 0; j < b->cols; ++j) {
            double sum = 0.0;
            for (k = 0; k < a->cols; ++k) {
                sum += a->data[matrix_index(a, i, k)] *
                       b->data[matrix_index(b, k, j)];
            }
            r->data[matrix_index(r, i, j)] = sum;
        }
    }

    *out = r;
    return FOSSIL_DATA_MATRIX_OK;
}
