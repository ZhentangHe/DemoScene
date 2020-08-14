#pragma once

#include "ofMain.h"
#include "ofxAssimpModelLoader.h"

class BrainGlow {
private:
	ofxAssimpModelLoader brainModel;
	ofMesh brainMesh;
	ofShader brainShader;
    class CGragh {
        int numVertices;
        list<int>* adjList;
        void DFSUtil(int v, bool visited[]);
    public:
        CGragh(const ofMesh& mesh);
        void connectedComponents();
    };
public:
	void init(string modelPath);
};

