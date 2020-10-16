#pragma once

#include "ofMain.h"

class DemoCam{
public:
	DemoCam(ofVec3f initPos, ofVec3f initDir);
	~DemoCam();

	void update();
	void begin();
	void end();
private:
	ofEasyCam cam;

	ofVec3f initPos;
	ofVec3f initDir;

	ofVec3f startPos;
	ofVec3f targetPos;

	ofQuaternion startQuat;
	ofQuaternion targetQuat;

	size_t phase = 1;
	const size_t SIZE = 3;
	const vector<glm::vec3> vecPos{ {100, 200, 2000},{100,200,1000},{100,200,1000} };
	const vector<glm::vec3> vecDir{ {-50, 150, 2050},{-50,200,500},{-50,200,500} };
	const vector<int> vecJunc{ 0, 300, 600, 1200 };
};