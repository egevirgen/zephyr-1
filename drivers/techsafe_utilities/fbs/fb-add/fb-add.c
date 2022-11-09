#include <zephyr/devicetree.h>
#include <zephyr/device.h>
#include <zephyr/techsafe_utilities/ports/port-int/port-int.h>

#include <zephyr/logging/log.h>
LOG_MODULE_REGISTER(fb_add, CONFIG_TECHSAFE_UTILITIES_LOG_LEVEL);

#define DT_DRV_COMPAT techsafe_fb_add

/** fb_add configuration (DT). */
struct fb_add_config {
    const struct device *input1;
    const struct device *input2;
    const struct device *output;
    const char * name;

};

struct fb_add_data {
    int value1;
    int value2;
    int output;
};

static int fb_add_init(const struct device *dev)
{
    const struct fb_add_config *config = dev->config;
    struct fb_add_data *data = dev->data;

    port_int_get_value(config->input1, &data->value1);
    port_int_get_value(config->input2, &data->value2);

    data->output = data->value1 + data->value2;
    port_int_set_value(config->output, data->output);

    LOG_DBG("FB Name = %s || IN1=%d IN2=%d OUT=%d", config->name, data->value1, data->value2, data->output);

    return 0;
}

#define FB_ADD_INIT(index)                                                     \
    static const struct fb_add_config fb_add_config_##index = {	       \
            .input1 = DEVICE_DT_GET(DT_INST_PHANDLE(index, input1)),	\
            .input2 = DEVICE_DT_GET(DT_INST_PHANDLE(index, input2)),	\
            .output = DEVICE_DT_GET(DT_INST_PHANDLE(index, output)),	\
            .name = DT_PROP(DT_INST(index, DT_DRV_COMPAT), fb_name)  \
    }; \
    static struct fb_add_data fb_add_data_##index; \
    DEVICE_DT_INST_DEFINE(index, fb_add_init, NULL,			       \
                &fb_add_data_##index, &fb_add_config_##index,      \
                POST_KERNEL, CONFIG_TECHSAFE_UTILITIES_INIT_PRIORITY,	       \
                NULL);

DT_INST_FOREACH_STATUS_OKAY(FB_ADD_INIT)

