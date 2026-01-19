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
#include <fossil/pizza/framework.h>

#include "fossil/data/framework.h"


// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test Utilites
// * * * * * * * * * * * * * * * * * * * * * * * *
// Setup steps for things like test fixtures and
// mock objects are set here.
// * * * * * * * * * * * * * * * * * * * * * * * *

// Define the test suite and add test cases
FOSSIL_SUITE(c_matrix_suite);

// Setup function for the test suite
FOSSIL_SETUP(c_matrix_suite) {
    // Setup code here
}

// Teardown function for the test suite
FOSSIL_TEARDOWN(c_matrix_suite) {
    // Teardown code here
}

// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test Cases
// * * * * * * * * * * * * * * * * * * * * * * * *
// The test cases below are provided as samples, inspired
// by the Meson build system's approach of using test cases
// as samples for library usage.
// * * * * * * * * * * * * * * * * * * * * * * * *

FOSSIL_TEST(c_test_matrix_create_and_free) {
    fossil_data_matrix_t *m = fossil_data_matrix_create(3, 4);
    ASSUME_NOT_CNULL(m);
    ASSUME_ITS_EQUAL_SIZE(3, fossil_data_matrix_rows(m));
    ASSUME_ITS_EQUAL_SIZE(4, fossil_data_matrix_cols(m));
    fossil_data_matrix_free(m);

    // Test zero dimensions
    ASSUME_ITS_CNULL(fossil_data_matrix_create(0, 4));
    ASSUME_ITS_CNULL(fossil_data_matrix_create(3, 0));
}

FOSSIL_TEST(c_test_matrix_get_set) {
    fossil_data_matrix_t *m = fossil_data_matrix_create(2, 2);
    ASSUME_NOT_CNULL(m);

    // Set and get valid
    ASSUME_ITS_EQUAL_I32(FOSSIL_DATA_MATRIX_OK, fossil_data_matrix_set(m, 1, 1, 42.0));
    double val = 0.0;
    ASSUME_ITS_EQUAL_I32(FOSSIL_DATA_MATRIX_OK, fossil_data_matrix_get(m, 1, 1, &val));
    ASSUME_ITS_EQUAL_F64(val, 42.0, 1e-9);

    // Out of bounds
    ASSUME_ITS_EQUAL_I32(FOSSIL_DATA_MATRIX_ERR_BOUNDS, fossil_data_matrix_set(m, 2, 0, 1.0));
    ASSUME_ITS_EQUAL_I32(FOSSIL_DATA_MATRIX_ERR_BOUNDS, fossil_data_matrix_get(m, 0, 2, &val));

    // Null pointer
    ASSUME_ITS_EQUAL_I32(FOSSIL_DATA_MATRIX_ERR_NULL, fossil_data_matrix_set(NULL, 0, 0, 1.0));
    ASSUME_ITS_EQUAL_I32(FOSSIL_DATA_MATRIX_ERR_NULL, fossil_data_matrix_get(NULL, 0, 0, &val));
    ASSUME_ITS_EQUAL_I32(FOSSIL_DATA_MATRIX_ERR_NULL, fossil_data_matrix_get(m, 0, 0, NULL));

    fossil_data_matrix_free(m);
}

FOSSIL_TEST(c_test_matrix_fill) {
    fossil_data_matrix_t *m = fossil_data_matrix_create(2, 3);
    ASSUME_NOT_CNULL(m);
    fossil_data_matrix_fill(m, 7.5);

    for (size_t r = 0; r < 2; ++r) {
        for (size_t c = 0; c < 3; ++c) {
            double v = 0.0;
            ASSUME_ITS_EQUAL_I32(FOSSIL_DATA_MATRIX_OK, fossil_data_matrix_get(m, r, c, &v));
            ASSUME_ITS_EQUAL_F64(v, 7.5, 1e-9);
        }
    }

    // Null pointer
    fossil_data_matrix_fill(NULL, 1.0);

    fossil_data_matrix_free(m);
}

FOSSIL_TEST(c_test_matrix_copy) {
    fossil_data_matrix_t *m = fossil_data_matrix_create(2, 2);
    ASSUME_NOT_CNULL(m);
    fossil_data_matrix_set(m, 0, 0, 1.0);
    fossil_data_matrix_set(m, 0, 1, 2.0);
    fossil_data_matrix_set(m, 1, 0, 3.0);
    fossil_data_matrix_set(m, 1, 1, 4.0);

    fossil_data_matrix_t *copy = NULL;
    ASSUME_ITS_EQUAL_I32(FOSSIL_DATA_MATRIX_OK, fossil_data_matrix_copy(m, &copy));
    ASSUME_NOT_CNULL(copy);

    double v = 0.0;
    fossil_data_matrix_get(copy, 1, 1, &v);
    ASSUME_ITS_EQUAL_F64(v, 4.0, 1e-9);

    // Null pointer
    ASSUME_ITS_EQUAL_I32(FOSSIL_DATA_MATRIX_ERR_NULL, fossil_data_matrix_copy(NULL, &copy));
    ASSUME_ITS_EQUAL_I32(FOSSIL_DATA_MATRIX_ERR_NULL, fossil_data_matrix_copy(m, NULL));

    fossil_data_matrix_free(m);
    fossil_data_matrix_free(copy);
}

