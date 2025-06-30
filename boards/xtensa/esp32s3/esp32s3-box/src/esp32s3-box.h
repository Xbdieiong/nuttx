/****************************************************************************
 * boards/xtensa/esp32s3/esp32s3-box/src/esp32s3-box.h
 *
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.  The
 * ASF licenses this file to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance with the
 * License.  You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  See the
 * License for the specific language governing permissions and limitations
 * under the License.
 *
 ****************************************************************************/

#ifndef __BOARDS_XTENSA_ESP32S3_ESP32S3_BOX_SRC_ESP32S3_BOX_H
#define __BOARDS_XTENSA_ESP32S3_ESP32S3_BOX_SRC_ESP32S3_BOX_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>
#include <nuttx/compiler.h>
#include <stdint.h>
#include "esp32s3_spi.h"

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* ESP32-S3-BOX GPIOs *******************************************************/

/* BOOT Button */

#define BUTTON_BOOT         0

/* Display */

#define DISPLAY_SPI         2

/* CS:   5
 * CLK:  7
 * MOSI: 6
 * MISO: N/A
 */

#define DISPLAY_DC          4
#ifdef CONFIG_ESP32_S3_BOX
#  define DISPLAY_BCKL      45
#else
#  define DISPLAY_BCKL      47
#endif

#define DISPLAY_RST         48

/* Touchpad */

#define TOUCHSCEEN_I2C      0

/* SCL: 18
 * SDA: 8
 */

#ifdef CONFIG_ESP32_S3_BOX
#  define TOUCHSCEEN_ADDR   0x24
#else
#  define TOUCHSCEEN_ADDR   0x5d
#endif

#define TOUCHSCEEN_CLOCK    (400 * 1000)
#define TOUCHSCEEN_INT      3

/* I2C Port */

#define I2C_PORT            0

#ifdef CONFIG_AUDIO_ES8311
#  define SPEAKER_ENABLE_GPIO  46
#endif

/****************************************************************************
 * Public Types
 ****************************************************************************/

/****************************************************************************
 * Public Data
 ****************************************************************************/

#ifndef __ASSEMBLY__

/****************************************************************************
 * Public Function Prototypes
 ****************************************************************************/

/****************************************************************************
 * Name: esp32s3_bringup
 *
 * Description:
 *   Perform architecture-specific initialization
 *
 *   CONFIG_BOARD_LATE_INITIALIZE=y :
 *     Called from board_late_initialize().
 *
 *   CONFIG_BOARD_LATE_INITIALIZE=y && CONFIG_BOARDCTL=y :
 *     Called from the NSH library via board_app_initialize()
 *
 ****************************************************************************/

int esp32s3_bringup(void);

/****************************************************************************
 * Name: board_spiflash_init
 *
 * Description:
 *   Initialize the SPIFLASH and register the MTD device.
 *
 ****************************************************************************/

#ifdef CONFIG_ESP32S3_SPIFLASH
int board_spiflash_init(void);
#endif

/****************************************************************************
 * Name: board_lcd_initialize
 *
 * Description:
 *   Initialize the LCD video hardware. The initial state of the LCD is fully
 *   initialized, display memory cleared, and the LCD ready to use, but with
 *   the power setting at 0 (full off).
 *
 ****************************************************************************/

#ifdef CONFIG_ESP32S3_BOX_LCD
int board_lcd_initialize(void);
#endif

/****************************************************************************
 * Name: board_lcd_getdev
 *
 * Description:
 *   Return a reference to the LCD object for the specified LCD. This allows
 *   support for multiple LCD devices.
 *
 ****************************************************************************/

#ifdef CONFIG_ESP32S3_BOX_LCD
struct lcd_dev_s *board_lcd_getdev(int lcddev);
#endif

/****************************************************************************
 * Name: board_lcd_uninitialize
 *
 * Description:
 *   Uninitialize the LCD support.
 *
 ****************************************************************************/

#ifdef CONFIG_ESP32S3_BOX_LCD
void board_lcd_uninitialize(void);
#endif

/****************************************************************************
 * Name: board_touchscreen_initialize
 *
 * Description:
 *   Initialize touchscreen.
 *
 * Input Parameters:
 *   None.
 *
 * Returned Value:
 *   Zero (OK) on success; a negated errno value on failure.
 *
 ****************************************************************************/

#ifdef CONFIG_ESP32S3_BOARD_TOUCHSCREEN
int board_touchscreen_initialize(void);
#endif

/****************************************************************************
 * Name: esp32s3_es8311_initialize
 *
 * Description:
 *   This function is called by platform-specific, setup logic to configure
 *   and register the ES8311 device.  This function will register the driver
 *   as /dev/audio/pcm[x] where x is determined by the I2S port number.
 *
 * Input Parameters:
 *   i2c_port  - The I2C port used for the device
 *   i2c_addr  - The I2C address used by the device
 *   i2c_freq  - The I2C frequency used for the device
 *   i2s_port  - The I2S port used for the device
 *
 * Returned Value:
 *   Zero is returned on success.  Otherwise, a negated errno value is
 *   returned to indicate the nature of the failure.
 *
 ****************************************************************************/

#ifdef CONFIG_AUDIO_ES8311
int esp32s3_es8311_initialize(int i2c_port, uint8_t i2c_addr, int i2c_freq,
                            int i2s_port);
#endif

#endif /* __ASSEMBLY__ */
#endif /* __BOARDS_XTENSA_ESP32S3_ESP32S3_BOX_SRC_ESP32S3_BOX_H */
