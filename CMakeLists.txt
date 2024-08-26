cmake_minimum_required(VERSION 3.5.0)
project(Kids_Room VERSION 0.1.0 LANGUAGES C CXX)

# Добавляем все исходные файлы проекта
add_executable(Kids_Room 
    main.cpp 
    Utils/Utils.cpp
    UserInterface/userinterface.cpp 
    DataBase/database.cpp 
    Toys/Ball.cpp 
    Toys/Car.cpp 
    Toys/Cube.cpp 
    Toys/Doll.cpp 
    Toys/Toy.cpp 
    Toys/ToysRoom.cpp
)

# Указываем путь к заголовочным файлам
include_directories(${CMAKE_SOURCE_DIR}/UserInterface)
include_directories(${CMAKE_SOURCE_DIR}/DataBase)
include_directories(${CMAKE_SOURCE_DIR}/Toys)

# Подключаем библиотеку SQLite3
add_library(sqlite3 STATIC IMPORTED)
set_target_properties(sqlite3 PROPERTIES IMPORTED_LOCATION "${CMAKE_SOURCE_DIR}/sqlite3/libsqlite3.a")

# Линкуем библиотеку SQLite3 с вашим исполняемым файлом
target_link_libraries(Kids_Room sqlite3)
