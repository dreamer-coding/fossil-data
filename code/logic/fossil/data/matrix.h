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
#ifndef FOSSIL_DATA_MATRIX_H
#define FOSSIL_DATA_MATRIX_H

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ============================================================================
 * Status Codes
 * ============================================================================
 */
typedef enum {
    FOSSIL_DATA_MATRIX_OK = 0,
    FOSSIL_DATA_MATRIX_ERR_NULL,
    FOSSIL_DATA_MATRIX_ERR_ALLOC,
    FOSSIL_DATA_MATRIX_ERR_BOUNDS,
    FOSSIL_DATA_MATRIX_ERR_DIM_MISMATCH
} fossil_data_matrix_status_t;

/* ============================================================================
 * Opaque Type
 * ============================================================================
 */
typedef struct fossil_data_matrix fossil_data_matrix_t;

/**
 * @brief Creates a new matrix with the specified number of rows and columns.
 *
 * Allocates memory for a matrix of doubles with the given dimensions.
 *
 * @param rows Number of rows in the matrix.
 * @param cols Number of columns in the matrix.
 * @return Pointer to the newly created matrix, or NULL if allocation fails.
 */
fossil_data_matrix_t *fossil_data_matrix_create(size_t rows, size_t cols);

/**
 * @brief Frees the memory associated with a matrix.
 *
 * Destroys the matrix and releases all allocated resources.
 *
 * @param m Pointer to the matrix to be freed. If NULL, no action is taken.
 */
void fossil_data_matrix_free(fossil_data_matrix_t *m);

/**
 * @brief Returns the number of rows in the matrix.
 *
 * @param m Pointer to the matrix.
 * @return Number of rows, or 0 if m is NULL.
 */
size_t fossil_data_matrix_rows(const fossil_data_matrix_t *m);

/**
 * @brief Returns the number of columns in the matrix.
 *
 * @param m Pointer to the matrix.
 * @return Number of columns, or 0 if m is NULL.
 */
size_t fossil_data_matrix_cols(const fossil_data_matrix_t *m);

/**
 * @brief Retrieves the value of an element at the specified row and column.
 *
 * Checks bounds and writes the value to out_value if successful.
 *
 * @param m Pointer to the matrix.
 * @param row Row index (zero-based).
 * @param col Column index (zero-based).
 * @param out_value Pointer to where the value will be stored.
 * @return Status code indicating success or error (e.g., out of bounds, NULL pointer).
 */
fossil_data_matrix_status_t fossil_data_matrix_get(
    const fossil_data_matrix_t *m,
    size_t row,
    size_t col,
    double *out_value
);

/**
 * @brief Sets the value of an element at the specified row and column.
 *
 * Checks bounds and updates the value if successful.
 *
 * @param m Pointer to the matrix.
 * @param row Row index (zero-based).
 * @param col Column index (zero-based).
 * @param value Value to set.
 * @return Status code indicating success or error (e.g., out of bounds, NULL pointer).
 */
fossil_data_matrix_status_t fossil_data_matrix_set(
    fossil_data_matrix_t *m,
    size_t row,
    size_t col,
    double value
);

/**
 * @brief Fills all elements of the matrix with the specified value.
 *
 * @param m Pointer to the matrix.
 * @param value Value to fill the matrix with.
 */
void fossil_data_matrix_fill(
    fossil_data_matrix_t *m,
    double value
);

/**
 * @brief Creates a deep copy of the source matrix.
 *
 * Allocates a new matrix and copies all elements from src.
 *
 * @param src Pointer to the source matrix.
 * @param out Pointer to where the new matrix pointer will be stored.
 * @return Status code indicating success or error (e.g., allocation failure, NULL pointer).
 */
fossil_data_matrix_status_t fossil_data_matrix_copy(
    const fossil_data_matrix_t *src,
    fossil_data_matrix_t **out
);

/**
 * @brief Adds two matrices element-wise and stores the result in a new matrix.
 *
 * Both matrices must have the same dimensions.
 *
 * @param a Pointer to the first matrix.
 * @param b Pointer to the second matrix.
 * @param out Pointer to where the result matrix pointer will be stored.
 * @return Status code indicating success or error (e.g., dimension mismatch, NULL pointer).
 */
fossil_data_matrix_status_t fossil_data_matrix_add(
    const fossil_data_matrix_t *a,
    const fossil_data_matrix_t *b,
    fossil_data_matrix_t **out
);

/**
 * @brief Multiplies two matrices and stores the result in a new matrix.
 *
 * The number of columns in the first matrix must equal the number of rows in the second.
 *
 * @param a Pointer to the first matrix.
 * @param b Pointer to the second matrix.
 * @param out Pointer to where the result matrix pointer will be stored.
 * @return Status code indicating success or error (e.g., dimension mismatch, NULL pointer).
 */
fossil_data_matrix_status_t fossil_data_matrix_mul(
    const fossil_data_matrix_t *a,
    const fossil_data_matrix_t *b,
    fossil_data_matrix_t **out
);

#ifdef __cplusplus
}
#include <string>

/**
 * C++ API namespace for Fossil Logic source code.
 */
