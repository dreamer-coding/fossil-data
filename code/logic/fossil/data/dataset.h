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
#ifndef FOSSIL_DATA_DATASET_H
#define FOSSIL_DATA_DATASET_H

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Dataset utilities for Fossil Data Science.
 *
 * Provides lightweight functions for creating, inspecting, and summarizing datasets.
 * Each dataset is essentially a table of columns with known type IDs.
 *
 * Supported column type IDs:
 *   - "i8", "i16", "i32", "i64"
 *   - "u8", "u16", "u32", "u64", "size"
 *   - "f32", "f64"
 *   - "bool"
 *   - "hex", "oct", "bin"
 */

/**
 * @brief Create a dataset with a given number of rows and columns.
 *
 * @param rows       Number of rows.
 * @param cols       Number of columns.
 * @param col_types  Array of type strings for each column.
 * @param out_data   Output pointer to dataset handle.
 * @return           0 on success, non-zero on error.
 */
int fossil_data_dataset_create(
    size_t rows,
    size_t cols,
    const char** col_types,
    void** out_data
);

/**
 * @brief Free a dataset previously created.
 *
 * @param dataset    Dataset handle.
 * @return           0 on success, non-zero on error.
 */
int fossil_data_dataset_free(void* dataset);

/**
 * @brief Load a dataset from a CSV file.
 *
 * @param path       Path to CSV file.
 * @param out_data   Output pointer to dataset handle.
 * @return           0 on success, non-zero on error.
 */
int fossil_data_dataset_load_csv(
    const char* path,
    void** out_data
);

/**
 * @brief Get the number of rows in a dataset.
 *
 * @param dataset    Dataset handle.
 * @param out_rows   Output row count.
 * @return           0 on success, non-zero on error.
 */
int fossil_data_dataset_rows(
    const void* dataset,
    size_t* out_rows
);

/**
 * @brief Get the number of columns in a dataset.
 *
 * @param dataset    Dataset handle.
 * @param out_cols   Output column count.
 * @return           0 on success, non-zero on error.
 */
int fossil_data_dataset_cols(
    const void* dataset,
    size_t* out_cols
);

/**
 * @brief Get a column type string.
 *
 * @param dataset    Dataset handle.
 * @param col_index  Column index.
 * @param out_type   Output pointer to column type string.
 * @return           0 on success, non-zero on error.
 */
int fossil_data_dataset_col_type(
    const void* dataset,
    size_t col_index,
    const char** out_type
);

/**
 * @brief Summarize a numeric column (min, max, mean).
 *
 * @param dataset    Dataset handle.
 * @param col_index  Column index.
 * @param out_min    Output minimum value.
 * @param out_max    Output maximum value.
 * @param out_mean   Output mean (double)
 * @return           0 on success, non-zero on error.
 */
int fossil_data_dataset_col_summary(
    const void* dataset,
    size_t col_index,
    void* out_min,
    void* out_max,
    double* out_mean
);

#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
#include <string>

namespace fossil::data {

/**
 * @brief C++ wrapper for dataset utilities
 */
class Dataset {
public:
    static int create(size_t rows, size_t cols, const char** col_types, void** out_data) {
        return fossil_data_dataset_create(rows, cols, col_types, out_data);
    }

    static int free(void* dataset) {
        return fossil_data_dataset_free(dataset);
    }

    static int load_csv(const std::string& path, void** out_data) {
        return fossil_data_dataset_load_csv(path.c_str(), out_data);
    }

    static int rows(const void* dataset, size_t* out_rows) {
        return fossil_data_dataset_rows(dataset, out_rows);
    }

    static int cols(const void* dataset, size_t* out_cols) {
        return fossil_data_dataset_cols(dataset, out_cols);
    }

    static int col_type(const void* dataset, size_t col_index, const char** out_type) {
        return fossil_data_dataset_col_type(dataset, col_index, out_type);
    }

    static int col_summary(const void* dataset, size_t col_index, void* out_min, void* out_max, double* out_mean) {
        return fossil_data_dataset_col_summary(dataset, col_index, out_min, out_max, out_mean);
    }
};

} // namespace fossil::data
#endif

#endif /* FOSSIL_DATA_DATASET_H */
