#pragma once

#include <string>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

// class that loads and parses the config file
class ServiceConfig {
public:
    ServiceConfig(const std::string& config_file_path = "/etc/plugin-manager/config.json") {
        boost::property_tree::read_json(config_file_path, config);
    }

    std::string get_remote_url() {
        return config.get<std::string>("remote_url");
    }

private:
    boost::property_tree::ptree config;
};
