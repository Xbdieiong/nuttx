/****************************************************************************
 * drivers/sensors/bmi088_base.c
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

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include "bmi088_base.h"

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/****************************************************************************
 * Private Types
 ****************************************************************************/

/****************************************************************************
 * Private Functions
 ****************************************************************************/

/****************************************************************************
 * Private Data
 ****************************************************************************/

/****************************************************************************
 * Public Functions
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
{
  /* Configure SPI for the BMI088 */

  SPI_SETMODE(spi, SPIDEV_MODE3);
  SPI_SETBITS(spi, 8);
  SPI_HWFEATURES(spi, 0);
  SPI_SETFREQUENCY(spi, BMI160_SPI_MAXFREQUENCY);
}

/****************************************************************************
 * Name: bmi088_acc_getreg8
 *
 * Description:
 *   Read from an 8-bit BMI088 accelerometer register.
 *
 ****************************************************************************/
void bmi088_acc_getreg8(FAR struct bmi088_dev_s *priv,
                                uint8_t regaddr,uint8_t *regval)
{
  /* If SPI bus is shared then lock and configure it */

  SPI_LOCK(priv->spi, true);
  bmi088_configspi(priv->spi);

  /* Select the device */

  SPI_SELECT(priv->spi, SPIDEV_IMU(0),true);

  /* Write the register address and read value */

  SPI_SEND(priv->spi, regaddr | 0x80);
  SPI_RECVBLOCK(priv->spi, &regval, 1);

  /* Deselect the device */

  spi_deselect(priv->spi, SPIDEV_IMU(0),false);

  /* Unlock bus */

  SPI_LOCK(priv->spi, false);

}

/****************************************************************************
 * Name: bmi088_gyro_getreg8
 *
 * Description:
 *   Read from an 8-bit BMI088 gyroscope register.
 *
 ****************************************************************************/
void bmi088_gyro_getreg8(FAR struct bmi088_dev_s *priv,
                                uint8_t regaddr,uint8_t *regval)
{
  /* If SPI bus is shared then lock and configure it */

  SPI_LOCK(priv->spi, true);
  bmi088_configspi(priv->spi);

  /* Select the device */

  SPI_SELECT(priv->spi, SPIDEV_IMU(1),true);

  /* Write the register address and read value */

  SPI_SEND(priv->spi, regaddr | 0x80);
  SPI_RECVBLOCK(priv->spi, &regval, 1);

  /* Deselect the device */

  spi_deselect(priv->spi, SPIDEV_IMU(1),false);

  /* Unlock bus */

  SPI_LOCK(priv->spi, false);

}

/****************************************************************************
 * Name: bmi088_acc_putreg8
 *
 * Description:
 *   Write a value to an 8-bit BMI088 accelerometer register.
 *
 ****************************************************************************/
void bmi088_acc_putreg8(FAR struct bmi088_dev_s *priv,
                                uint8_t regaddr, uint8_t regval)
{
  /* If SPI bus is shared then lock and configure it */

  SPI_LOCK(priv->spi, true);
  bmi088_configspi(priv->spi);

  /* Select the device */

  SPI_SELECT(priv->spi, SPIDEV_IMU(0),true);

  /* Write the register address and value */

  SPI_SEND(priv->spi, regaddr);
  SPI_SEND(priv->spi, regval);

  /* Deselect the device */

  spi_deselect(priv->spi, SPIDEV_IMU(0),false);

  /* Unlock bus */

  SPI_LOCK(priv->spi, false);

}

/****************************************************************************
 * Name: bmi088_gyro_putreg8
 *
 * Description:
 *   Write a value to an 8-bit BMI088 gyroscope register.
 *
 ****************************************************************************/
void bmi088_gyro_putreg8(FAR struct bmi088_dev_s *priv,
                                uint8_t regaddr, uint8_t regval)
{
  /* If SPI bus is shared then lock and configure it */

  SPI_LOCK(priv->spi, true);
  bmi088_configspi(priv->spi);

  /* Select the device */

  SPI_SELECT(priv->spi, SPIDEV_IMU(1),true);

  /* Write the register address and value */

  SPI_SEND(priv->spi, regaddr);
  SPI_SEND(priv->spi, regval);

  /* Deselect the device */

  spi_deselect(priv->spi, SPIDEV_IMU(1),false);

  /* Unlock bus */

  SPI_LOCK(priv->spi, false);

}

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
int bmi088_acc_check_id(FAR struct bmi088_dev_s *priv)
{
  uint8_t id;

  /* Read the chip ID */

  bmi088_acc_getreg8(priv, BMI088_ACC_CHIP_ID, &id);
  sninfo("Accelerometer Chip ID: %02x\n", id);

  if (id != BMI088_ACC_CHIP_ID_VALUE)
    {
      snerr("ERROR: Invalid Accelerometer Chip ID: %02x\n", id);
      return -ENODEV;
    }

  return OK;
}

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
int bmi088_gyro_check_id(FAR struct bmi088_dev_s *priv)
{
  uint8_t id;

  /* Read the chip ID */

  bmi088_gyro_getreg8(priv, BMI088_GYRO_CHIP_ID, &id);
  sninfo("Gyroscope Chip ID: %02x\n", id);

  if (id != BMI088_GYRO_CHIP_ID_VALUE)
    {
      snerr("ERROR: Invalid Gyroscope Chip ID: %02x\n", id);
      return -ENODEV;
    }

  return OK;
}

#endif
