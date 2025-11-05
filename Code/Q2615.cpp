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
const int maxn=200010;
const int inf=1e9;
bool mbe;

map<pii,bool> in,vis;
int s,t;
int fx[6][2]={{1,0},{1,1},{0,1},{-1,0},{-1,-1},{0,-1}};
map<pii,map<pii,int>> dis;
map<pii,int> d;
void get(){
	bool fl=0;for(int i=0;i<6;i++)if(in[{s+fx[i][0],t+fx[i][1]}])fl|=!vis[{s+fx[i][0],t+fx[i][1]}];
	if(!fl)exit(0);
	s=read(),t=read();
	// for(int i=0;i<6;i++)if(in[{s+fx[i][0],t+fx[i][1]}]&&!vis[{s+fx[i][0],t+fx[i][1]}]){s+=fx[i][0],t+=fx[i][1];break;}
}
void work(){
	s=read(),t=read();
	vector<pii> pos;
	for(int i=-9;i<=9;i++){
		for(int j=-9;j<=9;j++){
			if(j<=i+9&&j>=i-9)in[{i,j}]=1,pos.pb({i,j});
		}
	}
	vector<pii> p,p1;
	for(int i=-9;i<=9;i++){
		for(int j=-9;j<=9;j++)if(in[{i,j}]){
			bool fl=0;for(int p=0;p<6;p++)if(!in[{i+fx[p][0],j+fx[p][1]}])fl=1;
			if(fl){
				p.pb({i,j});
				if(i*j>=0){
					if(i+j>0){
						if((i+j)&1)p1.pb({i,j});
					}
					else{
						if(!((i+j)&1))p1.pb({i,j});
					}
				}
				else{
					if(i>0){
						if(!(j&1))p1.pb({i,j});
					}
					else{
						if(!(i&1))p1.pb({i,j});
					}
				}
			}
		}
	}
	// for(auto[u,v]:p)cout<<u<<" "<<v<<" a\n";
	// for(auto[u,v]:p1)cout<<u<<" "<<v<<" b\n";
	queue<pii> q;
	for(auto[i,j]:p)d[{i,j}]=0,q.push({i,j});
	while(!q.empty()){
		auto[x,y]=q.front();q.pop();
		for(int i=0;i<6;i++){
			int nx=x+fx[i][0],ny=y+fx[i][1];
			if(!in[{nx,ny}])continue;
			if(d.find({nx,ny})==d.end()){
				d[{nx,ny}]=d[{x,y}]+1;
				q.push({nx,ny});
			}
		}
	}
	for(auto[u,v]:pos){
		dis[{u,v}][{u,v}]=0,q.push({u,v});
		while(!q.empty()){
			auto[x,y]=q.front();q.pop();
			for(int i=0;i<6;i++){
				int nx=x+fx[i][0],ny=y+fx[i][1];
				if(!in[{nx,ny}])continue;
				if(dis[{u,v}].find({nx,ny})==dis[{u,v}].end()){
					dis[{u,v}][{nx,ny}]=dis[{u,v}][{x,y}]+1;
					q.push({nx,ny});
				}
			}
		}
	}
	for(int T=0;T<p.size();T++){
		if(d[{s,t}]==1||dis[{8,0}][{s,t}]==1||dis[{-8,-8}][{s,t}]==1||dis[{0,8}][{s,t}]==1){
			pii mn={inf,0};
			for(int i=0;i<p.size();i++)if(!vis[p[i]])mn=min(mn,{dis[p[i]][{s,t}],i});
			printf("%d %d\n",p[mn.se].fi,p[mn.se].se);fflush(stdout);vis[p[mn.se]]=1;
		}
		else{
			pii mn={inf,0};
			for(int i=0;i<p1.size();i++)if(!vis[p1[i]])mn=min(mn,{dis[p1[i]][{s,t}],i});
			if(mn.fi!=inf){
				printf("%d %d\n",p1[mn.se].fi,p1[mn.se].se);fflush(stdout);vis[p1[mn.se]]=1;
			}
			else{
				for(int i=0;i<p.size();i++)if(!vis[p[i]])mn=min(mn,{dis[p[i]][{s,t}],i});
				printf("%d %d\n",p[mn.se].fi,p[mn.se].se);fflush(stdout);vis[p[mn.se]]=1;
			}
		}
		get();
	}
	for(int T=0;T<=200;T++){
		for(int i=-9;i<=9;i++){
			for(int j=-9;j<=9;j++)if(in[{i,j}]&&!vis[{i,j}]){
				if(i!=s||j!=t){
					printf("%d %d\n",i,j);vis[{i,j}]=1;fflush(stdout);
					get();
					// cout<<s<<" "<<t<<" a\n";
				}
			}
		}
	}
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