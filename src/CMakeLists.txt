
find_package(SDL2 REQUIRED)
find_package(Freetype REQUIRED)

set(OpenGL_GL_PREFERENCE GLVND)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)

# TODO: Create dependencies in readme and dockerfile
# TODO: sudo apt install libsdl2-dev
# TODO: sudo apt install libfreetype6-dev
# TODO: sudo apt install freeglut3-dev   ????
# TODO: GLEW????

# Get headers
set(header_path "${RGUI_SOURCE_DIR}/include/rgui")
set(header
	${RGUI_SOURCE_DIR}/include/rgui.hpp
	${header_path}/KSBasicTimer.h
	${header_path}/RGApp.hpp
	${header_path}/RGConst.hpp
	${header_path}/ColorRGBA.hpp
	${header_path}/RGDraw.hpp
	${header_path}/RGEventHandlerBase.hpp
	${header_path}/RGObj.hpp
	${header_path}/RGOSWindow.hpp
	${header_path}/RGShader.hpp
	${header_path}/RGRect.hpp
	${header_path}/RGRoot.hpp
	${header_path}/RGTTF.hpp
	${header_path}/RGSDLWindow.hpp
	${header_path}/ui/RGButton.hpp
	${header_path}/ui/RGCheckGroup.hpp
	${header_path}/ui/RGFrame.hpp
	${header_path}/ui/RGGraph.hpp
	${header_path}/ui/RGLabel.hpp
	${header_path}/ui/RGLineGraph.hpp
	${header_path}/ui/RGList.hpp
	${header_path}/ui/RGRadioGroup.hpp
	${header_path}/ui/RGSlider.hpp
	${header_path}/ui/RGToggle.hpp
)

# Source
set(src
	KSBasicTimer.cpp
	RGApp.cpp
	ColorRGBA.cpp
	RGDraw.cpp
	RGEventHandlerBase.cpp
	RGObj.cpp
	RGRect.cpp
	RGRoot.cpp
	RGShader.cpp
	RGSDLWindow.cpp
	RGTTF.cpp
	ui/RGButton.cpp
	ui/RGCheckGroup.cpp
	ui/RGFrame.cpp
	ui/RGGraph.cpp
	ui/RGLabel.cpp
	ui/RGLineGraph.cpp
	ui/RGList.cpp
	ui/RGRadioGroup.cpp
	ui/RGSlider.cpp
	ui/RGToggle.cpp
		)



add_library(rgui
		${header}
		${src}
		)

target_include_directories(rgui 
	PUBLIC 
	${RGUI_SOURCE_DIR}/include
	${SDL2_INCLUDE_DIRS}
	${FREETYPE_INCLUDE_DIRS}
	${OPENGL_INCLUDE_DIR}
	${GLEW_INCLUDE_DIRS}

	${OPENGL_INCLUDE_DIR}
	${CMAKE_CURRENT_BINARY_DIR}
)


#Strip whitespace from SDL libraries to Cmake errors
string(STRIP ${SDL2_LIBRARIES} SDL2_LIBRARIES)

target_link_libraries(rgui
		${SDL2_LIBRARIES}
		${FREETYPE_LIBRARIES}
		#OpenGL::OpenGL
		${OPENGL_LIBRARIES}
		GLEW::GLEW
		stdc++fs 	#Experimental C++17 filesystem
		)


set_target_properties(rgui PROPERTIES
		CXX_STANDARD 17
		)

