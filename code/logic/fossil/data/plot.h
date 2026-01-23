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
#ifndef FOSSIL_DATA_PLOT_H
#define FOSSIL_DATA_PLOT_H

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

/* ============================================================================
 * Opaque Plot
 * ============================================================================
 */

typedef struct fossil_data_plot fossil_data_plot_t;

/* ============================================================================
 * Creation / Destruction
 * ============================================================================
 */

/* id examples:
 *   "line"
 *   "scatter"
 *   "bar"
 *   "histogram"
 *   "heatmap"
 */
fossil_data_plot_t *
fossil_data_plot_create(fossil_data_id_t id);

void
fossil_data_plot_destroy(fossil_data_plot_t *plot);

/* ============================================================================
 * Configuration
 * ============================================================================
 */

/* key examples:
 *   "title"
 *   "xlabel"
 *   "ylabel"
 *   "width"
 *   "height"
 *   "color"
 */
fossil_data_status_t
fossil_data_plot_set(
    fossil_data_plot_t *plot,
    fossil_data_id_t    key,
    fossil_data_id_t    value
);

/* ============================================================================
 * Data Binding
 * ============================================================================
 */

fossil_data_status_t
fossil_data_plot_bind(
    fossil_data_plot_t        *plot,
    const fossil_data_buffer_t *data
);

/* ============================================================================
 * Render
 * ============================================================================
 */

/* target examples:
 *   "png"
 *   "svg"
 *   "ascii"
 *   "framebuffer"
 */
fossil_data_status_t
fossil_data_plot_render(
    fossil_data_plot_t *plot,
    fossil_data_id_t    target
);

#ifdef __cplusplus
}
#include <string>

namespace fossil {
    
    namespace data {



    } // namespace data

} // namespace fossil

#endif

#endif /* FOSSIL_DATA_PLOT_H */
