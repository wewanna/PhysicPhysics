cmake_minimum_required( VERSION 3.0 )

project( PhysicPhysics )

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)
message(STATUS "module path: ${CMAKE_MODULE_PATH}")

add_compile_options( -O3 )
set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17" )
set( CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -DNDEBUG -O3" )
set( CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g" )

add_executable(
        PhysicPhysics
        src/main.cpp
        src/SimulationBox.cpp
        src/Rendering.cpp
        src/Simulation.cpp
        src/calculation/particle.cpp
        src/Particles.cpp
)

add_library(
        imgui
        imgui/imgui.cpp
        imgui/imgui_demo.cpp
        imgui/imgui_draw.cpp
        imgui/imgui_widgets.cpp
        imgui/examples/imgui_impl_opengl3.cpp
        imgui/examples/imgui_impl_sdl.cpp
)
target_link_libraries(PhysicPhysics imgui)
include_directories( imgui/ )
set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DIMGUI_IMPL_OPENGL_LOADER_GLEW" )

# sdl
find_package( SDL2 REQUIRED )
include_directories( ${SDL2_INCLUDE_DIR} )
target_link_libraries( PhysicPhysics ${SDL2_LIBRARY} )

# opengl
find_package ( OpenGL REQUIRED )
if (OPENGL_FOUND )
    target_link_libraries ( PhysicPhysics ${OPENGL_LIBRARY} )
    target_link_libraries ( PhysicPhysics ${OPENGiL_gl_LIBRARY} )
    target_link_libraries ( PhysicPhysics ${OPENGL_glu_LIBRARY} )
endif()
set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DGL_SILENCE_DEPRECATION" )

# glm
find_package( GLM REQUIRED )
if( GLM_FOUND )
    include_directories( ${GLM_INCLUDE_DIRS} )
endif()

# glew
find_package( GLEW REQUIRED )
if( GLEW_FOUND )
    include_directories( ${GLEW_INCLUDE_DIRECTORIES} )
    target_link_libraries( PhysicPhysics ${GLEW_LIBRARIES} )
endif()
