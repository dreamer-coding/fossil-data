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
#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

/* ============================================================================
 * Opaque Transform
 * ============================================================================
 */

typedef struct fossil_data_transform fossil_data_transform_t;

/* ============================================================================
 * Creation / Destruction
 * ============================================================================
 */

/* id examples:
 *   "normalize"
 *   "standardize"
 *   "log"
 *   "fft"
 *   "rolling_mean"
 */
fossil_data_transform_t *
fossil_data_transform_create(fossil_data_id_t id);

void
fossil_data_transform_destroy(fossil_data_transform_t *transform);

/* ============================================================================
 * Configuration
 * ============================================================================
 */

/* key examples:
 *   "window"
 *   "epsilon"
 *   "axis"
 */
fossil_data_status_t
fossil_data_transform_set(
    fossil_data_transform_t *transform,
    fossil_data_id_t         key,
    fossil_data_id_t         value
);

/* ============================================================================
 * Execution
 * ============================================================================
 */

fossil_data_status_t
fossil_data_transform_apply(
    fossil_data_transform_t *transform,
    const fossil_data_buffer_t *input,
    fossil_data_buffer_t       *output
);

#ifdef __cplusplus
}
#include <string>

namespace fossil {
    
    namespace data {



    } // namespace data

} // namespace fossil

#endif

#endif /* FOSSIL_DATA_TRANSFORM_H */
