add_executable(ECS_TESTS ecs_test.c)
add_executable(MPOOL_TESTS mpool_test.c)

target_link_libraries(ECS_TESTS ECS MPool)
target_link_libraries(MPOOL_TESTS MPool)