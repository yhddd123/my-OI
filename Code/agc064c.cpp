// Problem: AT_agc064_c [AGC064C] Erase and Divide Game
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/AT_agc064_c
// Memory Limit: 1 MB
// Time Limit: 2000 ms
// Written by yhm.
// Start codeing:2025-04-01 13:00:33
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define int long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
#define mkp make_pair
#define mems(a,x) memset((a),(x),sizeof(a))
using namespace std;
inline int read(){
	int x=0,fl=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')fl=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*fl;
}
const int maxn=20100;
const int inf=(1ll<<60)-1;
bool mbe;

int n,m;
struct node{
	int l,r,w;
}a[maxn],b[maxn],c[maxn];
int get(int u,int v){
	if(u==-1&&v==-1)return -1;
	if(u==1&&v==1)return 0;
	return 1;
}
void work(){
	n=read();a[m=0].r=-1;
	for(int i=1;i<=n;i++){
		int l=read(),r=read();
		if(a[m].r+1<l)m++,a[m]={a[m-1].r+1,l-1,-1};
		a[++m]={l,r,1};
	}
	if(a[m].r+1<=inf)m++,a[m]={a[m-1].r+1,inf,-1};
	// for(int j=1;j<=m;j++)cout<<a[j].l<<" "<<a[j].r<<" "<<a[j].w<<"\n";
	for(int i=59;~i;i--){
		int mid=(1ll<<i)-1,tp=0,tp1=0;
		for(int j=1;j<=m;j++){
			if(a[j].r<=mid)b[++tp]=a[j];
			else if(a[j].l<=mid)b[++tp]={a[j].l,mid,a[j].w},c[++tp1]={0,a[j].r-mid-1,a[j].w};
			else c[++tp1]={a[j].l-mid-1,a[j].r-mid-1,a[j].w};
		}
		m=0;
		for(int j=1,k=1;j<=tp&&k<=tp1;){
			int pos=min(b[j].r,c[k].r);
			a[++m]={max(b[j].l,c[k].l),pos,get(b[j].w,c[k].w)};
			if(b[j].r==pos)j++;
			if(c[k].r==pos)k++;
		}
		// cout<<i<<" "<<tp<<" "<<tp1<<" i\n";
		// for(int j=1;j<=m;j++)cout<<a[j].l<<" "<<a[j].r<<" "<<a[j].w<<"\n";
	}
	puts(a[1].w==1?"Takahashi":"Aoki");
}

bool med;
int T;
signed main(){
	// freopen(".in","r",stdin);
	// freopen(".out","w",stdout);
	
	// cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
	
	T=read();
	while(T--)work();
}