idf_component_register(INCLUDE_DIRS "include")

set(BADGE_CONNECT_LIBS "")
add_prebuilt_library(badge_connect_lib "${CMAKE_CURRENT_SOURCE_DIR}/lib/libbadge_connect_src.a")
list(APPEND BADGE_CONNECT_LIBS badge_connect_lib)
target_link_libraries(${COMPONENT_LIB} INTERFACE ${BADGE_CONNECT_LIBS})
target_compile_options(${COMPONENT_LIB} INTERFACE $<$<COMPILE_LANGUAGE:C>:-Wno-strict-prototypes>)
