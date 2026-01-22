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
#include "fossil/data/stats.h"
#include <stdlib.h>
#include <math.h>

/* ============================================================================
 * Accumulator (Welford)
 * ============================================================================
 */
void fossil_data_stats_accumulator_init(fossil_data_stats_accumulator_t *acc)
{
    if (!acc) {
        return;
    }

    acc->count = 0;
    acc->mean  = 0.0;
    acc->m2    = 0.0;
}

void fossil_data_stats_accumulator_push(
    fossil_data_stats_accumulator_t *acc,
    double value) {
    double delta;
    double delta2;

    if (!acc) {
        return;
    }

    acc->count++;
    delta  = value - acc->mean;
    acc->mean += delta / acc->count;
    delta2 = value - acc->mean;
    acc->m2 += delta * delta2;
}

double fossil_data_stats_accumulator_mean(const fossil_data_stats_accumulator_t *acc) {
    return (acc && acc->count > 0) ? acc->mean : 0.0;
}

double fossil_data_stats_accumulator_variance(const fossil_data_stats_accumulator_t *acc) {
    if (!acc || acc->count < 2) {
        return 0.0;
    }

    return acc->m2 / (acc->count - 1);
}

double fossil_data_stats_accumulator_stddev(const fossil_data_stats_accumulator_t *acc) {
    return sqrt(fossil_data_stats_accumulator_variance(acc));
}

/* ============================================================================
 * Vector Statistics
 * ============================================================================
 */
fossil_data_stats_status_t fossil_data_stats_mean(
    const double *x,
    size_t n,
    double *out) {
    size_t i;
    double sum = 0.0;

    if (!x || !out) {
        return FOSSIL_DATA_STATS_ERR_NULL;
    }

    if (n == 0) {
        return FOSSIL_DATA_STATS_ERR_EMPTY;
    }

    for (i = 0; i < n; ++i) {
        sum += x[i];
    }

    *out = sum / n;
    return FOSSIL_DATA_STATS_OK;
}

fossil_data_stats_status_tfossil_data_stats_variance(
    const double *x,
    size_t n,
    double *out) {
    fossil_data_stats_accumulator_t acc;
    size_t i;

    if (!x || !out) {
        return FOSSIL_DATA_STATS_ERR_NULL;
    }

    if (n < 2) {
        return FOSSIL_DATA_STATS_ERR_EMPTY;
    }

    fossil_data_stats_accumulator_init(&acc);
    for (i = 0; i < n; ++i) {
        fossil_data_stats_accumulator_push(&acc, x[i]);
    }

    *out = fossil_data_stats_accumulator_variance(&acc);
    return FOSSIL_DATA_STATS_OK;
}

fossil_data_stats_status_t fossil_data_stats_stddev(
    const double *x,
    size_t n,
    double *out) {
    fossil_data_stats_status_t rc;
    double var;

    rc = fossil_data_stats_variance(x, n, &var);
    if (rc != FOSSIL_DATA_STATS_OK) {
        return rc;
    }

    *out = sqrt(var);
    return FOSSIL_DATA_STATS_OK;
}

fossil_data_stats_status_t fossil_data_stats_minmax(
    const double *x,
    size_t n,
    double *out_min,
    double *out_max) {
    size_t i;
    double minv, maxv;

    if (!x || !out_min || !out_max) {
        return FOSSIL_DATA_STATS_ERR_NULL;
    }

    if (n == 0) {
        return FOSSIL_DATA_STATS_ERR_EMPTY;
    }

    minv = maxv = x[0];
    for (i = 1; i < n; ++i) {
        if (x[i] < minv) minv = x[i];
        if (x[i] > maxv) maxv = x[i];
    }

    *out_min = minv;
    *out_max = maxv;
    return FOSSIL_DATA_STATS_OK;
}

/* ============================================================================
 * Matrix Statistics
 * ============================================================================
 */
fossil_data_stats_status_t fossil_data_stats_matrix_column_mean(
    const fossil_data_matrix_t *m,
    fossil_data_matrix_t **out) {
    fossil_data_matrix_t *r;
    size_t rows, cols;
    size_t i, j;

    if (!m || !out) {
        return FOSSIL_DATA_STATS_ERR_NULL;
    }

    rows = fossil_data_matrix_rows(m);
    cols = fossil_data_matrix_cols(m);

    if (rows == 0 || cols == 0) {
        return FOSSIL_DATA_STATS_ERR_EMPTY;
    }

    r = fossil_data_matrix_create(1, cols);
    if (!r) {
        return FOSSIL_DATA_STATS_ERR_ALLOC;
    }

    for (j = 0; j < cols; ++j) {
        double sum = 0.0;
        for (i = 0; i < rows; ++i) {
            double v;
            fossil_data_matrix_get(m, i, j, &v);
            sum += v;
        }
        fossil_data_matrix_set(r, 0, j, sum / rows);
    }

    *out = r;
    return FOSSIL_DATA_STATS_OK;
}

fossil_data_stats_status_t fossil_data_stats_matrix_covariance(
    const fossil_data_matrix_t *m,
    fossil_data_matrix_t **out) {
    fossil_data_matrix_t *cov;
    size_t rows, cols;
    size_t i, j, k;

    if (!m || !out) {
        return FOSSIL_DATA_STATS_ERR_NULL;
    }

    rows = fossil_data_matrix_rows(m);
    cols = fossil_data_matrix_cols(m);

    if (rows < 2) {
        return FOSSIL_DATA_STATS_ERR_EMPTY;
    }

    cov = fossil_data_matrix_create(cols, cols);
    if (!cov) {
        return FOSSIL_DATA_STATS_ERR_ALLOC;
    }

    for (i = 0; i < cols; ++i) {
        for (j = i; j < cols; ++j) {
            double sum = 0.0;

            for (k = 0; k < rows; ++k) {
                double xi, xj;
                fossil_data_matrix_get(m, k, i, &xi);
                fossil_data_matrix_get(m, k, j, &xj);
                sum += xi * xj;
            }

            sum /= (rows - 1);

            fossil_data_matrix_set(cov, i, j, sum);
            fossil_data_matrix_set(cov, j, i, sum);
        }
    }

    *out = cov;
    return FOSSIL_DATA_STATS_OK;
}
