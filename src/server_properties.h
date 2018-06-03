#pragma once

#include <properties/property.h>
#include <fstream>
#include <mcpelauncher/path_helper.h>

namespace {

using namespace properties;

class ServerProperties {

public:
    property_list properties;
    property<std::string> worldDir;
    property<std::string> worldName;

    ServerProperties() :
            worldDir (properties, "level-dir", "world"),
            worldName (properties, "level-name", "world") {
    }

    void load() {
        std::ifstream propertiesFile("server.properties");
        if (propertiesFile) {
            properties.load(propertiesFile);
        } else {
            try {
                propertiesFile.open(PathHelper::findDataFile("server.properties"));
                if (propertiesFile) {
                    properties.load(propertiesFile);
                    return;
                }
            } catch (std::runtime_error& e) {
            }
            save();
        }
    }

    void save() {
        std::ofstream propertiesFile(PathHelper::getPrimaryDataDirectory() + "server.properties");
        properties.save(propertiesFile);
    }

};

}