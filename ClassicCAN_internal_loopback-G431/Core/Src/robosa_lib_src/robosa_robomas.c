#include "robosa_robomas.h"
#include "robosa_can.h"
#include "main.h"

void robomas_init(robomas_t *robomas, FDCAN_HandleTypeDef *hfdcan) {
  robomas->hfdcan = hfdcan;
  for(int i = 0; i < 4; i++){
    robomas->current[i] = 0;
    robomas->max_current[i] = 10000;
  }

  FDCAN_FilterTypeDef sFilterConfig = {0};
  sFilterConfig.IdType = FDCAN_STANDARD_ID;
  sFilterConfig.FilterIndex = 0;
  sFilterConfig.FilterType = FDCAN_FILTER_MASK;
  sFilterConfig.FilterConfig = FDCAN_FILTER_TO_RXFIFO0;
  sFilterConfig.FilterID1 = 0;
  sFilterConfig.FilterID2 = 0;
  can_init(hfdcan, &sFilterConfig, 1);
}

void robomas_put(robomas_t *robomas, uint8_t motor_id, int current){
    if(motor_id > 4 || motor_id == 0){
        return;
    }
    uint8_t motor_index = motor_id-1;
    if(current > robomas->max_current[motor_index]){
        current = robomas->max_current[motor_index];
    } else if(current < -robomas->max_current[motor_index]){
        current = -robomas->max_current[motor_index ];
    }
    robomas->current[motor_index] = current;
    printf("motor %d, current %d\n", motor_id, current);//TODO
    return;
}

void robomas_rotate(robomas_t *robomas){
    FDCAN_TxHeaderTypeDef tx_header;
    tx_header.Identifier = 0x200;
    tx_header.IdType = FDCAN_STANDARD_ID;
    tx_header.TxFrameType = FDCAN_DATA_FRAME;
    tx_header.DataLength = FDCAN_DLC_BYTES_8;
    tx_header.ErrorStateIndicator = FDCAN_ESI_ACTIVE;
    tx_header.BitRateSwitch = FDCAN_BRS_OFF;
    tx_header.FDFormat = FDCAN_CLASSIC_CAN;
    tx_header.TxEventFifoControl = FDCAN_NO_TX_EVENTS;
    tx_header.MessageMarker = 0;
    uint8_t txdata[8];
    for(int i = 0; i < 4; i++){
        txdata[2 * i] = (uint8_t)(robomas->current[i] >> 8);
        txdata[2 * i + 1] = (uint8_t)(robomas->current[i]);
    }
    can_send(robomas->hfdcan, &tx_header, txdata, 8);
}
