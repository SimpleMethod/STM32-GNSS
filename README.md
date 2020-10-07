# STM32 GNSS

## STM32 library with DMA support for u-blox devices supporting Global Navigation Satellite Systems and UBX standard

![proof of concept](https://raw.githubusercontent.com/SimpleMethod/STM32-GNSS/master/doc/GNSS_01.png)

# Example:

     /* USER CODE BEGIN 2 */
    	GNSS_Init(&GNSS_Handle, &huart1);
    	HAL_Delay(1000);
    	GNSS_LoadConfig(&GNSS_Handle);
    	uint32_t Timer = HAL_GetTick();
     /* USER CODE END 2 */
     /* Infinite loop */
     /* USER CODE BEGIN WHILE */
    	while (1) {
    
    		if ((HAL_GetTick() - Timer) > 1000) {
    			GNSS_GetUniqID(&GNSS_Handle);
    			GNSS_ParseBuffer(&GNSS_Handle);
    			HAL_Delay(250);
    			GNSS_GetPVTData(&GNSS_Handle);
    			GNSS_ParseBuffer(&GNSS_Handle);
    			printf("Day: %d-%d-%d \r\n", GNSS_Handle.day, GNSS_Handle.month,GNSS_Handle.year);
    			printf("Time: %d:%d:%d \r\n", GNSS_Handle.hour, GNSS_Handle.min,GNSS_Handle.sec);
    			printf("Status of fix: %d \r\n", GNSS_Handle.fixType);
    			printf("Latitude: %f \r\n", GNSS_Handle.fLat);
    			printf("Longitude: %f \r\n",(float) GNSS_Handle.lon / 10000000.0);
    			printf("Height above ellipsoid: %d \r\n", GNSS_Handle.height);
    			printf("Height above mean sea level: %d \r\n", GNSS_Handle.hMSL);
    			printf("Ground Speed (2-D): %d \r\n", GNSS_Handle.gSpeed);
    			printf("Unique ID: %04X %04X %04X %04X %04X \n\r",
    					GNSS_Handle.uniqueID[0], GNSS_Handle.uniqueID[1],
    					GNSS_Handle.uniqueID[2], GNSS_Handle.uniqueID[3],
    					GNSS_Handle.uniqueID[4], GNSS_Handle.uniqueID[5]);
    			Timer = HAL_GetTick();
    		}
    		/* USER CODE END WHILE */
    		/* USER CODE BEGIN 3 */
    	}
     /* USER CODE END 3 */

# Successfully tested on:
- [x] MAX-M8Q
- [x] NEO-M8
- [x] NEO-M9N
# NVIC configuration:
|                             Interrupt Table                             | Enable | Preenmption Priority | SubPriority |
|-------------------------------------------------------------------------|--------|----------------------|-------------|
| USART1 global interrupt / USART1 wake-up interrupt through EXTI line 25 |  true  |                    0 |           0 |
| USART2 global interrupt / USART2 wake-up interrupt through EXTI line 26 | true   |                    0 |           0 |

# DMA configuration:
| DMA request |    Stream     |      Direction       | Priority |
|-------------|---------------|----------------------|----------|
| USART1_RX   | DMA1_Channel3 | Peripheral To Memory | Low      |
| USART1_TX   | DMA1_Channel4 | Memory To Peripheral | Low      |

# IPs and Middleware Configuration:
| Type   |     Mode     | Baud Rate |        Word Length        | Parity | Stop Bits |    Data Direction    |
|--------|--------------|-----------|---------------------------|--------|-----------|----------------------|
| USART1 | Asynchronous |      **9600** | 8 Bits (including Parity) | None   |         1 | Receive and Transmit |

#  UBX configuration:

    //Setting input and output only for UBX standard
    static uint8_t configUBX[]={0xB5,0x62,0x06,0x00,0x14,0x00,0x01,0x00,0x00,0x00,0xD0,0x08,0x00,0x00,0x80,0x25,0x00,0x00,0x01,0x00,0x01,0x00,0x00,0x00,0x00,0x00,0x9A,0x79};
    
    //Changing the NMEA version to 4.10
    static uint8_t setNMEA410[]={0xB5,0x62,0x06,0x17,0x14,0x00,0x00,0x41,0x00,0x02,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x75,0x57};
    
    //Activation of navigation system: Galileo, Glonass, GPS, SBAS, IMES
    static uint8_t setGNSS[]={0xB5,0x62,0x06,0x3E,0x24,0x00,0x00,0x00,0x20,0x04,0x00,0x08,0x10,0x00,0x01,0x00,0x01,0x01,0x01,0x01,0x03,0x00,0x01,0x00,0x01,0x01,0x02,0x04,0x08,0x00,0x01,0x00,0x01,0x01,0x06,0x08,0x0E,0x00,0x01,0x00,0x01,0x01,0xDF,0xFB};


# Pins configuration:

| PERIPHERALS | MODES                 | FUNCTIONS      | PINS              |
|-------------|-----------------------|----------------|-------------------|
| USART1      | Asynchronous          | USART2_RX      | PB10              |
| USART1      | Asynchronous          | USART2_TX      | PB6               |
| SYS         | Trace Asynchronous Sw | SYS_JTMS-SWDIO | PA13              |
| SYS         | Trace Asynchronous Sw | SYS_JTCK-SWCLK | PA14              |
| SYS         | Trace Asynchronous Sw | SYS_JTDO-SWO   | PB3               |
| SYS         | SysTick               | SYS_VS_Systick | VP_SYS_VS_Systick |
| USART2      | Asynchronous          | USART2_RX      | PA3               |
| USART2      | Asynchronous          | USART2_TX      | PA2               |


### **For using printf with float should be add flag -u _printf_float in C compiler**

![enter image description here](https://raw.githubusercontent.com/SimpleMethod/STM32-AM2320/master/Images/am2320_Atolic_TrueSTUDIO.png)

### More information can be found in [u-blox M8 Receiver description](https://www.u-blox.com/sites/default/files/products/documents/u-blox8-M8_ReceiverDescrProtSpec_%28UBX-13003221%29.pdf)
