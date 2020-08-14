#include "BrainGlow.h"

void BrainGlow::init(string modelPath) {
	brainModel.loadModel(modelPath);
	brainModel.setScale(.75, .75, .75);
	brainModel.setPosition(75, -150, 0);
	brainModel.setRotation(brainModel.getNumRotations(), 90, 1, 0, 0);
	brainModel.setRotation(brainModel.getNumRotations(), -90, 0, 0, 1);

	CGragh cGraph(brainModel.getMesh(0));
	cGraph.connectedComponents();
	
}

void BrainGlow::CGragh::DFSUtil(int v, bool visited[]) {  
    // Mark the current node as visited and print it 
    visited[v] = true;
    cout << v << " ";

    // Recur for all the vertices 
    // adjacent to this vertex 
    list<int>::iterator i;
    for (i = adjList[v].begin(); i != adjList[v].end(); ++i)
        if (!visited[*i])
            DFSUtil(*i, visited);
}

BrainGlow::CGragh::CGragh(const ofMesh& mesh) {
	vector<pair<int, glm::vec3>> vecVert;
	for (size_t i = 0; i < mesh.getNumVertices(); i++) {
		vecVert.push_back(make_pair(i, mesh.getVertex(i)));
	}
	sort(vecVert.begin(), vecVert.end(), [](const pair<int, glm::vec3>& a, const pair<int, glm::vec3>& b) -> bool {
		if (abs(a.second.x - b.second.x) < 0.01) {
			if (abs(a.second.y - b.second.y) < 0.01) {
				return a.second.z < b.second.z;
			}
			else
				return a.second.y < b.second.y;
		}
		else
			return a.second.x < b.second.x;
		});
	vecVert.erase(unique(vecVert.begin(), vecVert.end(),
		[](const pair<int, glm::vec3>& a, const pair<int, glm::vec3>& b) {
			return abs(a.second.x - b.second.x) < 0.01 && abs(a.second.y - b.second.y) < 0.01 && abs(a.second.z - b.second.z) < 0.01;
		}), vecVert.end());

	numVertices = vecVert.size();
	adjList = new list<int>[numVertices];
	auto faces = mesh.getUniqueFaces();

	for (int i = 0; i < faces.size(); i++) {

		auto vert0 = faces[i].getVertex(0),
			vert1 = faces[i].getVertex(1),
			vert2 = faces[i].getVertex(2);

		auto iter0 = std::find_if(vecVert.begin(), vecVert.end(),
			[&](const pair<int, glm::vec3>& v) {
				return abs(v.second.x - vert0.x) < 0.01 && abs(v.second.y - vert0.y) < 0.01 && abs(v.second.z - vert0.z) < 0.01;
			});
		auto iter1 = std::find_if(vecVert.begin(), vecVert.end(),
			[&](const pair<int, glm::vec3>& v) {
				return abs(v.second.x - vert1.x) < 0.01 && abs(v.second.y - vert1.y) < 0.01 && abs(v.second.z - vert1.z) < 0.01;
			});
		auto iter2 = std::find_if(vecVert.begin(), vecVert.end(),
			[&](const pair<int, glm::vec3>& v) {
				return abs(v.second.x - vert2.x) < 0.01 && abs(v.second.y - vert2.y) < 0.01 && abs(v.second.z - vert2.z) < 0.01;
			});

		if (iter0 != vecVert.end() && iter1 != vecVert.end() && iter2 != vecVert.end()) {

			int idx0 = std::distance(vecVert.begin(), iter0),
				idx1 = std::distance(vecVert.begin(), iter1),
				idx2 = std::distance(vecVert.begin(), iter2);

			adjList[idx0].push_back(idx1);
			adjList[idx0].push_back(idx2);

			adjList[idx1].push_back(idx2);
			adjList[idx1].push_back(idx0);

			adjList[idx2].push_back(idx0);
			adjList[idx2].push_back(idx1);
		}
	}
}

void BrainGlow::CGragh::connectedComponents() {
    // Mark all the vertices as not visited 
    bool* visited = new bool[numVertices];
    for (int v = 0; v < numVertices; v++)
        visited[v] = false;

    for (int v = 0; v < numVertices; v++)
    {
        if (visited[v] == false)
        {
            // print all reachable vertices 
            // from v 
            DFSUtil(v, visited);

            cout << "\n";
        }
    }
    delete[] visited;
}
