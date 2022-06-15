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

/*
 * DO NOT EDIT THIS FILE MANUALLY!
 * It was automatically generated by `json-autotype`.
 */

#include <stdlib.h>
#include <string.h>

#include "json/json.h"

#include "neu_json_plugin.h"

int neu_json_decode_add_plugin_req(char *                      buf,
                                   neu_json_add_plugin_req_t **result)
{
    int                        ret      = 0;
    void *                     json_obj = NULL;
    neu_json_add_plugin_req_t *req =
        calloc(1, sizeof(neu_json_add_plugin_req_t));
    if (req == NULL) {
        return -1;
    }

    json_obj = neu_json_decode_new(buf);

    neu_json_elem_t req_elems[] = { {
        .name = "library",
        .t    = NEU_JSON_STR,
    } };
    ret = neu_json_decode_by_json(json_obj, NEU_JSON_ELEM_SIZE(req_elems),
                                  req_elems);
    if (ret != 0) {
        goto decode_fail;
    }

    req->library = req_elems[0].v.val_str;

    *result = req;
    goto decode_exit;

decode_fail:
    if (req != NULL) {
        free(req);
    }
    ret = -1;

decode_exit:
    if (json_obj != NULL) {
        neu_json_decode_free(json_obj);
    }
    return ret;
}

void neu_json_decode_add_plugin_req_free(neu_json_add_plugin_req_t *req)
{

    free(req->library);

    free(req);
}

int neu_json_decode_del_plugin_req(char *                      buf,
                                   neu_json_del_plugin_req_t **result)
{
    int                        ret      = 0;
    void *                     json_obj = NULL;
    neu_json_del_plugin_req_t *req =
        calloc(1, sizeof(neu_json_del_plugin_req_t));
    if (req == NULL) {
        return -1;
    }

    json_obj = neu_json_decode_new(buf);

    neu_json_elem_t req_elems[] = { {
        .name = "plugin",
        .t    = NEU_JSON_STR,
    } };
    ret = neu_json_decode_by_json(json_obj, NEU_JSON_ELEM_SIZE(req_elems),
                                  req_elems);
    if (ret != 0) {
        goto decode_fail;
    }

    req->plugin = req_elems[0].v.val_str;

    *result = req;
    goto decode_exit;

decode_fail:
    if (req != NULL) {
        free(req);
    }
    ret = -1;

decode_exit:
    if (json_obj != NULL) {
        neu_json_decode_free(json_obj);
    }
    return ret;
}

void neu_json_decode_del_plugin_req_free(neu_json_del_plugin_req_t *req)
{
    free(req->plugin);
    free(req);
}

int neu_json_encode_get_plugin_resp(void *json_object, void *param)
{
    int                         ret  = 0;
    neu_json_get_plugin_resp_t *resp = (neu_json_get_plugin_resp_t *) param;

    void *                                 plugin_lib_array = neu_json_array();
    neu_json_get_plugin_resp_plugin_lib_t *p_plugin_lib     = resp->plugin_libs;
    for (int i = 0; i < resp->n_plugin_lib; i++) {
        neu_json_elem_t plugin_lib_elems[] = {
            {
                .name      = "node_type",
                .t         = NEU_JSON_INT,
                .v.val_int = p_plugin_lib->node_type,
            },
            {
                .name      = "name",
                .t         = NEU_JSON_STR,
                .v.val_str = p_plugin_lib->name,
            },
            {
                .name      = "library",
                .t         = NEU_JSON_STR,
                .v.val_str = p_plugin_lib->library,
            },
            {
                .name      = "description",
                .t         = NEU_JSON_STR,
                .v.val_str = p_plugin_lib->description,
            },
            {
                .name      = "kind",
                .t         = NEU_JSON_INT,
                .v.val_int = p_plugin_lib->kind,
            },
        };
        plugin_lib_array =
            neu_json_encode_array(plugin_lib_array, plugin_lib_elems,
                                  NEU_JSON_ELEM_SIZE(plugin_lib_elems));
        p_plugin_lib++;
    }

    neu_json_elem_t resp_elems[] = { {
        .name         = "plugins",
        .t            = NEU_JSON_OBJECT,
        .v.val_object = plugin_lib_array,
    } };
    ret = neu_json_encode_field(json_object, resp_elems,
                                NEU_JSON_ELEM_SIZE(resp_elems));

    return ret;
}
