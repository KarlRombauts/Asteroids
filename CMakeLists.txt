

cmake_minimum_required(VERSION 3.6)

set(PROJECT_NAME "main")
set(CMAKE_C_STANDARD 99)
set(GL_SILENCE_DEPRECATION)

add_executable(${PROJECT_NAME} main.cpp Ship.cpp Ship.h Components/Transform.h Vec2.h Vec2.cpp OpenGL.h KeyboardState.cpp KeyboardState.h Globals.h GameState.cpp GameState.h Coordinates.h ecs/Entity.cpp ecs/Entity.h ecs/Component.h ecs/EntityManager.cpp ecs/EntityManager.h ecs/Service.cpp ecs/Service.h Components/Momentum.h Components/Acceleration.h Components/Rotation.h Components/PlayerInput.h Systems/RenderSystem.cpp Systems/RenderSystem.h Systems/System.h Systems/PlayerInputSystem.cpp Systems/PlayerInputSystem.h Components/Moveable.h Systems/PhysicsSystem.cpp Systems/PhysicsSystem.h Coordinates.cpp)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

include_directories(${OPENGL_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS})

target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})