CMAKE_MINIMUM_REQUIRED( VERSION 2.8 )
SET( CMAKE_CONFIGURATION_TYPES Debug Release CACHE TYPE INTERNAL FORCE )
PROJECT( reverseWordPairs C CXX )

# Project Version
SET( ${PROJECT_NAME}_VERSION_MAJOR 1 )
SET( ${PROJECT_NAME}_VERSION_MINOR 0 )
SET( ${PROJECT_NAME}_VERSION_PATCH 0 )
SET( ${PROJECT_NAME}_VERSION ${${PROJECT_NAME}_VERSION_MAJOR}.${${PROJECT_NAME}_VERSION_MINOR}.${${PROJECT_NAME}_VERSION_PATCH} )
MESSAGE( ${PROJECT_NAME} " Version " ${${PROJECT_NAME}_VERSION} )

# Include config file
INCLUDE( ${PROJECT_SOURCE_DIR}/cmake/config.cmake )

# Define the path of our additional CMake modules
# We don't need this for a simple algorithm test like this
# SET( CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake/modules/" )

# Detect operating system
IF( APPLE )
	MESSAGE( WARNING "Apple has not yet been tested!" )
ELSEIF( WIN32 )
	MESSAGE( "Windows System detected" )
ELSEIF( UNIX )
	MESSAGE( "Unix System detected" )
ENDIF()

# SET default compiler flags
# Note: on some platforms (OS X), CMAKE_COMPILER_IS_GNUCXX is true
# even when CLANG is used, therefore the Clang test is done first
IF( CMAKE_CXX_COMPILER MATCHES ".*clang[+][+]" OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang" )
	# CMAKE_CXX_COMPILER_ID is an internal CMake variable subject to change,
	# but there is no other way to detect Clang at the moment
	MESSAGE( "Clang compiler detected" )
	MESSAGE( WARNING "Clang has not yet been tested or configured properly within the script!" )
	SET( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11" )
	IF( COMPILER_WARNING_HIGH )
		SET( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Weverything" )
	ENDIF()
	MESSAGE( "Compiler Flags: " ${CMAKE_CXX_FLAGS} )
ELSEIF( CMAKE_COMPILER_IS_GNUCXX )
	MESSAGE( "GCC Compiler detected" )
	SET( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1y" )
	IF( COMPILER_WARNING_HIGH )
		SET( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra" )
	ENDIF()
	MESSAGE( "Compiler Flags: " ${CMAKE_CXX_FLAGS} )
ELSEIF( MSVC )
	MESSAGE( "MSVC Compiler detected" )
	MESSAGE( WARNING "MSVC has not yet been tested or configured properly within the script!" )
	IF( COMPILER_WARNING_HIGH )
		IF( CMAKE_CXX_FLAGS MATCHES "/W[0-4]" )
			string( REGEX REPLACE "/W[0-4]" "/W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
		ELSE()
			SET( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4" )
		ENDIF()
	ELSE()
		IF( CMAKE_CXX_FLAGS MATCHES "/W[0-4]" )
			string( REGEX REPLACE "/W[0-4]" "/W2" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
		ELSE()
			SET( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W2" )
		ENDIF()
	ENDIF()
	MESSAGE( "Compiler Flags: " ${CMAKE_CXX_FLAGS} )
ELSE()
	MESSAGE( FATAL_ERROR "Unsupported compiler! Please add your compiler of choice to the cmake script!" )
	RETURN()
ENDIF()
ADD_DEFINITIONS( -DUNICODE -D_UNICODE ) # SET Unicode Definitions

# Demo source path
SET( ${PROJECT_NAME}_SRC_PATH ${PROJECT_SOURCE_DIR}/src )

# Include Files
SET( ${PROJECT_NAME}_INC_FILES
	${${PROJECT_NAME}_SRC_PATH}/attempts/attempt.h
	${${PROJECT_NAME}_SRC_PATH}/attempts/attemptClock.h
	${${PROJECT_NAME}_SRC_PATH}/attempts/attemptManager.h
	${${PROJECT_NAME}_SRC_PATH}/attempts/attemptResult.h
	${${PROJECT_NAME}_SRC_PATH}/attempts/attempts.h
	${${PROJECT_NAME}_SRC_PATH}/attempts/allAttempts/attempt01.h
	${${PROJECT_NAME}_SRC_PATH}/attempts/allAttempts/attempt02.h
	${${PROJECT_NAME}_SRC_PATH}/attempts/allAttempts/attempt03.h
	${${PROJECT_NAME}_SRC_PATH}/attempts/allAttempts/attempt04.h
)

# Source Files
SET( ${PROJECT_NAME}_SRC_FILES
	${${PROJECT_NAME}_SRC_PATH}/attempts/allAttempts/attempt01.cpp
	${${PROJECT_NAME}_SRC_PATH}/attempts/allAttempts/attempt02.cpp
	${${PROJECT_NAME}_SRC_PATH}/attempts/allAttempts/attempt03.cpp
	${${PROJECT_NAME}_SRC_PATH}/attempts/allAttempts/attempt04.cpp
	${${PROJECT_NAME}_SRC_PATH}/attempts/attemptManager.cpp
	${${PROJECT_NAME}_SRC_PATH}/main.cpp
)

# Demo executable building
INCLUDE_DIRECTORIES( ${${PROJECT_NAME}_SRC_PATH} )
ADD_EXECUTABLE( ${PROJECT_NAME} ${${PROJECT_NAME}_SRC_FILES} ${${PROJECT_NAME}_INC_FILES} )
IF( ${BUILD_FINAL_RESULT} )
	ADD_EXECUTABLE( ${PROJECT_NAME}_final ${${PROJECT_NAME}_SRC_PATH}/main_final.cpp )
ENDIF()

ADD_CUSTOM_COMMAND( TARGET ${PROJECT_NAME} POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_directory
	${PROJECT_SOURCE_DIR}/data $<TARGET_FILE_DIR:${PROJECT_NAME}>/data )

# Demo INSTALL
SET( ${PROJECT_NAME}_INSTALL_PATH ./ )

INSTALL( TARGETS ${PROJECT_NAME} RUNTIME DESTINATION ${${PROJECT_NAME}_INSTALL_PATH} )
IF( ${BUILD_FINAL_RESULT} )
	INSTALL( TARGETS ${PROJECT_NAME}_final RUNTIME DESTINATION ${${PROJECT_NAME}_INSTALL_PATH} )
ENDIF()
INSTALL( FILES
	${PROJECT_SOURCE_DIR}/data/TheReverseWordTest.txt
	DESTINATION ${${PROJECT_NAME}_INSTALL_PATH}/data )
