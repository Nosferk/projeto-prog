cmake_minimum_required(VERSION 3.14)
project(main C)

# Define o padrão da linguagem C
set(CMAKE_C_STANDARD 11)

# Puxa automaticamente a versão 6.2 oficial do raylib do GitHub
include(FetchContent)
FetchContent_Declare(
    raylib
    URL https://github.com/raysan5/raylib/archive/refs/tags/6.2.tar.gz
)
FetchContent_MakeAvailable(raylib)

# Cria o executável apontando para a pasta src/
add_executable(${PROJECT_NAME} src/main.c)

# Vincula a biblioteca raylib ao seu executável
target_link_libraries(${PROJECT_NAME} PRIVATE raylib)

# Configurações extras de plataforma para o raylib funcionar no Linux
if (NOT WIN32)
    target_link_libraries(${PROJECT_NAME} PRIVATE m pthread dl rt)
endif()
