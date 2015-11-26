#include<string>
#include<vector>
#include<algorithm>
#include<iostream>

using namespace std;


/************

O(N)


*************/


class SAIS{
public:
	typedef vector<int> VI;
	int L, S;

	vector<int> str;
	vector<int> l, r, rr, ll;
	int bucket;

	SAIS(){
		L = 0;S = 1;
	}
	
	SAIS(string sstr){
		L = 0;S = 1;
		for(int i = 0;i < sstr.size();i++){
			str.push_back(((int)sstr[i]) + 1);
		}
		bucket = 1024;
		str.push_back(0);
	}
	
	SAIS(VI vec){    
		L = 0;S = 1;
		for(int i = 0;i < vec.size();i++){
			str.push_back(vec[i] + 1);
		}
		bucket = str.size() + 1;  
		str.push_back(0);
	}

	void IS(vector<int> &res, vector<int> &ls){
		for(int i = 0;i < res.size();i++){
			if(res[i] <= 0)continue;
			int s = res[i]-1;
			if(ls[s] == L){
				res[l[str[s]]++] = s;
			}
		}
		r = rr;
		for(int i = res.size() - 1;i >= 0;i--){
			if(res[i] <= 0)continue;
			int s = res[i] - 1;
			if(ls[s] == S){
				res[r[str[s]]--] = s;
			}
		}                                                                   
	}
	
	vector<int> LS(){
		VI res(str.size(), 0);
		for(int i = str.size() - 1;i >= 0;i--){
			if(i == str.size() - 1)res[i] = S;
			else if(str[i] < str[i+1])res[i] = S;
			else if(str[i] > str[i+1])res[i] = L;
			else res[i] = res[i+1];
		}
		return res;
	}
	
	vector<int> SA(){
		l.assign(bucket, 0);
		r.assign(bucket, 0);
		for(int i = 0;i < str.size();i++){
			r[str[i]]++;
		}
		for(int i = 1;i < bucket;i++){
			r[i] += r[i-1];
		}
		for(int i = 0;i < bucket;i++){
			if(i == 0)l[i] = 0;
			else l[i] = r[i-1]+1;
			r[i]--;
		}
		ll = l;
		rr = r;
		VI res(str.size(), -1);
		VI lms(str.size(), -1);
		VI ls = LS();
		int scnt = 0;
		for(int i = 0;i < str.size();i++)scnt += ls[i] == S;

		for(int i = 1;i < str.size();i++){
			if(ls[i] == S && ls[i-1] == L || i + 1 == str.size()){
				res[r[str[i]]--] = i;
				lms[i] = 1;
			}
		}
		IS(res, ls);
		if(scnt == 1){                            
			res.erase(res.begin());
			return res;	
		}
		int p = 0;
		for(int i = 0;i < str.size();i++){
			if(lms[res[i]] == -1)continue;
			else lms[res[i]] = p++;
		}
		
		VI tmp(p, 0);
		for(int i = 0;i < str.size();i++){
			if(lms[i] == -1)continue;
			else tmp[lms[i]] = i;
		}
		
		res.assign(str.size(), -1);
		r = rr;
		l = ll;
		for(int i = tmp.size() - 1;i >= 0;i--){
			int s = tmp[i];
			res[r[str[s]]--] = s;
		}
		IS(res, ls);                              
		res.erase(res.begin());
		return res;
	}			
	
};
