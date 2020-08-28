#pragma once

#include "ofMain.h"
#include "ofxAssimpModelLoader.h"

class BrainGlow {
private:
    ofxAssimpModelLoader brainModel;
    ofMesh brainMesh;
    ofShader brainShader;//TODO
    vector<vector<int>> adjList;
    vector<bool> visited;
    class CGragh {
        int numVertices;
        vector<vector<int>> adjList;
        void DFSUtil(int v, bool visited[]);
    public:
        CGragh(const ofMesh& mesh);
        void connectedComponents();
        vector<vector<int>> getAdjList();
        const int getNumVertices();
    };
public:
    void init(string modelPath);
    vector<int> spread(vector<int> vecIndices);
    ofMesh getMesh();
};

