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
#ifndef FOSSIL_DATA_STREAM_H
#define FOSSIL_DATA_STREAM_H

#include <stddef.h>
#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

/* ============================================================================
 * Opaque Stream
 * ============================================================================
 */

typedef struct fossil_data_stream fossil_data_stream_t;

/* ============================================================================
 * Creation / Destruction
 * ============================================================================
 */

/* id examples:
 *   "csv"
 *   "binary"
 *   "memory"
 *   "socket"
 */
fossil_data_stream_t *fossil_data_stream_create(fossil_data_id_t id);

void fossil_data_stream_destroy(fossil_data_stream_t *stream);

/* ============================================================================
 * Configuration
 * ============================================================================
 */

/* key examples:
 *   "path"
 *   "delimiter"
 *   "endianness"
 *   "schema"
 */
fossil_data_status_t fossil_data_stream_set(
    fossil_data_stream_t *stream,
    fossil_data_id_t      key,
    fossil_data_id_t      value
);

/* ============================================================================
 * IO
 * ============================================================================
 */

fossil_data_status_t fossil_data_stream_read(
    fossil_data_stream_t       *stream,
    fossil_data_buffer_t       *out_buffer
);

fossil_data_status_t fossil_data_stream_write(
    fossil_data_stream_t       *stream,
    const fossil_data_buffer_t *in_buffer
);

#ifdef __cplusplus
}
#include <string>

namespace fossil {
    
    namespace data {



    } // namespace data

} // namespace fossil

#endif

#endif /* FOSSIL_DATA_STREAM_H */
