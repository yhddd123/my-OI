// Problem: C - Adjusting a Rectangle
// Contest: AtCoder - AtCoder Regular Contest 209 (Div. 1)
// URL: https://atcoder.jp/contests/arc209/tasks/arc209_c
// Memory Limit: 1024 MB
// Time Limit: 3000 ms
// Written by yhm.
// Start codeing:2025-11-09 21:48:44
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
const int maxn=100010;
const int B=3;
const int inf=1e9;
bool mbe;

int n,x,q,a[maxn],b[maxn];
struct ask{
	int l,r,id;
}que[maxn];
int ans[maxn];
int res,g1,g2;
void init(int p){
	if(b[p]==1){
		if(x>=a[p])res=1,f1=g1=a[p],f2=g2=x;
		else res=0,f1=g1=1,f2=g2=x;
	}
	else{
		if(a[p]==1)res=-1,f1=g1=1,f2=g2=x;
		else res=0,f1=g1=1,f2=g2=min(x,a[p]-1);
	}
}
void insg(int p,int &res,int &g1,int &g2){
	if(b[p]==1){
		if(x*g2>=a[p])res++,g1=(a[p]+g2-1)/g2,g2=x;
		else g1=1,g2=x;
	}
	else{
		if(g1>=a[p])res--,g1=1,g2=x;
		else g2=min(x,(a[p]-1)/g1),g1=1;
	}
}
map<pii,tuple<int,int,int>> to[maxn];
tuple<int,int,int> val[maxn];
void work(){
	n=read();x=read();q=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<=n;i++)b[i]=read();
	for(int i=1;i<=q;i++){
		int l=read(),r=read();
		init(l);
		for(int j=l+1;j<=r;){
			if((j/B+1)*B-1<=r){
				if(to[j].find({g1,g2})!=to[j].end()){
					auto[d,p1,p2]=to[j][{g1,g2}];
					res+=d,g1=p1,g2=p2;
				}
				else{
					int p=(j/B+1)*B-1;
					int tmp=res,gg1=g1,gg2=g2;
					for(int k=j;k<=p;k++){
						insg(k,res,g1,g2);
						val[i]={res,g1,g2};
					}
					to[j][{gg1,gg2}]={res-tmp,g1,g2};
					for(int k=j;k<p;k++){
						auto[v,f1,f2]=
						to[k+1][{gg1,gg2}]={}
					}
				}
				j=(j/B+1)*B;
			}
			else{
				insg(j,res,g1,g2);
				j++;
			}
		}
		printf("%lld\n",res);
	}
	for(int i=1;i<=q;i++)printf("%lld\n",ans[i]);
}

bool med;
int T;
signed main(){
	// freopen(".in","r",stdin);
	// freopen(".out","w",stdout);
	
	// cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
	
	T=1;
	while(T--)work();
}