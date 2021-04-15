SET(USED_LIBS ${Boost_SYSTEM_LIBRARY} ${Boost_THREAD_LIBRARY} ${Boost_REGEX_LIBRARY})

ADD_EXECUTABLE(steady_timer.o steady_timer.cpp)
TARGET_LINK_LIBRARIES(steady_timer.o ${USED_LIBS})

ADD_EXECUTABLE(web_client.o web_client.cpp)
TARGET_LINK_LIBRARIES(web_client.o ${USED_LIBS})

ADD_EXECUTABLE(time_server.o time_server.cpp)
TARGET_LINK_LIBRARIES(time_server.o ${USED_LIBS})

ADD_SUBDIRECTORY(daytime)
