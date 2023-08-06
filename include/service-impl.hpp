#pragma once

#include <thread>
#include <string>
#include <chrono>

#include <supervisor.hpp>

#include "i-plugin-manager.hpp"

using namespace std;

INIT_MIDF_SERVER(plugin_manager);

MIDF_IMPL_FUNC(std::vector<std::string>, plugin_manager, get_plugins_list) () {
    return std::vector<std::string>({"plugin1", "plugin2", "plugin3"});
}

MIDF_IMPL_FUNC(std::vector<std::string>, plugin_manager, get_installed_plugins_list) () {
    return std::vector<std::string>({"plugin1", "plugin2", "plugin3"});
}

MIDF_IMPL_FUNC(bool, plugin_manager, install, std::string) (std::string plugin_name) {
    return true;
}

MIDF_IMPL_FUNC(bool, plugin_manager, uninstall, std::string) (std::string plugin_name) {
    return true;
}

MIDF_IMPL_FUNC(bool, plugin_manager, enable, std::string) (std::string plugin_name) {
    return true;
}

MIDF_IMPL_FUNC(bool, plugin_manager, disable, std::string) (std::string plugin_name) {
    return true;
}

MIDF_IMPL_FUNC(bool, plugin_manager, is_installed, std::string) (std::string plugin_name) {
    return true;
}

MIDF_IMPL_FUNC(bool, plugin_manager, is_enabled, std::string) (std::string plugin_name) {
    return true;
}

void start_plugin_manager_async() {
    START_MIDF_SERVER(plugin_manager);
}