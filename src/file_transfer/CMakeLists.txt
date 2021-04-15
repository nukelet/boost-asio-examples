SET(USED_LIBS ${Boost_SYSTEM_LIBRARY} ${Boost_THREAD_LIBRARY} ${Boost_REGEX_LIBRARY})

ADD_EXECUTABLE(file_transfer_server.o file_transfer_server.cpp)
TARGET_LINK_LIBRARIES(file_transfer_server.o ${USED_LIBS})

ADD_EXECUTABLE(file_transfer_client.o file_transfer_client.cpp)
TARGET_LINK_LIBRARIES(file_transfer_client.o ${USED_LIBS})
