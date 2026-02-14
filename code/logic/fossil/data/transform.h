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
#ifndef FOSSIL_DATA_TRANSFORM_H
#define FOSSIL_DATA_TRANSFORM_H

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @file fossil_data_transform.h
 * @brief Data transformation utilities for feature engineering and preprocessing.
 *
 * This module provides scaling, normalization, and encoding operations for
 * data arrays. Functions support a flexible type system using string IDs.
 *
 * Supported type string IDs:
 *   - "i8", "i16", "i32", "i64"
 *   - "u8", "u16", "u32", "u64"
 *   - "f32", "f64"
 *   - "cstr" (categorical strings)
 *
 * Supported method string IDs for scaling:
 *   - "minmax": scales values to [0,1]
 *   - "zscore": standard score normalization
 *
 * Supported method string IDs for encoding:
 *   - "onehot": one-hot encoding for categorical values
 *   - "label": label encoding
 */

/* Scale numeric data */
int fossil_data_transform_scale(
    const void* input,
    void* output,
    size_t count,
    const char* type_id,      /* numeric type string ID */
    const char* method_id     /* scaling method string ID */
);

/* Encode categorical data */
int fossil_data_transform_encode(
    const void* input,
    void* output,
    size_t count,
    const char* type_id,      /* "cstr" for strings */
    const char* method_id     /* encoding method string ID */
);

#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
#include <string>

namespace fossil::data {

/**
 * @brief Transform utility class (C++ interface)
 *
 * Supports type-safe scaling and encoding of numeric and categorical data.
 */
class Transform {
public:
    static int scale(
        const void* input,
        void* output,
        size_t count,
        const std::string& type_id,
        const std::string& method_id
    ) {
        return fossil_data_transform_scale(
            input, output, count, type_id.c_str(), method_id.c_str()
        );
    }

    static int encode(
        const void* input,
        void* output,
        size_t count,
        const std::string& type_id,
        const std::string& method_id
    ) {
        return fossil_data_transform_encode(
            input, output, count, type_id.c_str(), method_id.c_str()
        );
    }

};

} // namespace fossil::data
#endif

#endif /* FOSSIL_DATA_TRANSFORM_H */
