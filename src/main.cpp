#include <log.h>
#include <mcpelauncher/minecraft_utils.h>
#include <mcpelauncher/crash_handler.h>
#include <mcpelauncher/path_helper.h>
#include <minecraft/Common.h>
#include <mcpelauncher/app_platform.h>
#include "server_properties.h"

int main(int argc, char *argv[]) {
    CrashHandler::registerCrashHandler();
    MinecraftUtils::workaroundLocaleBug();
    MinecraftUtils::setupForHeadless();

    ServerProperties props;
    props.load();

    Log::trace("Launcher", "Loading Minecraft library");
    void* handle = MinecraftUtils::loadMinecraftLib();
    Log::info("Launcher", "Loaded Minecraft library");

    Log::debug("Launcher", "Minecraft is at offset 0x%x", MinecraftUtils::getLibraryBase(handle));
    MinecraftUtils::initSymbolBindings(handle);
    Log::info("Launcher", "Game version: %s", Common::getGameVersionStringNet().c_str());

    Log::info("Launcher", "Applying patches");
    // Patches go here

    Log::trace("Launcher", "Initializing AppPlatform (vtable)");
    LauncherAppPlatform::initVtable(handle);
    Log::trace("Launcher", "Initializing AppPlatform (create instance)");
    std::unique_ptr<LauncherAppPlatform> appPlatform (new LauncherAppPlatform());
    Log::trace("Launcher", "Initializing AppPlatform (initialize call)");
    appPlatform->initialize();

    //

    MinecraftUtils::workaroundShutdownCrash(handle);
    return 0;
}
