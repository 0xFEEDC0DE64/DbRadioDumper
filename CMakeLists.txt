project(DbRadioDumper)

find_package(Qt5Core CONFIG REQUIRED)
find_package(Qt5Network CONFIG REQUIRED)

set(HEADERS
    dumpjob.h
)

set(SOURCES
    dumpjob.cpp
    main.cpp
)

add_executable(radiodumper ${HEADERS} ${SOURCES})

target_link_libraries(radiodumper stdc++ Qt5::Core Qt5::Network)
