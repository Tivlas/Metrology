cmake_minimum_required(VERSION 3.16)

project("JilbMetrics" C CXX) # Название проекта и язык


# Стандарт C++
set(CMAKE_CXX_STANDARD 17)


# Необходим Qt для работы с графическим интерфейсом
find_package(Qt6 REQUIRED COMPONENTS Core Widgets Gui)

find_package(LLVM REQUIRED CONFIG)

add_definitions(-D__STDC_LIMIT_MACROS -D__STDC_CONSTANT_MACROS)


# Все исходные файлы приложения
file(GLOB_RECURSE SRC "src/include/*.hpp" "src/include/*.h" "src/ui/*.ui" "src/code/*.cpp" )


add_executable(JilbMetrics ${SRC} ${resources})
target_compile_options(JilbMetrics PRIVATE -fno-rtti)
target_link_libraries(JilbMetrics PRIVATE LLVM clangTooling clangFrontend clangParse clangSema clangAnalysis clangAST clangBasic clangDriver clangSerialization clangEdit clangLex)
include_directories(${LLVM_INCLUDE_DIRS})






# Автоматическое преобразование форм в код, добавление ресурсов в сборку
set_target_properties(JilbMetrics PROPERTIES AUTOMOC TRUE AUTOUIC TRUE AUTORCC TRUE)

# Линковка всех библиотек к цели сборки
target_link_libraries(JilbMetrics PRIVATE Qt6::Core Qt6::Widgets Qt::Gui)