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

#include "neu_json_tag.h"

int neu_json_decode_add_tags_req(char *buf, neu_json_add_tags_req_t **result)
{
    int                      ret      = 0;
    void *                   json_obj = NULL;
    neu_json_add_tags_req_t *req = calloc(1, sizeof(neu_json_add_tags_req_t));
    if (req == NULL) {
        return -1;
    }

    json_obj = neu_json_decode_new(buf);

    neu_json_elem_t req_elems[] = { {
                                        .name = "node",
                                        .t    = NEU_JSON_STR,
                                    },
                                    {
                                        .name = "group",
                                        .t    = NEU_JSON_STR,
                                    } };
    ret = neu_json_decode_by_json(json_obj, NEU_JSON_ELEM_SIZE(req_elems),
                                  req_elems);
    if (ret != 0) {
        goto decode_fail;
    }

    req->node  = req_elems[0].v.val_str;
    req->group = req_elems[1].v.val_str;

    req->n_tag = neu_json_decode_array_size_by_json(json_obj, "tags");
    if (req->n_tag < 0) {
        goto decode_fail;
    }

    req->tags = calloc(req->n_tag, sizeof(neu_json_add_tags_req_tag_t));
    neu_json_add_tags_req_tag_t *p_tag = req->tags;
    for (int i = 0; i < req->n_tag; i++) {
        neu_json_elem_t tag_elems[] = {
            {
                .name = "type",
                .t    = NEU_JSON_INT,
            },
            {
                .name = "name",
                .t    = NEU_JSON_STR,
            },
            {
                .name = "attribute",
                .t    = NEU_JSON_INT,
            },
            {
                .name = "address",
                .t    = NEU_JSON_STR,
            },
            {
                .name      = "description",
                .t         = NEU_JSON_STR,
                .attribute = NEU_JSON_ATTRIBUTE_OPTIONAL,
            },
        };
        ret = neu_json_decode_array_by_json(
            json_obj, "tags", i, NEU_JSON_ELEM_SIZE(tag_elems), tag_elems);
        if (ret != 0) {
            goto decode_fail;
        }

        p_tag->type        = tag_elems[0].v.val_int;
        p_tag->name        = tag_elems[1].v.val_str;
        p_tag->attribute   = tag_elems[2].v.val_int;
        p_tag->address     = tag_elems[3].v.val_str;
        p_tag->description = tag_elems[4].v.val_str;
        p_tag++;
    }

    *result = req;
    goto decode_exit;

decode_fail:
    if (req->tags != NULL) {
        free(req->tags);
    }
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

void neu_json_decode_add_tags_req_free(neu_json_add_tags_req_t *req)
{

    neu_json_add_tags_req_tag_t *p_tag = req->tags;
    for (int i = 0; i < req->n_tag; i++) {
        if (p_tag->description != NULL) {
            free(p_tag->description);
        }
        free(p_tag->name);
        free(p_tag->address);
        p_tag++;
    }

    free(req->tags);
    free(req->node);
    free(req->group);
    free(req);
}

int neu_json_encode_au_tags_resp(void *json_object, void *param)
{
    int                     ret          = 0;
    neu_json_add_tag_res_t *resp         = (neu_json_add_tag_res_t *) param;
    neu_json_elem_t         resp_elems[] = {
        {
            .name      = "index",
            .t         = NEU_JSON_INT,
            .v.val_int = resp->index,
        },
        {
            .name      = "error",
            .t         = NEU_JSON_INT,
            .v.val_int = resp->error,

        },
    };

    ret = neu_json_encode_field(json_object, resp_elems,
                                NEU_JSON_ELEM_SIZE(resp_elems));

    return ret;
}

int neu_json_decode_del_tags_req(char *buf, neu_json_del_tags_req_t **result)
{
    int                      ret      = 0;
    void *                   json_obj = NULL;
    neu_json_del_tags_req_t *req = calloc(1, sizeof(neu_json_del_tags_req_t));
    if (req == NULL) {
        return -1;
    }

    json_obj = neu_json_decode_new(buf);

    neu_json_elem_t req_elems[] = { {
                                        .name = "node",
                                        .t    = NEU_JSON_STR,
                                    },
                                    {
                                        .name = "group",
                                        .t    = NEU_JSON_STR,
                                    } };
    ret = neu_json_decode_by_json(json_obj, NEU_JSON_ELEM_SIZE(req_elems),
                                  req_elems);
    if (ret != 0) {
        goto decode_fail;
    }

    req->node  = req_elems[0].v.val_str;
    req->group = req_elems[1].v.val_str;

    req->n_tags = neu_json_decode_array_size_by_json(json_obj, "tags");
    if (req->n_tags < 0) {
        goto decode_fail;
    }

    req->tags = calloc(req->n_tags, sizeof(neu_json_del_tags_req_name_t));
    neu_json_del_tags_req_name_t *p_tag = req->tags;
    for (int i = 0; i < req->n_tags; i++) {
        neu_json_elem_t id_elems[] = { {
            .name = NULL,
            .t    = NEU_JSON_STR,
        } };
        ret                        = neu_json_decode_array_by_json(
            json_obj, "tags", i, NEU_JSON_ELEM_SIZE(id_elems), id_elems);
        if (ret != 0) {
            goto decode_fail;
        }

        *p_tag = id_elems[0].v.val_str;
        p_tag++;
    }

    *result = req;
    goto decode_exit;

decode_fail:
    if (req->tags != NULL) {
        free(req->tags);
    }
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

void neu_json_decode_del_tags_req_free(neu_json_del_tags_req_t *req)
{
    free(req->node);
    free(req->group);

    for (int i = 0; i < req->n_tags; i++) {
        free(req->tags[i]);
    }
    free(req->tags);

    free(req);
}

int neu_json_encode_get_tags_resp(void *json_object, void *param)
{
    int                       ret  = 0;
    neu_json_get_tags_resp_t *resp = (neu_json_get_tags_resp_t *) param;

    void *                        tag_array = neu_json_array();
    neu_json_get_tags_resp_tag_t *p_tag     = resp->tags;
    for (int i = 0; i < resp->n_tag; i++) {
        neu_json_elem_t tag_elems[] = {
            {
                .name      = "type",
                .t         = NEU_JSON_INT,
                .v.val_int = p_tag->type,
            },
            {
                .name      = "name",
                .t         = NEU_JSON_STR,
                .v.val_str = p_tag->name,
            },
            {
                .name      = "attribute",
                .t         = NEU_JSON_INT,
                .v.val_int = p_tag->attribute,
            },
            {
                .name      = "address",
                .t         = NEU_JSON_STR,
                .v.val_str = p_tag->address,
            },
            {
                .name      = "description",
                .t         = NEU_JSON_STR,
                .v.val_str = p_tag->description,
            },
        };
        tag_array = neu_json_encode_array(tag_array, tag_elems,
                                          NEU_JSON_ELEM_SIZE(tag_elems));
        p_tag++;
    }

    neu_json_elem_t resp_elems[] = { {
        .name         = "tags",
        .t            = NEU_JSON_OBJECT,
        .v.val_object = tag_array,
    } };
    ret = neu_json_encode_field(json_object, resp_elems,
                                NEU_JSON_ELEM_SIZE(resp_elems));

    return ret;
}

int neu_json_decode_update_tags_req(char *                       buf,
                                    neu_json_update_tags_req_t **result)
{
    int                         ret      = 0;
    void *                      json_obj = NULL;
    neu_json_update_tags_req_t *req =
        calloc(1, sizeof(neu_json_update_tags_req_t));
    if (req == NULL) {
        return -1;
    }

    json_obj = neu_json_decode_new(buf);

    neu_json_elem_t req_elems[] = { {
                                        .name = "node",
                                        .t    = NEU_JSON_STR,
                                    },
                                    {
                                        .name = "group",
                                        .t    = NEU_JSON_STR,
                                    } };
    ret = neu_json_decode_by_json(json_obj, NEU_JSON_ELEM_SIZE(req_elems),
                                  req_elems);
    if (ret != 0) {
        goto decode_fail;
    }

    req->node  = req_elems[0].v.val_str;
    req->group = req_elems[1].v.val_str;

    req->n_tag = neu_json_decode_array_size_by_json(json_obj, "tags");
    if (req->n_tag < 0) {
        goto decode_fail;
    }

    req->tags = calloc(req->n_tag, sizeof(neu_json_update_tags_req_tag_t));
    neu_json_update_tags_req_tag_t *p_tag = req->tags;
    for (int i = 0; i < req->n_tag; i++) {
        neu_json_elem_t tag_elems[] = {
            {
                .name = "type",
                .t    = NEU_JSON_INT,
            },
            {
                .name = "name",
                .t    = NEU_JSON_STR,
            },
            {
                .name = "attribute",
                .t    = NEU_JSON_INT,
            },
            {
                .name = "address",
                .t    = NEU_JSON_STR,
            },
            {
                .name      = "description",
                .t         = NEU_JSON_STR,
                .attribute = NEU_JSON_ATTRIBUTE_OPTIONAL,
            },
        };
        ret = neu_json_decode_array_by_json(
            json_obj, "tags", i, NEU_JSON_ELEM_SIZE(tag_elems), tag_elems);
        if (ret != 0) {
            goto decode_fail;
        }

        p_tag->type        = tag_elems[0].v.val_int;
        p_tag->name        = tag_elems[1].v.val_str;
        p_tag->attribute   = tag_elems[2].v.val_int;
        p_tag->address     = tag_elems[3].v.val_str;
        p_tag->description = tag_elems[4].v.val_str;
        p_tag++;
    }

    *result = req;
    goto decode_exit;

decode_fail:
    if (req->tags != NULL) {
        free(req->tags);
    }
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

void neu_json_decode_update_tags_req_free(neu_json_update_tags_req_t *req)
{

    neu_json_update_tags_req_tag_t *p_tag = req->tags;
    for (int i = 0; i < req->n_tag; i++) {
        if (p_tag->description != NULL) {
            free(p_tag->description);
        }
        free(p_tag->name);
        free(p_tag->address);
        p_tag++;
    }

    free(req->tags);
    free(req->group);
    free(req->node);

    free(req);
}
