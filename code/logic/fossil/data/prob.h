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
#ifndef FOSSIL_DATA_PROB_H
#define FOSSIL_DATA_PROB_H

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @file fossil_data_prob.h
 * @brief Probability and statistics utilities.
 *
 * Supports mean, standard deviation, and random sampling from distributions.
 *
 * Supported type string IDs:
 *   - "i32", "i64", "f32", "f64"
 *
 * Supported distribution string IDs:
 *   - "normal"
 *   - "uniform"
 *   - "binomial" (integer parameters)
 */

/* Compute mean */
int fossil_data_prob_mean(
    const void* data,
    size_t count,
    const char* type_id,
    double* result
);

/* Compute standard deviation */
int fossil_data_prob_std(
    const void* data,
    size_t count,
    const char* type_id,
    double* result
);

/* Sample random values */
int fossil_data_prob_sample(
    void* output,
    size_t count,
    const char* dist_id,
    const char* type_id,
    const void* params
);

#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
#include <string>

namespace fossil::data {

class Prob {
public:
    static double mean(const void* data, size_t count, const std::string& type_id);
    static double std(const void* data, size_t count, const std::string& type_id);
    static int sample(void* output, size_t count, const std::string& dist_id,
                      const std::string& type_id, const void* params);
};

} // namespace fossil::data
#endif

#endif /* FOSSIL_DATA_PROB_H */
