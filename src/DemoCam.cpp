#include "DemoCam.h"

DemoCam::DemoCam(ofVec3f initPos, ofVec3f initDir) :initPos(initPos), initDir(initDir) {
	cam.setPosition(initPos);
	cam.lookAt(initDir, ofVec3f(0, 1, 0));
}

DemoCam::~DemoCam() {

}

void DemoCam::update() {
	if (ofGetFrameNum() < vecJunc[SIZE]) {
		float tweenvalue = (float)(ofGetFrameNum() - vecJunc[phase - 1]) / (float)(vecJunc[phase] - vecJunc[phase - 1]);

		//when each phase starts:
		if (phase <= SIZE && ofGetFrameNum() == vecJunc[phase - 1]) {
			startPos.set(cam.getGlobalPosition());
			targetPos.set(vecPos[phase - 1]);

			startQuat = cam.getGlobalOrientation();
			targetQuat = glm::conjugate(glm::toQuat(glm::lookAt((glm::vec3)targetPos, vecDir[phase - 1], glm::vec3(0, 1, 0))));

			if (ofGetFrameNum() != 0) {
				phase++;
			}
		}

		ofQuaternion tweenedCameraQuaternion;

		tweenedCameraQuaternion.slerp(tweenvalue, startQuat, targetQuat);

		ofVec3f lerpPos = startPos + ((targetPos - startPos) * tweenvalue);

		cam.setOrientation(tweenedCameraQuaternion);
		cam.setGlobalPosition(lerpPos);
		cout << lerpPos << endl;

	}
}

void DemoCam::begin() {
	cam.begin();
}

void DemoCam::end() {
	cam.end();
}
