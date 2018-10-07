project(DbRadioDumper)

set(HEADERS
    dumpjob.h
)

set(SOURCES
    dumpjob.cpp
    main.cpp
)

add_executable(radiodumper ${HEADERS} ${SOURCES})

target_link_libraries(radiodumper Qt5::Core Qt5::Network)
