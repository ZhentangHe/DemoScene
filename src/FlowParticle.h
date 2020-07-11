#pragma once

#include "ofMain.h"

class FlowParticle {

public:
	FlowParticle() = delete;
	FlowParticle(const ofVec3f& initPos);
	~FlowParticle();

	void update();
	bool checkEdge();
	void display();
	const bool isDead() const;
	//TODO: get; set;
private:
	ofVec3f vel;	//velocity
	ofVec3f acc;	//acceleration
	ofVec3f pos;	//position 
	ofColor color;  //color
	float speed;
	int life;
	//std::vector<std::shared_ptr<FlowParticle>> fpList;

};
