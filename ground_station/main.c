#include <stdio.h>
#include "nrf24l01.h"
#include <avr/io.h>

#define F_CPU 16000000UL
#define BAUD 9600
#define MYUBRR ((F_CPU/16/BAUD) - 1)

void uart_init(void)
{
    uint16_t ubrr = MYUBRR;
    UBRR0H = (uint8_t)(ubrr>>8);
    UBRR0L = (uint8_t)ubrr;
    UCSR0B = (1 << TXEN0);          // Enable transmitter
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00); // 8-bit data
}

int uart_putchar(char c, FILE *stream)
{
    if (c == '\n') uart_putchar('\r', stream); // add carriage return
    while (!(UCSR0A & (1<<UDRE0)));           // wait until buffer empty
    UDR0 = c;
    return 0;
}

FILE uart_output = FDEV_SETUP_STREAM(uart_putchar, NULL, _FDEV_SETUP_WRITE);

int main()
{
    uint8_t data;

    uart_init();
    stdout = &uart_output;   

    nrf24_device(RECEIVER, RESET);     // initialize as receiver

    nrf24_rf_power(6);                 // same power (not critical but fine)
    nrf24_rf_channel(40);              // must match transmitter

    nrf24_datapipe_address_configuration();  // load RX addresses
    nrf24_datapipe_enable(1);                // enable pipe 0
    nrf24_prx_static_payload_width(1,1);
    delay_function(100); 
    while(1)
    {
        if(nrf24_receive(&data,1) == OPERATION_DONE)
        {
           printf("Received: %d\n", data);   
        }
    }
}