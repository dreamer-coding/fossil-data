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
#ifndef FOSSIL_DATA_TYPES_H
#define FOSSIL_DATA_TYPES_H

#include <stddef.h>
#include <stdint.h>

/* ============================================================================
 * Core Scalar Types
 * ============================================================================
 */

typedef double fossil_data_real_t;
typedef int64_t fossil_data_int_t;

/* ============================================================================
 * Result Codes (string-based dispatch encouraged)
 * ============================================================================
 */

typedef enum {
    FOSSIL_DATA_OK = 0,
    FOSSIL_DATA_ERROR,
    FOSSIL_DATA_INVALID,
    FOSSIL_DATA_NOMEM,
    FOSSIL_DATA_UNSUPPORTED
} fossil_data_status_t;

/* ============================================================================
 * Generic Buffer
 * ============================================================================
 */

typedef struct {
    void   *data;
    size_t  length;
    size_t  stride;
} fossil_data_buffer_t;

/* ============================================================================
 * String ID Type
 * ============================================================================
 */

typedef const char *fossil_data_id_t;

#endif /* FOSSIL_DATA_FRAMEWORK_H */
