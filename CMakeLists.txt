project(PvZLib LANGUAGES CXX)

cmake_minimum_required(VERSION 3.19.2)

set(CMAKE_CXX_STANDARD 20)

add_library(pvz MODULE)
target_compile_definitions(pvz PUBLIC VERSION=V_1_0_0_1051_EN)
target_include_directories(pvz
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include

        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        )
target_sources(pvz
        PUBLIC
        include/pvz.h
        include/pvz_base.h
        include/pvz_button.h
        include/pvz_card.h
        include/pvz_cardselectionui.h
        include/pvz_cursor.h
        include/pvz_enum.h
        include/pvz_floatingitem.h
        include/pvz_game.h
        include/pvz_griditem.h
        include/pvz_hook.h
        include/pvz_plant.h
        include/pvz_pregameui.h
        include/pvz_projectile.h
        include/pvz_reference.h
        include/pvz_screen.h
        include/pvz_seedbank.h
        include/pvz_seedslot.h
        include/pvz_zombie.h

        PRIVATE
        src/pvz_base.cpp
        src/pvz_hook.cpp
        src/pvz_pregameui.cpp
        )
