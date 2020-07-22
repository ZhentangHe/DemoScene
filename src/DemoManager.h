#pragma once

#include "ofMain.h"
#include "ofxAssimpModelLoader.h"
#include "FlowParticle.h"

class DemoManager {
private:
    static DemoManager* pinstance_;
    static std::mutex mutex_;

    //General Settings
    ofEasyCam cam;
    vector<int> timeSeq;
    of3dPrimitive area;

    //Flow Field Scene
    std::vector<std::shared_ptr<FlowParticle>> fpList;
    const int fpSize = 1000;

    //Wire Scene
    ofxAssimpModelLoader chipModel;

    //Brain Glowing Scene
    ofxAssimpModelLoader brainModel;
protected:
    DemoManager() {}
    ~DemoManager() {}
public:
    
    DemoManager(DemoManager& other) = delete;
    void operator=(const DemoManager&) = delete;

    static DemoManager* getInstance() {
        if (pinstance_ == nullptr) {
            std::lock_guard<std::mutex> lock(mutex_);
            if (pinstance_ == nullptr)
            {
                pinstance_ = new DemoManager();
            }
        }
        return pinstance_;
    }

    static void release() {
        if (pinstance_ != nullptr)
            delete pinstance_;
    }


};
