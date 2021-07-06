//
// Created by yair0 on 04/07/2021.
//

#pragma once
#include <iostream>
#include "custom_objects.hpp"



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



