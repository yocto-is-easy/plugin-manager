#pragma once

#include <string>
#include <filesystem>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

namespace fs = std::filesystem;

// class that loads and parses the config file
class ServiceConfig {
public:
    ServiceConfig(const std::string& config_file_path = "/etc/plugin-manager/config.json") {
        if (fs::exists(config_file_path)) {
            boost::property_tree::read_json(config_file_path, config);    
        } else {
            fs::create_directories(fs::path(config_file_path).parent_path());
        }
    }

    std::string get_remote_url() {
        return config.get<std::string>("remote_url");
    }

private:
    boost::property_tree::ptree config;
};
