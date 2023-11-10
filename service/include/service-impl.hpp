#pragma once

#include <thread>
#include <string>
#include <chrono>
#include <memory>

#include "i-plugin-manager.hpp"
#include "PluginRegistrator.hpp"

#include <supervisor.hpp>

using namespace std;

std::shared_ptr<PluginRegistrator> m_plugin_registrator = nullptr;

INIT_MIDF_SERVER(plugin_manager);

// interface for managing plugins
MIDF_IMPL_FUNC(PluginsList, plugin_manager, get_plugins_list) () {
    return PluginsList({"plugin1", "plugin2", "plugin3"});
}

MIDF_IMPL_FUNC(PluginsList, plugin_manager, get_installed_plugins_list) () {
    return PluginsList({"plugin1", "plugin2", "plugin3"});
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
    return m_plugin_registrator->register_plugin(plugin_name);
}

MIDF_IMPL_FUNC(PluginsList, plugin_manager, get_registered_plugins_list) () {
    return m_plugin_registrator->get_registered_plugins_list();
}

MIDF_IMPL_FUNC(bool, plugin_manager, register_function, std::string, std::string, PluginFunction, midf::JsonAsVar)
(std::string plugin_name, std::string function_name, PluginFunction func, midf::JsonAsVar func_description/*json*/) {
    return m_plugin_registrator->register_function(plugin_name, function_name, func, func_description);
}

MIDF_IMPL_FUNC(bool, plugin_manager, unregister_plugin, std::string) (std::string plugin_name) {
    return m_plugin_registrator->unregister_plugin(plugin_name);
}

// interface to interract with the plugins
MIDF_IMPL_FUNC(midf::JsonAsRet, plugin_manager, get_plugin_info, std::string) (std::string plugin_name) {
    return m_plugin_registrator->get_plugin_info(plugin_name);
}

MIDF_IMPL_FUNC(midf::JsonAsRet, plugin_manager, get_function_info, std::string, std::string)
(std::string plugin_name, std::string function_name) {
    return m_plugin_registrator->get_function_info(plugin_name, function_name);
}

MIDF_IMPL_FUNC(PluginFunction, plugin_manager, get_function, std::string, std::string) (std::string plugin_name, std::string function_name) {
    return m_plugin_registrator->get_function(plugin_name, function_name);
}

MIDF_IMPL_FUNC(bool, plugin_manager, function_exists, std::string, std::string)
(std::string plugin_name, std::string function_name) {
    return m_plugin_registrator->function_exists(plugin_name, function_name);
}

void start_plugin_manager_async(std::shared_ptr<PluginRegistrator> plugin_registrator) {
    m_plugin_registrator = plugin_registrator;
    START_MIDF_SERVER(plugin_manager);
}
