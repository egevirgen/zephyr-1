#include <zephyr/devicetree.h>
#include <zephyr/device.h>

#include <zephyr/logging/log.h>
LOG_MODULE_REGISTER(fb_add, CONFIG_TECHSAFE_UTILITIES_LOG_LEVEL);

#define DT_DRV_COMPAT techsafe_fb_add

/** fb_add configuration (DT). */
struct fb_add_config {
    const struct device *input1;
    const struct device *input2;
    const struct device *output;
    const struct device *app;

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

    data->output = data->value1 = data->value2 = 0;

    LOG_DBG("FB Name = %s || IN1=%s IN2=%s OUT=%s", config->app->name, config->input1->name, config->input2->name, config->output->name);

    return 0;
}

#define FB_ADD_INIT(index)                                                     \
    static const struct fb_add_config fb_add_config_##index = {	       \
            .input1 = DEVICE_DT_GET(DT_CHILD(DT_CHILD(DT_INST(index, DT_DRV_COMPAT),in_ports), in_1)),	\
            .input2 = DEVICE_DT_GET(DT_CHILD(DT_CHILD(DT_INST(index, DT_DRV_COMPAT),in_ports), in_2)),	\
            .output = DEVICE_DT_GET(DT_CHILD(DT_CHILD(DT_INST(index, DT_DRV_COMPAT),out_ports), out)), \
            .app = DEVICE_DT_GET(DT_BUS(DT_INST(index, DT_DRV_COMPAT))) \
    }; \
    static struct fb_add_data fb_add_data_##index; \
    DEVICE_DT_INST_DEFINE(index, fb_add_init, NULL,			       \
                &fb_add_data_##index, &fb_add_config_##index,      \
                POST_KERNEL, CONFIG_TECHSAFE_UTILITIES_INIT_PRIORITY,	       \
                NULL);

DT_INST_FOREACH_STATUS_OKAY(FB_ADD_INIT)

