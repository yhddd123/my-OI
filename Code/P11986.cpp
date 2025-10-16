#include<bits/stdc++.h>
// #define int long long
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
const int maxn=165;
const int maxm=20010;
const int inf=1e9;
bool mbe;

int l,n,m;
pii a[maxn];
int lsh[maxn];
int f1[maxn][maxm],f2[maxn][maxm],g1[maxn][maxm],g2[maxn][maxm];
int val1[maxm],val2[maxm];
inline void chkmn(int &u,int v){(u>v)&&(u=v);}
int id[maxn],rnk[maxn];
void work(){
	l=read();n=read();m=read()/2;
	for(int i=1;i<=n;i++)a[i]={read(),read()};
	sort(a+1,a+n+1,[&](pii u,pii v){return u.fi+u.se<v.fi+v.se;});
	for(int i=1;i<=n;i++)id[i]=i;
	sort(id+1,id+n+1,[&](int u,int v){return a[u].se-a[u].fi<a[v].se-a[v].fi;});
	for(int i=1;i<=n;i++)rnk[id[i]]=i;
	for(int i=0;i<=n;i++){
		for(int j=1;j<=n;j++){
			int v1=0,v2=0;
			if(rnk[j]<=i)v1=a[j].fi+a[j].se-2,v2=l-a[j].fi+a[j].se-1;
			for(int k=0;k<=m;k++){
				f1[j][k]=min(m+1,f1[j-1][k]+v2);
				if(k>=v1)chkmn(f1[j][k],f1[j-1][k-v1]);
			}
			v1=0,v2=0;
			if(rnk[j]>i)v1=a[j].fi+a[j].se-2,v2=a[j].fi-1+l-a[j].se;
			for(int k=0;k<=m;k++){
				f2[j][k]=min(m+1,f2[j-1][k]+v2);
				if(k>=v1)chkmn(f2[j][k],f2[j-1][k-v1]);
			}
		}
		for(int j=n;j;j--){
			int v1=0,v2=0;
			if(rnk[j]<=i)v1=l-a[j].fi+l-a[j].se,v2=l-a[j].fi+a[j].se-1;
			for(int k=0;k<=m;k++){
				g1[j][k]=min(m+1,g1[j+1][k]+v2);
				if(k>=v1)chkmn(g1[j][k],g1[j+1][k-v1]);
			}
			v1=0,v2=0;
			if(rnk[j]>i)v1=l-a[j].fi+l-a[j].se,v2=a[j].fi-1+l-a[j].se;
			for(int k=0;k<=m;k++){
				g2[j][k]=min(m+1,g2[j+1][k]+v2);
				if(k>=v1)chkmn(g2[j][k],g2[j+1][k-v1]);
			}
		}
		for(int j=0;j<=n;j++){
			for(int k=0;k<=m;k++)val1[k]=val2[k]=m+1;
			// for(int k=0;k<=m;k++)cout<<g1[j+1][k]<<" "<<g2[j+1][k]<<"\n";
			for(int k=0;k<=m;k++)chkmn(val1[f1[j][k]],f2[j][m-k]);
			for(int k=0;k<=m;k++)chkmn(val2[g1[j+1][k]],g2[j+1][m-k]);
			// for(int k=0;k<=m;k++)cout<<val1[k]<<" ";cout<<"\n";
			// for(int k=0;k<=m;k++)cout<<val2[k]<<" ";cout<<"\n";
			for(int k=1;k<=m;k++)chkmn(val1[k],val1[k-1]),chkmn(val2[k],val2[k-1]);
			for(int k=0;k<=m;k++)if(val1[k]+val2[m-k]<=m){
				// cout<<i<<" "<<j<<" "<<k<<" "<<val1[k]<<" "<<val2[m-k]<<"\n";
				puts("Yes");return ;}
		}
	}
	puts("No");
}

bool med;
int T;
signed main(){
	freopen("ambulance.in","r",stdin);
	freopen("ambulance.out","w",stdout);
	
	// cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
	
	T=1;
	while(T--)work();
}