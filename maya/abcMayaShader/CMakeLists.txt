set(MAYAPLUGIN abcMayaShader)

file(GLOB SRC "*.cpp" "*h")

add_library(${MAYAPLUGIN} SHARED ${SRC})

MAYA_SET_PLUGIN_PROPERTIES(${MAYAPLUGIN})
ALEMBIC_SET_PROPERTIES(${MAYAPLUGIN})

include_directories(${Boost_INCLUDE_DIR})

include_directories(${MTOA_INCLUDE_DIR})
include_directories(${PYSTRING_INCLUDE_DIR})
include_directories(${ARNOLD_INCLUDE_DIR})

target_link_libraries(${MAYAPLUGIN} ${PYSTRING_LIBRARIES} ${MTOA_LIBRARY} ${Boost_REGEX_LIBRARY} ${Boost_SYSTEM_LIBRARY} ${Boost_CHRONO_LIBRARY} ${Boost_DATE_TIME_LIBRARY} ${Boost_THREAD_LIBRARY} ${MAYA_LIBRARIES} ${ARNOLD_LIBRARY})




if (${CMAKE_SYSTEM_NAME} MATCHES "Windows")
	install(TARGETS ${MAYAPLUGIN} RUNTIME DESTINATION ${PLUGINS_INSTALL_DIR})
else()
	install(TARGETS ${MAYAPLUGIN} DESTINATION ${PLUGINS_INSTALL_DIR})
endif()
