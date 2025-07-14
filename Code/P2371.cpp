#include<bits/stdc++.h>
#define int long long
#define mod 1000000007
using namespace std;
const int maxn=500010;
const int inf=1e9;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}

int n,l,r,a[maxn],ans;
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
	
	n=read();l=read()-1;r=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=0;i<a[1];i++)tim[i]=r+1;
	tim[0]=0;q.push({tim[0],0});
	while(!q.empty()){
		int u=q.top().id;q.pop();
		if(vis[u])continue;
		vis[u]=1;
		if(q.top().dis>r)break;
		for(int i=2;i<=n;i++){
			if(tim[(u+a[i])%a[1]]>tim[u]+a[i]){
				tim[(u+a[i])%a[1]]=tim[u]+a[i];
				q.push({tim[(u+a[i])%a[1]],(u+a[i])%a[1]});
			}
		}
	}
	for(int i=0;i<a[1];i++)if(tim[i]<=r)ans+=(r-tim[i])/a[1]+1;
	for(int i=0;i<a[1];i++)if(tim[i]<=l)ans-=(l-tim[i])/a[1]+1;
	printf("%lld\n",ans);
}
