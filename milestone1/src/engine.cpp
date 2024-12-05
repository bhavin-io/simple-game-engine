#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "engine.h"
#include "globals.h"
#include "scene.h"

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}

Engine::Engine() {
}

void Engine::SetScene(Scene* scene) {
    scene_ = scene;
}

void Engine::Run() {
    GLFWwindow* window;

    if (!glfwInit()) {
        std::cout << "Failed to init GLFW." << std::endl;
        return;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Anubis's Dark Nebula", NULL, NULL);

    if (!window) {
        glfwTerminate();
        std::cout << "Engine: failed to open window." << std::endl;
        return;
    }

    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, key_callback);
    glEnable(GL_DEPTH_TEST);

    glewExperimental = GL_TRUE;
    glewInit();

    if (!scene_->Init()) {
        glfwDestroyWindow(window);
        glfwTerminate();
        std::cout << "Engine: failed to initialize scene." << std::endl;
        return;
    }

    float t = 0.0;
    float start_time = glfwGetTime();
    std::cout << "Engine: starting draw loop" << std::endl;

    while (!glfwWindowShouldClose(window)) {
        float current_time = glfwGetTime();
        t = (current_time - start_time) / SCENE_DURATION_SECONDS;

        if (t > 1.0) {
            t = 1.0;
        }

        static const float black[] = {0.0f, 0.0f, 0.0f, 0.0f};
        glClearBufferfv(GL_COLOR, 0, black);
        glClear(GL_DEPTH_BUFFER_BIT);
        glClearDepth(1.0f);

        scene_->SceneDraw(t);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
}