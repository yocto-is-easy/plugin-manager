#pragma once

#include <thread>
#include <string>
#include <chrono>

#include <supervisor.hpp>

#include "i-plugin-manager.hpp"

using namespace std;

INIT_MIDF_SERVER(plugin_manager);

// interface for managing plugins
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

// inteface for the plugins' initialization
MIDF_IMPL_FUNC(bool, plugin_manager, register_plugin, std::string) (std::string plugin_name) {
    return true;
}

MIDF_IMPL_FUNC(bool, plugin_manager, register_function, std::string, std::string, midf::function<std::string, std::string>, std::string)
(std::string plugin_name, std::string function_name, midf::function<std::string, std::string> func, std::string func_description/*json*/) {
    return true;
}

// interface to interract with the plugins
MIDF_IMPL_FUNC(std::string, plugin_manager, get_plugin_info, std::string) (std::string plugin_name) {
    return "";
}

MIDF_IMPL_FUNC(std::string, plugin_manager, get_function_info, std::string, std::string)
(std::string plugin_name, std::string function_name) {
    return "";
}

MIDF_IMPL_FUNC(PluginFunction, plugin_manager, get_function, std::string, std::string) (std::string plugin_name, std::string function_name) {
    return midf::function<std::string, std::string>(1337, "temp_service", "temp_func");
}

void start_plugin_manager_async() {
    START_MIDF_SERVER(plugin_manager);
}