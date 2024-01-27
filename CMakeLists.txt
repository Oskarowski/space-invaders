cmake_minimum_required(VERSION 3.12)
project(SpaceInvadersP)
enable_language(CXX)

set(CMAKE_CXX_STANDARD 17)

# Find SFML
find_package(SFML 2.5 COMPONENTS graphics window audio system  REQUIRED)

find_package(nlohmann_json 3.2.0 REQUIRED)

# Find Boost
find_package(Boost COMPONENTS unit_test_framework REQUIRED)

# Set the paths for headers and sources
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${Boost_INCLUDE_DIRS}
)

set (HEADERS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include/)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")

# Source files
set(SOURCES
    src/main.cpp
    src/helpers/MainMenu.cpp
    src/helpers/EndGameMenu.cpp
    src/helpers/DrawText.cpp
    src/abstracts/RenderableEntity.cpp
    src/abstracts/DamageableEntity.cpp
    src/abstracts/ShooterableEntity.cpp
    src/models/Projectile.cpp
    src/models/Player.cpp
    src/models/Barrier.cpp
    src/models/Enemy.cpp
    src/controllers/BarrierController.cpp
    src/controllers/StoreGameStateController.cpp
    src/controllers/EnemyContoller.cpp
    src/controllers/CollisionController.cpp
    src/controllers/GameController.cpp
)


add_executable(SpaceInvadersP ${SOURCES})

# Link SFML
target_link_libraries(SpaceInvadersP PRIVATE sfml-graphics sfml-window sfml-audio sfml-system)

# Link the nlohmann/json library
target_link_libraries(SpaceInvadersP PRIVATE nlohmann_json::nlohmann_json)

add_custom_command(TARGET SpaceInvadersP POST_BUILD
COMMAND "${CMAKE_COMMAND}" -E copy_directory "${CMAKE_SOURCE_DIR}/assets" "${CMAKE_BINARY_DIR}/assets")

enable_testing()

find_package (Boost 1.60.0 COMPONENTS "unit_test_framework" REQUIRED)

set(SOURCE_TEST_CONTAINER_FILES
        tests/master.cpp
        tests/test.cpp
        tests/PlayerTest.cpp
        tests/EnemyTest.cpp
        

        src/helpers/MainMenu.cpp
        src/helpers/EndGameMenu.cpp
        src/helpers/DrawText.cpp
        src/abstracts/RenderableEntity.cpp
        src/abstracts/DamageableEntity.cpp
        src/abstracts/ShooterableEntity.cpp
        src/models/Projectile.cpp
        src/models/Player.cpp
        src/models/Barrier.cpp
        src/models/Enemy.cpp
        src/controllers/BarrierController.cpp
        src/controllers/StoreGameStateController.cpp
        src/controllers/EnemyContoller.cpp
        src/controllers/CollisionController.cpp
        src/controllers/GameController.cpp
)

add_executable (TestContainer ${SOURCE_TEST_CONTAINER_FILES})

target_include_directories(TestContainer PRIVATE ${HEADERS_DIR})

target_link_libraries(TestContainer
    ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
    sfml-graphics sfml-window sfml-audio sfml-system
    nlohmann_json::nlohmann_json
)

     
        

# TestTest
add_test(TestTest TestContainer
--run_test=TestTestSuite
--report_level=detailed
--log_level=all
--color_output=yes
)

# PlayerTest
add_test(PlayerTest TestContainer
    --run_test=PlayerTestSuite
    --report_level=detailed
    --log_level=all
    --color_output=yes
)

# EnemyTest
add_test(EnemyTest TestContainer
    --run_test=EnemyTestSuite
    --report_level=detailed
    --log_level=all
    --color_output=yes
)


# Set labels for tests
set_tests_properties(PlayerTest PROPERTIES LABELS "player")
set_tests_properties(TestTest PROPERTIES LABELS "exampleTests")

# Custom target for running tests
add_custom_target(check
    ${CMAKE_COMMAND} -E env CTEST_OUTPUT_ON_FAILURE=1 BOOST_TEST_LOG_LEVEL=all
    ${CMAKE_CTEST_COMMAND} -C $<CONFIGURATION> --verbose
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)

