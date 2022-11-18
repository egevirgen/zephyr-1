#include <zephyr/devicetree.h>
#include <zephyr/device.h>

#include <zephyr/logging/log.h>
LOG_MODULE_REGISTER(application, CONFIG_TECHSAFE_UTILITIES_LOG_LEVEL);

#define DT_DRV_COMPAT techsafe_application

/** APPLICATION configuration (DT). */
typedef const struct device * const function;

struct application_config {
    const function * functions;
    size_t function_count;
};

struct application_data {
};

static int application_init(const struct device *dev)
{
    const struct application_config *config = dev->config;
    for (size_t index = 0; index < config->function_count; index++) {
        LOG_DBG("FB Name = %s", config->functions[index]->name);
    }
    return 0;
}


#define APPLICATION_INIT(index)                                                     \
    function application_##index_functions[] =  { DT_FOREACH_CHILD_SEP(DT_CHILD(DT_INST(index, DT_DRV_COMPAT),functions), DEVICE_DT_GET ,(,)) }; \
    static const struct application_config application_config_##index = {	       \
        .functions =  application_##index_functions \
        , .function_count = ARRAY_SIZE(application_##index_functions) \
    }; \
    static struct application_data application_data_##index; \
    DEVICE_DT_INST_DEFINE(index, application_init, NULL,			       \
                &application_data_##index, &application_config_##index,      \
                POST_KERNEL, CONFIG_TECHSAFE_UTILITIES_INIT_PRIORITY,	       \
                NULL);

DT_INST_FOREACH_STATUS_OKAY(APPLICATION_INIT)

