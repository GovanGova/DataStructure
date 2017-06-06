//Graph drirected breadth search traversal

#include<iostream>
#include<list>
#include<map>
using namespace std;

class graph{
private:
	list<int> *adj;
	int vertices;
	map<int,bool> visited;
	list<int> queue;
public:
	graph(int v): vertices(v){
		adj=new list<int>[v];
	}

	void addEdges(int start, int end)
	{
		adj[start].push_back(end);
	}
	 void topology(int vertex);
	 void topologysort(int v);
};

void graph::topologysort(int v)
{
	visited[v]=true;

	for(list<int>::iterator it=adj[v].begin(); it!=adj[v].end(); it++)
	{
		if(visited[*it]==true)
			continue;
		else{
			visited[*it]=true;
			topologysort(*it);
		}		
	}

	queue.push_front(v);
}

void graph::topology(int  v)
{
	

	//visited = new bool[vertices];

	// set everything to false
	
	auto next=v;
	// start the topologysort
	do{
	topologysort(next);
		if(visited.size()!=vertices)
		{
			for(int i=0; i<vertices;i++)
			{
				cout<<visited[i];
				if(visited[i]!=true)
				{
					next=i;
					break;
				}
			}
		}
	}while(visited.size()!=vertices);

	// print topology sort
	for(list<int>::iterator it=queue.begin(); it!=queue.end(); it++)
	{
		cout<<*it<<" ";
	}
	
}


int main()
{
	graph a(4);
	a.addEdges(0,1);
	a.addEdges(0,2);
	a.addEdges(1,2);
	a.addEdges(2,3);
	//a.addEdges(2,0);
	a.addEdges(3,3);
	a.topology(2);
}
