//
// Created by erico on 17/01/2020.
//

#include "imgui.h"
#include "imgui_impl_sdl.h"
#include "imgui_impl_opengl2.h"
#include <stdio.h>
#include <SDL.h>
#include <SDL_opengl.h>
#include <fstream>
#include <string>
#include <iostream>
#include "DroidSans.h"
#include "AgsConfigCore.h"

int ClampInt(int value, int min, int max) {
    if (value > max) return max;
    else if (value < min) return min;
    return value;
}

// Main code
int main(int, char**)
{
    // Setup SDL
    // (Some versions of SDL before <2.0.10 appears to have performance/stalling issues on a minority of Windows systems,
    // depending on whether SDL_INIT_GAMECONTROLLER is enabled or disabled.. updating to latest version of SDL is recommended!)
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER) != 0)
    {
        printf("Error: %s\n", SDL_GetError());
        return -1;
    }

    // Setup window
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
    SDL_WindowFlags window_flags = (SDL_WindowFlags)(SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);

    // Query default monitor resolution
    float ddpi, hdpi, vdpi;
    if (SDL_GetDisplayDPI(0, &ddpi, &hdpi, &vdpi) != 0) {
        fprintf(stderr, "Failed to obtain DPI information for display 0: %s\n", SDL_GetError());
        exit(1);
    }
    float dpi_scaling = ddpi / 72.f;
    SDL_Rect display_bounds;
    if (SDL_GetDisplayUsableBounds(0, &display_bounds) != 0) {
        fprintf(stderr, "Failed to obtain bounds of display 0: %s\n", SDL_GetError());
        exit(1);
    }
    int win_w = ClampInt( (int)(dpi_scaling*580),display_bounds.w * 3 / 8, display_bounds.w * 7 / 8);
    int win_h = ClampInt( (int)(dpi_scaling*580),display_bounds.h * 4 / 8, display_bounds.h * 7 / 8);

    AgsConfigCore agsConfig;

    SDL_Window* window = SDL_CreateWindow(agsConfig.GetTitleText().c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, win_w, win_h, window_flags);
    SDL_GLContext gl_context = SDL_GL_CreateContext(window);
    SDL_GL_MakeCurrent(window, gl_context);
    SDL_GL_SetSwapInterval(1); // Enable vsync

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    // Setup Dear ImGui style
    ImGui::StyleColorsLight();
    //ImGui::StyleColorsClassic();

    ImGuiStyle& style = ImGui::GetStyle();
    ImGuiIO& io = ImGui::GetIO();

    style.ScaleAllSizes(dpi_scaling);
    io.FontGlobalScale = dpi_scaling*0.5; // this makes the font looks crispy
    io.DisplayFramebufferScale = {dpi_scaling, dpi_scaling};

    // Load Fonts
    // - If no fonts are loaded, dear imgui will use the default font. You can also load multiple fonts and use ImGui::PushFont()/PopFont() to select them.
    // - AddFontFromFileTTF() will return the ImFont* so you can store it if you need to select the font among multiple.
    // - If the file cannot be loaded, the function will return NULL. Please handle those errors in your application (e.g. use an assertion, or display an error and quit).
    // - The fonts will be rasterized at a given size (w/ oversampling) and stored into a texture when calling ImFontAtlas::Build()/GetTexDataAsXXXX(), which ImGui_ImplXXXX_NewFrame below will call.
    // - Read 'libs/imgui/docs/FONTS.txt' for more instructions and details.
    // - Remember that in C/C++ if you want to include a backslash \ in a string literal you need to write a double backslash \\ !
    //io.Fonts->AddFontDefault();
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/Roboto-Medium.ttf", 16.0f);
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/Cousine-Regular.ttf", 15.0f);
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/DroidSans.ttf", 16.0f);
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/ProggyTiny.ttf", 10.0f);
    //ImFont* font = io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\ArialUni.ttf", 18.0f, NULL, io.Fonts->GetGlyphRangesJapanese());
    //IM_ASSERT(font != NULL);
    ImFontConfig fontConfig;
    fontConfig.OversampleH = 6;
    fontConfig.OversampleV = 3;
    fontConfig.SizePixels = dpi_scaling * 12.0f * 2.0;
    io.Fonts->AddFontFromMemoryCompressedTTF(DroidSans_compressed_data,DroidSans_compressed_size,dpi_scaling * 12.0f*2.0, &fontConfig); // times 2 here is due FontGlobalScale
    io.Fonts->Build();

    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    int hspacing = 8;
    int vspacing = 6;

    style.DisplaySafeAreaPadding = ImVec2(0, 0);
    style.WindowPadding = ImVec2(hspacing/2, vspacing);
    style.FramePadding = ImVec2(hspacing, vspacing);
    style.ItemSpacing = ImVec2(hspacing, vspacing);
    style.ItemInnerSpacing = ImVec2(hspacing, vspacing);
    style.IndentSpacing = 20.0f;

    style.WindowRounding = 0.0f;
    style.FrameRounding = 0.0f;

    style.WindowBorderSize = 0.0f;
    style.FrameBorderSize = 1.0f;
    style.PopupBorderSize = 1.0f;

    style.ScrollbarSize = 20.0f;
    style.ScrollbarRounding = 0.0f;
    style.GrabMinSize = 14.0f;
    style.GrabRounding = 0.0f;

    ImVec4 white = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
    ImVec4 transparent = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    ImVec4 dark = ImVec4(0.00f, 0.00f, 0.00f, 0.20f);
    ImVec4 darker = ImVec4(0.00f, 0.00f, 0.00f, 0.50f);

    ImVec4 background = ImVec4(0.95f, 0.95f, 0.95f, 1.00f);
    ImVec4 text = ImVec4(0.10f, 0.10f, 0.10f, 1.00f);
    ImVec4 border = ImVec4(0.60f, 0.60f, 0.60f, 1.00f);
    ImVec4 grab = ImVec4(0.69f, 0.69f, 0.69f, 1.00f);
    ImVec4 header = ImVec4(0.86f, 0.86f, 0.86f, 1.00f);
    ImVec4 active = ImVec4(0.00f, 0.47f, 0.84f, 1.00f);
    ImVec4 hover = ImVec4(0.00f, 0.47f, 0.84f, 0.20f);

    style.Colors[ImGuiCol_Text] = text;
    style.Colors[ImGuiCol_WindowBg] = background;
    style.Colors[ImGuiCol_ChildBg] = background;
    style.Colors[ImGuiCol_PopupBg] = white;

    style.Colors[ImGuiCol_Border] = border;
    style.Colors[ImGuiCol_BorderShadow] = transparent;

    style.Colors[ImGuiCol_Button] = header;
    style.Colors[ImGuiCol_ButtonHovered] = hover;
    style.Colors[ImGuiCol_ButtonActive] = active;

    style.Colors[ImGuiCol_FrameBg] = white;
    style.Colors[ImGuiCol_FrameBgHovered] = hover;
    style.Colors[ImGuiCol_FrameBgActive] = active;

    style.Colors[ImGuiCol_MenuBarBg] = header;
    style.Colors[ImGuiCol_Header] = header;
    style.Colors[ImGuiCol_HeaderHovered] = hover;
    style.Colors[ImGuiCol_HeaderActive] = active;

    style.Colors[ImGuiCol_CheckMark] = text;
    style.Colors[ImGuiCol_SliderGrab] = grab;
    style.Colors[ImGuiCol_SliderGrabActive] = darker;

    style.Colors[ImGuiCol_ScrollbarBg] = header;
    style.Colors[ImGuiCol_ScrollbarGrab] = grab;
    style.Colors[ImGuiCol_ScrollbarGrabHovered] = dark;
    style.Colors[ImGuiCol_ScrollbarGrabActive] = darker;


    // Setup Platform/Renderer bindings
    ImGui_ImplSDL2_InitForOpenGL(window, gl_context);
    ImGui_ImplOpenGL2_Init();

    bool runTheGameBeforeQuit = false;
    bool saveBeforeQuit = false;
    //ImGuiStyle::ScaleAllSizes(0.5f);

    // Our state
    ImVec4 clear_color = ImVec4(0.0f, 0.0f, 0.0f, 1.00f);

    // Main loop
    bool done = false;
    while (!done)
    {
        // Poll and handle events (inputs, window resize, etc.)
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            ImGui_ImplSDL2_ProcessEvent(&event);
            if (event.type == SDL_QUIT)
                done = true;
        }

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL2_NewFrame();
        ImGui_ImplSDL2_NewFrame(window);
        ImGui::NewFrame();

        int width, height;
        SDL_GetWindowSize(window, &width, &height);

        if(ImGui::BeginMainMenuBar()){
            if(ImGui::BeginMenu("File", true)){
                if(ImGui::MenuItem("Reset Config to Game Default")){
                    agsConfig.ResetConfigToGameDefault();
                }
                if(ImGui::MenuItem("Reset Config to Current")){
                    agsConfig.ResetConfigToCurrent();
                }

                if(ImGui::MenuItem("Reset Window Size")){
                    SDL_SetWindowSize(window, win_w, win_h);
                }
                if(ImGui::MenuItem("Exit and Save")){
                    saveBeforeQuit = true;
                    break;
                }
                if(ImGui::MenuItem("Exit")){
                    break;
                }
                ImGui::EndMenu();
            }
            ImGui::EndMainMenuBar();
        }
        ImVec2 menuSize = ImGui::GetItemRectSize();

        ImGui::SetNextWindowPos(ImVec2(.0f, menuSize.y+.0f), ImGuiCond_Always);
        ImGui::SetNextWindowSize(ImVec2(width+2, -menuSize.y+height+2), ImGuiCond_Always);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);

        ImGui::Begin("AGS Config",nullptr,ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse );
        ImGui::PopStyleVar();
        ImGui::PopStyleVar();

        ImGui::SetNextTreeNodeOpen(true,ImGuiCond_Once);
        if(ImGui::TreeNode("Graphics options")) {
            ImGui::Text("Native game resolution: %d x %d", agsConfig.GetNativeResolutionWidth(),agsConfig.GetNativeResolutionHeight());
            ImGui::Text("Native game color depth: %d", agsConfig.GetNativeColorDepth());

            if (ImGui::BeginCombo("Driver", agsConfig.GetGraphicsDriver().c_str())) {
                vector<string>::iterator it;
                for (it = agsConfig.GetOptionsGraphicsDriver()->begin();
                     it != agsConfig.GetOptionsGraphicsDriver()->end();
                     it++) {

                    if (ImGui::Selectable(it->c_str()))  agsConfig.SetGraphicsDriver(*it);
                }
                ImGui::EndCombo();
            }

            ImGui::Checkbox("Start in windowed mode", agsConfig.GraphicsWindowed);

            if (ImGui::BeginCombo("Fullscreen scale", agsConfig.GetFullscreenScale().c_str())) {
                vector<string>::iterator it;
                for (it = agsConfig.GetOptionsFullscrenScaling()->begin();
                     it != agsConfig.GetOptionsFullscrenScaling()->end();
                     it++) {

                    if (ImGui::Selectable(it->c_str())) agsConfig.SetFullscreenScale(*it);
                }
                ImGui::EndCombo();
            }

            if (ImGui::BeginCombo("Windowed scale",  agsConfig.GetWindowedScale().c_str())) {
                vector<string>::iterator it;
                for (it = agsConfig.GetOptionsWindowedScaling()->begin();
                     it != agsConfig.GetOptionsWindowedScaling()->end();
                     it++) {

                    if (ImGui::Selectable(it->c_str())) agsConfig.SetWindowedScale(*it);
                }
                ImGui::EndCombo();
            }

            if (ImGui::BeginCombo("Filter", agsConfig.GetGraphicsFilter().c_str())) {
                vector<string>::iterator it;
                for (it = agsConfig.GetOptionsFilter()->begin();
                     it != agsConfig.GetOptionsFilter()->end();
                     it++) {

                    if (ImGui::Selectable(it->c_str())) agsConfig.SetGraphicsFilter(*it);
                }
                ImGui::EndCombo();
            }

            if (ImGui::BeginCombo("Sprite Cache Maximum Size", agsConfig.GetSpriteCacheMaxSize().c_str())) {
                for (unsigned int i = 0;
                     i < agsConfig.GetOptionsSpriteCache()->size();
                     i++) {

                    if (ImGui::Selectable( (*(agsConfig.GetOptionsSpriteCache()))[i].c_str()))
                        agsConfig.SetSpriteCacheMaxSize((*(agsConfig.GetOptionsSpriteCacheValue()))[i]);
                }
                ImGui::EndCombo();
            }

            ImGui::Checkbox("Vertical Sync", agsConfig.GraphicsVsync);
            ImGui::Checkbox("Render sprites at screen resolution", agsConfig.GraphicsRenderAtScreenResolution);
            ImGui::Checkbox("Match Device Ratio", agsConfig.GraphicsMatchDeviceRatio);
            ImGui::TreePop();
        }

        ImGui::Separator();

        ImGui::SetNextTreeNodeOpen(true,ImGuiCond_Once);
        if(ImGui::TreeNode("Sound options")) {
            if (ImGui::BeginCombo("Sound Driver", agsConfig.GetSoundDriver().c_str() )) {
                vector<string>::iterator it;
                for (it = agsConfig.GetOptionsSoundDigiid()->begin();
                     it != agsConfig.GetOptionsSoundDigiid()->end();
                     it++) {

                    if (ImGui::Selectable(it->c_str()))  agsConfig.SetSoundDriver(*it);
                }

                ImGui::EndCombo();
            }

            if (ImGui::BeginCombo("MIDI Driver", agsConfig.GetMidiDriver().c_str() )) {
                vector<string>::iterator it;
                for (it = agsConfig.GetOptionsSoundMidiid()->begin();
                     it != agsConfig.GetOptionsSoundMidiid()->end();
                     it++) {

                    if (ImGui::Selectable(it->c_str())) agsConfig.SetMidiDriver(*it);
                }

                ImGui::EndCombo();
            }

            ImGui::Checkbox("Threaded Audio", agsConfig.SoundThreaded);
            ImGui::Checkbox("Use speech pack", agsConfig.SoundUsesSpeechPack);
            ImGui::TreePop();
        }

        ImGui::Separator();

        ImGui::SetNextTreeNodeOpen(true,ImGuiCond_Once);
        if(ImGui::TreeNode("Mouse options")) {
            ImGui::SliderFloat("Mouse speed", agsConfig.MouseSpeed,0.1f,10.0f,"%.1f"); //may not work depending on locale in ags
            ImGui::TreePop();
        }

        ImGui::Separator();

        if(ImGui::Button("Save and Exit")) {
            saveBeforeQuit = true;
            break;
        };
        ImGui::SameLine();
        if(ImGui::Button("Save and Run")) {
            saveBeforeQuit = true;
            runTheGameBeforeQuit = true;
            break;
        }
        ImGui::SameLine();
        if(ImGui::Button("Cancel")) break;

        ImGui::End();

        // Rendering
        ImGui::Render();
        glViewport(0, 0, (int)io.DisplaySize.x, (int)io.DisplaySize.y);
        glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT);
        //glUseProgram(0); // You may want this if using this code in an OpenGL 3+ context where shaders may be bound
        ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());
        SDL_GL_SwapWindow(window);
    }

    if(saveBeforeQuit){
        agsConfig.SaveConfig();
    }

    if(runTheGameBeforeQuit){
        agsConfig.RunGame();
    }

    // Cleanup
    ImGui_ImplOpenGL2_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();

    SDL_GL_DeleteContext(gl_context);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}

#ifdef _WIN32
int APIENTRY WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
	return main(__argc, __argv);
}
#endif