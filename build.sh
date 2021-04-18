clang main.cpp \
Helpers.cpp \
GameConfig.cpp \
Vec2.cpp \
KeyboardState.cpp \
Coordinates.cpp \
GameModel.cpp \
ecs/Entity.cpp \
ecs/EntityManager.cpp \
ecs/Service.cpp \
Systems/RenderSystem.cpp \
Systems/PlayerInputSystem.cpp \
Systems/CollisionSystem.cpp \
Systems/OutOfBoundsSystem.cpp \
Systems/FiringSystem.cpp \
Systems/ImpactCleanupSystem.cpp  \
Systems/DamageSystem.cpp  \
Systems/BulletCleanupSystem.cpp  \
Systems/WarningSystem.cpp \
Systems/AsteroidSystem.cpp \
Systems/ShipImpactSystem.cpp \
Systems/ParticleSystem.cpp \
Systems/BlackHoleSystem.cpp \
Systems/DestroySystem.cpp \
-Wno-deprecated-declarations -framework GLUT -framework OpenGL -framework Carbon