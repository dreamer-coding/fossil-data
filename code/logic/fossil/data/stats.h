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
#ifndef FOSSIL_DATA_STATS_H
#define FOSSIL_DATA_STATS_H

#include <stddef.h>
#include "fossil/data/matrix.h"

#ifdef __cplusplus
extern "C" {
#endif


/* ============================================================================
 * Status Codes
 * ============================================================================
 */
typedef enum {
    FOSSIL_DATA_STATS_OK = 0,
    FOSSIL_DATA_STATS_ERR_NULL,
    FOSSIL_DATA_STATS_ERR_EMPTY,
    FOSSIL_DATA_STATS_ERR_ALLOC,
    FOSSIL_DATA_STATS_ERR_DIM_MISMATCH
} fossil_data_stats_status_t;

/* ============================================================================
 * Streaming Accumulator
 * ============================================================================
 */
typedef struct {
    size_t count;
    double mean;
    double m2;   /* sum of squares of differences from the mean */
} fossil_data_stats_accumulator_t;

/* ============================================================================
 * Accumulator API (Welford)
 * ============================================================================
 */
void fossil_data_stats_accumulator_init(
    fossil_data_stats_accumulator_t *acc
);

void fossil_data_stats_accumulator_push(
    fossil_data_stats_accumulator_t *acc,
    double value
);

double fossil_data_stats_accumulator_mean(
    const fossil_data_stats_accumulator_t *acc
);

double fossil_data_stats_accumulator_variance(
    const fossil_data_stats_accumulator_t *acc
);

double fossil_data_stats_accumulator_stddev(
    const fossil_data_stats_accumulator_t *acc
);

/* ============================================================================
 * Vector Statistics
 * ============================================================================
 */
fossil_data_stats_status_t fossil_data_stats_mean(
    const double *x,
    size_t n,
    double *out
);

fossil_data_stats_status_t fossil_data_stats_variance(
    const double *x,
    size_t n,
    double *out
);

fossil_data_stats_status_t fossil_data_stats_stddev(
    const double *x,
    size_t n,
    double *out
);

fossil_data_stats_status_t fossil_data_stats_minmax(
    const double *x,
    size_t n,
    double *out_min,
    double *out_max
);

/* ============================================================================
 * Matrix Statistics
 * ============================================================================
 */

/* Column-wise means: result is (1 x cols) */
fossil_data_stats_status_t fossil_data_stats_matrix_column_mean(
    const fossil_data_matrix_t *m,
    fossil_data_matrix_t **out
);

/* Covariance matrix: (cols x cols) */
fossil_data_stats_status_t fossil_data_stats_matrix_covariance(
    const fossil_data_matrix_t *m,
    fossil_data_matrix_t **out
);

#ifdef __cplusplus
}
#include <string>

namespace fossil {
    
    namespace data {



    } // namespace data

} // namespace fossil

#endif

#endif /* FOSSIL_DATA_STATS_H */
