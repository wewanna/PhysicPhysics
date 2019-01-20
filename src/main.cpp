#include <stdio.h>
#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <OpenGL/gl3.h>

#include <imgui.h>
#include <examples/imgui_impl_opengl3.h>
#include <examples/imgui_impl_sdl.h>

#include "Simulation.h"
#include "Rendering.h"
#include "SimulationBox.h"

SDL_Window *window = nullptr;
SDL_GLContext context;

int init();
void release();
void render_gui();

int main() {
  SDL_Init(SDL_INIT_VIDEO|SDL_INIT_EVENTS);
  if(0 == init()) {
    fprintf(stderr, "failed initialize.\n");
    return -1;
  }

  SDL_Event event;
  int quit = false;

  PhysicPhysics::Simulation &simulation = PhysicPhysics::Simulation::Get();

  while(!quit) {
    while(SDL_PollEvent(&event)) {
      ImGui_ImplSDL2_ProcessEvent(&event);
      if(SDL_QUIT == event.type)
        quit = true;
    }

    simulation.update();

    render_gui();

    render();

    SDL_GL_SwapWindow(window);

    SDL_Delay(16);
  }


  release();

  return 0;
}

int init() {
  // setup opengl
  const char* glsl_version = "#version 410";
#ifdef __APPLE__
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG);
#endif
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
  SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
  SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

  window = SDL_CreateWindow("PhsyicPhysics",
                            SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                            960, 720, SDL_WINDOW_OPENGL);
  if(nullptr == window) {
    fprintf(stderr, "failed to create window\n");
    return false;
  }

  context = SDL_GL_CreateContext(window);
  if(GLEW_OK != glewInit()) {
    fprintf(stderr, "failed initialize glew(opengl loader)\n");
    return false;
  }

  // setup opengl
  glEnable(GL_PROGRAM_POINT_SIZE);

  // setup imgui
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO &io = ImGui::GetIO(); (void)io;
  io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
  ImGui::StyleColorsDark();
  ImGui_ImplSDL2_InitForOpenGL(window, context);
  ImGui_ImplOpenGL3_Init(glsl_version);

  return init_shader();
}

void release() {
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplSDL2_Shutdown();

  SDL_GL_DeleteContext(context);
  SDL_DestroyWindow(window);

  SDL_Quit();
}

void render_gui() {
  ImGuiIO &io = ImGui::GetIO();

  ImGui_ImplOpenGL3_NewFrame();
  ImGui_ImplSDL2_NewFrame(window);
  ImGui::NewFrame();

  PhysicPhysics::Simulation::Get().render_gui();

  ImGui::Render();
  SDL_GL_MakeCurrent(window, context);
  glViewport(0, 0, (int)io.DisplaySize.x, (int)io.DisplaySize.y);

  glClear(GL_COLOR_BUFFER_BIT);
  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

}