/**
 *
 * OFDevCon Example Code Sprint
 * Quaternion Example for plotting latitude and longitude onto a sphere
 *
 * Created by James George on 2/23/2012
 */

#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

	
	ofSetFrameRate(30);
	ofEnableAlphaBlending();
	ofNoFill();
	
	// create little objects for each city. 
	// A Lat/Lon like this: 
	// Lewiston, Idaho 	W 46 24' N 117 2'
	// This translate to angles and degrees (1 degree = 1/60. of an angle)
	// West and South are negative values
	
	// here is a list of big cities and their positions
	// http://www.infoplease.com/ipa/A0001796.html
	
    //read in earthquakes
    csv.loadFile(ofToDataPath("earthquakes_all_month.csv"));
    for(int i=1; i < csv.numRows; i++){
      Earthquake quake;
      quake.latitude = ofToFloat(csv.data[i][1]);
      quake.longitude = ofToFloat(csv.data[i][2]);
      quake.name = ofToString(csv.data[i][13]);
      earthquakes.push_back(quake);
    }
}

//--------------------------------------------------------------
void ofApp::update(){
	
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofBackground(0);
	
	ofPushMatrix();
	
	//translate so that the center of the screen is 0,0
	ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
	ofSetColor(255, 255, 255, 20);
	
	//draw a translucent wireframe sphere (ofNoFill() is on)
	ofPushMatrix();
	//add an extra spin at the rate of 1 degree per frame
	ofRotate(ofGetFrameNum(), 0, 1, 0);
	ofDrawSphere(0, 0, 0, 300);
	ofPopMatrix();
	
	ofSetColor(255);	
	for(unsigned int i = 0; i < earthquakes.size(); i++){
		
		//three rotations
		//two to represent the latitude and lontitude of the city
		//a third so that it spins along with the spinning sphere 
		ofQuaternion latRot, longRot, spinQuat;
		latRot.makeRotate(earthquakes[i].latitude, 1, 0, 0);
		longRot.makeRotate(earthquakes[i].longitude, 0, 1, 0);
		spinQuat.makeRotate(ofGetFrameNum(), 0, 1, 0);
		
		//our starting point is 0,0, on the surface of our sphere, this is where the meridian and equator meet
		ofVec3f center = ofVec3f(0,0,300);
		//multiplying a quat with another quat combines their rotations into one quat
		//multiplying a quat to a vector applies the quat's rotation to that vector
		//so to to generate our point on the sphere, multiply all of our quaternions together then multiple the centery by the combined rotation
		ofVec3f worldPoint = latRot * longRot * spinQuat * center;
		
		//draw it and label it
		ofDrawLine(ofVec3f(0,0,0), worldPoint);

		//set the bitmap text mode billboard so the points show up correctly in 3d
		ofDrawBitmapString(earthquakes[i].name, worldPoint );
	}
	
	ofPopMatrix();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
