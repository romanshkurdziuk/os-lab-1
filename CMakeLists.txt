# Указываем минимально необходимую версию CMake.
cmake_minimum_required(VERSION 3.10)

# Задаем имя нашего проекта и указываем язык (C++).
project(OperatingSystemsLab1 CXX)

# --- Настройка путей ---
# Добавляем папку 'include' в пути поиска заголовочных файлов.
# Теперь #include "employee.h" будет работать из любого места.
include_directories(include)

# --- Настройка Google Test ---
add_subdirectory(${CMAKE_SOURCE_DIR}/../googletest ${CMAKE_BINARY_DIR}/googletest)
include_directories(SYSTEM ${CMAKE_BINARY_DIR}/googletest/googletest/include ${CMAKE_BINARY_DIR}/googletest/googlemock/include)

# --- Описание наших исполняемых файлов (теперь с указанием пути) ---

# 1. Утилита Creator
add_executable(Creator src/creator.cpp)

# 2. Утилита Reporter
add_executable(Reporter src/reporter.cpp)

# 3. Главная программа Main
add_executable(Main src/main.cpp)

# 4. Исполняемый файл для тестов
add_executable(run_tests tests/tests.cpp)

# --- Связывание тестов с библиотекой Google Test ---
target_link_libraries(run_tests gtest gtest_main)