#include "driver/gpio/gpio.h"
#include "driver/timer/systemTimer.h"

void abort(void){
	while(1)
	{
		_setGpio(16, 0);
		_wait(75000);
		_setGpio(16, 1);
		_wait(75000);
	}
}
void _fstat_r(void){}
void _open_r(void){}
void _sbrk_r(void){}
void _getpid_r(void){}
void _kill_r(void){}
void _write_r(void){}
void _close_r(void){}
void _gettimeofday_r(void){}
void _isatty_r(void){}
void _lseek_r(void){}
void _read_r(void){}
void _read(void){}


