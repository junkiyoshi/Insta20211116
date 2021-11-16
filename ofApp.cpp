#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openFrameworks");

	ofBackground(255);
	ofSetRectMode(ofRectMode::OF_RECTMODE_CENTER);

	ofSetCircleResolution(36);
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
}

//--------------------------------------------------------------
void ofApp::draw() {

	ofTranslate(ofGetWindowSize() * 0.5);

	auto noise_seed = glm::vec3(ofRandom(1000), ofRandom(1000), ofRandom(1000));
	int tmp_x, tmp_y;

	ofSetLineWidth(2);
	ofSetColor(0);

	// Param 1
	ofBeginShape();
	for (int x = 340; x >= 120; x -= 1) {

		tmp_y = ofMap(ofNoise(noise_seed.x, x * 0.005 + ofGetFrameNum() * 0.01), 0, 1, -100, 100);
		ofVertex(x, tmp_y);
	}
	ofEndShape();

	ofDrawLine(glm::vec2(120, -100), glm::vec2(120, 100));
	ofDrawLine(glm::vec2(340, -100), glm::vec2(340, 100));

	ofColor color;
	int hue = ofMap(ofNoise(noise_seed.x, 120 * 0.005 + ofGetFrameNum() * 0.01), 0, 1, 0, 255);
	color.setHsb(hue, 230, 255);

	ofSetColor(color);
	ofFill();
	ofDrawCircle(glm::vec2(120, tmp_y), 15);

	ofSetColor(0);
	ofNoFill();
	ofDrawCircle(glm::vec2(120, tmp_y), 15);

	// Param 2
	ofBeginShape();
	for (int x = -340; x <= -120; x += 1) {

		tmp_y = ofMap(ofNoise(noise_seed.y, x * 0.005 - ofGetFrameNum() * 0.01), 0, 1, -100, 100);
		ofVertex(x, tmp_y);
	}
	ofEndShape();

	ofDrawLine(glm::vec2(-120, -100), glm::vec2(-120, 100));
	ofDrawLine(glm::vec2(-340, -100), glm::vec2(-340, 100));

	int gon = ofMap(ofNoise(noise_seed.y, -120 * 0.005 - ofGetFrameNum() * 0.01), 0, 1, 3, 8);
	int deg_span = 360 / gon;

	ofSetColor(255);
	ofFill();
	ofBeginShape();
	for (int deg = 0; deg < 360; deg += deg_span) {

		ofVertex(glm::vec2(15 * cos(deg * DEG_TO_RAD), 15 * sin(deg * DEG_TO_RAD)) + glm::vec2(-120, tmp_y));
	}
	ofEndShape(true);

	ofSetColor(0);
	ofNoFill();
	ofBeginShape();
	for (int deg = 0; deg < 360; deg += deg_span) {

		ofVertex(glm::vec2(15 * cos(deg * DEG_TO_RAD), 15 * sin(deg * DEG_TO_RAD)) + glm::vec2(-120, tmp_y));
	}
	ofEndShape(true);
	
	// Param 3
	ofBeginShape();
	for (int y = -340; y <= -120; y += 1) {

		tmp_x = ofMap(ofNoise(noise_seed.z, y * 0.005 - ofGetFrameNum() * 0.01), 0, 1, -100, 100);
		ofVertex(tmp_x, y);
	}
	ofEndShape();

	ofDrawLine(glm::vec2(-100, -120), glm::vec2(100, -120));
	ofDrawLine(glm::vec2(-100, -340), glm::vec2(100, -340));

	int deg_start = ofMap(ofNoise(noise_seed.z, -120 * 0.005 - ofGetFrameNum() * 0.01), 0, 1, 0, 360);
	
	ofSetColor(255);
	ofFill();
	ofBeginShape();
	for (int deg = deg_start; deg < deg_start + 360; deg += 90) {

		ofVertex(glm::vec2(15 * cos(deg * DEG_TO_RAD), 15 * sin(deg * DEG_TO_RAD)) + glm::vec2(tmp_x, -120));
	}
	ofEndShape(true);

	ofSetColor(0);
	ofNoFill();
	ofBeginShape();
	for (int deg = deg_start; deg < deg_start + 360; deg += 90) {

		ofVertex(glm::vec2(15 * cos(deg * DEG_TO_RAD), 15 * sin(deg * DEG_TO_RAD)) + glm::vec2(tmp_x, -120));
	}
	ofEndShape(true);

	// Draw
	ofSetLineWidth(2);
	for (int y = 250; y > 0; y -= 10) {

		hue = ofMap(ofNoise(noise_seed.x, 120 * 0.005 + (ofGetFrameNum() - y / 5) * 0.01), 0, 1, 0, 255);
		color.setHsb(hue, 230, 255);

		gon = ofMap(ofNoise(noise_seed.y, -120 * 0.005 - (ofGetFrameNum() - y / 5) * 0.01), 0, 1, 3, 8);
		deg_span = 360 / gon;

		int deg_start = ofMap(ofNoise(noise_seed.z, -120 * 0.005 - (ofGetFrameNum() - y / 5) * 0.01), 0, 1, 0, 360);
		float alpha = ofMap(y, 320, 0, 0, 255);

		ofSetColor(color, alpha);
		ofFill();
		ofBeginShape();
		for (int deg = deg_start; deg <= deg_start + 360; deg += deg_span) {

			ofVertex(glm::vec2(85 * cos(deg * DEG_TO_RAD), 85 * sin(deg * DEG_TO_RAD)) + glm::vec2(0, y));
		}
		ofEndShape(true);

		ofSetColor(255, alpha);
		ofNoFill();
		ofBeginShape();
		for (int deg = deg_start; deg <= deg_start + 360; deg += deg_span) {

			ofVertex(glm::vec2(85 * cos(deg * DEG_TO_RAD), 85 * sin(deg * DEG_TO_RAD)) + glm::vec2(0, y));
		}
		ofEndShape(true);
	}
}

//--------------------------------------------------------------6
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}