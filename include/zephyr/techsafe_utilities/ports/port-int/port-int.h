/*
 * Copyright (c) 2015 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef PORT_INT_INCLUDE_H_
#define PORT_INT_INCLUDE_H_

#include <errno.h>
#include <zephyr/device.h>

#ifdef __cplusplus
extern "C" {
#endif

int port_int_get_value(const struct device *port, int *value);
int port_int_set_value(const struct device *port, int value);

#ifdef __cplusplus
}
#endif

#endif /* PORT_INT_INCLUDE_H_ */
