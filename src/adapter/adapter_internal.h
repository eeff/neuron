/**
 * NEURON IIoT System for Industry 4.0
 * Copyright (C) 2020-2022 EMQ Technologies Co., Ltd All rights reserved.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 3 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 **/

#ifndef ADAPTER_INTERNAL_H
#define ADAPTER_INTERNAL_H

#include <nng/nng.h>
#include <nng/protocol/pair1/pair.h>
#include <nng/supplemental/util/platform.h>

#include "event/event.h"
#include "plugin.h"

#include "adapter_info.h"
#include "core/manager.h"

struct neu_adapter {
    char *name;
    char *setting;

    int64_t timestamp;

    neu_node_running_state_e state;

    neu_persister_t *   persister;
    adapter_callbacks_t cb_funs;

    void *               handle;
    neu_plugin_module_t *module;
    neu_plugin_t *       plugin;

    nng_socket sock;
    nng_dialer dialer;

    neu_events_t *     events;
    neu_event_io_t *   nng_io;
    neu_event_timer_t *timer;
    int                recv_fd;

    // metrics
    struct {
        NEU_NODE_METRICS_UNION;
    } metrics;
};

typedef void (*adapter_handler)(neu_adapter_t *     adapter,
                                neu_reqresp_head_t *header);
typedef struct adapter_msg_handler {
    neu_reqresp_type_e type;
    adapter_handler    handler;
} adapter_msg_handler_t;

neu_adapter_t *neu_adapter_create(neu_adapter_info_t *info);
void           neu_adapter_init(neu_adapter_t *adapter, bool auto_start);

int neu_adapter_start(neu_adapter_t *adapter);
int neu_adapter_start_single(neu_adapter_t *adapter);
int neu_adapter_stop(neu_adapter_t *adapter);

neu_node_type_e neu_adapter_get_type(neu_adapter_t *adapter);

int  neu_adapter_uninit(neu_adapter_t *adapter);
void neu_adapter_destroy(neu_adapter_t *adapter);

neu_event_timer_t *neu_adapter_add_timer(neu_adapter_t *         adapter,
                                         neu_event_timer_param_t param);
void neu_adapter_del_timer(neu_adapter_t *adapter, neu_event_timer_t *timer);

int neu_adapter_set_setting(neu_adapter_t *adapter, const char *config);
int neu_adapter_get_setting(neu_adapter_t *adapter, char **config);
neu_node_state_t neu_adapter_get_state(neu_adapter_t *adapter);

int neu_adapter_validate_tag(neu_adapter_t *adapter, neu_datatag_t *tag);

#endif
