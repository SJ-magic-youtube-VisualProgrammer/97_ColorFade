/************************************************************
************************************************************/
#pragma once

/************************************************************
************************************************************/
#include "ofMain.h"
#include "sj_common.h"

/************************************************************
************************************************************/

class ofApp : public ofBaseApp{
private:
	/****************************************
	****************************************/
	enum{
		MAIN_WINDOW_W	= 800,
		MAIN_WINDOW_H	= 800,
	};
	
	enum STATE{
		STATE__WAIT,
		STATE__FADE,
	};
	
	/****************************************
	****************************************/
	ofImage img_back;
	ofTrueTypeFont font;
	
	float H_current = 0.0;
	
	STATE State = STATE__WAIT;
	int t_LastUpdate;
	
	/****************************************
	****************************************/
	void setup_Gui();
	void draw_cusror(string str_Caption, float Hue, glm::vec2 pos_Cursor, glm::vec2 pos_Font);
	
public:
	/****************************************
	****************************************/
	ofApp();
	~ofApp();
	
	void setup();
	void update();
	void draw();
	void exit();
	
	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y );
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void mouseEntered(int x, int y);
	void mouseExited(int x, int y);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);
};
