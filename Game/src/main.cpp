#include "Engine/Application.hpp"
#include "Engine/ApplicationConfig.hpp"

int main() {
    ApplicationConfig config;
    config.WindowWidth = 1920;
    config.WindowHeight = 1080;
    config.WindowTitle = "MinecraftCPP";

    Application app(config);
    app.Run();
}