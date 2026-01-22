// Problem: CF2157I Hyper Smawk Bros
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/CF2157I
// Memory Limit: 1000 MB
// Time Limit: 4000 ms
// Written by yhm.
// Start codeing:2026-01-22 15:36:49
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define int long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
#define db long double
#define mems(a,x) memset((a),(x),sizeof(a))
using namespace std;
inline int read(){
	int x=0,fl=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')fl=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*fl;
}
const int maxn=1000010;
const int inf=1e9;
bool mbe;

vector<int> pos[maxn];
bool f(int m,int n,int i,int p){
	if(!n)return 0;
	if(n<m)return 1;
	auto chk=[&](int l){return 1<=l&&l<=m;};
	while(pos[m][p]>n)p--;
	if(i!=(m+1)/2&&n-pos[m][p]+1==(m+1)/2&&p&&pos[m][p]-pos[m][p-1]==m+2)return 1;
	if(!((n-pos[m][p])&1)&&i!=(n-pos[m][p])/2&&chk(n-(n+pos[m][p])/2)&&!f(m,(n+pos[m][p])/2,(n-pos[m][p])/2,p))return 1;
	if(p&&!((n-pos[m][p-1])&1)&&i!=(n-pos[m][p-1])/2&&chk(n-(n+pos[m][p-1])/2)&&(n+pos[m][p-1])/2<pos[m][p]&&!f(m,(n+pos[m][p-1])/2,(n-pos[m][p-1])/2,p-1))return 1;
	return 0;
}
int n,m;
void work(){
	n=read();m=read();
	if(!(m&1))puts(n%(m+1)?"YES":"NO");
	else{
		int p=lower_bound(pos[m].begin(),pos[m].end(),n)-pos[m].begin();
		puts(pos[m][p]==n?"NO":"YES");
	}
}

bool med;
int T;
signed main(){
	// freopen(".in","r",stdin);
	// freopen(".out","w",stdout);
	
	// cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
	
	for(int m=3;m<=maxn-10;m+=2){
		pos[m].pb(0);
		while(pos[m].back()<=maxn-10){
			if(f(m,pos[m].back()+m+1,1,pos[m].size()-1))pos[m].pb(pos[m].back()+m+2);
			else pos[m].pb(pos[m].back()+m+1);
		}
		// for(int v:pos[m])cout<<v<<" ";cout<<"\n";
	}
	T=read();
	while(T--)work();
}