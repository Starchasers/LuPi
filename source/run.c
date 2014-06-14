

void _setGpioFunction(unsigned int gpioRegister, unsigned int function);
void _setGpio(unsigned int gpioRegister, unsigned int value);
void _wait(unsigned int delayInMicroSeconds);

void run(void)
{
	_setGpioFunction(1,16);
	while(1)
	{
		_setGpio(16, 0);
		_wait(100000);
		_setGpio(16, 1);
		_wait(500000);
	}
}
