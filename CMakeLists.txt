

cmake_minimum_required(VERSION 3.6)

set(PROJECT_NAME "main")
set(CMAKE_CXX_STANDARD 17)
set(GL_SILENCE_DEPRECATION)

add_executable(${PROJECT_NAME} main.cpp Components/Transform.h Vec2.h Vec2.cpp OpenGL.h KeyboardState.h KeyboardState.cpp Globals.h GameState.cpp GameState.h Coordinates.h ecs/Entity.cpp ecs/Entity.h ecs/Component.h ecs/EntityManager.cpp ecs/EntityManager.h ecs/Service.cpp ecs/Service.h Components/Momentum.h Components/Acceleration.h Components/Rotation.h Components/PlayerInput.h Systems/RenderSystem.cpp Systems/RenderSystem.h Systems/System.h Systems/PlayerInputSystem.cpp Systems/PlayerInputSystem.h Components/Kinematics.h Systems/PhysicsSystem.cpp Systems/PhysicsSystem.h Coordinates.cpp Components/Texture.h ecs/EventManager.cpp ecs/EventManager.h Systems/CollisionSystem.cpp Systems/CollisionSystem.h Events/CollisionEvent.h Components/Identity.h Events/AsteroidHitEvent.h Events/Death.h Events/SpaceShipHitEvent.h Components/Collision.h Components/Asteroid.h Components/SpaceShip.h Components/Bullet.h Components/Helpers.cpp Components/Helpers.h Components/Destroy.h Systems/OutOfBoundsSystem.cpp Systems/OutOfBoundsSystem.h Components/FiringBullet.h Systems/FiringSystem.cpp Systems/FiringSystem.h Components/GravityForce.h Components/BlackHole.h Components/Shape.h Components/Draggable.h Systems/DragSystem.cpp Systems/DragSystem.h MouseState.cpp MouseState.h Factories/AteroidFactory.cpp Factories/AteroidFactory.h Factories/LineFactory.cpp Factories/LineFactory.h Arena.cpp Arena.h Components/Line.h Components/Impact.h Systems/ImpactCleanupSystem.cpp Systems/ImpactCleanupSystem.h Systems/DamageSystem.cpp Systems/DamageSystem.h Components/Damage.h Components/Health.h Components/HealthBar.h Components/SplitOnDeath.h Systems/BulletCleanupSystem.cpp Systems/BulletCleanupSystem.h GameManager.cpp GameManager.h Components/Child.h Components/BoundingCircle.h Components/Wall.h Systems/WarningSystem.cpp Systems/WarningSystem.h Systems/AsteroidSystem.cpp Systems/AsteroidSystem.h Components/OutsideArena.h Systems/ShipImpactSystem.cpp Systems/ShipImpactSystem.h Components/ParticleSource.h Components/Particle.h Systems/ParticleSystem.cpp Systems/ParticleSystem.h Components/Text.h Systems/BlackHoleSystem.cpp Systems/BlackHoleSystem.h Systems/DestroySystem.cpp Systems/DestroySystem.h GameConfig.h GameConfig.cpp)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

include_directories(${OPENGL_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS})

target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})