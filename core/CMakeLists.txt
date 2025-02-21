# Core MVC Framework CMakeLists.txt

add_library(mvc_framework
    Application.cpp
    Database.cpp
    Request.cpp
    Response.cpp
    Router.cpp
    View.cpp
)

target_include_directories(mvc_framework PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})