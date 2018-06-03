#pragma once

#include <properties/property.h>
#include <fstream>
#include <mcpelauncher/path_helper.h>
#include <minecraft/Level.h>

namespace {

using namespace properties;

class ServerProperties {

public:
    property_list properties;
    property<std::string> worldDir;
    property<std::string> worldName;
    property<int> worldGenerator;
    property<std::string> motd;
    property<std::string> worldSeed;
    property<int> gamemode;
    property<bool> forceGamemode;
    property<int> difficulty;
    property<int> port;
    property<int> portV6;
    property<int> maxPlayers;
    property<int> viewDistance;
    property<bool> onlineMode;
    property<float> playerIdleTimeout;

    ServerProperties() :
            worldDir (properties, "level-dir", "world"),
            worldName (properties, "level-name", "world"),
            worldSeed (properties, "level-seed", std::to_string(Level::createRandomSeed())),
            worldGenerator (properties, "level-generator", 1),
            motd (properties, "motd", "A Minecraft Server"),
            gamemode (properties, "gamemode", 0),
            forceGamemode (properties, "force-gamemode", false),
            difficulty (properties, "difficulty", 0),
            port (properties, "server-port", 19132),
            portV6 (properties, "server-port-v6", 19133),
            maxPlayers (properties, "max-players", 20),
            viewDistance (properties, "view-distance", 22),
            onlineMode (properties, "online-mode", true),
            playerIdleTimeout (properties, "player-idle-timeout", 0.f) {
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