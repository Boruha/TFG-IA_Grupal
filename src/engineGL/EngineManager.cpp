#include <engineGL/EngineManager.hpp>

#include <iostream>

namespace eGL {

/* ENGINE SETUP */
EngineManager::EngineManager(int win_w, int win_h, const char* name) {
//OpenGL & GLFW
    glfwSetErrorCallback( [](int error, const char* description) {
        std::cout << "GLFW Error " << error << ": " << description << "\n";
    });

    if (!glfwInit())
        std::terminate();

    constexpr const char* glsl_version = "#version 130";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

    GLFWmonitor* monitor    = glfwGetPrimaryMonitor();
    const GLFWvidmode* mode = glfwGetVideoMode(monitor);
    
    glfwWindowHint(GLFW_RED_BITS, mode->redBits);
    glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
    glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
    glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);

    display_w = mode->width;
    display_h = mode->height;
    window    = glfwCreateWindow(display_w, display_h, name, monitor, NULL);
    
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


/* BASIC RENDER FUCTIONS
    - RENDER     : CLEANS, DRAWS ALL CONTENT IN NEW FRAME
    - START_FRAME: READS ALL WINDOW EVENTS AND SET NEW ITEAM LIST
*/
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


/* GETTERS
    - GET WINDOW STATUS
    - GET WINDOW DIMENSIONS
*/
bool
EngineManager::shouldClose() noexcept {
    return glfwWindowShouldClose(window);
}

constexpr const std::tuple<int, int> 
EngineManager::getWindowSize() const noexcept {
    return { display_w, display_h };
}

/* WIDGETS FUNTIONS AND SECUNDARY WINDOWS SETTERS
    - DRAW (FILL) RECTAGLES
    - DRAW LINES
    - OPEN A DEBUG INTERFACE
    - OPEN A GAMEPLAY INTERFACE
*/
void 
EngineManager::drawRect(uint32_t pos_x, uint32_t pos_y, uint32_t size_x, uint32_t size_y, uint32_t color, bool filled) noexcept {
    const auto* viewport = ImGui::GetMainViewport();
    auto bg_draw         = ImGui::GetBackgroundDrawList();
    auto work_pos        = viewport->WorkPos;
    auto p1              = ImVec2(work_pos.x + pos_x, work_pos.y + pos_y);
    
    if(filled)
        bg_draw->AddRectFilled(p1, ImVec2(p1.x + size_x, p1.y + size_y), color);
    else
        bg_draw->AddRect(p1, ImVec2(p1.x + size_x, p1.y + size_y), color);
}

void 
EngineManager::drawLine(uint32_t p1_x, uint32_t p1_y, uint32_t p2_x, uint32_t p2_y, uint32_t color) noexcept {
    const auto* viewport = ImGui::GetMainViewport();
    auto bg_draw         = ImGui::GetBackgroundDrawList();
    auto work_pos        = viewport->WorkPos;

    bg_draw->AddLine(ImVec2(work_pos.x + p1_x, work_pos.y + p1_y), ImVec2(work_pos.x + p2_x, work_pos.y + p2_y), color);  
}
/*
void 
EngineManager::drawMsg(uint32_t p1_x, uint32_t p1_y, std::string text) noexcept {
    const  auto* viewport = ImGui::GetMainViewport();
           auto  viewSize = viewport->Size;
    static auto  p_open   { true };
    
    ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoDecoration 
                                  | ImGuiWindowFlags_AlwaysAutoResize 
                                  | ImGuiWindowFlags_NoMove 
                                  | ImGuiWindowFlags_NoFocusOnAppearing 
                                  | ImGuiWindowFlags_NoNav;

    ImGui::SetNextWindowPos( ImVec2(p1_x, p1_y), ImGuiCond_Always );
    ImGui::SetNextWindowSize( ImVec2(viewSize.x/8, viewSize.y/8) );
    {
    ImGui::Begin(text.c_str(), &p_open, window_flags);
        ImGui::Text(text.c_str());
    ImGui::End();
    }   
}*/

void 
EngineManager::debugInterface(bool& showDebug, float& DT, float& LT, bool& changed) const noexcept {
    ImGui::SetNextWindowPos(ImVec2(0,0));
    ImGui::SetNextWindowSize(ImVec2(300,150));
    {
    ImGui::Begin("Debug controller");
        ImGui::Checkbox("Show Debug Vectors", &showDebug);
        if( ImGui::SliderFloat("DeltaTime", &DT, 1.f, 120.f, "%.2f", 1.f) )
            changed = true;
        if( ImGui::SliderFloat("LoopTime", &LT, 1.f, 120.f, "%.2f", 1.f) )
            changed = true;
        if( ImGui::SliderFloat("Both", &LT, 1.f, 120.f, "%.2f", 1.f) ) {
            DT = LT;
            changed = true;
        }
    ImGui::End();
    }
}

void
EngineManager::modeInterface(unsigned int& opc, unsigned int& frm) const noexcept {
     const auto* viewport = ImGui::GetMainViewport();
           auto  viewSize = viewport->Size;
    static auto  p_open   { true };
    
    ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoDecoration 
                                  | ImGuiWindowFlags_AlwaysAutoResize 
                                  | ImGuiWindowFlags_NoMove 
                                  | ImGuiWindowFlags_NoFocusOnAppearing 
                                  | ImGuiWindowFlags_NoNav;

    ImGui::SetNextWindowPos( ImVec2(1, viewSize.y - 1), ImGuiCond_Always, ImVec2(0.0,1.0) );
    ImGui::SetNextWindowSize( ImVec2(210, 150));
    {
    ImGui::Begin("escuadron", &p_open, window_flags);
        {
        if( ImGui::Selectable("Libre" , opc == 0u, ImGuiSelectableFlags_None, ImVec2(60, 60)) )
            opc = 0u;
        ImGui::SameLine();        
        if( ImGui::Selectable("Ataque", opc == 2u, ImGuiSelectableFlags_None, ImVec2(60, 60)) )
            opc = 2u;
        ImGui::SameLine();
        if( ImGui::Selectable("Huida" , opc == 5u, ImGuiSelectableFlags_None, ImVec2(60, 60)) )
            opc = 5u;
        }
        {
        if( ImGui::Selectable("Desordenado" , frm == 0u, ImGuiSelectableFlags_None, ImVec2(90, 60)) )
            frm = 0u;
        ImGui::SameLine();        
        if( ImGui::Selectable("Anillo", frm == 1u, ImGuiSelectableFlags_None, ImVec2(90, 60)) )
            frm = 1u;
        }
    ImGui::End();
    }
}

void 
EngineManager::minimap() noexcept {
    const  auto* viewport = ImGui::GetMainViewport();
           auto  viewSize = viewport->Size;
    static auto  p_open   { true };
    
    ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoDecoration 
                                  | ImGuiWindowFlags_AlwaysAutoResize 
                                  | ImGuiWindowFlags_NoMove 
                                  | ImGuiWindowFlags_NoFocusOnAppearing 
                                  | ImGuiWindowFlags_NoNav;

    ImGui::SetNextWindowPos( ImVec2(viewSize.x, viewSize.y), ImGuiCond_Always, ImVec2(1.0,1.0) );
    ImGui::SetNextWindowSize( ImVec2(viewSize.x/4, viewSize.y/4) );
    {
    ImGui::Begin("MiniMap boy", &p_open, window_flags);
    ImGui::End();
    }
}

void 
EngineManager::drawInMinimap(uint32_t pos_x, uint32_t pos_y, uint32_t size_x, uint32_t size_y, uint32_t color, bool filled) noexcept {
    {
    ImGui::Begin("MiniMap boy");
        auto  winPos   = ImGui::GetWindowPos();
        auto* drawList = ImGui::GetWindowDrawList();
        auto  p1       = ImVec2( winPos.x + (pos_x*fraction.x), winPos.y + (pos_y*fraction.y) );

        if(filled)
            drawList->AddRectFilled(p1, ImVec2(p1.x + (size_x*fraction.x), p1.y + (size_y*fraction.y)), color);
        else
            drawList->AddRect(p1, ImVec2(p1.x + (size_x*fraction.x), p1.y + (size_y*fraction.y)), color);
    ImGui::End();
    }

}

void 
EngineManager::setMiniMapFraction(int64_t world_x, int64_t world_y) noexcept {
    float WorldWindowRatio_x { static_cast<float>(display_w) / static_cast<float>(world_x) };
    float WorldWindowRatio_y { static_cast<float>(display_h) / static_cast<float>(world_y) };

    fraction = ImVec2(WorldWindowRatio_x/4.f, WorldWindowRatio_y/4.f);
}

} //NS