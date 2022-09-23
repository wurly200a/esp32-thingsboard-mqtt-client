// Copyright 2022 liangzhuzhi2020@gmail.com, https://github.com/liang-zhu-zi/thingsboard-mqttclient-basedon-espmqtt
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

// This file is called by tb_mqtt_client_helper.c/.h.

#ifndef _SHARED_ATTRIBUTE_OBSERVER_H_
#define _SHARED_ATTRIBUTE_OBSERVER_H_

#include <stdint.h>
#include <stdbool.h>

#include "sys/queue.h"
#include "tb_mqtt_client_helper.h"

#ifdef __cplusplus
extern "C" {
#endif

//====3.shared attribute===============================================================================================

/**
 * ThingsBoard MQTT Client Helper shared attribute
 */
typedef struct tbmch_sharedattribute
{
     tbmch_handle_t client; /*!< ThingsBoard MQTT Client Helper */

     char *key; /*!< Key */

     void *context;                         /*!< Context of getting/setting value*/
     tbmch_sharedattribute_on_set_t on_set; /*!< Callback of setting value to context */

     LIST_ENTRY(tbmch_sharedattribute) entry;
} tbmch_sharedattribute_t;

tbmch_sharedattribute_t *_tbmch_sharedattribute_init(tbmch_handle_t client, const char *key, void *context,
                                                    tbmch_sharedattribute_on_set_t on_set);
tbmch_err_t _tbmch_sharedattribute_destroy(tbmch_sharedattribute_t *sharedattribute); /*!< Destroys the tbmc key-value handle */

const char *_tbmch_sharedattribute_get_key(tbmch_sharedattribute_t *sharedattribute); /*!< Get key of the tbmc tbmch_attribute handle */
tbmch_err_t _tbmch_sharedattribute_do_set(tbmch_sharedattribute_t *sharedattribute, cJSON *value); /*!< add item value to json object */

#ifdef __cplusplus
}
#endif //__cplusplus

#endif