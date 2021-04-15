SET(USED_LIBS ${Boost_SYSTEM_LIBRARY} ${Boost_THREAD_LIBRARY} ${Boost_REGEX_LIBRARY})

ADD_EXECUTABLE(daytime_server.o daytime_server.cpp)
TARGET_LINK_LIBRARIES(daytime_server.o ${USED_LIBS})

ADD_EXECUTABLE(daytime_client.o daytime_client.cpp)
TARGET_LINK_LIBRARIES(daytime_client.o ${USED_LIBS})
