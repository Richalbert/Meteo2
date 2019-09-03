/*
 *	Meteo/src/capteurs.h
 */

#pragma once

#ifdef __cplusplus
extern "C" {
#endif
#include "bme280.h"

void initSensor(struct bme280_dev *dev);
void refreshSensor(struct bme280_dev *dev, struct bme280_data *comp_data);

#ifdef __cplusplus
}
#endif

