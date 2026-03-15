#include <stdio.h>
#include "drivers/nrf24l01.h"
#include "drivers/ina226.h"


int main(void)
{
    nrf24_device(TRANSMITTER, RESET);
    nrf24_rf_power(6);
    nrf24_rf_channel(40);
    nrf24_datapipe_ptx(0);
    nrf24_flush(TX_BUFFER);
    uint8_t data = 1;
    nrf24_prx_static_payload_width(1,1);

    while(1)
    {

    nrf24_transmit(&data, 1, NO_ACK_MODE);
    while(nrf24_transmit_status() == TRANSMIT_IN_PROGRESS);
    delay_function(100); 
    }
    return 0;
}