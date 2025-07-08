/****************************************************************************
 * drivers/sensors/bmi088_base.h
 *
 * SPDX-License-Identifier: Apache-2.0
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

#ifndef __INCLUDE_NUTTX_SENSORS_BMI088_BASE_H
#define __INCLUDE_NUTTX_SENSORS_BMI088_BASE_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>

#include <stdint.h>
#include <stdlib.h>
#include <errno.h>
#include <debug.h>

#include <nuttx/arch.h>
#include <nuttx/kmalloc.h>
#include <nuttx/fs/fs.h>
#include <nuttx/sensors/bmi088.h>
#  include <nuttx/spi/spi.h>

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

#define BMI160_SPI_MAXFREQUENCY 10000000

/* BMI088 Accelerometer Register Definations and Configuration Values */

#define BMI088_ACC_CHIP_ID             (0x00) /* Chip ID for accelerometer */
#define BMI088_ACC_CHIP_ID_VALUE       (0x1E) /* ID Code for accelerometer */

#define BMI088_ACC_ERR                 (0x02) /* Error register */
#define BMI088_ACC_CONFIG_ERROR        (0x04) /* Configuration error flag */
#define BMI088_ACC_FATAL_ERROR         (0x01) /* Fatal error flag */

#define BMI088_ACC_STATUS              (0x03) /* Sensor status flag */
#define BMI088_ACC_DRDY                (0x10) /* Data ready flag */

#define BMI088_ACC_X_LSB               (0x12) /* Acc X-axis data LSB */
#define BMI088_ACC_X_MSB               (0x13) /* Acc X-axis data MSB */
#define BMI088_ACC_Y_LSB               (0x14) /* Acc Y-axis data LSB */
#define BMI088_ACC_Y_MSB               (0x15) /* Acc Y-axis data MSB */
#define BMI088_ACC_Z_LSB               (0x16) /* Acc Z-axis data LSB */
#define BMI088_ACC_Z_MSB               (0x17) /* Acc Z-axis data MSB */

#define BMI088_SENSORTIME_DATA_LSB     (0x18) /* Sensor time data LSB */
#define BMI088_SENSORTIME_DATA_MSB     (0x19) /* Sensor time data MSB */
#define BMI088_SENSORTIME_DATA_HSB     (0x1A) /* Sensor time data HSB */

#define BMI088_ACC_INT_STAT_1          (0x1D) /* Interrupt status register */
#define BMI088_ACC_DRDY_INTERRUPT      (0x80) /* Data ready interrupt */

#define BMI088_TEMP_MSB                (0x22) /* Temperature MSB */
#define BMI088_TEMP_LSB                (0x23) /* Temperature LSB */

#define BMI088_ACC_CONF                (0x40) /* Acc configuration */
#define BMI088_ACC_OSR4                (0x80) /* OSR4 mode */
#define BMI088_ACC_OSR2                (0x90) /* OSR2 mode */
#define BMI088_ACC_NORMAL              (0xA0) /* Normal mode */
#define BMI088_ACC_ODR_12_5_HZ         (0x05) /* ODR 12.5 Hz */
#define BMI088_ACC_ODR_25_HZ           (0x06) /* ODR 25 Hz */
#define BMI088_ACC_ODR_50_H            (0x07) /* ODR 50 Hz */
#define BMI088_ACC_ODR_100_H           (0x08) /* ODR 100 Hz */
#define BMI088_ACC_ODR_200_H           (0x09) /* ODR 200 Hz */
#define BMI088_ACC_ODR_400_H           (0x0A) /* ODR 400 Hz */
#define BMI088_ACC_ODR_800_H           (0x0B) /* ODR 800 Hz */
#define BMI088_ACC_ODR_1600_H          (0x0C) /* ODR 1600 Hz */

