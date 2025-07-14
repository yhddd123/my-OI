//#include<bits/stdc++.h>
//using namespace std;
//int n,m,x,y,sum,cnt;
//int f[5010];
//
//int fd(int x){
//	if(f[x]==x)return x;
//	return f[x]=fd(f[x]);
//}
//int mrg(int x,int y){
//	f[x]=fd(f[y]);
//}
//
//int tot;
//struct nd{
//	int x,y,val;
//}e[400010];
//void add(int x,int y,int z){
//	e[++tot]=(nd){x,y,z};
//}
//bool cmp(nd u,nd v){
//	return u.val<v.val;
//}
//
//signed main(){
//	scanf("%d%d",&n,&m);
//	for(int i=1;i<=m;i++){
//		int u,v,w;
//		scanf("%d%d%d",&u,&v,&w);
//		add(u,v,w);add(v,u,w);
//	}
//	for(int i=1;i<=n;i++)f[i]=i;
//	sort(e+1,e+tot+1,cmp);
//	for(int i=1;i<=tot;i++){
//		x=fd(e[i].x);y=fd(e[i].y);
//		if(x!=y){
//			sum+=e[i].val;
//			mrg(x,y);cnt++;
//			if(cnt==n-1){
//				printf("%d",sum);
//				exit(0);
//			}
//		}
//	}
//	printf("orz");
//}

//prim
#include<bits/stdc++.h>
using namespace std;
const int maxn=5010;

int n,m;
int head[maxn],tot;
struct nd{
	int nxt,to,val;
}e[400010];
void add(int u,int v,int w){
	e[++tot].nxt=head[u];e[tot].to=v;e[tot].val=w;
	head[u]=tot;
}
bool vis[maxn];
int dis[maxn],ans;

struct Dis{
	int dis,id;
	bool operator <(const Dis&tmp)const{return dis>tmp.dis;}
};
priority_queue<Dis> q;

void prim(){
	int res=0,cnt=1;
	memset(dis,0x3f,sizeof(dis));
	dis[1]=0;q.push({0,1});
	while(cnt<=n){
		if(q.empty()){
			printf("orz");
			return ;
		}
		int u=q.top().id;q.pop();
		if(!vis[u]){
			vis[u]=1;ans+=dis[u];++cnt;
			for(int i=head[u];i;i=e[i].nxt){
				int v=e[i].to;
				if(dis[v]>e[i].val)dis[v]=e[i].val,q.push({dis[v],v});
			}
		}
	}
	printf("%d\n",ans);
}
signed main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++){
		int u,v,w;
		scanf("%d%d%d",&u,&v,&w);
		add(u,v,w);add(v,u,w);
	}
	prim();
}
