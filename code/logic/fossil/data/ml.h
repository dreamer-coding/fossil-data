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
#ifndef FOSSIL_DATA_ML_H
#define FOSSIL_DATA_ML_H

#include <stddef.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @file fossil_data_ml.h
 * @brief Machine learning utilities for training and inference.
 *
 * Supports basic ML tasks such as regression, classification, and clustering.
 *
 * Supported type string IDs:
 *   - "i32", "i64", "f32", "f64"
 *
 * Supported model string IDs:
 *   - "linear_regression"
 *   - "logistic_regression"
 *   - "kmeans"
 *
 * Model handles are opaque pointers managed by the library.
 */

/* Train an ML model */
int fossil_data_ml_train(
    const void* X,
    const void* y,
    size_t rows,
    size_t cols,
    const char* type_id,
    const char* model_id,
    void** model_handle
);

/* Make predictions with a trained model */
int fossil_data_ml_predict(
    const void* X,
    size_t rows,
    size_t cols,
    void* y_pred,
    void* model_handle,
    const char* type_id
);

/* Free a trained model */
int fossil_data_ml_free_model(void* model_handle);

#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
#include <string>

namespace fossil::data {

class ML {
public:
    static void* train(
        const void* X,
        const void* y,
        size_t rows,
        size_t cols,
        const std::string& type_id,
        const std::string& model_id
    ) {
        void* model_handle = nullptr;
        int result = fossil_data_ml_train(
            X, y, rows, cols, type_id.c_str(), model_id.c_str(), &model_handle
        );
        return (result == 0) ? model_handle : nullptr;
    }

    static int predict(
        const void* X,
        size_t rows,
        size_t cols,
        void* y_pred,
        void* model_handle,
        const std::string& type_id
    ) {
        return fossil_data_ml_predict(
            X, rows, cols, y_pred, model_handle, type_id.c_str()
        );
    }

    static void free_model(void* model_handle) {
        fossil_data_ml_free_model(model_handle);
    }
};

} // namespace fossil::data
#endif

#endif /* FOSSIL_DATA_ML_H */
