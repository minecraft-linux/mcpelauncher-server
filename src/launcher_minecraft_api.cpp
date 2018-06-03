#include <hybris/dlfcn.h>
#include <mcpelauncher/path_helper.h>
#include "launcher_minecraft_api.h"

LauncherMinecraftApi::LauncherMinecraftApi(void* handle) {
    vtable = (void**) hybris_dlsym(handle, "_ZTVN9minecraft3api3ApiE") + 2;
    envPath = PathHelper::getWorkingDir();
    playerIfaceVtable = (void**) hybris_dlsym(handle, "_ZTVN9minecraft3api15PlayerInterfaceE") + 2;
    entityIfaceVtable = (void**) hybris_dlsym(handle, "_ZTVN9minecraft3api15EntityInterfaceE") + 2;
    networkIfaceVtable = (void**) hybris_dlsym(handle, "_ZTVN9minecraft3api16NetworkInterfaceE") + 2;
    playerInteractionsIfaceVtable = (void**) hybris_dlsym(handle, "_ZTVN9minecraft3api26PlayerInteractionInterfaceE") + 2;
}