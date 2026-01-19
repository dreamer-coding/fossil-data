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
FOSSIL_SUITE(cpp_matrix_suite);

// Setup function for the test suite
FOSSIL_SETUP(cpp_matrix_suite) {
    // Setup code here
}

// Teardown function for the test suite
FOSSIL_TEARDOWN(cpp_matrix_suite) {
    // Teardown code here
}

// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test Cases
// * * * * * * * * * * * * * * * * * * * * * * * *
// The test cases below are provided as samples, inspired
// by the Meson build system's approach of using test cases
// as samples for library usage.
// * * * * * * * * * * * * * * * * * * * * * * * *

using fossil::data::Matrix;

FOSSIL_TEST(cpp_test_matrix_create_and_free) {
    Matrix m(3, 4);
    ASSUME_ITS_TRUE(m.is_valid());
    ASSUME_ITS_EQUAL_SIZE(3, m.rows());
    ASSUME_ITS_EQUAL_SIZE(4, m.cols());

    // Test zero dimensions
    Matrix m_zero_row(0, 4);
    Matrix m_zero_col(3, 0);
    ASSUME_ITS_FALSE(m_zero_row.is_valid());
    ASSUME_ITS_FALSE(m_zero_col.is_valid());
}

FOSSIL_TEST(cpp_test_matrix_get_set) {
    Matrix m(2, 2);
    ASSUME_ITS_TRUE(m.is_valid());

    // Set and get valid
    ASSUME_ITS_TRUE(m.set(1, 1, 42.0));
    ASSUME_ITS_EQUAL_F64(m.get(1, 1), 42.0, 1e-9);

    // Out of bounds (should not crash, but not successful)
    ASSUME_ITS_FALSE(m.set(2, 0, 1.0));
    // get returns 0.0 if out of bounds, but we can't check error code directly
    // so just check that value is not set
    double val = m.get(0, 2);
    ASSUME_ITS_EQUAL_F64(val, 0.0, 1e-9);

    // Null pointer: handled by is_valid()
    Matrix m_null(0, 0);
    ASSUME_ITS_FALSE(m_null.set(0, 0, 1.0));
    ASSUME_ITS_EQUAL_F64(m_null.get(0, 0), 0.0, 1e-9);
}

FOSSIL_TEST(cpp_test_matrix_fill) {
    Matrix m(2, 3);
    ASSUME_ITS_TRUE(m.is_valid());
    m.fill(7.5);

    for (size_t r = 0; r < 2; ++r) {
        for (size_t c = 0; c < 3; ++c) {
            ASSUME_ITS_EQUAL_F64(m.get(r, c), 7.5, 1e-9);
        }
    }

    // Null pointer
    Matrix m_null(0, 0);
    m_null.fill(1.0); // Should not crash
}

FOSSIL_TEST(cpp_test_matrix_copy) {
    Matrix m(2, 2);
    ASSUME_ITS_TRUE(m.is_valid());
    m.set(0, 0, 1.0);
    m.set(0, 1, 2.0);
    m.set(1, 0, 3.0);
    m.set(1, 1, 4.0);

    Matrix copy = m;
    ASSUME_ITS_TRUE(copy.is_valid());
    ASSUME_ITS_EQUAL_F64(copy.get(1, 1), 4.0, 1e-9);

    // Null pointer
    Matrix m_null(0, 0);
    Matrix copy_null = m_null;
    ASSUME_ITS_FALSE(copy_null.is_valid());
}

FOSSIL_TEST(cpp_test_matrix_add) {
    Matrix a(2, 2);
    Matrix b(2, 2);
    ASSUME_ITS_TRUE(a.is_valid());
    ASSUME_ITS_TRUE(b.is_valid());

    a.set(0, 0, 1.0);
    a.set(0, 1, 2.0);
    a.set(1, 0, 3.0);
    a.set(1, 1, 4.0);

    b.set(0, 0, 10.0);
    b.set(0, 1, 20.0);
    b.set(1, 0, 30.0);
    b.set(1, 1, 40.0);

    Matrix sum = a.add(b);
    ASSUME_ITS_TRUE(sum.is_valid());
    ASSUME_ITS_EQUAL_F64(sum.get(1, 1), 44.0, 1e-9);

    // Dimension mismatch
    Matrix bad(1, 2);
    Matrix bad_sum = a.add(bad);
    ASSUME_ITS_FALSE(bad_sum.is_valid());

    // Null pointer
    Matrix null_sum = a.add(Matrix(0, 0));
    ASSUME_ITS_FALSE(null_sum.is_valid());
}

FOSSIL_TEST(cpp_test_matrix_mul) {
    Matrix a(2, 3);
    Matrix b(3, 2);
    ASSUME_ITS_TRUE(a.is_valid());
    ASSUME_ITS_TRUE(b.is_valid());

    // Fill a: [1 2 3; 4 5 6]
    a.set(0, 0, 1.0);
    a.set(0, 1, 2.0);
    a.set(0, 2, 3.0);
    a.set(1, 0, 4.0);
    a.set(1, 1, 5.0);
    a.set(1, 2, 6.0);

    // Fill b: [7 8; 9 10; 11 12]
    b.set(0, 0, 7.0);
    b.set(0, 1, 8.0);
    b.set(1, 0, 9.0);
    b.set(1, 1, 10.0);
    b.set(2, 0, 11.0);
    b.set(2, 1, 12.0);

    Matrix prod = a.mul(b);
    ASSUME_ITS_TRUE(prod.is_valid());
    ASSUME_ITS_EQUAL_F64(prod.get(0, 0), 58.0, 1e-9); // 1*7 + 2*9 + 3*11
    ASSUME_ITS_EQUAL_F64(prod.get(1, 1), 154.0, 1e-9); // 4*8 + 5*10 + 6*12

    // Dimension mismatch
    Matrix bad(2, 2);
    Matrix bad_prod = a.mul(bad);
    ASSUME_ITS_FALSE(bad_prod.is_valid());

    // Null pointer
    Matrix null_prod = a.mul(Matrix(0, 0));
    ASSUME_ITS_FALSE(null_prod.is_valid());
}

// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test Pool
// * * * * * * * * * * * * * * * * * * * * * * * *

FOSSIL_TEST_GROUP(cpp_matrix_tests) {
    FOSSIL_TEST_ADD(cpp_matrix_suite, cpp_test_matrix_create_and_free);
    FOSSIL_TEST_ADD(cpp_matrix_suite, cpp_test_matrix_get_set);
    FOSSIL_TEST_ADD(cpp_matrix_suite, cpp_test_matrix_fill);
    FOSSIL_TEST_ADD(cpp_matrix_suite, cpp_test_matrix_copy);
    FOSSIL_TEST_ADD(cpp_matrix_suite, cpp_test_matrix_add);
    FOSSIL_TEST_ADD(cpp_matrix_suite, cpp_test_matrix_mul);

    // Register the test suite
    FOSSIL_TEST_REGISTER(cpp_matrix_suite);
}
