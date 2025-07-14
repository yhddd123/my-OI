#include<bits/stdc++.h>
#define int unsigned long long
#define mod 1000000007
using namespace std;
const int maxn=100010;
const int inf=1e9;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}

int n,x,y,z,ans;
struct Dis{
	int dis,id;
	bool operator <(const Dis &tmp)const{return dis>tmp.dis;}
};
priority_queue<Dis> q;
int tim[maxn];
bool vis[maxn];

int T;
signed main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	
	n=read()-1;x=read();y=read();z=read();
	if(x==1||y==1||z==1){
		printf("%lld\n",n+1);
		return 0;
	}
	for(int i=0;i<x;i++)tim[i]=n+1;
	tim[0]=0;q.push({tim[0],0});
	while(!q.empty()){
		int u=q.top().id;q.pop();
		if(vis[u])continue;
		vis[u]=1;
		if(q.top().dis>n)break;
		if(tim[(u+y)%x]>tim[u]+y){
			tim[(u+y)%x]=tim[u]+y;
			q.push({tim[(u+y)%x],(u+y)%x});
		}
		if(tim[(u+z)%x]>tim[u]+z){
			tim[(u+z)%x]=tim[u]+z;
			q.push({tim[(u+z)%x],(u+z)%x});
		}
	}
	for(int i=0;i<x;i++){
		if(tim[i]<=n)ans+=(n-tim[i])/x+1;
	}
	printf("%lld\n",ans);
}
