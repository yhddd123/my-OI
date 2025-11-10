// Problem: G. Pointless Machine
// Contest: Codeforces - Codeforces Global Round 30 (Div. 1 + Div. 2)
// URL: https://codeforces.com/contest/2164/problem/G
// Memory Limit: 256 MB
// Time Limit: 4000 ms
// Written by yhm.
// Start codeing:2025-11-10 19:21:53
// 
// Powered by CP Editor (https://cpeditor.org)

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
const int maxn=200010;
const int inf=1e9;
bool mbe;

int n;
mt19937 rnd(1);
vector<int> e[maxn];
vector<int> p[31];
int d[maxn],f[maxn][10][3];
int val[3][maxn];
bool vis[maxn];
vector<int> ask(vector<int> p){
	vector<int> ans;int res=0;
	for(int u:p){
		for(int v:e[u])res+=vis[v];
		vis[u]=1;
		ans.pb(res);
	}
	for(int u:p)vis[u]=0;
	return ans;
}
void work(){
	n=read();
	for(int i=1;i<=n;i++)e[i].clear();
	for(int i=2;i<=n;i++){
		int u=rnd()%(i-1)+1;
		e[u].pb(i),e[i].pb(u);
		// cout<<u<<" "<<i<<" e\n";
	}
	cout<<"31"<<endl;
	for(int i=0,pw=1;i<10;i++,pw=pw*3){
		for(int o=0;o<3;o++){
			vector<int> id;
			for(int j=1;j<=n;j++){
				if((j/pw)%3==o)id.pb(j);
			}
			for(int j=1;j<=n;j++){
				if((j/pw)%3==(o+1)%3)id.pb(j);
			}
			for(int j=1;j<=n;j++){
				if((j/pw)%3==(o+2)%3)id.pb(j);
			}
			for(int j:id)cout<<j<<" ";cout<<endl;
			p[3*i+o]=id;
		}
	}
	p[30]=p[0];reverse(p[30].begin(),p[30].end());
	for(int j:p[30])cout<<j<<" ";cout<<endl;
	for(int i=0,pw=1;i<10;i++,pw*=3){
		for(int o=0;o<3;o++){
			// vector<int> ans=ask(p[3*i+o]);
			for(int j=1,lst=0;j<=n;j++){
				int v=read();
				// int v=ans[j-1];
				val[o][p[3*i+o][j-1]]=v-lst;lst=v;
			}
		}
		if(i==0){
			for(int j=1;j<=n;j++)d[j]=val[0][j];
			// for(int j=1;j<=n;j++)cout<<d[j]<<" ";cout<<"\n";
		}
		for(int j=1;j<=n;j++){
			int o=(j/pw)%3;
			f[j][i][(o+1)%3]=val[(o+1)%3][j]-val[(o+2)%3][j];
			f[j][i][(o+2)%3]=val[(o+2)%3][j]-val[o][j];
			// cout<<j<<" "<<f[j][i][0]<<" "<<f[j][i][1]<<" "<<f[j][i][2]<<"\n";
		}
	}
	// vector<int> ans=ask(p[30]);
	for(int j=1,lst=0;j<=n;j++){
		int v=read();
		// int v=ans[j-1];
		d[p[30][j-1]]=abs(d[p[30][j-1]]-(lst-v));lst=v;
	}
	for(int i=1;i<=n;i++){
		for(int j=0,pw=1;j<10;j++,pw*=3)f[i][j][(i/pw)%3]=d[i]-f[i][j][(i/pw+1)%3]-f[i][j][(i/pw+2)%3];
	}
	queue<int> q;
	for(int i=1;i<=n;i++)if(d[i]==1)q.push(i);
	for(int t=1;t<n;t++){
		int u=q.front();q.pop();
		int v=0;for(int i=0,pw=1;i<10;i++,pw=pw*3){
			if(f[u][i][0]){}
			else if(f[u][i][1])v+=pw;
			else v+=2*pw;
		}
		if(v){
			for(int i=0,pw=1;i<10;i++,pw*=3){
				f[v][i][(u/pw)%3]--;
			}
			cout<<u<<" "<<v<<endl;
			d[v]--;
			if(d[v]==1)q.push(v);
		}
	}
}

bool med;
int T;
signed main(){
	// freopen(".in","r",stdin);
	// freopen(".out","w",stdout);
	
	// cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
	
    ios::sync_with_stdio(false);cin.tie(0),cout.tie(0);
	
	T=read();
	while(T--)work();
}