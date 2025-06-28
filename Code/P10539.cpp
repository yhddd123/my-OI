// Problem: P10539 [APIO2024] 魔术表演
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P10539
// Memory Limit: 1 MB
// Time Limit: 1000 ms
// Written by yhm.
// Start codeing:2025-05-08 13:00:25
// 
// Powered by CP Editor (https://cpeditor.org)


#include <bits/stdc++.h>
using namespace std;
const long long inf=1e18;

long long setN(int n);

vector<pair<int,int>>Alice(){
    int n=5000;
    long long x = setN(n);
    vector<pair<int,int>> res(n-1);
    for(int i=2;i<=n;i++)res[i-2]={x%(i-1)+1,i};
    return res;
}

long long Bob(vector<pair<int,int>> edge){
    long long ans=1,lst=1;
    for(auto[u,v]:edge){
    	u--,v--;
    	if(u>v)swap(u,v);
    	while(ans%v!=u)ans+=lst;
    	int d=v/__gcd(lst,(long long)v);
    	if(inf/d<lst)break;
    	lst*=d;
    }
    return ans;
}
