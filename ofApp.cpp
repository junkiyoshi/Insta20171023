#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	ofSetFrameRate(60);
	ofBackground(0);
	ofSetWindowTitle("Insta");

	ofSetCircleResolution(60);

	this->box2d.init();
	this->box2d.setGravity(0, 0);
	this->box2d.createBounds();
	this->box2d.setFPS(60);
	this->box2d.registerGrabbing();
}

//--------------------------------------------------------------
void ofApp::update() {
	if (ofGetMousePressed()) {
		ofVec2f mouse_position = ofVec2f(ofGetMouseX(), ofGetMouseY());
		ofVec2f prev_mouse_position = ofVec2f(ofGetPreviousMouseX(), ofGetPreviousMouseY());
		ofVec2f difference = mouse_position - prev_mouse_position;

		for (int i = 0; i < 10; i++) {
			this->circles.push_back(shared_ptr<ofxBox2dCircle>(new ofxBox2dCircle));
			this->circles.back().get()->setPhysics(3.0, 0.53, 0.1);
			this->circles.back().get()->setup(this->box2d.getWorld(), mouse_position.x, mouse_position.y, 5);
			this->circles.back().get()->addForce(difference, 20.0);

			ofColor line_color;
			line_color.setHsb(ofGetFrameNum() % 255, 255, 255);
			this->circles_color.push_back(line_color);

			this->circles_life.push_back(255);
		}
	}

	this->box2d.update();

	for (int i = 0; i < this->circles.size(); i++) {
		if (this->circles_life[i] < 0) {
			this->circles[i].get()->destroy();
			this->circles.erase(this->circles.begin() + i);
			this->circles_color.erase(this->circles_color.begin() + i);
			this->circles_life.erase(this->circles_life.begin() + i);
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {
	ofFill();

	for (int i = 0; i < this->circles.size(); i++) {
		ofSetColor(this->circles_color[i], this->circles_life[i]);
		//this->circles[i].get()->draw();
		ofDrawCircle(this->circles[i].get()->getPosition(), 5);
		this->circles_life[i] -= 1.5f;
	}
}

//--------------------------------------------------------------
int main() {
	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}