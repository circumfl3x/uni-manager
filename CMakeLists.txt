cmake_minimum_required(VERSION 3.16)

# Название проекта (можешь поменять на любое)
project(UniDistributor VERSION 1.0 LANGUAGES CXX)

# Используем стандарт C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Эти три строчки — магия Qt. Они заставляют CMake автоматически 
# обрабатывать файлы .ui, а также генерировать код для Q_OBJECT (слоты и сигналы)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# Поиск Qt (сначала ищем 6-ю версию, если нет — 5-ю)
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

# СПИСОК ФАЙЛОВ ПРОЕКТА
# Сюда нужно добавлять ВСЕ твои .cpp и .h файлы, иначе компилятор их не увидит.
set(PROJECT_SOURCES
    src/main.cpp
    
    src/models/Applicant.cpp
    src/models/Applicant.h
    src/models/University.cpp
    src/models/University.h
    
    src/logic/DistributionManager.cpp
    src/logic/DistributionManager.h
    
    src/ui/MainWindow.cpp
    src/ui/MainWindow.h
    # src/ui/MainWindow.ui
)

# Создаем исполняемый файл
add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})

# Привязываем библиотеку Qt Widgets к нашему проекту
target_link_libraries(${PROJECT_NAME} PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

# Указываем компилятору, что папка src — это корень для наших заголовочных файлов
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)