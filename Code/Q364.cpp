#include "Annalib.h"
#include<bits/stdc++.h>
using namespace std;
const int maxn=150;
const int maxm=40;
long long x;
int n,k,a[maxn],p[maxm],id[maxn];
bool vis[maxn];
void Anna( int N, long long X, int K, int P[] ){
	n=N,x=X,k=K;
	for(int i=0;i<k;i++)p[i]=P[i];
	for(int i=0;i<n;i++)id[i]=i,vis[i]=0;
	mt19937 rnd(20240912);
	shuffle(id,id+n,rnd);
	for(int i=0;i<k;i++)vis[p[i]]=1;
	for(int i=0;i<n;i+=2){
		int v=x%3;
		if(vis[id[i]]&&vis[id[i+1]])Set(id[i],0),Set(id[i+1],0);
		else if(vis[id[i]]){
			if(v==0)Set(id[i],0),Set(id[i+1],1),x/=3;
			else Set(id[i],0),Set(id[i+1],0);
		}
		else if(vis[id[i+1]]){
			if(v==1)Set(id[i],1),Set(id[i+1],0),x/=3;
			else Set(id[i],0),Set(id[i+1],0);
		}
		else{
			if(v==1||v==2)Set(id[i],1);
			else Set(id[i],0);
			if(v==0||v==2)Set(id[i+1],1);
			else Set(id[i+1],0);
			x/=3;
		}
	}
	// for(int i=0;i<n;i++)cout<<id[i]<<" ";cout<<"\n";
}

#include "Brunolib.h"
#include<bits/stdc++.h>
using namespace std;
const int maxn=150;
long long x;
int n,k,a[maxn],id[maxn];
long long Bruno( int N, int A[] ){
	n=N;
	for(int i=0;i<n;i++)id[i]=i,a[i]=A[i];
	mt19937 rnd(20240912);
	shuffle(id,id+n,rnd);
	// for(int i=0;i<n;i++)cout<<id[i]<<" ";cout<<"\n";
	// for(int i=0;i<n;i++)cout<<A[id[i]]<<" ";cout<<"\n";
	x=0;
	for(int i=n-2;i>=0;i-=2){
		if(!a[id[i]]&&!a[id[i+1]])continue;
		if(!a[id[i]])x=x*3;
		else if(!a[id[i+1]])x=x*3+1;
		else x=x*3+2;
		// cout<<i<<" "<<x<<"\n";
	}
	return x;
}