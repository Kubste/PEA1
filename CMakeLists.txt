# Ustawienie minimalnej wersji CMake
cmake_minimum_required(VERSION 3.10)

# Ustalamy nazwę projektu
project(PEAProjekt1)  # Zmień MyProject na nazwę swojego projektu

# Dodaj ścieżki do katalogów z nagłówkami i bibliotekami
include_directories(include)
link_directories(libs)

# Znajdowanie biblioteki xlsxwriter
find_package(xlsxwriter REQUIRED)

# Ustawienie pliku źródłowego
add_executable(PEAProjekt1 main.cpp)  # Zmień MyExecutable i main.cpp na odpowiednie nazwy

# Linkowanie biblioteki xlsxwriter
target_link_libraries(MyExecutable PRIVATE xlsxwriter)