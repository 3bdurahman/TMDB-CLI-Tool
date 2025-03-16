cmake_minimum_required(VERSION 3.31)

project(tmdb-app)

find_package(Poco REQUIRED NetSSL)
find_package(fmt REQUIRED)

set(SOURCES
"source/tmdb-app.cpp"
"source/TMDB.cpp"
)
add_executable(tmdb-app ${SOURCES})

target_include_directories(tmdb-app PRIVATE "header/")
target_link_libraries(tmdb-app PRIVATE Poco::Foundation Poco::NetSSL fmt::fmt)