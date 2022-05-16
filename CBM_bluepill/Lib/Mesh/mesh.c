/*
 * mesh.c
 *
 *  Created on: 20 apr. 2022
 *      Author: Mike
 */
#include "mesh.h"

void mesh_init(){
	//SPSGRF module initialized! now searching for gateway first
	uint8_t rxdata[20];
	int i = 0; int j = 0; int k = 0;
	comm_command(GATEWAY_CHECK, 0);
	SPSGRF_StartRx();
	while(i<TIMEOUT){
		if(irqStatus.IRQ_RX_DATA_READY == 1){
			comm_decrypt(rxdata);
			//if data is received check data and proces it
			if(rxdata[1] == COMMAND){
				if(rxdata[2] == ACK)
				{
					nodes.gateway_id = rxdata[0];
					nodes.gateway_connected = 1;
					nodes.destination_node = GATEWAY_ADDRESS;
					HAL_TIM_Base_Start_IT(&htim2);
				}else{
					nodes.gateway_connected = 0;
				}
			}
		}
		i++;
	}

	//check for sensors arround me
	comm_command(SENSORS_CHECK, 0);
	while(i<TIMEOUT)
	{
		if(irqStatus.IRQ_RX_DATA_READY == 1){
			comm_decrypt(rxdata);
			if(rxdata[1] == COMMAND){
				if(rxdata[2] == ACK){
					nodes.node[j].node_id = rxdata[0];
					nodes.node_in_range++;
					nodes.node[j].node_gw_connected =rxdata[3];
					nodes.node[j].rssi =0;
					j++;
					i = 0;
					irqStatus.IRQ_RX_DATA_READY = 0;
				}
			}
		}
		i++;
	}
	k = 0;
	while(1){
		if(nodes.gateway_connected == 0 && nodes.node[k].node_gw_connected == 1)
		{
			comm_command(CONV_TO_CONPOINT, nodes.node[k].node_id);
			while(i<TIMEOUT)
			{
				if(irqStatus.IRQ_RX_DATA_READY == 1){
					comm_decrypt(rxdata);
					if(rxdata[1] == COMMAND){
						if(rxdata[2] == ACK){
							nodes.destination_node = nodes.node[k].node_id;
							break;
							nodes.gateway_connected = 1;
						}
					}
				}
				i++;
			}
		}
		k++;
		if(k > nodes.node_in_range) break;
	}
}