namespace fossil {
    /**
     * Data namespace for data related code.
     */
    namespace data {

        class Matrix
        {
        public:
            /**
             * @brief Constructs a matrix with the specified number of rows and columns.
             *
             * Allocates a new matrix using the C API.
             *
             * @param rows Number of rows.
             * @param cols Number of columns.
             */
            Matrix(size_t rows, size_t cols)
                : m_ptr(fossil_data_matrix_create(rows, cols))
            {}

            /**
             * @brief Destructor. Frees the matrix resources.
             */
            ~Matrix() {
                fossil_data_matrix_free(m_ptr);
            }

            /**
             * @brief Copy constructor. Creates a deep copy of another matrix.
             *
             * @param other Matrix to copy from.
             */
            Matrix(const Matrix& other) {
                fossil_data_matrix_t* copy = nullptr;
                if (fossil_data_matrix_copy(other.m_ptr, &copy) == FOSSIL_DATA_MATRIX_OK) {
                    m_ptr = copy;
                } else {
                    m_ptr = nullptr;
                }
            }

            /**
             * @brief Copy assignment operator. Deep copies another matrix.
             *
             * @param other Matrix to copy from.
             * @return Reference to this matrix.
             */
            Matrix& operator=(const Matrix& other) {
                if (this != &other) {
                    fossil_data_matrix_free(m_ptr);
                    fossil_data_matrix_t* copy = nullptr;
                    if (fossil_data_matrix_copy(other.m_ptr, &copy) == FOSSIL_DATA_MATRIX_OK) {
                        m_ptr = copy;
                    } else {
                        m_ptr = nullptr;
                    }
                }
                return *this;
            }

            /**
             * @brief Move constructor. Transfers ownership from another matrix.
             *
             * @param other Matrix to move from.
             */
            Matrix(Matrix&& other) noexcept
                : m_ptr(other.m_ptr)
            {
                other.m_ptr = nullptr;
            }

            /**
             * @brief Move assignment operator. Transfers ownership from another matrix.
             *
             * @param other Matrix to move from.
             * @return Reference to this matrix.
             */
            Matrix& operator=(Matrix&& other) noexcept {
                if (this != &other) {
                    fossil_data_matrix_free(m_ptr);
                    m_ptr = other.m_ptr;
                    other.m_ptr = nullptr;
                }
                return *this;
            }

            /**
             * @brief Returns the number of rows in the matrix.
             *
             * @return Number of rows.
             */
            size_t rows() const {
                return fossil_data_matrix_rows(m_ptr);
            }

            /**
             * @brief Returns the number of columns in the matrix.
             *
             * @return Number of columns.
             */
            size_t cols() const {
                return fossil_data_matrix_cols(m_ptr);
            }

            /**
             * @brief Gets the value at the specified row and column.
             *
             * @param row Row index (zero-based).
             * @param col Column index (zero-based).
             * @return Value at the specified position.
             */
            double get(size_t row, size_t col) const {
                double value = 0.0;
                fossil_data_matrix_get(m_ptr, row, col, &value);
                return value;
            }

            /**
             * @brief Sets the value at the specified row and column.
             *
             * @param row Row index (zero-based).
             * @param col Column index (zero-based).
             * @param value Value to set.
             * @return True if successful, false otherwise.
             */
            bool set(size_t row, size_t col, double value) {
                return fossil_data_matrix_set(m_ptr, row, col, value) == FOSSIL_DATA_MATRIX_OK;
            }

            /**
             * @brief Fills the matrix with the specified value.
             *
             * @param value Value to fill.
             */
            void fill(double value) {
                fossil_data_matrix_fill(m_ptr, value);
            }

            /**
             * @brief Adds this matrix to another and returns the result.
             *
             * @param other Matrix to add.
             * @return Resulting matrix, or an invalid matrix if addition fails.
             */
            Matrix add(const Matrix& other) const {
                fossil_data_matrix_t* result = nullptr;
                if (fossil_data_matrix_add(m_ptr, other.m_ptr, &result) == FOSSIL_DATA_MATRIX_OK) {
                    return Matrix(result);
                }
                return Matrix(0, 0);
            }

            /**
             * @brief Multiplies this matrix with another and returns the result.
             *
             * @param other Matrix to multiply with.
             * @return Resulting matrix, or an invalid matrix if multiplication fails.
             */
            Matrix mul(const Matrix& other) const {
                fossil_data_matrix_t* result = nullptr;
                if (fossil_data_matrix_mul(m_ptr, other.m_ptr, &result) == FOSSIL_DATA_MATRIX_OK) {
                    return Matrix(result);
                }
                return Matrix(0, 0);
            }

            /**
             * @brief Checks if the matrix is valid (not null).
             *
             * @return True if valid, false otherwise.
             */
            bool is_valid() const {
                return m_ptr != nullptr;
            }

        private:
            explicit Matrix(fossil_data_matrix_t* ptr)
                : m_ptr(ptr)
            {}

            fossil_data_matrix_t* m_ptr;
        };

    } // namespace data

} // namespace fossil

#endif

#endif /* FOSSIL_DATA_MATRIX_H */
