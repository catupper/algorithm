#include<vector>

using namespace std;

class UnionFind{
public:
	vector<int> u;	
	void init(int n){
		u.clear();
		for(int i = 0;i < n;i++){
			u.push_back(-1);
		}
	}
	
	UnionFind(int n){
		init(n);
	}
	
	int r(int x){
		if(u[x] < 0)return x;
		return u[x] = r(u[x]);
	}
	
	void unite(int x, int y){
		if(same(x, y))return;
		x = r(x);
		y = r(y);
		if(-u[x] > -u[y]){
			swap(x, y);
		}
		u[x] += u[y];
		u[y] = x;
	}

	bool same(int x, int y){
		return r(x) == r(y);
	}
	
	int size(int x){
		return -u[r(x)];
	}

};