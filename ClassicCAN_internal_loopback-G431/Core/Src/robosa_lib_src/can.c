#include "can.h"
#include "main.h"

void can_init(FDCAN_HandleTypeDef *hfdcan, FDCAN_FilterTypeDef *sFilterConfig, uint8_t filter_num)
{
    if (filter_num > 18)
    {
        return; // TODO
    }
    for (int i = 0; i < filter_num; i++)
    {
        if (HAL_FDCAN_ConfigFilter(hfdcan, &sFilterConfig[i]) != HAL_OK)
        {
            Error_Handler();
        }
    }
    HAL_FDCAN_ConfigGlobalFilter(hfdcan,
                                 FDCAN_REJECT,
                                 FDCAN_REJECT,
                                 FDCAN_FILTER_REMOTE,
                                 FDCAN_FILTER_REMOTE);
    if (HAL_FDCAN_Start(hfdcan) != HAL_OK)
    {
        Error_Handler();
    }
    if (HAL_FDCAN_ActivateNotification(hfdcan, FDCAN_IT_RX_FIFO0_NEW_MESSAGE, 0) != HAL_OK)
    {
        Error_Handler();
    }
    if (HAL_FDCAN_ActivateNotification(hfdcan, FDCAN_IT_BUS_OFF, 0) != HAL_OK)
    {
        Error_Handler();
    }
}

void can_send(FDCAN_HandleTypeDef *hfdcan, FDCAN_TxHeaderTypeDef tx_header, uint8_t *tx_data, uint8_t txdata_size)
{
    switch (txdata_size)
    {
    case 0:
        if (tx_header.DataLength != FDCAN_DLC_BYTES_0)
            return;
        break;
    case 1:
        if (tx_header.DataLength != FDCAN_DLC_BYTES_1)
            return;
        break;
    case 2:
        if (tx_header.DataLength != FDCAN_DLC_BYTES_2)
            return;
        break;
    case 3:
        if (tx_header.DataLength != FDCAN_DLC_BYTES_3)
            return;
        break;
    case 4:
        if (tx_header.DataLength != FDCAN_DLC_BYTES_4)
            return;
        break;
    case 5:
        if (tx_header.DataLength != FDCAN_DLC_BYTES_5)
            return;
        break;
    case 6:
        if (tx_header.DataLength != FDCAN_DLC_BYTES_6)
            return;
        break;
    case 7:
        if (tx_header.DataLength != FDCAN_DLC_BYTES_7)
            return;
        break;
    case 8:
        if (tx_header.DataLength != FDCAN_DLC_BYTES_8)
            return;
        break;
    case 12:
        if (tx_header.DataLength != FDCAN_DLC_BYTES_12)
            return;
        break;
    case 16:
        if (tx_header.DataLength != FDCAN_DLC_BYTES_16)
            return;
        break;
    case 20:
        if (tx_header.DataLength != FDCAN_DLC_BYTES_20)
            return;
        break;
    case 24:
        if (tx_header.DataLength != FDCAN_DLC_BYTES_24)
            return;
        break;
    case 32:
        if (tx_header.DataLength != FDCAN_DLC_BYTES_32)
            return;
        break;
    case 48:
        if (tx_header.DataLength != FDCAN_DLC_BYTES_48)
            return;
        break;
    case 64:
        if (tx_header.DataLength != FDCAN_DLC_BYTES_64)
            return;
        break;
    default:
        return;
    }
    HAL_FDCAN_AddMessageToTxFifoQ(hfdcan, &tx_header, tx_data);
}

__attribute__((weak)) void can_recv(FDCAN_HandleTypeDef *hfdcan, FDCAN_RxHeaderTypeDef rx_header, uint8_t recv_data[64])
{
    UNUSED(hfdcan);
    printf("id: 0x%x, data: %d, %d, %d, %d, %d, %d, %d, %d\n", rx_header.Identifier, recv_data[0], recv_data[1], recv_data[2], recv_data[3], recv_data[4], recv_data[5], recv_data[6], recv_data[7]);
    HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_8);
}

void HAL_FDCAN_RxFifo0Callback(FDCAN_HandleTypeDef *hfdcan, uint32_t RxFifo0ITs)
{
    if ((RxFifo0ITs & FDCAN_IT_RX_FIFO0_NEW_MESSAGE) != 0)
    {
        FDCAN_RxHeaderTypeDef rx_header;
        uint8_t recv_data[64];
        if (HAL_FDCAN_GetRxMessage(hfdcan, FDCAN_RX_FIFO0, &rx_header, recv_data) != HAL_OK)
        {
            return;
        }
        can_recv(hfdcan, rx_header, recv_data);
    }
}
void HAL_FDCAN_ErrorStatusCallback(FDCAN_HandleTypeDef *hfdcan, uint32_t ErrorStatusITs)
{
    if ((ErrorStatusITs & FDCAN_IE_BOE) != 0) /* If Bus-Off error occured */
    {
        hfdcan->Instance->CCCR &= ~FDCAN_CCCR_INIT; /* Recover from Bus-Off */
    }
}