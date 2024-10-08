cmake_minimum_required(VERSION 3.10)  # Możesz ustawić odpowiednią wersję
project(PEAProjekt1)

# Ustaw ścieżkę do vcpkg
set(CMAKE_TOOLCHAIN_FILE "C:/Users/jakub/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "Vcpkg toolchain file")

# Dodaj swoje źródła
add_executable(PEAProjekt1 main.cpp)

# Wyszukaj pakiet
find_package(xlsxwriter CONFIG REQUIRED)

# Dodaj bibliotekę do projektu
target_link_libraries(PEAProjekt1 PRIVATE xlsxwriter)