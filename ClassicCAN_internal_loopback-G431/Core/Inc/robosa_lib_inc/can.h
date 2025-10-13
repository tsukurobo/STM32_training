#ifndef __CAN_H__
#define __CAN_H__
#include "main.h"
void can_init(FDCAN_HandleTypeDef *hfdcan, FDCAN_FilterTypeDef *sFilterConfig, uint8_t filter_num);
void can_send(FDCAN_HandleTypeDef *hfdcan, FDCAN_TxHeaderTypeDef tx_header, uint8_t *tx_data, uint8_t txdata_size);
void can_recv(FDCAN_HandleTypeDef *hfdcan, FDCAN_RxHeaderTypeDef rx_header, uint8_t recv_data[64]);
void HAL_FDCAN_RxFifo0Callback(FDCAN_HandleTypeDef *hfdcan, uint32_t RxFifo0ITs);
void HAL_FDCAN_ErrorStatusCallback(FDCAN_HandleTypeDef *hfdcan, uint32_t ErrorStatusITs);

#endif // __CAN_H__