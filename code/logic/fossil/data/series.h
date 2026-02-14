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
#ifndef FOSSIL_DATA_SERIES_H
#define FOSSIL_DATA_SERIES_H

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @file fossil_data_series.h
 * @brief Sequence and time series operations.
 *
 * Provides cumulative sum, rolling mean, and other sequence-level transformations.
 *
 * Supported type string IDs:
 *   - "i32", "i64", "f32", "f64"
 */

/* Cumulative sum */
int fossil_data_series_cumsum(
    const void* input,
    void* output,
    size_t count,
    const char* type_id
);

/* Rolling mean with fixed window */
int fossil_data_series_rolling_mean(
    const void* input,
    void* output,
    size_t count,
    size_t window,
    const char* type_id
);

#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
#include <string>

namespace fossil::data {

class Series {
public:
    static int cumsum(const void* input, void* output, size_t count, const std::string& type_id) {
        return fossil_data_series_cumsum(input, output, count, type_id.c_str());
    }

    static int rolling_mean(const void* input, void* output, size_t count,
                            size_t window, const std::string& type_id) {
        return fossil_data_series_rolling_mean(input, output, count, window, type_id.c_str());
    }
};

} // namespace fossil::data
#endif

#endif /* FOSSIL_DATA_SERIES_H */
