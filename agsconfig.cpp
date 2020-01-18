//
// Created by erico on 17/01/2020.
//

// dear imgui: standalone example application for SDL2 + OpenGL
// If you are new to dear imgui, see examples/README.txt and documentation at the top of imgui.cpp.
// (SDL is a cross-platform general purpose library for handling windows, inputs, OpenGL/Vulkan graphics context creation, etc.)

// **DO NOT USE THIS CODE IF YOUR CODE/ENGINE IS USING MODERN OPENGL (SHADERS, VBO, VAO, etc.)**
// **Prefer using the code in the example_sdl_opengl3/ folder**
// See imgui_impl_sdl.cpp for details.

#include "imgui.h"
#include "imgui_impl_sdl.h"
#include "imgui_impl_opengl2.h"
#include <stdio.h>
#include <SDL.h>
#include <SDL_opengl.h>
#include "inipp.h"
#include "AgsData.h"
#include "AgsTold.h"
#include <fstream>
#include <string>
#include <iostream>
#include "DroidSans.h"
#include "AgsConfigUtilStr.h"


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
    int win_w = display_bounds.w * 6 / 8;
    int win_h = display_bounds.h * 7 / 8;


    AgsTold agsTold;
    agsTold.InitFromTell("agsimgui_demo"); //TODO: do not hardcode this!!!!!!!!!

    AgsData agsData_default;
    AgsData agsData_global;
    AgsData agsData_user;
    agsData_default.LoadFromIni(agsTold.configPath._default);
    agsData_global.LoadFromIni(agsTold.configPath.global);
    agsData_user.LoadFromIni(agsTold.configPath.user);

    AgsData agsData_current;
    agsData_current.Reset();
    agsData_current.MergeIn(agsData_default);
    agsData_current.MergeIn(agsData_user);
    agsData_current.MergeIn(agsData_global);

    AgsData agsData = AgsData();
    agsData.SetSaneInitialValue();
    agsData.MergeIn(agsData_current);

    vector<string> scalingOptions = {"max_round", "stretch", "proportional", "1", "2", "3" };
    vector<string> soundOptionsDigiid = { "auto", "none", "ALSA", "ARTS", "ESSD", "JACK", "OSSD", "SGIA", "SDL" };
    vector<string> soundOptionsMidiid = { "auto","none","AMID", "OSSM"};
    vector<string> spriteCacheOptions = { "16 MB","32 MB","64 MB", "128 MB (default)","256 MB","512 MB"};
    vector<int> spriteCacheOptions_value = { 16*1024,32*1024,64*1024, 128*1024,256*1024,512*1024};


    SDL_Window* window = SDL_CreateWindow(agsTold.config_AT_misc.titletext.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, win_w, win_h, window_flags);
    SDL_GLContext gl_context = SDL_GL_CreateContext(window);
    SDL_GL_MakeCurrent(window, gl_context);
    SDL_GL_SetSwapInterval(1); // Enable vsync

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    ImGui::GetStyle().ScaleAllSizes(dpi_scaling);
    ImGui::GetIO().FontGlobalScale = dpi_scaling;
    ImGui::GetIO().DisplayFramebufferScale = {dpi_scaling, dpi_scaling};
    ImGui::GetIO().Fonts->AddFontFromMemoryCompressedTTF(DroidSans_compressed_data,DroidSans_compressed_size,dpi_scaling * 14.0f);

    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsLight();
    //ImGui::StyleColorsClassic();

    // Setup Platform/Renderer bindings
    ImGui_ImplSDL2_InitForOpenGL(window, gl_context);
    ImGui_ImplOpenGL2_Init();

    bool runTheGameBeforeQuit = false;
    bool saveBeforeQuit = false;
    //ImGuiStyle::ScaleAllSizes(0.5f);

    // Load Fonts
    // - If no fonts are loaded, dear imgui will use the default font. You can also load multiple fonts and use ImGui::PushFont()/PopFont() to select them.
    // - AddFontFromFileTTF() will return the ImFont* so you can store it if you need to select the font among multiple.
    // - If the file cannot be loaded, the function will return NULL. Please handle those errors in your application (e.g. use an assertion, or display an error and quit).
    // - The fonts will be rasterized at a given size (w/ oversampling) and stored into a texture when calling ImFontAtlas::Build()/GetTexDataAsXXXX(), which ImGui_ImplXXXX_NewFrame below will call.
    // - Read 'docs/FONTS.txt' for more instructions and details.
    // - Remember that in C/C++ if you want to include a backslash \ in a string literal you need to write a double backslash \\ !
    //io.Fonts->AddFontDefault();
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/Roboto-Medium.ttf", 16.0f);
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/Cousine-Regular.ttf", 15.0f);
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/DroidSans.ttf", 16.0f);
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/ProggyTiny.ttf", 10.0f);
    //ImFont* font = io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\ArialUni.ttf", 18.0f, NULL, io.Fonts->GetGlyphRangesJapanese());
    //IM_ASSERT(font != NULL);


    // Our state
    ImVec4 clear_color = ImVec4(0.0f, 0.0f, 0.0f, 1.00f);
    ImGuiStyle& style = ImGui::GetStyle();



        // Main loop
    bool done = false;
    while (!done)
    {
        // Poll and handle events (inputs, window resize, etc.)
        // You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
        // - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application.
        // - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application.
        // Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
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
        ImGui::SetNextWindowPos(ImVec2(.0f, .0f), ImGuiCond_Always);
        ImGui::SetNextWindowSize(ImVec2(width+2, height+2), ImGuiCond_Always);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
        static float f = 0.0f;
        static int counter = 0;



        ImGui::Begin("AGS Config",NULL,ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoMove |ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse );                          // Create a window called "Hello, world!" and append into it.
        ImGui::PopStyleVar();

        ImGui::SetNextTreeNodeOpen(true,ImGuiCond_Once);
        if(ImGui::TreeNode("Graphics options")) {
            ImGui::Text("Driver:");
            ImGui::SameLine();
            if (ImGui::BeginCombo("##driver", agsData.graphics.driver.value().c_str())) {
                vector<string>::iterator it;
                for (it = agsTold.graphicdriver.drivers.begin();
                     it != agsTold.graphicdriver.drivers.end();
                     it++) {

                    if (ImGui::Selectable(it->c_str())) agsData.graphics.driver = it->c_str();
                }

                ImGui::EndCombo();
            }

            ImGui::Checkbox("Start in windowed mode", &(agsData.graphics.windowed.value()));

            ImGui::Text("Fullscreen scale:");
            ImGui::SameLine();
            if (ImGui::BeginCombo("##Fullscreen scale", agsData.graphics.game_scale_fs.value().c_str())) {
                vector<string>::iterator it;
                for (it = scalingOptions.begin();
                     it != scalingOptions.end();
                     it++) {

                    if (ImGui::Selectable(it->c_str())) agsData.graphics.game_scale_fs = it->c_str();
                }

                ImGui::EndCombo();
            }

            ImGui::Text("Windowed scale:");
            ImGui::SameLine();
            if (ImGui::BeginCombo("##Windowed scale", agsData.graphics.game_scale_win.value().c_str())) {
                vector<string>::iterator it;
                for (it = scalingOptions.begin();
                     it != scalingOptions.end();
                     it++) {

                    if (ImGui::Selectable(it->c_str())) agsData.graphics.game_scale_win = it->c_str();
                }

                ImGui::EndCombo();
            }

            ImGui::Text("Sprite Cache Maximum Size:");
            ImGui::SameLine();
            if (ImGui::BeginCombo("##Sprite Cache", IntToStr(agsData.misc.cachemax.value()).c_str())) {
                vector<string>::iterator it;
                vector<int>::iterator it2;
                for (int i = 0;
                     i < spriteCacheOptions.size();
                     i++) {

                    if (ImGui::Selectable(spriteCacheOptions[i].c_str()))
                        agsData.misc.cachemax = spriteCacheOptions_value[i];
                }

                ImGui::EndCombo();
            }

            ImGui::Checkbox("Vertical Sync", &(agsData.graphics.vsync.value()));
            ImGui::Checkbox("Render sprites at screen resolution", &(agsData.graphics.render_at_screenres.value()));
            ImGui::Checkbox("Match Device Ratio", &(agsData.graphics.match_device_ratio.value()));
            ImGui::TreePop();
        }

        ImGui::Separator();


        ImGui::SetNextTreeNodeOpen(true,ImGuiCond_Once);
        if(ImGui::TreeNode("Sound options")) {
            ImGui::Text("Sound");               // Display some text (you can use a format strings too)

            ImGui::Text("Sound Driver:");
            ImGui::SameLine();
            if (ImGui::BeginCombo("##Sound Driver", agsData.sound.digiid.value().c_str())) {
                vector<string>::iterator it;
                for (it = soundOptionsDigiid.begin();
                     it != soundOptionsDigiid.end();
                     it++) {

                    if (ImGui::Selectable(it->c_str())) agsData.sound.digiid = it->c_str();;
                }

                ImGui::EndCombo();
            }

            ImGui::Text("MIDI Driver:");
            ImGui::SameLine();
            if (ImGui::BeginCombo("##MIDI Driver", agsData.sound.midiid.value().c_str())) {
                vector<string>::iterator it;
                for (it = soundOptionsMidiid.begin();
                     it != soundOptionsMidiid.end();
                     it++) {

                    if (ImGui::Selectable(it->c_str())) agsData.sound.midiid = it->c_str();
                }

                ImGui::EndCombo();
            }

            ImGui::Checkbox("Threaded Audio", &(agsData.sound.threaded.value()));
            ImGui::Checkbox("Use speech pack", &(agsData.sound.usespeech.value()));
            ImGui::TreePop();
        }

        ImGui::Separator();

        ImGui::SetNextTreeNodeOpen(true,ImGuiCond_Once);
        if(ImGui::TreeNode("Mouse options")) {
            ImGui::Text("Mouse");

            ImGui::SliderFloat("Mouse speed",&(agsData.mouse.speed.value()),0.1f,10.0f,"%.1f"); //may not work depending on locale in ags
            ImGui::TreePop();
        }


        ImGui::Separator();

        if(ImGui::Button("Save")) {
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
        agsData.WriteToFile(agsTold.configPath.user);
    }

    if(runTheGameBeforeQuit){
        agsTold.RunGame();
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