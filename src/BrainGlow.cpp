#include "BrainGlow.h"
#include <unordered_set>

void BrainGlow::init(string modelPath) {

	brainModel.loadModel(modelPath);
	brainModel.setScale(.75, .75, .75);
	brainModel.setPosition(75, -150, 0);
	brainModel.setRotation(brainModel.getNumRotations(), 90, 1, 0, 0);
	brainModel.setRotation(brainModel.getNumRotations(), -90, 0, 0, 1);

	CGragh cGraph(brainModel.getMesh(0));
	adjList = cGraph.getAdjList();
	vecNum = cGraph.getVecNum();

	//cGraph.connectedComponents();
	visited.resize(cGraph.getNumVertices(), false);
	brainMesh.setMode(OF_PRIMITIVE_LINES);
	visited[0] = true;
	//cGraph.getAdjList()[0][(int)ofRandom(cGraph.getAdjList()[0].size())];

}

vector<int> BrainGlow::spread(vector<int> vecIdxForeSpread) {
	vector<int> vecIdxPostSpread;
	for (auto idx : vecIdxForeSpread) {
		size_t sampleSize = adjList[idx].size() / 2;
		//int sampleSize = ofRandom(min((size_t)4, adjList[idx].size()));
		//if (sampleSize == 0)
		//	sampleSize++;
		ofFloatColor color(ofRandom(1), ofRandom(1), ofRandom(1));
		random_shuffle(adjList[idx].begin(), adjList[idx].end());
		for (size_t i = 0; i < sampleSize; i++) {
			if (!visited[adjList[idx][i]]) {
				brainMesh.addVertex(brainModel.getMesh(0).getVertex(vecNum[idx]));
				//brainMesh.addColor(color);
				int adjacent = adjList[idx][i];
				brainMesh.addVertex(brainModel.getMesh(0).getVertex(vecNum[adjacent]));
				//brainMesh.addColor(color);
				visited[adjacent] = true;
				vecIdxPostSpread.push_back(adjacent);
			}
		}
	}
	return vecIdxPostSpread;
}

ofMesh BrainGlow::getMesh() {
	return brainMesh;
}

//deprecated
//void BrainGlow::CGragh::DFSUtil(int v, bool visited[]) {
//
//	// Mark the current node as visited and print it 
//	visited[v] = true;
//	cout << v << " ";
//
//	// Recur for all the vertices 
//	// adjacent to this vertex 
//	for (auto i = adjList[v].begin(); i != adjList[v].end(); ++i)
//		if (!visited[*i])
//			DFSUtil(*i, visited);
//
//}

BrainGlow::CGragh::CGragh(const ofMesh& mesh) {

	//get non-overlapping vertices for given mesh
	//1687 non-overlapping vertices, 9996 overlapping vertices
	vector<pair<int, glm::vec3>> vecVert;
	vecVert.clear();
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

	// get renumbering list for vertices
	vecNum.resize(vecVert.size());
	for (int i = 0; i < vecVert.size(); i++) {
		vecNum[i] = vecVert[i].first;
	}

	numVertices = vecVert.size();
	adjList.resize(numVertices);
	auto faces = mesh.getUniqueFaces();

	//get adjacent list for given mesh
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

	//remove duplicated neighbors
	auto remove = [](vector<int>& v) {
		auto itr = v.begin();
		unordered_set<int> s;
		for (auto curr = v.begin(); curr != v.end(); ++curr) {
			if (s.insert(*curr).second)
				*itr++ = *curr;
		}
		v.erase(itr, v.end());
	};
	for (int i = 0; i < adjList.size(); i++) {
		remove(adjList[i]);
	}
}

//deprecated
//void BrainGlow::CGragh::connectedComponents() {
//	// Mark all the vertices as not visited 
//	bool* visited = new bool[numVertices];
//	for (int v = 0; v < numVertices; v++)
//		visited[v] = false;
//
//	for (int v = 0; v < numVertices; v++)
//	{
//		if (visited[v] == false)
//		{
//			// print all reachable vertices 
//			// from v 
//			DFSUtil(v, visited);
//
//			cout << "\n\n";
//		}
//	}
//	delete[] visited;
//}

vector<vector<int>> BrainGlow::CGragh::getAdjList() {
	return adjList;
}

vector<int> BrainGlow::CGragh::getVecNum()
{
	return vecNum;
}

const int BrainGlow::CGragh::getNumVertices() {
	return numVertices;
}
