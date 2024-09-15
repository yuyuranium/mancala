set(TARGET strategy)

set(SOURCES
  chaotic.c
  maximal_first.c
  minimal_first.c)

add_library(${TARGET} STATIC ${SOURCES})
target_link_libraries(${TARGET} PUBLIC mancala)
target_include_directories(${TARGET} PUBLIC ${mancala_SOURCE_DIR}/include)
