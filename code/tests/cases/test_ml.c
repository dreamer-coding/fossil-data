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
FOSSIL_SUITE(c_ml_suite);

// Setup function for the test suite
FOSSIL_SETUP(c_ml_suite) {
    // Setup code here
}

// Teardown function for the test suite
FOSSIL_TEARDOWN(c_ml_suite) {
    // Teardown code here
}

// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test Cases
// * * * * * * * * * * * * * * * * * * * * * * * *
// The test cases below are provided as samples, inspired
// by the Meson build system's approach of using test cases
// as samples for library usage.
// * * * * * * * * * * * * * * * * * * * * * * * *

FOSSIL_TEST(c_test_ml_train_predict_free_linear_regression_f64) {
    // Simple linear regression: y = 2x + 1
    double X[4] = {1.0, 2.0, 3.0, 4.0};
    double y[4] = {3.0, 5.0, 7.0, 9.0};
    void *model = NULL;

    // Train model
    int rc = fossil_data_ml_train(X, y, 4, 1, "f64", "linear_regression", &model);
    ASSUME_ITS_EQUAL_I32(0, rc);
    ASSUME_NOT_CNULL(model);

    // Predict
    double X_test[2] = {5.0, 6.0};
    double y_pred[2] = {0.0, 0.0};
    rc = fossil_data_ml_predict(X_test, 2, 1, y_pred, model, "f64");
    ASSUME_ITS_EQUAL_I32(0, rc);
    // Should be close to 11.0 and 13.0
    ASSUME_ITS_EQUAL_F64(11.0, y_pred[0], 1e-6);
    ASSUME_ITS_EQUAL_F64(13.0, y_pred[1], 1e-6);

    // Free model
    rc = fossil_data_ml_free_model(model);
    ASSUME_ITS_EQUAL_I32(0, rc);
}

FOSSIL_TEST(c_test_ml_train_predict_free_logistic_regression_i32) {
    // Simple binary classification: y = 1 if x > 0, else 0
    int X[6] = {-2, -1, 0, 1, 2, 3};
    int y[6] = {0, 0, 0, 1, 1, 1};
    void *model = NULL;

    int rc = fossil_data_ml_train(X, y, 6, 1, "i32", "logistic_regression", &model);
    ASSUME_ITS_EQUAL_I32(0, rc);
    ASSUME_NOT_CNULL(model);

    int X_test[3] = {-3, 0, 5};
    int y_pred[3] = {0, 0, 0};
    rc = fossil_data_ml_predict(X_test, 3, 1, y_pred, model, "i32");
    ASSUME_ITS_EQUAL_I32(0, rc);
    // Should be 0, 0, 1 (depending on implementation, 0 for <=0, 1 for >0)
    ASSUME_ITS_EQUAL_I32(0, y_pred[0]);
    ASSUME_ITS_EQUAL_I32(0, y_pred[1]);
    ASSUME_ITS_EQUAL_I32(1, y_pred[2]);

    rc = fossil_data_ml_free_model(model);
    ASSUME_ITS_EQUAL_I32(0, rc);
}

FOSSIL_TEST(c_test_ml_train_predict_free_kmeans_f32) {
    // Two clusters: [0,0], [0,1], [10,10], [10,11]
    float X[8] = {0.0f, 0.0f, 0.0f, 1.0f, 10.0f, 10.0f, 10.0f, 11.0f};
    // Labels are not used for kmeans, but API requires y, so pass NULL
    void *model = NULL;

    int rc = fossil_data_ml_train(X, NULL, 4, 2, "f32", "kmeans", &model);
    ASSUME_ITS_EQUAL_I32(0, rc);
    ASSUME_NOT_CNULL(model);

    float X_test[4] = {0.0f, 0.5f, 10.0f, 10.5f};
    int y_pred[2] = {0, 0};
    rc = fossil_data_ml_predict(X_test, 2, 2, y_pred, model, "i32");
    ASSUME_ITS_EQUAL_I32(0, rc);
    // Should assign first to cluster 0, second to cluster 1 (order may vary)
    ASSUME_ITS_TRUE(y_pred[0] != y_pred[1]);

    rc = fossil_data_ml_free_model(model);
    ASSUME_ITS_EQUAL_I32(0, rc);
}

