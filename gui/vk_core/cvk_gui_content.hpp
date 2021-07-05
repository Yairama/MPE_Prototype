//
// Created by yair0 on 04/07/2021.
//

#pragma once
#include <iostream>

namespace cvk{



    //TODO: Complete the Main Menu Bar
    void CreateMainMenuBar(){
        if (ImGui::BeginMainMenuBar())
        {
            if (ImGui::BeginMenu("File"))
            {
                if (ImGui::MenuItem("New Project", nullptr)) {}
                if (ImGui::MenuItem("Open", nullptr)) {}
                if (ImGui::MenuItem("Open Recent", nullptr)) {}
                if (ImGui::MenuItem("Close Project", nullptr)) {}
                if (ImGui::MenuItem("Settings", "Ctrl+Alt+S")) {}
                if (ImGui::MenuItem("Save All", "Ctrl+S")) {}

                ImGui::EndMenu();
            }

            if (ImGui::BeginMenu("Edit"))
            {
                if (ImGui::MenuItem("Add Edit", "CTRL+Z")) {}
                ImGui::EndMenu();
            }

            if (ImGui::BeginMenu("View"))
            {
                if (ImGui::MenuItem("Add View", "CTRL+Z")) {}
                ImGui::EndMenu();
            }

            if (ImGui::BeginMenu("Tool"))
            {
                if (ImGui::MenuItem("Add Tools", "CTRL+Z")) {}
                ImGui::EndMenu();
            }

            if (ImGui::BeginMenu("Help"))
            {
                if (ImGui::MenuItem("Add Help", "CTRL+Z")) {}
                ImGui::EndMenu();
            }

            ImGui::EndMainMenuBar();
        }
    }

    void ShowSimpleWindow(bool &show_demo_window, bool &show_another_window, ImVec4& clear_color){



        static float f = 0.0f;
        static int counter = 0;

        ImGui::Begin("Hello, world!");  // Create a window called "Hello, world!" and append into it.

        ImGui::Text(
                "This is some useful text.");  // Display some text (you can use a format strings too)
        ImGui::Checkbox(
                "Demo Window",
                &show_demo_window);  // Edit bools storing our window open/close state
        ImGui::Checkbox("Another Window", &show_another_window);

        ImGui::SliderFloat("float", &f, 0.0f, 1.0f);  // Edit 1 float using a slider from 0.0f to 1.0f
        ImGui::ColorEdit3("clear color",
                          (float *) &clear_color);  // Edit 3 floats representing a color

        if (ImGui::Button("Button"))  // Buttons return true when clicked (most widgets return true
            // when edited/activated)
            counter++;
        ImGui::SameLine();
        ImGui::Text("counter = %d", counter);

        ImGui::Text(
                "Application average %.3f ms/frame (%.1f FPS)",
                1000.0f / ImGui::GetIO().Framerate,
                ImGui::GetIO().Framerate);
        ImGui::End();
    }

    void ShowAnotherSimpleWindow(bool& show_another_window){
        if (show_another_window) {
            ImGui::Begin(
                    "Another Window",
                    &show_another_window);  // Pass a pointer to our bool variable (the window will have a
            // closing button that will clear the bool when clicked)
            ImGui::Text("Hello from another window!");
            if (ImGui::Button("Close Me")) show_another_window = false;
            ImGui::End();
        }
    }

    //TODO: Complete the Left Layout
    void CreateLeftLayout(ImVec2& projectNodesSize){
        //Currently represents the Platform Window created by the application which is hosting our Dear ImGui windows
        const ImGuiViewport* main_viewport = ImGui::GetMainViewport();


        bool* closeable = NULL;
        ImGuiWindowFlags window_flags = 0;
        window_flags |= ImGuiWindowFlags_NoCollapse;
        window_flags |= ImGuiWindowFlags_NoMove;

        ImGui::SetNextWindowPos(ImVec2(main_viewport->WorkPos.x, main_viewport->WorkPos.y), ImGuiCond_None);
        ImGui::SetNextWindowSizeConstraints(ImVec2(200, main_viewport->WorkSize.y*1/5),  ImVec2(500, main_viewport->WorkSize.y*4/5));
        ImGui::SetNextWindowSize(projectNodesSize);

        ImGui::Begin("Project nodes tree##1", closeable, window_flags);
        projectNodesSize = ImGui::GetWindowSize();
        ImGui::Text("Here will be the nodes");
        ImGui::End();

        ImVec2 filesChooserSize = ImVec2(projectNodesSize.x, main_viewport->WorkSize.y - projectNodesSize.y);

        ImGui::SetNextWindowPos(ImVec2(main_viewport->WorkPos.x, main_viewport->WorkPos.y+projectNodesSize.y), ImGuiCond_None);
        ImGui::SetNextWindowSizeConstraints(ImVec2(200, main_viewport->Size.y*1/5),  ImVec2(500, main_viewport->Size.y*4/5));
        ImGui::SetNextWindowSize(filesChooserSize);

        ImGui::Begin("File's chooser##2", closeable, window_flags);
        filesChooserSize = ImGui::GetWindowSize();
        projectNodesSize = ImVec2(filesChooserSize.x, main_viewport->WorkSize.y-filesChooserSize.y);
        ImGui::Text("Here will be the nodes");
        ImGui::End();

    }




}