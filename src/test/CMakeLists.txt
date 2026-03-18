add_executable(ECS_TESTS ecs_test.c)
add_executable(MPOOL_TESTS mpool_test.c)
add_executable(SDL_TEST_GAME sdlTest_game.c)

add_custom_command(TARGET SDL_TEST_GAME POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    $<TARGET_FILE:SDL3::SDL3> # Esto obtiene la ruta al .dll automáticamente
    $<TARGET_FILE_DIR:SDL_TEST_GAME> # Esto obtiene la carpeta de salida del .exe
)

target_link_libraries(ECS_TESTS ECS MPool)
target_link_libraries(MPOOL_TESTS MPool)
target_link_libraries(SDL_TEST_GAME SDL3::SDL3)