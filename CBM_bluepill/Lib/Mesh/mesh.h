/*
 * mesh.h
 *
 *  Created on: 20 apr. 2022
 *      Author: user
 */

#ifndef MESH_MESH_H_
#define MESH_MESH_H_

#include "SPSGRF/SPSGRF.h"
#include "Comm/comm.h"
#include "Cbm/config.h"
#include "stdio.h"
#include "main.h"

struct node_info {
	uint8_t node_id;
	uint8_t node_gw_connected;
	uint8_t rssi;
};

struct nodes_info {
	uint8_t gateway_id;
	uint8_t gateway_connected;
	uint8_t node_in_range;
	uint8_t destination_node;
	struct node_info node[8];

};
extern struct nodes_info nodes;
//Commands
#define GATEWAY_CHECK 0
#define SENSORS_CHECK 1
#define ACK 2
#define NOTACK 3
#define CONV_TO_CONPOINT 4

void mesh_init();

#endif /* MESH_MESH_H_ */
