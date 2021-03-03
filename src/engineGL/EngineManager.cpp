#include <engineGL/EngineManager.hpp>

#include <iostream>

namespace eGL {

//static void glfw_error_callback(int error, const char* description) {
//    fprintf(stderr, "Glfw Error %d: %s\n", error, description);
//}


EngineManager::EngineManager(int win_w, int win_h, const char* name) {
//OpenGL & GLFW
    // Setup window
    glfwSetErrorCallback( [](int error, const char* description) {
        std::cout << "GLFW Error " << error << " : " << description << "\n";
    });

    if (!glfwInit())
        std::terminate();

    // GL v3.0 + GLSL v130 versions
    constexpr const char* glsl_version = "#version 130";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    
    display_w = win_w;
    display_h = win_h;
    window    = glfwCreateWindow(win_w, win_h, name, NULL, NULL);
    
    if (window == nullptr) {
        std::cout << "Failed to create a window!\n";
        std::terminate();
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Enable vsync

    if (gl3wInit() != 0) {
        std::cout << "Failed to initialize OpenGL loader!\n";
        std::terminate();
    }

//Dear ImGui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::StyleColorsDark();

    // Bind/Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);
}

EngineManager::~EngineManager() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();
}

void 
EngineManager::render() noexcept {
    ImGui::Render();
    
    glfwGetFramebufferSize(window, &display_w, &display_h);
    glViewport(0, 0, display_w, display_h);
   
    glClearColor(red, green, blue, alpha);
    glClear(GL_COLOR_BUFFER_BIT);
    
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    glfwSwapBuffers(window);
}

void 
EngineManager::start_frame() noexcept {
    // inputs, window resize, etc...
    glfwPollEvents();
    // Start the Dear ImGui frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

bool
EngineManager::shouldClose() noexcept {
    return glfwWindowShouldClose(window);
}


constexpr const std::tuple<int, int> 
EngineManager::getWindowSize() const noexcept {
    return { display_w, display_h };
}

void 
EngineManager::drawRectFilled(uint32_t pos_x, uint32_t pos_y, uint32_t size_x, uint32_t size_y, uint32_t color) noexcept {
    const auto* viewport = ImGui::GetMainViewport();
    auto bg_draw         = ImGui::GetBackgroundDrawList();
    auto work_pos        = viewport->WorkPos;
  
    bg_draw->AddRectFilled(ImVec2(work_pos.x + pos_x, work_pos.y + pos_y), ImVec2(pos_x + size_x, pos_y + size_y), color);
}


void 
EngineManager::drawLine(uint32_t p1_x, uint32_t p1_y, uint32_t p2_x, uint32_t p2_y, uint32_t color) noexcept {
    const auto* viewport = ImGui::GetMainViewport();
    auto bg_draw         = ImGui::GetBackgroundDrawList();
    auto work_pos        = viewport->WorkPos;

    bg_draw->AddLine(ImVec2(work_pos.x + p1_x, work_pos.y + p1_y), ImVec2(work_pos.x + p2_x, work_pos.y + p2_y), color);  
}


} //NS