#define BMI088_ACC_RANGE               (0x41) /* Acc range */
#define BMI088_ACC_RANGE_3G            (0x00) /* 3G range */
#define BMI088_ACC_RANGE_6G            (0x01) /* 6G range */
#define BMI088_ACC_RANGE_12G           (0x02) /* 12G range */
#define BMI088_ACC_RANGE_24G           (0x03) /* 24G range */

#define BMI088_FIFO_CONFIG_0           (0x48) /* FIFO configuration_0 */
#define BMI088_STREAM_CONFIG           (0x02) /* Stream configuration */
#define BMI088_FIFO_CONFIG             (0x03) /* FIFO configuration */
#define BMI088_FIFO_CONFIG_1           (0x49) /* FIFO configuration_1 */

#define BMI088_ACC_PWR_CONF            (0x7C) /* Power configuration */
#define BMI088_ACC_PWR_SUSPEND_MODE    (0x03) /* Suspend mode */
#define BMI088_ACC_PWR_ACTIVE_MODE     (0x00) /* Active mode */

#define BMI088_ACC_PWR_CTRL            (0x7D) /* Power control register */
#define BMI088_ACC_ENABLE_ACC_OFF      (0x00) /* Disable accelerometer */
#define BMI088_ACC_ENABLE_ACC_ON       (0x04) /* Enable accelerometer */

#define BMI088_ACC_SOFTRESET           (0x7E) /* Soft reset register */
#define BMI088_ACC_SOFTRESET_VALUE     (0xB6) /* Soft reset value */

/* BMI088 GYRO Register Definations and Configuration Values */

#define BMI088_GYRO_CHIP_ID            (0x00) /* Chip ID for gyroscope */
#define BMI088_GYRO_CHIP_ID_VALUE      (0x0F) /* ID Code for gyroscope */

#define BMI088_GYRO_X_LSB              (0x02) /* Gyro X-axis data LSB */
#define BMI088_GYRO_X_MSB              (0x03) /* Gyro X-axis data MSB */
#define BMI088_GYRO_Y_LSB              (0x04) /* Gyro Y-axis data LSB */
#define BMI088_GYRO_Y_MSB              (0x05) /* Gyro Y-axis data MSB */
#define BMI088_GYRO_Z_LSB              (0x06) /* Gyro Z-axis data LSB */
#define BMI088_GYRO_Z_MSB              (0x07) /* Gyro Z-axis data MSB */

#define BMI088_GYRO_INT_STAT_1         (0x0A) /* Gyro interrupt status  */
#define BMI088_GYRO_DRDY_INTERRUPT     (0x80) /* Data ready interrupt */

#define BMI088_GYRO_RANGE              (0x0F) /* Gyro range */
#define BMI088_GYRO_2000               (0x00) /* 2000 dps range */
#define BMI088_GYRO_1000               (0x01) /* 1000 dps range */
#define BMI088_GYRO_500                (0x02) /* 500 dps range */
#define BMI088_GYRO_250                (0x03) /* 250 dps range */
#define BMI088_GYRO_125                (0x04) /* 125 dps range */

#define BMI088_GYRO_BANDWIDTH          (0x10) /* Gyro bandwidth */
#define BMI088_GYRO_2000_532_HZ        (0x00) /* 2000 dps, 532 Hz */
#define BMI088_GYRO_2000_230_HZ        (0x01) /* 2000 dps, 230 Hz */
#define BMI088_GYRO_1000_116_HZ        (0x02) /* 1000 dps, 116 Hz */
#define BMI088_GYRO_400_47_HZ          (0x03) /* 400 dps, 47 Hz */
#define BMI088_GYRO_200_23_HZ          (0x04) /* 200 dps, 23 Hz */
#define BMI088_GYRO_100_12_HZ          (0x05) /* 100 dps, 12 Hz */
#define BMI088_GYRO_200_64_HZ          (0x06) /* 200 dps, 64 Hz */
#define BMI088_GYRO_100_32_HZ          (0x07) /* 100 dps, 32 Hz */

