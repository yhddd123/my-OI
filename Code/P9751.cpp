#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn=1000010;
const int inf=1e9;
inline int read(){
	int x=0,fl=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')fl=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+(ch-'0');ch=getchar();}
	return x*fl;
}

int n,m,k;
int head[maxn],tot;
struct nd{
	int nxt,to,t;
}e[maxn<<1];
void add(int u,int v,int l){e[++tot]={head[u],v,l};head[u]=tot;}
struct Dis{
	int id,dis;
	bool operator <(const Dis &tmp)const{return dis>tmp.dis;}
};
priority_queue<Dis> q;
int tim[maxn];
bool vis[maxn];

signed main(){
//	freopen("bus.in","r",stdin);
//	freopen("bus.out","w",stdout);
	n=read();m=read();k=read();
	for(int i=1;i<=m;i++){
		int u=read(),v=read(),lim=read();
		for(int j=0;j<k;j++)add(j*n+u,((j+1)%k)*n+v,lim);
	}
	memset(tim,0x3f,sizeof(tim));
	tim[1]=0;q.push({1,tim[1]});
	while(!q.empty()){
		int u=q.top().id;q.pop();
		// cout<<u<<" "<<tim[u]<<"\n";
		if(vis[u])continue;
		vis[u]=1;
		for(int i=head[u];i;i=e[i].nxt){
			int v=e[i].to;
			if(tim[u]>=e[i].t){
				if(tim[v]>tim[u]+1){
					tim[v]=tim[u]+1;
					q.push({v,tim[v]});
				}
			}
			else{
				int d=(e[i].t-tim[u]+k-1)/k;
				if(tim[v]>tim[u]+1+d*k){
					tim[v]=tim[u]+1+d*k;
					q.push({v,tim[v]});
				}
			}
		}
	}
	if(tim[n]>=inf)tim[n]=-1;
	printf("%lld\n",tim[n]);
}