FOSSIL_TEST(c_test_ml_train_invalid_args) {
    double X[2] = {1.0, 2.0};
    double y[2] = {1.0, 2.0};
    void *model = NULL;

    // Invalid type_id
    int rc = fossil_data_ml_train(X, y, 2, 1, "badtype", "linear_regression", &model);
    ASSUME_ITS_TRUE(rc != 0);

    // Invalid model_id
    rc = fossil_data_ml_train(X, y, 2, 1, "f64", "badmodel", &model);
    ASSUME_ITS_TRUE(rc != 0);
    // Null pointers
    rc = fossil_data_ml_train(NULL, y, 2, 1, "f64", "linear_regression", &model);
    ASSUME_ITS_TRUE(rc != 0);
    rc = fossil_data_ml_train(X, NULL, 2, 1, "f64", "linear_regression", &model);
    ASSUME_ITS_TRUE(rc != 0);
    rc = fossil_data_ml_train(X, y, 0, 1, "f64", "linear_regression", &model);
    ASSUME_ITS_TRUE(rc != 0);
    rc = fossil_data_ml_train(X, y, 2, 0, "f64", "linear_regression", &model);
    ASSUME_ITS_TRUE(rc != 0);
    rc = fossil_data_ml_train(X, y, 2, 1, "f64", "linear_regression", NULL);
    ASSUME_ITS_TRUE(rc != 0);
}

FOSSIL_TEST(c_test_ml_predict_invalid_args) {
    double X[2] = {1.0, 2.0};
    double y_pred[2] = {0.0, 0.0};
    void *model = NULL;

    // Model must be trained first
    int rc = fossil_data_ml_predict(X, 2, 1, y_pred, NULL, "f64");
    ASSUME_ITS_TRUE(rc != 0);

    // Null pointers
    rc = fossil_data_ml_predict(NULL, 2, 1, y_pred, model, "f64");
    ASSUME_ITS_TRUE(rc != 0);
    rc = fossil_data_ml_predict(X, 2, 1, NULL, model, "f64");
    ASSUME_ITS_TRUE(rc != 0);
    rc = fossil_data_ml_predict(X, 0, 1, y_pred, model, "f64");
    ASSUME_ITS_TRUE(rc != 0);
    rc = fossil_data_ml_predict(X, 2, 0, y_pred, model, "f64");
    ASSUME_ITS_TRUE(rc != 0);
    rc = fossil_data_ml_predict(X, 2, 1, y_pred, model, NULL);
    ASSUME_ITS_TRUE(rc != 0);
}

FOSSIL_TEST(c_test_ml_free_model_invalid_args) {
    // Freeing NULL should fail or be a no-op with error
    int rc = fossil_data_ml_free_model(NULL);
    ASSUME_ITS_TRUE(rc != 0);
}

// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test Pool
// * * * * * * * * * * * * * * * * * * * * * * * *

FOSSIL_TEST_GROUP(c_ml_tests) {
    FOSSIL_TEST_ADD(c_ml_suite, c_test_ml_train_predict_free_linear_regression_f64);
    FOSSIL_TEST_ADD(c_ml_suite, c_test_ml_train_predict_free_logistic_regression_i32);
    FOSSIL_TEST_ADD(c_ml_suite, c_test_ml_train_predict_free_kmeans_f32);
    FOSSIL_TEST_ADD(c_ml_suite, c_test_ml_train_invalid_args);
    FOSSIL_TEST_ADD(c_ml_suite, c_test_ml_predict_invalid_args);
    FOSSIL_TEST_ADD(c_ml_suite, c_test_ml_free_model_invalid_args);


    // Register the test suite
    FOSSIL_TEST_REGISTER(c_ml_suite);
}
