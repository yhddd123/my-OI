#include <bits/stdc++.h>
#include "Alice.h"
using namespace std;

vector<pair<int,int>>Alice(){
    int n=5000;
    long long x = setN(n);
    vector<pair<int,int>> res(n-1);
    for(int i=2;i<=n;i++)res[i-2]={x%(i-1)+1,i};
    return res;
}
