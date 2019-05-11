
find_package(SDL2 REQUIRED)
find_package(Freetype REQUIRED)

set(OpenGL_GL_PREFERENCE GLVND)
find_package(OpenGL REQUIRED)
#find_package(GLEW REQUIRED)

# TODO: Create dependencies in readme and dockerfile
# TODO: sudo apt install libsdl2-dev
# TODO: sudo apt install libfreetype6-dev
# TODO: sudo apt install freeglut3-dev   ????

# Get headers
set(header_path "${RGUI_SOURCE_DIR}/include/rgui")
set(header
	${header_path}/KSBasicTimer.h
	${header_path}/RGConst.hpp
	${header_path}/RGColor.hpp
	${header_path}/RGDraw.hpp
	${header_path}/RGEvent.hpp
	${header_path}/RGObj.hpp
	${header_path}/RGOSWindow.hpp
	${header_path}/RGRect.hpp
	${header_path}/RGTTF.hpp
	${header_path}/RGSDLWindow.hpp
	)


# Source
set(src
	KSBasicTimer.cpp
	RGColor.cpp
	RGDraw.cpp
	RGEvent.cpp
	RGRect.cpp
	RGObj.cpp
	RGSDLWindow.cpp
	RGTTF.cpp
	)



add_library(rgui ${header} ${src})

target_include_directories(rgui 
	PUBLIC 
	${RGUI_SOURCE_DIR}/include
	${SDL2_INCLUDE_DIRS}
	${FREETYPE_INCLUDE_DIRS}

	${OPENGL_INCLUDE_DIR}
	${CMAKE_CURRENT_BINARY_DIR}
)

#${GLEW_INCLUDE_DIRS}

target_link_libraries(rgui
		${SDL2_LIBRARIES}
		${FREETYPE_LIBRARIES}
		OpenGL::OpenGL
		)
#		GLEW::GLEW)


set_target_properties(rgui PROPERTIES
		CXX_STANDARD 17
		)

