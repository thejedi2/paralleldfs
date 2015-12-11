#include <iostream>
#include <stack>
#include <time.h> 
#include <fstream>
#include <vector>
#include <sys/time.h>
#include <sstream>
//#include <tbb/tbb.h>

using namespace std;


#define NODE_SIZE 10000000

int isVisited[NODE_SIZE+1] = { 0 };
int isVisitedS[NODE_SIZE+1] = { 0 };


bool globFound = false;
int threadCnt = 1;

//mygraph g(ERGen(gen, NODE_SIZE, 0.005), ERGen(), NODE_SIZE);

vector< vector<int> > graph(NODE_SIZE + 1);

int startNode = 1;


//Utility func to split string in Text File
vector<string> splitString(string str) {
	string buf; // Have a buffer string
	stringstream ss(str); // Insert the string into a stream

	vector<string> tokens; // Create vector to hold our words

	while (ss >> buf)
		tokens.push_back(buf);

	return tokens;
}

void readGraph(string fileName) {
	std::ifstream file(fileName.c_str());
	std::string str;
	while (std::getline(file, str))
	{
		vector<string> v = splitString(str);

		graph[atoi(v[0].c_str())].push_back(atoi(v[1].c_str()));
		graph[atoi(v[1].c_str())].push_back(atoi(v[0].c_str()));	
	}
}

vector<int> getNeighbours(int v) {
	return graph[v];
}


void doDFSeq(int vertex) {

	stack<int> stk;

	stk.push(vertex);

	while (!stk.empty()) {
		int curr = stk.top();
		stk.pop();
		if (isVisited[curr] == 0) {
			isVisited[curr] = 1;
			vector<int> neighbours = getNeighbours(curr);
			//tie(neighbourIt, neighbourEnd) = adjacent_vertices(curr, g);


			for (int i = 0; i < neighbours.size(); i++) {
				
					if(isVisitedS[neighbours[i]] == 0){	
					stk.push(neighbours[i]);
					isVisitedS[neighbours[i]]=1;
					}
			}

		}
	}

       		 }



int main() {

    	readGraph("erdos10M.txt");

	struct timeval tim;
	
	gettimeofday(&tim, NULL);
  
        double t1=tim.tv_sec+(tim.tv_usec/1000000.0);
	
	
	doDFSeq(startNode);

	gettimeofday(&tim, NULL);

        double t2=tim.tv_sec+(tim.tv_usec/1000000.0);

	printf("%.6lf seconds elapsed serial\n", t2-t1);


	 for(int i=0;i<NODE_SIZE+1;i++){

        	if(isVisited[i] ==0)
       		 { cout << i << "\n"; }

        }
	getchar();

	return 0;
}
