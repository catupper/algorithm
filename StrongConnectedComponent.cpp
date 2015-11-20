#include<algorithm>
#include<vector>
#include<map>

using namespace std;

class UnionFind{
public:
	vector<int> u;	


	void init(int n){
		u.clear();
		u.assign(n, -1);
	}
	
	UnionFind(int n = 0){
		init(n);
	}
	
	int r(int x){
		if(u[x] < 0)return x;
		return u[x] = r(u[x]);
	}
	
	void unite(int x, int y){
		x = r(x);
		y = r(y);
		if(-u[x] > -u[y]){
			swap(x, y);
		}
		u[x] += u[y];
		u[y] = x;
	}
	
	int size(int x){
		return -u[r(x)];
	}
	
};

class StrongConnectedComponent{
public:
	int n;
	vector<bool> done;
	vector<vector<int> > edge, redge;
 	vector<int> nodes;
	UnionFind uf;
	
	StrongConnectedComponent(int x){
		n = x;
		edge.assign(n, vector<int>());
		redge.assign(n, vector<int>());
		done.assign(n, false);
		nodes.clear();
		uf.init(n);
	}

	void dfs(int x){
		if(done[x])return;
		done[x] = true;
		for(int i = 0;i < edge[x].size();i++){
			int to = edge[x][i];
			dfs(to);
		}
		nodes.push_back(x);
	}
	
	void rdfs(int x){
		done[x] = true;
		for(int i = 0;i < redge[x].size();i++){
			int to = redge[x][i];
			if(done[to])continue;
			uf.unite(x, to);
			rdfs(to);
		}
	}
		
	void add_edge(int x, int y){
		edge[x].push_back(y);
		redge[y].push_back(x);
	}
	
	UnionFind SCC(){
		done.assign(n, false);
		for(int i = 0;i < n;i++){
			if(done[i])continue;
			dfs(i);
		}
	
		done.assign(n, false);
		for(int i = 0;i < n;i++){
			int x = nodes[n - i + 1];
			if(done[x])continue;
			rdfs(x);			
		}
		
		return uf;
	}
	
};
