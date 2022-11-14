// Copyright 2022 liangzhuzhi2020@gmail.com, https://github.com/liang-zhu-zi/esp32-thingsboard-mqtt-client
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

// This file is called by tbc_mqtt_helper.c/.h.

#ifndef _CLIENT_RPC_OBSERVER_H_
#define _CLIENT_RPC_OBSERVER_H_

#include <stdint.h>
#include <stdbool.h>

#include "sys/queue.h"
#include "tbc_mqtt_helper.h"

#ifdef __cplusplus
extern "C" {
#endif

//====6.Client-side RPC================================================================================================
/**
 * ThingsBoard MQTT Client Helper client-RPC
 */
typedef struct tbcmh_clientrpc
{
     tbcmh_handle_t client;        /*!< ThingsBoard MQTT Client Helper */

     ////const char *method_key;   /*!< method key, default "method" */
     ////const char *params_key;   /*!< params key, default "params" */
     ////const char *results_key;  /*!< results key, default "results" */

     char *method; /*!< method value */
     ////tbcmh_rpc_params_t *params;
     int request_id;
     void *context;                             /*!< Context of callback */
     tbcmh_clientrpc_on_response_t on_response; /*!< Callback of client-rpc response success */
     tbcmh_clientrpc_on_timeout_t on_timeout;   /*!< Callback of client-rpc response timeout */

     LIST_ENTRY(tbcmh_clientrpc) entry;
} tbcmh_clientrpc_t;

tbcmh_clientrpc_t *_tbcmh_clientrpc_init(tbcmh_handle_t client, int request_id,
                                         const char *method, ////tbcmh_rpc_params_t *params,
                                         void *context,
                                         tbcmh_clientrpc_on_response_t on_response,
                                         tbcmh_clientrpc_on_timeout_t on_timeout); /*!< Initialize tbcmh_clientrpc_t */
tbcmh_clientrpc_t *_tbcmh_clientrpc_clone_wo_listentry(tbcmh_clientrpc_t *src);
tbc_err_t _tbcmh_clientrpc_destroy(tbcmh_clientrpc_t *clientrpc);                /*!< Destroys the tbcmh_clientrpc_t */

int _tbcmh_clientrpc_get_request_id(tbcmh_clientrpc_t *clientrpc);
void _tbcmh_clientrpc_do_response(tbcmh_clientrpc_t *clientrpc, const tbcmh_rpc_results_t *results);
void _tbcmh_clientrpc_do_timeout(tbcmh_clientrpc_t *clientrpc);

//const char *_tbcmh_clientrpc_get_method(tbcmh_clientrpc_t *clientrpc);

//0.   Subscribe topic: client-side RPC response;

//1.    tbcmh_clientrpc_of_oneway_request(...)/tbcmh_clientrpc_of_oneway_request(...)
//1.1   tbcmh_clientrpc_t *_tbcmh_clientrpc_init(tbcmh_client_handle_t client, const char* method, tbcmh_rpc_params_t *params, void *context, tbcmh_clientrpc_response_callback_t on_response);
//1.1  _tbcm.clientrpc_request_pack(...) 
//1.2  _tbcm.clientrpc_request_send(...); //tbmqttclient_sendClientRpcRequest()

//2    _tbcm.on_clientrpc_response()
//2.1  _tbcm.on_clientrpc_response_unpack(): parse payload* to cJSON*, then push it to queue;
//2.2  _tbcm.on_clientrpc_response_deal(on_response): call a server RPC's on_request callback by method name, then send a replay if on_request callback has a return value of tbcmh_rpc_results_t.

//3.   _tbcm.on_clientrpc_timeout(on_timeout)
//3.1  _tbcm.on_clientrpc_response_timeout(on_timeout)

//2.f/3.f tbc_err_t _tbcmh_clientrpc_destroy(tbcmh_clientrpc_t *clientrpc)

//4     tbcmh_client_destroy(...)
//4.x   tbc_err_t _tbcmh_serverrpc_destroy(tbcmh_serverrpc_handle_t serverrpc)

#ifdef __cplusplus
}
#endif //__cplusplus

#endif