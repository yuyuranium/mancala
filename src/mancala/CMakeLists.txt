set(TARGET mancala)

set(SOURCES
  mancala.c)

add_library(${TARGET} STATIC ${SOURCES})

target_include_directories(${TARGET} PUBLIC ${mancala_SOURCE_DIR}/include)
