#pragma once

#include "ofMain.h"

class FlowParticle {

public:
	FlowParticle() = delete;
	FlowParticle(int i);
	FlowParticle(ofVec2f& l);
	FlowParticle(ofVec2f& l, float& fix);
	~FlowParticle();
	void update();
	bool checkEdge();
	void display();
private:
	ofVec3f vel;	//velocity
	ofVec3f acc;	//acceleration
	ofVec3f pos;	//position 
	ofColor color;  //color
	int life;
	std::vector<std::shared_ptr<FlowParticle>> fpList;

	bool isDead();
};

