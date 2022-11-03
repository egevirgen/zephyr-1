#include <zephyr/devicetree.h>
#include <zephyr/device.h>
#include <zephyr/techsafe_utilities/ports/port-int/port-int.h>

#include <zephyr/logging/log.h>
LOG_MODULE_REGISTER(port_int, CONFIG_TECHSAFE_UTILITIES_LOG_LEVEL);

#define DT_DRV_COMPAT techsafe_port_int

/** PORT_INT configuration (DT). */
struct port_int_config {
    const int value;
	const char * name;
};

struct port_int_data {
    int value;
};

static int port_int_init(const struct device *dev)
{
    const struct port_int_config *config = dev->config;
    struct port_int_data *data = dev->data;

    data->value = config->value;

    LOG_DBG("Port Name = %s || Port Value = %d\n", config->name, config->value);

    return 0;
}


int port_int_get_value(const struct device *port, int *value)
{
    if (port && value) {
        struct port_int_data *data = port->data;
        *value = data->value;
    } else {

    }
    return 0;
}

int port_int_set_value(const struct device *port, int value)
{
    if (port) {
        struct port_int_data *data = port->data;
        data->value = value;
    } else {

    }
    return 0;
}


#define PORT_INT_INIT(index)                                                     \
    static const struct port_int_config port_int_config_##index = {	       \
        .value = DT_PROP(DT_INST(index, DT_DRV_COMPAT), port_value),			       \
        .name = DT_PROP(DT_INST(index, DT_DRV_COMPAT), port_name) \
    }; \
    static struct port_int_data port_int_data_##index; \
    DEVICE_DT_INST_DEFINE(index, port_int_init, NULL,			       \
                &port_int_data_##index, &port_int_config_##index,      \
                POST_KERNEL, CONFIG_TECHSAFE_UTILITIES_INIT_PRIORITY,	       \
                NULL);

DT_INST_FOREACH_STATUS_OKAY(PORT_INT_INIT)

