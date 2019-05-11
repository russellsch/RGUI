
find_package(SDL2 REQUIRED)
find_package(Freetype REQUIRED)

# TODO: Create dependencies in readme and dockerfile
# TODO: sudo apt install libsdl2-dev
# TODO: sudo apt install libfreetype6-dev

# Get headers
set(header_path "${RGUI_SOURCE_DIR}/include/rgui")
set(header 
	${header_path}/something.h
	${header_path}/RGConst.hpp
	${header_path}/RGColor.hpp
	${header_path}/RGEvent.hpp
	${header_path}/RGOSWindow.hpp
	${header_path}/RGRect.hpp
	${header_path}/RGSDLWindow.hpp
	)


# Source
set(src 
	something.cpp
	RGColor.cpp
	RGEvent.cpp
	RGRect.cpp
	RGOSWindow.cpp
	RGSDLWindow.cpp
	)



add_library(rgui ${header} ${src})

target_include_directories(rgui 
	PUBLIC 
	${RGUI_SOURCE_DIR}/include
	${SDL2_INCLUDE_DIRS}
	${CMAKE_CURRENT_BINARY_DIR}
)

target_link_libraries(rgui ${SDL2_LIBRARIES})


