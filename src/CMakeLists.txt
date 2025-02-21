# Create the main library
add_library(mvc_framework
    ${CMAKE_SOURCE_DIR}/core/Application.cpp
    ${CMAKE_SOURCE_DIR}/core/Router.cpp
    ${CMAKE_SOURCE_DIR}/core/Response.cpp
    ${CMAKE_SOURCE_DIR}/core/Request.cpp
    ${CMAKE_SOURCE_DIR}/core/View.cpp
)

target_include_directories(mvc_framework PUBLIC
    ${CMAKE_SOURCE_DIR}
)

# Create the executable
add_executable(web_server
    main.cpp
)

# Link the executable with our library
target_link_libraries(web_server PRIVATE
    mvc_framework
)