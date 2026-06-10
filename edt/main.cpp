#include <iostream>
#include <window_manager.h>
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

ImGuiContext* context;


void updateImGui(float dt) {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    
    ImGui::Begin("Test");
    ImGui::Text("Hello World!");
    ImGui::End();
    
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    
}

void updateImGui2(float dt) {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    // ImGui::Begin("Test2");
    // ImGui::Text("Hello David!");
    // ImGui::End();
    ImGui::ShowDemoWindow();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

}

AppWindow* main_window;
AppWindow* secondary_window;


int main()
{
    WindowManager::init();
    main_window = WindowManager::addWindow();
    secondary_window = WindowManager::addWindow();

    IMGUI_CHECKVERSION();
    context = ImGui::CreateContext();

    ImGui::StyleColorsDark();

    ImGui::SetCurrentContext(context);
    ImGui_ImplGlfw_InitForOpenGL(main_window->window, true);
    ImGui_ImplOpenGL3_Init("#version 460");

    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;


    WindowManager::on_update.subscribe(updateImGui);
    WindowManager::on_update.subscribe(updateImGui2);

    WindowManager::run();

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    return 0;
}


