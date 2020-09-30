#pragma once

#include "ofMain.h"
#include "ofxAssimpModelLoader.h"

class BrainGlow {
private:
    ofxAssimpModelLoader brainModel;
    ofMesh brainMesh;
    ofShader brainShader;
    vector<vector<int>> adjList;
    vector<int> vecNum;
    vector<bool> visited;

    class CGragh {
    private:
        int numVertices;
        vector<vector<int>> adjList;
        vector<int> vecNum;
        //void DFSUtil(int v, bool visited[]);
    public:
        CGragh(const ofMesh& mesh);
        //void connectedComponents();
        vector<vector<int>> getAdjList();
        vector<int> getVecNum();
        const int getNumVertices();
    };

public:
    void init(string modelPath);
    vector<int> spread(vector<int> vecIndices);
    ofMesh getMesh();
};

