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
#ifndef FOSSIL_DATA_TENSOR_H
#define FOSSIL_DATA_TENSOR_H

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Tensor utilities for Fossil Data Science.
 *
 * Provides lightweight tensor inspection, statistics, and reductions.
 * Designed for portable AI/data workloads with Fossil string type IDs.
 *
 * Supported type string IDs:
 *   - "i8", "i16", "i32", "i64"
 *   - "u8", "u16", "u32", "u64", "size"
 *   - "f32", "f64"
 *   - "bool"
 *   - "hex", "oct", "bin"
 *
 * Tensor layout is row-major.
 */

/**
 * @brief Describe a tensor’s shape.
 *
 * @param shape        Pointer to dimension array.
 * @param rank         Number of dimensions.
 * @param out_elements Output total element count.
 * @return             0 on success.
 */
int fossil_data_tensor_elements(
    const size_t* shape,
    size_t rank,
    size_t* out_elements
);

/**
 * @brief Compute min/max of a tensor.
 *
 * @param data     Tensor buffer.
 * @param count    Number of elements.
 * @param type_id  Fossil type string.
 * @param out_min  Output minimum value.
 * @param out_max  Output maximum value.
 * @return         0 on success.
 */
int fossil_data_tensor_minmax(
    const void* data,
    size_t count,
    const char* type_id,
    void* out_min,
    void* out_max
);

/**
 * @brief Compute mean of tensor values.
 *
 * Always returned as f64 for numerical stability.
 *
 * @param data      Tensor buffer.
 * @param count     Element count.
 * @param type_id   Fossil type string.
 * @param out_mean  Output double mean.
 * @return          0 on success.
 */
int fossil_data_tensor_mean(
    const void* data,
    size_t count,
    const char* type_id,
    double* out_mean
);

/**
 * @brief Reduce tensor along one axis (sum).
 *
 * Result buffer must be preallocated.
 *
 * @param data        Tensor buffer.
 * @param shape       Shape array.
 * @param rank        Number of dims.
 * @param axis        Axis to reduce.
 * @param type_id     Fossil type string.
 * @param out_result  Output tensor.
 * @return            0 on success.
 */
int fossil_data_tensor_reduce_sum(
    const void* data,
    const size_t* shape,
    size_t rank,
    size_t axis,
    const char* type_id,
    void* out_result
);

/**
 * @brief Extract a slice from a tensor.
 *
 * Copies a sub-tensor defined by offsets.
 *
 * @param data        Tensor buffer.
 * @param shape       Shape array.
 * @param rank        Number of dims.
 * @param offsets     Start indices.
 * @param extents     Slice size per dim.
 * @param type_id     Fossil type string.
 * @param out_slice   Output buffer.
 * @return            0 on success.
 */
int fossil_data_tensor_slice(
    const void* data,
    const size_t* shape,
    size_t rank,
    const size_t* offsets,
    const size_t* extents,
    const char* type_id,
    void* out_slice
);

#ifdef __cplusplus
}
#endif


#ifdef __cplusplus
#include <string>

namespace fossil::data {

/**
 * @brief Tensor helper utilities (C++ wrapper)
 */
class Tensor {
public:

    static int elements(const size_t* shape, size_t rank, size_t* out_elements) {
        return fossil_data_tensor_elements(shape, rank, out_elements);
    }

    static int minmax(const void* data, size_t count,
                      const std::string& type_id,
                      void* out_min, void* out_max) {
        return fossil_data_tensor_minmax(
            data, count, type_id.c_str(), out_min, out_max);
    }

    static int mean(const void* data, size_t count,
                    const std::string& type_id,
                    double* out_mean) {
        return fossil_data_tensor_mean(
            data, count, type_id.c_str(), out_mean);
    }

    static int reduce_sum(const void* data,
                          const size_t* shape,
                          size_t rank,
                          size_t axis,
                          const std::string& type_id,
                          void* out_result) {
        return fossil_data_tensor_reduce_sum(
            data, shape, rank, axis, type_id.c_str(), out_result);
    }

    static int slice(const void* data,
                     const size_t* shape,
                     size_t rank,
                     const size_t* offsets,
                     const size_t* extents,
                     const std::string& type_id,
                     void* out_slice) {
        return fossil_data_tensor_slice(
            data, shape, rank, offsets, extents,
            type_id.c_str(), out_slice);
    }
};

} // namespace fossil::data
#endif

#endif /* FOSSIL_DATA_TENSOR_H */
