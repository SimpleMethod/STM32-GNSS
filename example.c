/*===============================================================
	This is only an example, it has only necessary code.
===============================================================*/
/* USER CODE BEGIN Header */
 /*
 * example.c
 *
 *  Created on: 06.09.2020
 *      Author: SimpleMethod
 *
 *Copyright 2020 SimpleMethod
 *
 *Permission is hereby granted, free of charge, to any person obtaining a copy of
 *this software and associated documentation files (the "Software"), to deal in
 *the Software without restriction, including without limitation the rights to
 *use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
 *of the Software, and to permit persons to whom the Software is furnished to do
 *so, subject to the following conditions:
 *
 *The above copyright notice and this permission notice shall be included in all
 *copies or substantial portions of the Software.
 *
 *THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 *THE SOFTWARE.
 ******************************************************************************
 */
 /* USER CODE END Header */
 /* Includes ------------------------------------------------------------------*/
 #include "main.h"

 /* Private includes ----------------------------------------------------------*/
 /* USER CODE BEGIN Includes */
 #include <GNSS.h>
 /* USER CODE END Includes */

 /* Private variables ---------------------------------------------------------*/
 I2C_HandleTypeDef hi2c1;

 /* Private function prototypes -----------------------------------------------*/
 void SystemClock_Config(void);
 static void MX_GPIO_Init(void);
 static void MX_I2C1_Init(void);


 /**
  * @brief  The application entry point.
  * @retval int
  */
 int main(void)
 {
	HAL_Init();
	SystemClock_Config();
	MX_GPIO_Init();
	MX_I2C1_Init();
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
}

	
