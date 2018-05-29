

add_executable(
    owman
    #$<TARGET_OBJECTS:odr>
	IO/event_handler.cpp
	math/aarect.cpp
	math/vec2f.cpp
	math/vec2i.cpp
	physics/physics_box.cpp
	physics/physics_box_factory.cpp
	physics/physics_component.cpp
	physics/physics_system.cpp
	renderer/animation.cpp
	renderer/animation_frame.cpp
	renderer/camera.cpp
	renderer/graphics_component.cpp
	renderer/graphics_system.cpp
	renderer/low_level_renderer_2d.cpp
	renderer/sprite.cpp
	renderer/sprite_factory.cpp
	resource_manager/resource.cpp
	resource_manager/resource_cell.cpp
	resource_manager/resource_cell_factory.cpp
	resource_manager/resource_factory.cpp
	resource_manager/resource_manager.cpp
	resource_manager/resource_manager_templates.cpp
	resource_manager/resource_request.cpp
	resource_manager/resource_sprite.cpp
	resource_manager/resource_table.cpp
	resource_manager/resource_table_entry.cpp
	resource_manager/resource_text.cpp
	resource_manager/resource_text_factory.cpp
	resource_manager/resource_texture.cpp
	resource_manager/resource_texture_factory.cpp
	resource_manager/work_queue.cpp
	util/file_to_string.cpp
	world_cell.cpp
	world_streamer.cpp
	world_window.cpp
	main_character.cpp
	position.cpp
	entity_factory.cpp
	entity.cpp
	engine.cpp
    main.cpp
)
set_property(TARGET owman PROPERTY CXX_STANDARD 17)
target_link_libraries(owman PRIVATE SDL2::SDL2 SDL2::SDL2main)
target_link_libraries(owman PRIVATE glm)
target_link_libraries(owman PRIVATE unofficial::box2d::Box2D)
target_link_libraries(owman PRIVATE GLEW::GLEW)