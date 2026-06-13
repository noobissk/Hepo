#include <iostream>
#include <window_manager.h>
#include <scene_manager.h>
#include <memory/scene_serializer.h>
#include <name_component.h>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

// #include <components/name_component.h>
// #include <src/scene_manager.h>
// int main() {
//     std::cout << "Hello world!" << std::endl;
//     Scene& scene = getCurrentScene();
//     std::cout << "DS name -> " << scene.name << std::endl;
//     Entity player = scene.createEntity();
//     auto name_components = scene.getStorage<NameComponent>();
//     name_components.add(player, NameComponent("David"));
//     std::cout << "Player name -> " << name_components.get(player)->name << std::endl;
//     std::cout << "\nPlease rename the player\nnew name: "; std::cin >> name_components.get(player)->name ;
//     std::cout << "Player name changed to -> " << name_components.get(player)->name << std::endl;
//     return 0;
// }

void DemoScene() {
    std::cout << "Hello world!" << std::endl;
    Scene& scene = getCurrentScene();
    std::cout << "DS name -> " << scene.name << std::endl;
    Entity player = scene.createEntity();
    scene.addComponent(player, NameComponent("David"));
    NameComponent* name_component = scene.getComponent<NameComponent>(player);
    std::cout << "Player name -> " << name_component->name << std::endl;
    std::cout << "\nPlease rename the player\nnew name: "; std::cin >> name_component->name ;
    std::cout << "Player name changed to -> " << name_component->name << std::endl;
    SceneSerializer::saveScene(scene);
}

ImGuiContext* context;
ImGuiIO* io;



void updateImGui(float dt) {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    ImGui::DockSpaceOverViewport(
        0,
        ImGui::GetMainViewport(),
        ImGuiDockNodeFlags_None
    );

    ImGui::Begin("Hierarchy");
    ImGui::Text("Hello");
    ImGui::End();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    if (io->ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        GLFWwindow* backup = glfwGetCurrentContext();

        ImGui::UpdatePlatformWindows();
        ImGui::RenderPlatformWindowsDefault();

        glfwMakeContextCurrent(backup);
    }

}

AppWindow* main_window;
AppWindow* secondary_window;


int main()
{
    DemoScene();
    WindowManager::init();
    main_window = WindowManager::addWindow();

    IMGUI_CHECKVERSION();
    context = ImGui::CreateContext();
    ImGui::SetCurrentContext(context);

    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(main_window->window, true);
    ImGui_ImplOpenGL3_Init("#version 460");

    io = &ImGui::GetIO();
    io->ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
    io->ConfigFlags |= ImGuiConfigFlags_DockingEnable;

    ImGuiStyle& style = ImGui::GetStyle();

    if (io->ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        style.WindowRounding = 0.0f;
        style.Colors[ImGuiCol_WindowBg].w = 1.0f;
    }


    WindowManager::on_update.subscribe(updateImGui);

    WindowManager::run();

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext(context);

    return 0;
}


