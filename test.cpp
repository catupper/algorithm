#include<iostream>
#include<algorithm>
#include<vector>

using namespace std;

int main(){
int n;
	cin >> n;
	vector< vector<int> > hoge;
	hoge.assign(n, vector<int>());
	for(int i = 0;i < n;i++)hoge[i].push_back(i);
	for(int i = 0;i < n;i++){
		for(int j = 0;j < hoge[i].size();j++)cout << hoge[i][j];
		cout << endl;
	}
}