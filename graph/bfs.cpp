//Graph drirected breadth search traversal

#include<iostream>
#include<list>
using namespace std;

class graph{
private:
	list<int> *adj;
	int vertices;

public:
	graph(int v): vertices(v){
		adj=new list<int>[v];
	}

	void addEdges(int start, int end)
	{
		adj[start].push_back(end);
	}
	 void bfs(int vertex);
};

void graph::bfs(int  v)
{
	list<int> queue;

	bool *visited = new bool[vertices];

	// set everything to false
	for(int i=0; i<vertices; i++)
	{
		visited[i]=false;
	}

	//now start from v
	visited[v]=true;
	queue.push_back(v);
	cout<<v<<" ";
	//now do breadth first search till queue is empty
	while(!queue.empty())
	{
		int front= queue.front();
		queue.pop_front();
		// print adjacent vertices if it is not visited and push to queue
		adj[front].sort();
		for(list<int>::iterator it=adj[front].begin(); it!=adj[front].end() ; it++){
			if(!visited[*it]){
				visited[*it]=true;
				cout<<*it<<" ";
				queue.push_back(*it);
			}
		}
	}

}


int main()
{
	graph a(4);
	a.addEdges(0,1);
	a.addEdges(0,2);
	a.addEdges(1,2);
	a.addEdges(2,3);
	a.addEdges(2,0);
	a.addEdges(3,3);
	a.bfs(2);
}
