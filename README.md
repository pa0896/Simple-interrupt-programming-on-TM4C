# Simple-interrupt-programming-on-TM4C

This program uses the PB6 pin of the TM4C microcontroller and periodically generates a signal using the SysTick_Handler function. The SysTick_Handler() has been configured by me in the startup file since the function is statically defined therefore it cannot be created outside of the startup file.
