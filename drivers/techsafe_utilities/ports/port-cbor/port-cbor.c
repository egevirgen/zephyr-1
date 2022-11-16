#include <zephyr/devicetree.h>
#include <zephyr/device.h>
//#include <zephyr/techsafe_utilities/ports/port-cbor/port-cbor.h>

#include <zephyr/logging/log.h>
LOG_MODULE_REGISTER(port_cbor, CONFIG_TECHSAFE_UTILITIES_LOG_LEVEL);

#define DT_DRV_COMPAT techsafe_port_cbor

/** PORT_CBOR configuration (DT). */
struct port_cbor_config {
    const unsigned char* initial_value;
    unsigned int initial_value_len;
};

struct port_cbor_data {
    unsigned char* value;
};

static int port_cbor_init(const struct device *dev)
{
    const struct port_cbor_config *config = dev->config;
    struct port_cbor_data *data = dev->data;

//    data->value = config->initial_value;

    LOG_DBG("ENC CBOR = %d\n", config->initial_value_len);

    return 0;
}


//int port_int_get_value(const struct device *port, int *value)
//{
//    if (port && value) {
//        struct port_int_data *data = port->data;
//        *value = data->value;
//    } else {

//    }
//    return 0;
//}

//int port_int_set_value(const struct device *port, int value)
//{
//    if (port) {
//        struct port_int_data *data = port->data;
//        data->value = value;
//    } else {

//    }
//    return 0;
//}


#define PORT_CBOR_INIT(index)                                                     \
    static const char initial_value_##index[] = DT_PROP(DT_INST(index, DT_DRV_COMPAT), initial_value);			       \
    static const struct port_cbor_config port_cbor_config_##index = {	       \
        .initial_value = initial_value_##index			       \
        , .initial_value_len = DT_PROP_LEN(DT_INST(index, DT_DRV_COMPAT), initial_value) \
    }; \
    static struct port_cbor_data port_cbor_data_##index; \
    DEVICE_DT_INST_DEFINE(index, port_cbor_init, NULL,			       \
                &port_cbor_data_##index, &port_cbor_config_##index,      \
                POST_KERNEL, CONFIG_TECHSAFE_UTILITIES_INIT_PRIORITY,	       \
                NULL);

DT_INST_FOREACH_STATUS_OKAY(PORT_CBOR_INIT)

