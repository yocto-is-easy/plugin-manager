#include <string>
#include <vector>
#include <iostream>
#include <thread>

#include "service-impl.hpp"

int main() {
    std::shared_ptr<PluginRegistrator> plugin_registrator = std::make_shared<PluginRegistrator>();
    start_plugin_manager_async(plugin_registrator);
}
