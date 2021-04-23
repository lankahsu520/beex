/***************************************************************************
 * Copyright (C) 2017 - 2020, Lanka Hsu, <lankahsu@gmail.com>, et al.
 *
 * This software is licensed as described in the file COPYING, which
 * you should have received as part of this distribution.
 *
 * You may opt to use, copy, modify, merge, publish, distribute and/or sell
 * copies of the Software, and permit persons to whom the Software is
 * furnished to do so, under the terms of the COPYING file.
 *
 * This software is distributed on an "AS IS" basis, WITHOUT WARRANTY OF ANY
 * KIND, either express or implied.
 *
 ***************************************************************************/
#ifndef __BEEX_HONEYCOMB_H__
#define __BEEX_HONEYCOMB_H__

//******************************************************************************
//** include **
//******************************************************************************


//******************************************************************************
//** feature **
//******************************************************************************


//******************************************************************************
//** define **
//******************************************************************************
#ifndef LEN_OF_TOPIC
#define LEN_OF_TOPIC LEN_OF_BUF1024
#endif

#define BEEX_REAL_PRECISION 3

typedef int honeycomb_topic_fn(char *topic, char *value);

typedef struct AddedNodeid_Struct
{
	void* next;

	char topic_nodeid[LEN_OF_TOPIC];
	json_t *jnodeid;
} AddedNodeid_t;

typedef struct TopicX_STRUCT
{
	json_t *jmac;
	char topic_mac[LEN_OF_TOPIC];
	json_t *juuid;
	char topic_uuid[LEN_OF_TOPIC];
	json_t *jnodeid;
	char topic_nodeid[LEN_OF_TOPIC];
	json_t *jepid;
	char topic_epid[LEN_OF_TOPIC];
	json_t *jissueid;
	char topic_issueid[LEN_OF_TOPIC];
} TopicX_t;

typedef struct Honeycomb_STRUCT
{
	int isfree;
	int isquit;

	int keepothers;
	char iface_mac[LEN_OF_MAC];
	char uuid_root[LEN_OF_UUID]; // GW

	int order;
	int watch;
	int logging;
	Reporter_t *reporter;
	Commander_t *commander;
	Notify_t *notify;

	char filename[LEN_OF_FILENAME256];
	char json_f_mctt[LEN_OF_FILENAME256];

	json_t *jroot;
	json_t *jmac;

	CLIST_STRUCT(added_list);

	honeycomb_topic_fn *topic_add_uuid_cb;
	honeycomb_topic_fn *topic_del_uuid_cb;
	honeycomb_topic_fn *topic_add_node_cb;
	honeycomb_topic_fn *topic_del_node_cb;
	honeycomb_topic_fn *topic_issue_cb;
} Honeycomb_t;


//******************************************************************************
//** function **
//******************************************************************************
void honeycomb_topic_get(Honeycomb_t *honeycomb_ctx, char *topic, char *payload);
void honeycomb_topic_put(Honeycomb_t *honeycomb_ctx, char *topic, char *payload);
void honeycomb_topic_pub(Honeycomb_t *honeycomb_ctx, char *topic, json_t *jvalue, honeycomb_topic_fn *topic_cb);

json_t *honeycomb_lookup_juuid_helper(Honeycomb_t *honeycomb_ctx, IssueItem_t *c_issueitem, ISSUE_TYPE_ID itype, JSON_ACTID act, TopicX_t *topicx_ctx);
json_t *honeycomb_lookup_jnodeid_helper(Honeycomb_t *honeycomb_ctx, IssueItem_t *c_issueitem, ISSUE_TYPE_ID itype, JSON_ACTID act, TopicX_t *topicx_ctx);
json_t *honeycomb_lookup_jepid_helper(Honeycomb_t *honeycomb_ctx, IssueItem_t *c_issueitem, ISSUE_TYPE_ID itype, JSON_ACTID act, TopicX_t *topicx_ctx);
json_t *honeycomb_lookup_jissueid_helper(Honeycomb_t *honeycomb_ctx, IssueItem_t *c_issueitem, ISSUE_TYPE_ID itype, JSON_ACTID act, TopicX_t *topicx_ctx);

void honeycomb_register(Honeycomb_t *honeycomb_ctx);

void honeycomb_save(Honeycomb_t *honeycomb_ctx);
void honeycomb_stop(Honeycomb_t *honeycomb_ctx);
void honeycomb_close(Honeycomb_t *honeycomb_ctx);
void honeycomb_open(Honeycomb_t *honeycomb_ctx);

#endif