#define BMI088_GYRO_LPM1               (0x11) /* Gyro low power mode 1 */
#define BMI088_GYRO_NORMAL_MODE        (0x00) /* Normal mode */
#define BMI088_GYRO_SUSPEND_MODE       (0x80) /* Suspend mode */
#define BMI088_GYRO_DEEP_SUSPEND_MODE  (0x20) /* Deep suspend mode */

#define BMI088_GYRO_SOFTRESET          (0x14) /* Gyro soft reset register */
#define BMI088_GYRO_SOFTRESET_VALUE    (0xB6) /* Soft reset value */

#define BMI088_GYRO_CTRL               (0x15) /* Gyro control register */
#define BMI088_DRDY_OFF                (0x00) /* Data ready off */
#define BMI088_DRDY_ON                 (0x80) /* Data ready on */

/****************************************************************************
 * Public Types
 ****************************************************************************/

struct bmi088_dev_s
{
#ifdef CONFIG_SENSORS_BMI088_SPI /* CONFIG_SENSORS_BMI088_SPI */
  FAR struct spi_dev_s    *spi;  /* SPI interface */
#endif
};

/****************************************************************************
 * Public Data
 ****************************************************************************/

extern const uint8_t g_bmi088_config_file[];

/****************************************************************************
 * Public Function Prototypes
 ****************************************************************************/

#ifdef CONFIG_SENSORS_BMI088_SPI

/****************************************************************************
 * Name: bmi088_configspi
 *
 * Description:
 *   Configure the SPI interface for the BMI088.
 *
 ****************************************************************************/
void bmi088_configspi(FAR struct spi_dev_s *spi)

/****************************************************************************
 * Name: bmi088_acc_getreg8
 *
 * Description:
 *   Read from an 8-bit BMI088 accelerometer register.
 *
 ****************************************************************************/
void bmi088_acc_getreg8(FAR struct bmi088_dev_s *priv,
                                uint8_t regaddr,uint8_t *regval)

/****************************************************************************
 * Name: bmi088_gyro_getreg8
 *
 * Description:
 *   Read from an 8-bit BMI088 gyroscope register.
 *
 ****************************************************************************/
void bmi088_gyro_getreg8(FAR struct bmi088_dev_s *priv,
                                uint8_t regaddr,uint8_t *regval);

/****************************************************************************
 * Name: bmi088_acc_putreg8
 *
 * Description:
 *   Write a value to an 8-bit BMI088 accelerometer register.
 *
 ****************************************************************************/
void bmi088_acc_putreg8(FAR struct bmi088_dev_s *priv,
                                uint8_t regaddr, uint8_t regval);

/****************************************************************************
 * Name: bmi088_gyro_putreg8
 *
 * Description:
 *   Write a value to an 8-bit BMI088 gyroscope register.
 *
 ****************************************************************************/
void bmi088_gyro_putreg8(FAR struct bmi088_dev_s *priv,
                                uint8_t regaddr, uint8_t regval);

/****************************************************************************
 * Name: bmi088_acc_check_id
 *
 * Description:
 *   Check the chip ID of the accelerometer.
 *
 * Input Parameters:
 *   priv - Pointer to the BMI088 device structure.
 *
 * Returned Value:
 *   OK on success; a negated errno value on failure.
 *
 ****************************************************************************/
int bmi088_acc_check_id(FAR struct bmi088_dev_s *priv);

/****************************************************************************
 * Name: bmi088_gyro_check_id
 *
 * Description:
 *   Check the chip ID of the gyroscope.
 *
 * Input Parameters:
 *   priv - Pointer to the BMI088 device structure.
 *
 * Returned Value:
 *   OK on success; a negated errno value on failure.
 *
 ****************************************************************************/
int bmi088_gyro_check_id(FAR struct bmi088_dev_s *priv);

#endif

#endif  /* __INCLUDE_NUTTX_SENSORS_BMI088_BASE_H */
