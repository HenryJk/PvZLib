project(PvZLib LANGUAGES CXX)

cmake_minimum_required(VERSION 3.12)

set(CMAKE_CXX_STANDARD 20)

set(include_dir "${CMAKE_CURRENT_SOURCE_DIR}/include")
set(source_files
        include/model/anim_info.hpp
        include/model/attachment.hpp
        include/model/award_screen.hpp
        include/model/beta_support.hpp
        include/model/board.hpp
        include/model/buffer.hpp
        include/model/button_listener.hpp
        include/model/button_widget.hpp
        include/model/challenge.hpp
        include/model/challenge_screen.hpp
        include/model/chosen_seed.hpp
        include/model/coin.hpp
        include/model/color.hpp
        include/model/credit_screen.hpp
        include/model/crit_sect.hpp
        include/model/cursor_object.hpp
        include/model/cursor_preview.hpp
        include/model/cut_scene.hpp
        include/model/d3d_interface.hpp
        include/model/d3d_tester.hpp
        include/model/data_array.hpp
        include/model/dd_image.hpp
        include/model/dd_interface.hpp
        include/model/dialog.hpp
        include/model/dialog_button.hpp
        include/model/effect_system.hpp
        include/enum.hpp
        include/model/flags_mod.hpp
        include/model/float_parameter_track.hpp
        include/model/foley_instance.hpp
        include/model/foley_type_data.hpp
        include/model/font.hpp
        include/model/game_button.hpp
        include/model/game_object.hpp
        include/model/game_selector.hpp
        include/model/graphics.hpp
        include/model/grid_item.hpp
        include/model/hyperlink_widget.hpp
        include/model/image.hpp
        include/model/insets.hpp
        include/model/internet_manager.hpp
        include/model/lawn_app.hpp
        include/model/lawn_mower.hpp
        include/model/lawn_stone_button.hpp
        include/model/level_stats.hpp
        include/model/magnet_item.hpp
        include/model/memory_image.hpp
        include/model/message_widget.hpp
        include/model/motion_trail_frame.hpp
        include/model/music.hpp
        include/model/new_lawn_button.hpp
        include/model/particle_field.hpp
        include/model/perf_timer.hpp
        include/model/plant.hpp
        include/model/player_info.hpp
        include/model/pool_effect.hpp
        include/model/pop_drm_comm.hpp
        include/model/potted_plant.hpp
        include/model/pre_modal_info.hpp
        include/model/profile_mgr.hpp
        include/model/projectile.hpp
        include/pvz.hpp
        include/pvz_reference.hpp
        include/model/ratio.hpp
        include/model/reanimation.hpp
        include/model/resource_manager.hpp
        include/model/seed_bank.hpp
        include/model/seed_chooser_screen.hpp
        include/model/seed_packet.hpp
        include/model/sexy_app.hpp
        include/model/sexy_app_base.hpp
        include/model/sexy_matrix3.hpp
        include/model/sexy_transform_2d.hpp
        include/model/sexy_vector2.hpp
        include/model/shared_image.hpp
        include/model/sound_instance.hpp
        include/model/sound_manager.hpp
        include/model/string_less_no_case.hpp
        include/model/title_screen.hpp
        include/model/tod_allocator.hpp
        include/model/tod_foley.hpp
        include/model/tod_list.hpp
        include/model/tod_particle.hpp
        include/model/tod_smooth_array.hpp
        include/model/tool_tip_widget.hpp
        include/model/trail.hpp
        include/model/typing_check.hpp
        include/model/widget.hpp
        include/model/widget_manager.hpp
        include/model/widget_safe_delete_info.hpp
        include/model/win_inet_http_transfer.hpp
        include/model/xml_parser.hpp
        include/model/zen_garden.hpp
        include/model/zombie.hpp
        include/model/incompatible_stdlib.hpp
        src/model/plant.cpp
        src/hook.cpp include/hook.hpp)

add_library(pvz_1_0_0_1051_en ${source_files})
set_target_properties(pvz_1_0_0_1051_en PROPERTIES LINKER_LANGUAGE CXX)
target_compile_definitions(pvz_1_0_0_1051_en PUBLIC VERSION=V_1_0_0_1051_EN)
target_include_directories(pvz_1_0_0_1051_en PUBLIC ${include_dir})

#add_library(pvz_1_2_0_1096_en ${source_files})
#target_compile_definitions(pvz_1_2_0_1096_en PUBLIC VERSION=V_1_2_0_1096_EN)
#target_include_directories(pvz_1_2_0_1096_en PUBLIC ${include_dir})
