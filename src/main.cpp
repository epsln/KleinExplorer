#include "ofMain.h"
#include "tree_explorer.h"
#include "Mobius.h"
#include "ofApp.h"

//========================================================================
int main( ){
	//Use ofGLFWWindowSettings for more options like multi-monitor fullscreen
	ofGLWindowSettings settings;
	settings.setSize(1024, 1024);
	settings.windowMode = OF_WINDOW; //can also be OF_FULLSCREEN

	auto window = ofCreateWindow(settings);

	//ke = KleinExplorer();

	ofRunApp(window, make_shared<ofApp>());
	ofRunMainLoop();

}
