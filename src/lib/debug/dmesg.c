#include "driver/uart/uart.h"
#include <string.h>

static int use_uart = 0;

void kprint(const char* data)
{
	int len = strlen(data);
	for(int i = 0; i < len; i++)
	{
		uart_putc ( data[i] );
	}
}

void dmesg_enable_uart(int baud_rate)
{
	use_uart = 1;
	uart_init ( baud_rate );
	
}
