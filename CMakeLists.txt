cmake_minimum_required(VERSION 3.14)
project(PlatformerSFML)

set(CMAKE_CXX_STANDARD 14)


if(WIN32)
    set(SFML_STATIC_LIBRARIES TRUE)
    set(CMAKE_EXE_LINKER_FLAGS "-static")
endif()


find_package(SFML 2.5.1 COMPONENTS system window graphics network audio)
set(SOURCE_FILES src/main.cpp src/Game.cpp src/Game.h src/GameStates/GameStateBase.cpp src/GameStates/GameStateBase.h src/GameStates/GameMenu.cpp src/GameStates/GameMenu.h src/GameStates/GameLevelSelect.cpp src/GameStates/GameLevelSelect.h src/GameStates/GamePlay.cpp src/GameStates/GamePlay.h src/GameStates/GamePaused.cpp src/GameStates/GamePaused.h src/GameStates/GameOver.cpp src/GameStates/GameOver.h src/GameStates/GameWin.cpp src/GameStates/GameWin.h src/Extra/Helper.cpp src/Extra/Helper.h src/Extra/LevelIcon.cpp src/Extra/LevelIcon.h src/GameObjects/GameObject.cpp src/GameObjects/GameObject.h src/GameObjects/Levels/Level.cpp src/GameObjects/Levels/Level.h src/GameObjects/Block.cpp src/GameObjects/Block.h src/Extra/Vector2.cpp src/Extra/Vector2.h src/GameObjects/Entities/Entity.cpp src/GameObjects/Entities/Entity.h src/PhysicsEngine/PhysicsEngine.cpp src/PhysicsEngine/PhysicsEngine.h "src/PhysicsEngine/Particle simulation.cpp" "src/PhysicsEngine/RigidBody simulation.cpp" src/PhysicsEngine/PhysicsStructs.cpp src/PhysicsEngine/PhysicsStructs.h src/GameObjects/Entities/Player.cpp src/GameObjects/Entities/Player.h src/PhysicsEngine/PhysicsCollisions.cpp src/PhysicsEngine/PhysicsCollisions.h src/GameObjects/Collectable.cpp src/GameObjects/Collectable.h src/Extra/UI.cpp src/Extra/UI.h src/GameObjects/Projectiles/Projectile.cpp src/GameObjects/Projectiles/Projectile.h src/GameObjects/Entities/ArtilleryEnemy.cpp src/GameObjects/Entities/ArtilleryEnemy.h src/GameObjects/Projectiles/Shell.cpp src/GameObjects/Projectiles/Shell.h src/GameObjects/Flag.cpp src/GameObjects/Flag.h src/GameObjects/Entities/NormalEnemy.cpp src/GameObjects/Entities/NormalEnemy.h src/GameObjects/Entities/HomingEnemy.cpp src/GameObjects/Entities/HomingEnemy.h src/GameStates/GameControls.cpp src/GameStates/GameControls.h src/GameObjects/Levels/LevelOne.cpp src/GameObjects/Levels/LevelOne.h src/GameObjects/Levels/LevelTwo.cpp src/GameObjects/Levels/LevelTwo.h src/GameObjects/Levels/LevelThree.cpp src/GameObjects/Levels/LevelThree.h)
add_executable(PlatformerSFML ${SOURCE_FILES})

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")

target_link_libraries (PlatformerSFML sfml-graphics sfml-window sfml-system sfml-network sfml-audio)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/Data/ DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Data/)