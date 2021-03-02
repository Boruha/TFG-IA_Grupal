#include <engineGL/EngineManager.hpp>

#include <cstdlib>
#include <iostream>

namespace eGL {

static void glfw_error_callback(int error, const char* description) {
    fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}

  
EngineManager::EngineManager(int win_w, int win_h, const char* name) {
//OpenGL & GLFW
    // Setup window
    glfwSetErrorCallback(glfw_error_callback);
    if (!glfwInit())
        std::exit(EXIT_FAILURE);

    // GL v3.0 + GLSL v130 versions
    const char* glsl_version = "#version 130";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    
    display_w = win_w;
    display_h = win_h;
    window    = glfwCreateWindow(win_w, win_h, name, NULL, NULL);
    
    if (window == NULL) {
        fprintf(stderr, "Failed to create a window!\n");
        std::exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Enable vsync

    if (gl3wInit() != 0) {
        fprintf(stderr, "Failed to initialize OpenGL loader!\n");
        std::exit(EXIT_FAILURE);
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
EngineManager::drawRectFilled(int pos_x, int pos_y, int size_x, int size_y, int color) noexcept {
    const auto* viewport = ImGui::GetMainViewport();

    // Use work area to avoid menu-bar/task-bar, if any!
    auto work_pos = viewport->WorkPos;
    auto pos      = ImVec2(work_pos.x + pos_x, work_pos.y + pos_y);
    auto bg_draw  = ImGui::GetBackgroundDrawList();
  
    bg_draw->AddRectFilled(pos, ImVec2(pos.x + size_x, pos.y + size_y), color);
}

}