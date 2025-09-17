# Указываем минимально необходимую версию CMake.
cmake_minimum_required(VERSION 3.10)

# Задаем имя нашего проекта и указываем язык (C++). ЭТА СТРОКА БЫЛА ПРОПУЩЕНА.
project(OperatingSystemsLab1 CXX)

# --- Настройка Google Test ---
# Добавляем папку с исходниками Google Test как подпроект.
add_subdirectory(${CMAKE_SOURCE_DIR}/../googletest ${CMAKE_BINARY_DIR}/googletest)

# Указываем CMake, что нужно включить заголовочные файлы gtest при сборке.
include_directories(SYSTEM ${CMAKE_BINARY_DIR}/googletest/googletest/include ${CMAKE_BINARY_DIR}/googletest/googlemock/include)

# --- Описание наших исполняемых файлов ---
add_executable(Creator creator.cpp)
add_executable(Reporter reporter.cpp)
add_executable(Main main.cpp)
add_executable(run_tests tests.cpp)

# --- Связывание тестов с библиотекой Google Test ---
target_link_libraries(run_tests gtest gtest_main)