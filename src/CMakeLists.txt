# Create the main library
add_library(mvc_framework
    ${CMAKE_CURRENT_SOURCE_DIR}/core/Application.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/core/Router.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/core/Response.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/core/Request.cpp
)

target_include_directories(mvc_framework PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

# Link any required external libraries
target_link_libraries(mvc_framework PRIVATE
    # Add external dependencies here
)