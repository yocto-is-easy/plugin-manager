#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <map>

#include "i-plugin-manager.hpp"

#include <nlohmann/json.hpp>
#include <spdlog/spdlog.h>

#include <supervisor.hpp>

using namespace nlohmann;

struct FunctionArgumentInfo {
    std::string name;
    std::string type;
    std::string description; // optional
};

struct FunctionReturnInfo {
    std::string type;
    std::string description; // optional
};

struct PluginFunctionInfo {
    std::string name;
    std::string description; // optional
    FunctionReturnInfo return_type;
    std::vector<FunctionArgumentInfo> arguments;
    PluginFunction func;
};

struct PluginInfo {
    std::string name;
    std::string description;
    std::string version;
    std::string author;
    std::string license;
    std::vector<PluginFunctionInfo> functions;
};

class PluginRegistrator {
private:
    std::map<std::string, PluginInfo> m_plugins;

public:
    PluginRegistrator() = default;
    ~PluginRegistrator() = default;

    bool register_plugin(std::string plugin_name) {
        spdlog::info("PluginRegistrator::register_plugin: {}", plugin_name);
        
        if (m_plugins.find(plugin_name) != m_plugins.end()) {
            spdlog::error("PluginRegistrator::register_plugin: plugin {} already registered", plugin_name);
            return false;
        }

        PluginInfo plugin_info;
        plugin_info.name = plugin_name;
        plugin_info.description = "None";
        plugin_info.version = "None";
        plugin_info.author = "None";
        plugin_info.license = "None";
        m_plugins.insert({plugin_name, plugin_info});

        spdlog::info("PluginRegistrator::register_plugin: plugin {} registered", plugin_name);
        return true;
    }

    /* 
     * Function description json example:
     *
     * func_description: {
     *    "description": "function description",
     *    "return":
     *    {
     *       "type": "int",
     *       "description": "return description"
     *    },
     *    }
     *    "arguments": [
     *    {
     *        "name": "arg1",
     *        "type": "int",
     *        "description": "arg1 description"
     *    },
     *    {
     *        "name": "arg2",
     *        "type": "float",
     *        "description": "arg2 description"
     *    }
     *    ]
     * }
     */
    bool register_function(std::string plugin_name,
                           std::string function_name,
                           PluginFunction func,
                           midf::JsonAsVar func_description) {
        spdlog::info("PluginRegistrator::register_function: {}, {}, {}", plugin_name, function_name, func_description.get().dump());
        
        if (m_plugins.find(plugin_name) == m_plugins.end()) {
            spdlog::error("PluginRegistrator::register_function: plugin {} not registered", plugin_name);
            return false;
        }

        try {
            PluginFunctionInfo func_info;
            func_info.name = function_name;
            if(func_description.get().contains("description")) {
                func_info.description = func_description.get()["description"];
            }

            func_info.return_type.type = func_description.get()["return"]["type"];

            if(func_description.get()["return"].contains("description")) {
                func_info.return_type.description = func_description.get()["return"]["description"];
            }

            for (auto& arg : func_description.get()["arguments"]) {
                FunctionArgumentInfo arg_info;
                arg_info.name = arg["name"];
                arg_info.type = arg["type"];

                if(arg.contains("description")) {
                    arg_info.description = arg["description"];
                }

                func_info.arguments.push_back(arg_info);
            }
            func_info.func = func;

            m_plugins[plugin_name].functions.push_back(func_info);
        } catch (std::exception& e) {
            spdlog::error("PluginRegistrator::register_function: {}", e.what());
            return false;
        }

        spdlog::info("PluginRegistrator::register_function: function {} registered", function_name);
        return true;
    }

    std::vector<std::string> get_registered_plugins_list() {
        spdlog::info("PluginRegistrator::get_registered_plugins_list");
        
        std::vector<std::string> plugins_list;
        for (auto& plugin : m_plugins) {
            plugins_list.push_back(plugin.first);
        }

        spdlog::info("PluginRegistrator::get_registered_plugins_list: {}", plugins_list.size());
        return plugins_list;
    }

