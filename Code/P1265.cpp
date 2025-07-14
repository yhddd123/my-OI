#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn=5010;

int n;
bool vis[maxn];
double dis[maxn],ans;
int a[maxn][2];
double calc(int u,int v){
	return 1.0*sqrt((a[u][0]-a[v][0])*(a[u][0]-a[v][0])+(a[u][1]-a[v][1])*(a[u][1]-a[v][1]));
}

struct Dis{
	double dis;
	int id;
	bool operator <(const Dis&tmp)const{return dis>tmp.dis;}
};
priority_queue<Dis> q;

void prim(){
	int res=0,cnt=1;
	for(int i=1;i<=n;i++)dis[i]=100000000.0;
	dis[1]=0.0;q.push({dis[1],1});
	while(cnt<=n){
		int u=q.top().id;q.pop();
//		cout<<cnt<<" "<<u<<"\n";
//		for(int i=1;i<=n;i++)cout<<dis[i]<<" ";
//		cout<<"\n";
		if(!vis[u]){
			vis[u]=1;ans+=dis[u];++cnt;
			for(int i=1;i<=n;i++){
				if(dis[i]>calc(u,i)){
					dis[i]=calc(u,i);
					q.push({dis[i],i});
				}
			}
		}
	}
	printf("%.2lf\n",ans);
}
signed main(){
//	freopen("P1265_2.in","r",stdin);
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%lld%lld",&a[i][0],&a[i][1]);
	prim();
}
