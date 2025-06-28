#include <bits/stdc++.h>
#include "Bob.h"
using namespace std;
const long long inf=1e18;

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
