# 1. Boilerplate
cmake_minimum_required(VERSION 3.10)
project(DinoGame)

# 2. Find and configure the SFML library
# This searches for SFML version 2.5 or newer and requires the
# graphics, window, and system components.
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

# 3. Add your executable
add_executable(${PROJECT_NAME} 
    src/main.cpp
    src/Game.cpp
    src/Dino.cpp
    src/Obstacle.cpp
)

# 4. Tell the compiler where to find your header files
target_include_directories(${PROJECT_NAME} PUBLIC include)

# 5. Link your game against the SFML library
# This tells the compiler to connect your code to the SFML code it needs.
target_link_libraries(${PROJECT_NAME} PRIVATE sfml-graphics)

# 6. Handle Resources
# This copies your 'resources' folder to the build directory so the
# executable can find your .png files.
file(COPY resources DESTINATION ${CMAKE_BINARY_DIR})