    bool unregister_plugin(std::string plugin_name) {
        spdlog::info("PluginRegistrator::unregister_plugin: {}", plugin_name);
        
        if (m_plugins.find(plugin_name) == m_plugins.end()) {
            spdlog::error("PluginRegistrator::unregister_plugin: plugin {} not registered", plugin_name);
            return false;
        }

        m_plugins.erase(plugin_name);

        spdlog::info("PluginRegistrator::unregister_plugin: plugin {} unregistered", plugin_name);
        return true;
    }

    midf::JsonAsRet get_plugin_info(std::string plugin_name) {
        spdlog::info("PluginRegistrator::get_plugin_info: {}", plugin_name);
        
        if (m_plugins.find(plugin_name) == m_plugins.end()) {
            spdlog::error("PluginRegistrator::get_plugin_info: plugin {} not registered", plugin_name);
            return midf::JsonAsRet();
        }

        midf::JsonAsRet plugin_info;
        plugin_info.get()["name"] = m_plugins[plugin_name].name;
        plugin_info.get()["description"] = m_plugins[plugin_name].description;
        plugin_info.get()["version"] = m_plugins[plugin_name].version;
        plugin_info.get()["author"] = m_plugins[plugin_name].author;
        plugin_info.get()["license"] = m_plugins[plugin_name].license;

        plugin_info.get()["functions"] = json::array();
        for (auto& func : m_plugins[plugin_name].functions) {
            json func_info;
            func_info["name"] = func.name;
            plugin_info.get()["functions"].push_back(func_info);
        }

        spdlog::info("PluginRegistrator::get_plugin_info: {}", plugin_info.get().dump());
        return plugin_info;
    }

    midf::JsonAsRet get_function_info(std::string plugin_name, std::string function_name) {
        spdlog::info("PluginRegistrator::get_function_info: {}, {}", plugin_name, function_name);
        
        if (m_plugins.find(plugin_name) == m_plugins.end()) {
            spdlog::error("PluginRegistrator::get_function_info: plugin {} not registered", plugin_name);
            return json::object({});
        }

        for (auto& func : m_plugins[plugin_name].functions) { // TODO: rewrite rue to changed structure
            if (func.name == function_name) {
                midf::JsonAsRet func_info;
                func_info.get()["name"] = func.name;
                
                func_info.get()["description"] = func.description;

                func_info.get()["return"]["type"] = func.return_type.type;
                func_info.get()["return"]["description"] = func.return_type.description;

                for (auto& arg : func.arguments) {
                    json arg_info;
                    arg_info["name"] = arg.name;
                    arg_info["type"] = arg.type;
                    arg_info["description"] = arg.description;
                    func_info.get()["arguments"].push_back(arg_info);
                }
                spdlog::info("PluginRegistrator::get_function_info: {}", func_info.get().dump());
                return func_info;
            }
        }

        spdlog::error("PluginRegistrator::get_function_info: function {} not registered", function_name);
        return json::object({});
    }

    PluginFunction get_function(std::string plugin_name, std::string function_name) {
        spdlog::info("PluginRegistrator::get_function: {}, {}", plugin_name, function_name);
        
        if (m_plugins.find(plugin_name) == m_plugins.end()) {
            spdlog::error("PluginRegistrator::get_function: plugin {} not registered", plugin_name);
            return PluginFunction();
        }

        for (auto& func : m_plugins[plugin_name].functions) {
            if (func.name == function_name) {
                spdlog::info("PluginRegistrator::get_function: function {} found", function_name);
                return func.func;
            }
        }

        spdlog::error("PluginRegistrator::get_function: function {} not registered", function_name);
        return PluginFunction();
    }

    bool function_exists(std::string plugin_name, std::string function_name) {
        spdlog::info("PluginRegistrator::function_exists: {}, {}", plugin_name, function_name);
        
        if (m_plugins.find(plugin_name) == m_plugins.end()) {
            spdlog::error("PluginRegistrator::function_exists: plugin {} not registered", plugin_name);
            return false;
        }

        for (auto& func : m_plugins[plugin_name].functions) {
            if (func.name == function_name) {
                spdlog::info("PluginRegistrator::function_exists: function {} found", function_name);
                return true;
            }
        }

        spdlog::error("PluginRegistrator::function_exists: function {} not registered", function_name);
        return false;
    }
};
