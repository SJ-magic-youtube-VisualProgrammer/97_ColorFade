/************************************************************
************************************************************/
#include "ofApp.h"

/************************************************************
************************************************************/

/******************************
******************************/
ofApp::ofApp()
{
	font.load("font/RictyDiminished-Regular.ttf", 30, true/* _bAntiAliased */, true/* _bFullCharacterSet */, false/* makeContours */, 0.3/* simplifyAmt */, 72/* dpi*/);
}

/******************************
******************************/
ofApp::~ofApp()
{
	delete Gui_Global;
	
	if(fp_Log)	fclose(fp_Log);
}


/******************************
******************************/
void ofApp::exit(){
	printf("> Good-bye\n");
	fflush(stdout);
}

/******************************
******************************/
void ofApp::setup(){
	/********************
	********************/
	ofSetBackgroundAuto(true);
	
	ofSetWindowTitle("ColorFade");
	ofSetVerticalSync(true);
	ofSetFrameRate(30);
	ofSetWindowShape(MAIN_WINDOW_W, MAIN_WINDOW_H);
	ofSetEscapeQuitsApp(false);
	
	ofEnableAlphaBlending();
	ofEnableBlendMode(OF_BLENDMODE_ALPHA); // OF_BLENDMODE_ADD
	ofEnableSmoothing();
	
	ofSetCircleResolution(30);
	
	/********************
	********************/
	fp_Log = fopen("../../../data/Log.csv", "w");
	
	setup_Gui();
	
	/********************
	********************/
	img_back.load("img/img.png");
}

/******************************
description
	memoryを確保は、app start後にしないと、
	segmentation faultになってしまった。
******************************/
void ofApp::setup_Gui()
{
	/********************
	********************/
	Gui_Global = new GUI_GLOBAL;
	Gui_Global->setup("param", "gui.xml", 10, 10);
}

/******************************
******************************/
void ofApp::update(){
	/********************
	********************/
	int now = ofGetElapsedTimeMillis();
	
	/********************
	********************/
	if(Gui_Global->ColorFade__Button_StartFade){
		Gui_Global->ColorFade__Button_StartFade = false;
		State = STATE__FADE;
	}
	
	/********************
	********************/
	if(State == STATE__FADE){
		/********************
		********************/
		float dHue = (now - t_LastUpdate) / (Gui_Global->ColorFade__dt_HchangeFull * 1000);
		
		float diff = Gui_Global->ColorFade__H - H_current;
		diff = fmod(diff, 1.0);
		
		/********************
		********************/
		int sgn = 1;
		if(diff < 0) sgn = -1;
		
		diff = abs(diff);
		
		if(0.5 < diff) { diff = 1.0 - diff; sgn *= -1; }
		
		/********************
		********************/
		if(diff <= dHue){
			H_current = Gui_Global->ColorFade__H;
			State = STATE__WAIT;
		}else{
			H_current += sgn * dHue;
			
			H_current = fmod(H_current, 1.0);
			while(H_current < 0) { H_current += 1.0; }
		}
		
		/********************
		********************/
		// fprintf(fp_Log, "%f, %f, %f\n", dHue, float(Gui_Global->ColorFade__H), H_current);
	}
	
	/********************
	********************/
	t_LastUpdate = now;
}

/******************************
******************************/
void ofApp::draw(){
	/********************
	********************/
	ofBackground(0, 0, 0, 0);
	
	/********************
	********************/
	ofSetColor(255);
	
	img_back.draw(0, 0);
	
	draw_cusror("Current", H_current, glm::vec2(0, -350), glm::vec2(40, -341));
	draw_cusror("Target", Gui_Global->ColorFade__H, glm::vec2(0, -260), glm::vec2(40, -251));
	
	/********************
	********************/
	if(Gui_Global->b_Disp){
		Gui_Global->gui.draw();
		
		ofSetColor(255);
		string info;
		info += "FPS = " + ofToString(ofGetFrameRate(), 2) + "\n";
		ofDrawBitmapString(info, 30, 30);
	}
}

/******************************
******************************/
void ofApp::draw_cusror(string str_Caption, float Hue, glm::vec2 pos_Cursor, glm::vec2 pos_Font){
	/********************
	********************/
	float theta = ofMap(Hue, 0, 1.0, 0, 360);
	
	float H_255 = ofMap(Hue, 0, 1.0, 0, 255);
	float S_255 = ofMap(Gui_Global->ColorFade__S, 0, 1.0, 0, 255);
	float V_255 = ofMap(Gui_Global->ColorFade__V, 0, 1.0, 0, 255);
	
	ofColor col;
	col.setHsb(H_255, S_255, V_255, 255);
	
	ofPushMatrix();
		ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
		ofRotateZDeg(theta);
		
		ofSetColor(col);
		ofFill();
		ofDrawCircle(pos_Cursor, 30);
		
		font.drawString(str_Caption, pos_Font.x, pos_Font.y);
	ofPopMatrix();
}

/******************************
******************************/
void ofApp::keyPressed(int key){
	switch(key){
		case 'd':
			Gui_Global->b_Disp = !Gui_Global->b_Disp;
			break;
			
		case 'm':
			Gui_Global->gui.minimizeAll();
			break;
	}
}

/******************************
******************************/
void ofApp::keyReleased(int key){

}

/******************************
******************************/
void ofApp::mouseMoved(int x, int y ){

}

/******************************
******************************/
void ofApp::mouseDragged(int x, int y, int button){

}

/******************************
******************************/
void ofApp::mousePressed(int x, int y, int button){

}

/******************************
******************************/
void ofApp::mouseReleased(int x, int y, int button){

}

/******************************
******************************/
void ofApp::mouseEntered(int x, int y){

}

/******************************
******************************/
void ofApp::mouseExited(int x, int y){

}

/******************************
******************************/
void ofApp::windowResized(int w, int h){

}

/******************************
******************************/
void ofApp::gotMessage(ofMessage msg){

}

/******************************
******************************/
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
