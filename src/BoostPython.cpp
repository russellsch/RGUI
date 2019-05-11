#ifndef _BOOST_PYTHON_RGUI
#define _BOOST_PYTHON_RGUI

#include "RGApp.hpp"
#include "RGRoot.hpp"
#include "RGButton.hpp"
#include "RGSlider.hpp"
#include "RGList.hpp"
#include "RGFrame.hpp"
#include "RGToggle.hpp"
#include "RGRadioGroup.hpp"
#include "RGGraph.hpp"
#include "RGColor.hpp"
#include "TestApp.hpp"

#include <string>

#include <boost/python/class.hpp>
#include <boost/python/module.hpp>
#include <boost/python/def.hpp>
#include <boost/python/wrapper.hpp>


struct RGAppWrap : RGApp, boost::python::wrapper<RGApp>{
	//wrap the virtuals
	void setup() {
		if(boost::python::override setup = this->get_override("setup")) {
			setup();
			return;
		}
		RGApp::setup();
		return; 
	}
	void default_setup() { 
		this->RGApp::setup();
		return;
	} 
	
	void update() {
		if(boost::python::override update = this->get_override("update")) {
			update();
			return;
		}
		RGApp::update();
		return; 
	}
	void default_update() { 
		this->RGApp::update();
		return;
	} 
	
	void draw() {
		if(boost::python::override draw = this->get_override("draw")) {
			draw();
			return;
		}
		RGApp::draw();
		return; 
	}
	void default_draw() { 
		this->RGApp::draw();
		return;
	} 
	
	void exit() {
		if(boost::python::override exit = this->get_override("exit")) {
			exit();
			return;
		}
		RGApp::exit();
		return; 
	}
	void default_exit() { 
		this->RGApp::exit();
		return;
	} 	
};


struct RGObjWrap : RGObj, boost::python::wrapper<RGObj>{
	void preChildrenRender(int xOffset, int yOffset) {
		if(boost::python::override preChildrenRender = this->get_override("preChildrenRender")) {
			preChildrenRender(xOffset, yOffset);
			return;
		}
		RGObj::preChildrenRender(xOffset, yOffset);
		return; 
	}
	void default_preChildrenRender(int xOffset, int yOffset) { 
		this->RGObj::preChildrenRender(xOffset, yOffset);
		return;
	} 

};

BOOST_PYTHON_MODULE(rgui_ext) {
	using namespace boost::python;
	
	
	class_<RGAppWrap, boost::noncopyable>("RGApp")
		.def("runApp", &RGApp::runApp)
		.add_property("windowW", &RGApp::getWindowW)
		.add_property("windowH", &RGApp::getWindowH)
		.def("setup", &RGApp::setup, &RGAppWrap::default_setup)
		.def("update", &RGApp::update, &RGAppWrap::default_update)
		.def("draw", &RGApp::draw, &RGAppWrap::default_draw)
		.def("exit", &RGApp::exit, &RGAppWrap::default_exit)
	;
	
	class_<TestApp, bases<RGApp> >("TestApp")

	;
	
	class_<RGColor>("RGColor")
		.def(init<int>())
		.def(init<int, int>())
		.def(init<int, int, int>())
		.def(init<int, int, int, int>())
		.def_readwrite("r", &RGColor::r)
		.def_readwrite("g", &RGColor::g)
		.def_readwrite("b", &RGColor::b)
		.def_readwrite("a", &RGColor::a)
	;
	
	class_<RGObjWrap, boost::noncopyable>("RGObj")
		.def( init<std::string, std::string, int, int, int, int>() )
	
		.def("pressEvent", &RGObj::pressEvent)
		.def("releaseEvent", &RGObj::releaseEvent)
		.def("dragEvent", &RGObj::dragEvent)
		.def("resizeEvent", &RGObj::resizeEvent)
		
		.def("mouseOverChild", &RGObj::mouseOverChild)
		
	
		.def("preChildrenRender", &RGObjWrap::preChildrenRender)
	;
	

	
	class_<RGButton >("RGButton", init<std::string, int, int, int, int, std::wstring>())
	
	;

}

#endif