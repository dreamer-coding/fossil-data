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
#include "fossil/data/plots.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/* ============================================================================
 * Internal Plot Representation
 * ============================================================================
 */

struct fossil_data_plot {
    fossil_data_id_t type;

    /* config */
    const char *title;
    const char *xlabel;
    const char *ylabel;

    size_t width;
    size_t height;

    /* data */
    const fossil_data_buffer_t *data;
};

/* ============================================================================
 * Helpers
 * ============================================================================
 */

static int fossil_data_id_eq(fossil_data_id_t a, fossil_data_id_t b) {
    if (!a || !b) return 0;
    return strcmp(a, b) == 0;
}

/* ============================================================================
 * Creation / Destruction
 * ============================================================================
 */

fossil_data_plot_t *fossil_data_plot_create(fossil_data_id_t id) {
    fossil_data_plot_t *plot = calloc(1, sizeof(*plot));
    if (!plot) {
        return NULL;
    }

    plot->type   = id;
    plot->width  = 80;
    plot->height = 20;

    return plot;
}

void fossil_data_plot_destroy(fossil_data_plot_t *plot) {
    if (!plot) return;
    free(plot);
}

/* ============================================================================
 * Configuration
 * ============================================================================
 */

fossil_data_status_t fossil_data_plot_set(
    fossil_data_plot_t *plot,
    fossil_data_id_t    key,
    fossil_data_id_t    value
) {
    if (!plot || !key || !value) {
        return FOSSIL_DATA_INVALID;
    }

    if (fossil_data_id_eq(key, "title")) {
        plot->title = value;
    }
    else if (fossil_data_id_eq(key, "xlabel")) {
        plot->xlabel = value;
    }
    else if (fossil_data_id_eq(key, "ylabel")) {
        plot->ylabel = value;
    }
    else if (fossil_data_id_eq(key, "width")) {
        plot->width = (size_t)atoi(value);
    }
    else if (fossil_data_id_eq(key, "height")) {
        plot->height = (size_t)atoi(value);
    }
    else {
        return FOSSIL_DATA_UNSUPPORTED;
    }

    return FOSSIL_DATA_OK;
}

/* ============================================================================
 * Data Binding
 * ============================================================================
 */

fossil_data_status_t fossil_data_plot_bind(
    fossil_data_plot_t        *plot,
    const fossil_data_buffer_t *data) {
    if (!plot || !data || !data->data) {
        return FOSSIL_DATA_INVALID;
    }

    plot->data = data;
    return FOSSIL_DATA_OK;
}

/* ============================================================================
 * ASCII Rendering (portable, zero deps)
 * ============================================================================
 */

static fossil_data_status_t fossil_data_plot_render_ascii(fossil_data_plot_t *plot) {
    size_t i;
    fossil_data_real_t min = 0.0, max = 0.0;
    fossil_data_real_t *values;

    if (!plot->data) {
        return FOSSIL_DATA_INVALID;
    }

    values = (fossil_data_real_t *)plot->data->data;

    /* compute min/max */
    min = max = values[0];
    for (i = 1; i < plot->data->length; ++i) {
        if (values[i] < min) min = values[i];
        if (values[i] > max) max = values[i];
    }

    if (plot->title) {
        printf("\n%s\n", plot->title);
    }

    for (size_t row = 0; row < plot->height; ++row) {
        fossil_data_real_t threshold =
            max - ((fossil_data_real_t)row / plot->height) * (max - min);

        for (i = 0; i < plot->data->length && i < plot->width; ++i) {
            if (values[i] >= threshold) {
                putchar('#');
            } else {
                putchar(' ');
            }
        }
        putchar('\n');
    }

    if (plot->xlabel) {
        printf("%s\n", plot->xlabel);
    }

    return FOSSIL_DATA_OK;
}

/* ============================================================================
 * Render Dispatch
 * ============================================================================
 */

fossil_data_status_t fossil_data_plot_render(
    fossil_data_plot_t *plot,
    fossil_data_id_t    target) {
    if (!plot || !target) {
        return FOSSIL_DATA_INVALID;
    }

    if (fossil_data_id_eq(target, "ascii")) {
        return fossil_data_plot_render_ascii(plot);
    }

    /* future backends */
    if (fossil_data_id_eq(target, "png") ||
        fossil_data_id_eq(target, "svg") ||
        fossil_data_id_eq(target, "framebuffer")) {
        return FOSSIL_DATA_UNSUPPORTED;
    }

    return FOSSIL_DATA_INVALID;
}
