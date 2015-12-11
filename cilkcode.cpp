#include <iostream>
#include <stack>
#include <time.h> 
#include <cilk/cilk.h> 
#include <cilk/cilk_api.h>
#include <cilk/reducer_ostream.h>
#include <fstream>
#include <vector>
#include <sstream>
#include <sys/time.h>
#include <tbb/tbb.h>

using namespace std;


#define NODE_SIZE 3000000

tbb::concurrent_vector<int> isVisited (NODE_SIZE+1);
tbb::concurrent_vector<int> isVisitedS (NODE_SIZE+1);

int cores1 = 8;
int LOCAL_LIMIT = NODE_SIZE/(cores1*7.5);
bool globFound = false;
int threadCnt = 1;

int cnt =0;

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
	}
}

vector<int> getNeighbours(int v) {
	return graph[v];
}

stack< vector<int> > getWork(int cores) {
        stack< vector<int> > workStacks;

        vector<int> A   = getNeighbours(1);

        vector<int> neighbours = A;

        isVisited[1] = 1;
        isVisitedS[1] = 1;
        int size = neighbours.size();

	int interval = size/cores;
         for(int j=0; j<cores; j++){
                vector<int> stk;
                for(int i=0; i < interval; i++) {
                   int curr = neighbours.back();
		if(!neighbours.empty()){
                   neighbours.pop_back();
                   stk.push_back(curr);
			}
                 }
                workStacks.push(stk);
        }

        return workStacks;
}

void doDFS(vector<int> &stk) {

	while (!stk.empty()) {
		if (stk.size() > LOCAL_LIMIT) {
			
			std::size_t const half_size = stk.size() / 2;
			std::vector<int> split_lo(stk.begin(), stk.begin() + half_size);
			std::vector<int> split_hi(stk.begin() + half_size, stk.end());
			cilk_spawn doDFS(split_hi);	
			cilk_spawn doDFS(split_lo);
			cilk_sync;

			return;
			//stk = split_lo;
		}
		int curr = stk.back();
		stk.pop_back();
		if (isVisited[curr] == 0) {
		
			vector<int> neighbours = getNeighbours(curr);

			for (int i = 0; i < neighbours.size(); i++) {

				if(isVisitedS[neighbours[i]] == 0){
                                   stk.push_back(neighbours[i]);
                                  isVisitedS[neighbours[i]]=1;
                                       }
					
			}
			isVisited[curr] = 1;
		}
	}
		
	
}


int main() {


        readGraph("erdos3M.txt");

	stack< vector<int> > workStacks = getWork(cores1);
	
	struct timeval tim;
	
	gettimeofday(&tim, NULL);
  
        double t1=tim.tv_sec+(tim.tv_usec/1000000.0);  

	int i =4;

	if(cores1 == 2){
        vector<int> g1= workStacks.top();
        cilk_spawn doDFS(g1);
        workStacks.pop();
        vector<int> g2= workStacks.top();
        cilk_spawn doDFS(g2);
        workStacks.pop();
        }
		
	if(cores1 == 4){
	vector<int> g1= workStacks.top();
	cilk_spawn doDFS(g1);
        workStacks.pop();
        vector<int> g2= workStacks.top();
        cilk_spawn doDFS(g2);
	workStacks.pop();
        vector<int> g3= workStacks.top();
        cilk_spawn doDFS(g3);
        workStacks.pop();
        vector<int> g4= workStacks.top();
        cilk_spawn doDFS(g4);
	workStacks.pop();
	}

	if(cores1 == 8){
	 vector<int> g1= workStacks.top();
        cilk_spawn doDFS(g1);
        workStacks.pop();
        vector<int> g2= workStacks.top();
        cilk_spawn doDFS(g2);
        workStacks.pop();
        vector<int> g3= workStacks.top();
        cilk_spawn doDFS(g3);
        workStacks.pop();
        vector<int> g4= workStacks.top();
        cilk_spawn doDFS(g4);
        workStacks.pop();
	 vector<int> g5= workStacks.top();
        cilk_spawn doDFS(g5);
        workStacks.pop();
        vector<int> g6= workStacks.top();
        cilk_spawn doDFS(g6);
        workStacks.pop();
        vector<int> g7= workStacks.top();
        cilk_spawn doDFS(g7);
        workStacks.pop();
        vector<int> g8= workStacks.top();
        cilk_spawn doDFS(g8);
        workStacks.pop();
	}
	
	 if(cores1 >= 16){
         vector<int> g1= workStacks.top();
        cilk_spawn doDFS(g1);
        workStacks.pop();
        vector<int> g2= workStacks.top();
        cilk_spawn doDFS(g2);
        workStacks.pop();
        cout << "into 2";
        vector<int> g3= workStacks.top();
        cilk_spawn doDFS(g3);
        workStacks.pop();
        vector<int> g4= workStacks.top();
        cilk_spawn doDFS(g4);
        workStacks.pop();
         vector<int> g5= workStacks.top();
        cilk_spawn doDFS(g5);
        workStacks.pop();
        vector<int> g6= workStacks.top();
        cilk_spawn doDFS(g6);
        workStacks.pop();
        vector<int> g7= workStacks.top();
        cilk_spawn doDFS(g7);
        workStacks.pop();
        vector<int> g8= workStacks.top();
        cilk_spawn doDFS(g8);
        workStacks.pop();
	 vector<int> g9= workStacks.top();
        cilk_spawn doDFS(g9);
        workStacks.pop();
        vector<int> g10= workStacks.top();
        cilk_spawn doDFS(g10);
        workStacks.pop();
        vector<int> g11= workStacks.top();
        cilk_spawn doDFS(g11);
        workStacks.pop();
        vector<int> g12= workStacks.top();
        cilk_spawn doDFS(g12);
        workStacks.pop();
         vector<int> g13= workStacks.top();
        cilk_spawn doDFS(g13);
        workStacks.pop();
        vector<int> g14= workStacks.top();
        cilk_spawn doDFS(g14);
        workStacks.pop();
        vector<int> g15= workStacks.top();
        cilk_spawn doDFS(g15);
        workStacks.pop();
        vector<int> g16= workStacks.top();
        cilk_spawn doDFS(g16);
        }

	cout << "\n";

	cilk_sync;

	gettimeofday(&tim, NULL);

        double t2=tim.tv_sec+(tim.tv_usec/1000000.0);

	printf("%.6lf seconds elapsed Parallel\n", t2-t1);  


	 for(int i=0;i<NODE_SIZE+1;i++){

                if(isVisited[i] ==0)
                 { cout << i; }

        }

	getchar();

	return 0;
}
