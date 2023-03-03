# ============================================================================
# External requirements
# ============================================================================

#----------------------------------------------------------------------------
# Threads
#----------------------------------------------------------------------------
find_package (Threads REQUIRED)

# ----------------------------------------------------------------------------
# Boost
# ----------------------------------------------------------------------------
find_package (Boost ${layer1_BOOST_VERSION} REQUIRED
	COMPONENTS locale)

# ============================================================================
# Targets configuration
# ============================================================================

configure_file (${PROJECT_SOURCE_DIR}/cmake/layer1Version.hh.in ${CMAKE_CURRENT_BINARY_DIR}/layer1Version.hh)

# ----------------------------------------------------------------------------
# library (common) configuration
# ----------------------------------------------------------------------------
add_library (layer1)

set_target_properties (layer1
	PROPERTIES
		OUTPUT_NAME layer1-${PROJECT_VERSION}
		VERSION ${PROJECT_VERSION}
		SOVERSION ${PROJECT_MAJOR}.${PROJECT_MINOR}
	)

target_sources (layer1
	PRIVATE
		src/layer1/fake.cc
	)

target_include_directories (layer1
	PUBLIC
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
	)

target_link_libraries (layer1
	PUBLIC
		Boost::disable_autolinking
		Boost::headers
		Boost::locale
	)

# ============================================================================
# Install configuration
# ============================================================================

install (TARGETS layer1 EXPORT layer1-export
	INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install (DIRECTORY src/layer1
	DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
	FILES_MATCHING PATTERN "*.hh"
)

install (FILES ${CMAKE_CURRENT_BINARY_DIR}/layer1Version.hh
	DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
	)

install (EXPORT layer1-export
	FILE ${PROJECT_NAME}-targets.cmake
	NAMESPACE ${PROJECT_NAME}::
	DESTINATION "${ConfigPackageLocation}"
	)

# ----------------------------------------------------------------------------
# Export configuration
# ----------------------------------------------------------------------------
add_library (${PROJECT_NAME}::layer1 ALIAS layer1)