FOSSIL_TEST(c_test_matrix_add) {
    fossil_data_matrix_t *a = fossil_data_matrix_create(2, 2);
    fossil_data_matrix_t *b = fossil_data_matrix_create(2, 2);
    ASSUME_NOT_CNULL(a);
    ASSUME_NOT_CNULL(b);

    fossil_data_matrix_set(a, 0, 0, 1.0);
    fossil_data_matrix_set(a, 0, 1, 2.0);
    fossil_data_matrix_set(a, 1, 0, 3.0);
    fossil_data_matrix_set(a, 1, 1, 4.0);

    fossil_data_matrix_set(b, 0, 0, 10.0);
    fossil_data_matrix_set(b, 0, 1, 20.0);
    fossil_data_matrix_set(b, 1, 0, 30.0);
    fossil_data_matrix_set(b, 1, 1, 40.0);

    fossil_data_matrix_t *sum = NULL;
    ASSUME_ITS_EQUAL_I32(FOSSIL_DATA_MATRIX_OK, fossil_data_matrix_add(a, b, &sum));
    ASSUME_NOT_CNULL(sum);

    double v = 0.0;
    fossil_data_matrix_get(sum, 1, 1, &v);
    ASSUME_ITS_EQUAL_F64(v, 44.0, 1e-9);

    // Dimension mismatch
    fossil_data_matrix_t *bad = fossil_data_matrix_create(1, 2);
    ASSUME_ITS_EQUAL_I32(FOSSIL_DATA_MATRIX_ERR_DIM_MISMATCH, fossil_data_matrix_add(a, bad, &sum));
    fossil_data_matrix_free(bad);

    // Null pointer
    ASSUME_ITS_EQUAL_I32(FOSSIL_DATA_MATRIX_ERR_NULL, fossil_data_matrix_add(NULL, b, &sum));
    ASSUME_ITS_EQUAL_I32(FOSSIL_DATA_MATRIX_ERR_NULL, fossil_data_matrix_add(a, NULL, &sum));
    ASSUME_ITS_EQUAL_I32(FOSSIL_DATA_MATRIX_ERR_NULL, fossil_data_matrix_add(a, b, NULL));

    fossil_data_matrix_free(a);
    fossil_data_matrix_free(b);
    fossil_data_matrix_free(sum);
}

FOSSIL_TEST(c_test_matrix_mul) {
    fossil_data_matrix_t *a = fossil_data_matrix_create(2, 3);
    fossil_data_matrix_t *b = fossil_data_matrix_create(3, 2);
    ASSUME_NOT_CNULL(a);
    ASSUME_NOT_CNULL(b);

    // Fill a: [1 2 3; 4 5 6]
    fossil_data_matrix_set(a, 0, 0, 1.0);
    fossil_data_matrix_set(a, 0, 1, 2.0);
    fossil_data_matrix_set(a, 0, 2, 3.0);
    fossil_data_matrix_set(a, 1, 0, 4.0);
    fossil_data_matrix_set(a, 1, 1, 5.0);
    fossil_data_matrix_set(a, 1, 2, 6.0);

    // Fill b: [7 8; 9 10; 11 12]
    fossil_data_matrix_set(b, 0, 0, 7.0);
    fossil_data_matrix_set(b, 0, 1, 8.0);
    fossil_data_matrix_set(b, 1, 0, 9.0);
    fossil_data_matrix_set(b, 1, 1, 10.0);
    fossil_data_matrix_set(b, 2, 0, 11.0);
    fossil_data_matrix_set(b, 2, 1, 12.0);

    fossil_data_matrix_t *prod = NULL;
    ASSUME_ITS_EQUAL_I32(FOSSIL_DATA_MATRIX_OK, fossil_data_matrix_mul(a, b, &prod));
    ASSUME_NOT_CNULL(prod);

    double v = 0.0;
    fossil_data_matrix_get(prod, 0, 0, &v);
    ASSUME_ITS_EQUAL_F64(v, 58.0, 1e-9); // 1*7 + 2*9 + 3*11

    fossil_data_matrix_get(prod, 1, 1, &v);
    ASSUME_ITS_EQUAL_F64(v, 154.0, 1e-9); // 4*8 + 5*10 + 6*12

    // Dimension mismatch
    fossil_data_matrix_t *bad = fossil_data_matrix_create(2, 2);
    ASSUME_ITS_EQUAL_I32(FOSSIL_DATA_MATRIX_ERR_DIM_MISMATCH, fossil_data_matrix_mul(a, bad, &prod));
    fossil_data_matrix_free(bad);

    // Null pointer
    ASSUME_ITS_EQUAL_I32(FOSSIL_DATA_MATRIX_ERR_NULL, fossil_data_matrix_mul(NULL, b, &prod));
    ASSUME_ITS_EQUAL_I32(FOSSIL_DATA_MATRIX_ERR_NULL, fossil_data_matrix_mul(a, NULL, &prod));
    ASSUME_ITS_EQUAL_I32(FOSSIL_DATA_MATRIX_ERR_NULL, fossil_data_matrix_mul(a, b, NULL));

    fossil_data_matrix_free(a);
    fossil_data_matrix_free(b);
    fossil_data_matrix_free(prod);
}

// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test Pool
// * * * * * * * * * * * * * * * * * * * * * * * *

FOSSIL_TEST_GROUP(c_matrix_tests) {
    FOSSIL_TEST_ADD(c_matrix_suite, c_test_matrix_create_and_free);
    FOSSIL_TEST_ADD(c_matrix_suite, c_test_matrix_get_set);
    FOSSIL_TEST_ADD(c_matrix_suite, c_test_matrix_fill);
    FOSSIL_TEST_ADD(c_matrix_suite, c_test_matrix_copy);
    FOSSIL_TEST_ADD(c_matrix_suite, c_test_matrix_add);
    FOSSIL_TEST_ADD(c_matrix_suite, c_test_matrix_mul);

    // Register the test suite
    FOSSIL_TEST_REGISTER(c_matrix_suite);
}
