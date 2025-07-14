#include<bits/stdc++.h>
using namespace std;
const int maxn=310;
int n,x,y,sum,cnt;
int f[maxn];

int fd(int x){
	if(f[x]==x)return x;
	return f[x]=fd(f[x]);
}
int mrg(int x,int y){
	f[x]=fd(f[y]);
}

int tot;
struct nd{
	int x,y,val;
}e[maxn*maxn<<1];
void add(int x,int y,int z){
	e[++tot]=(nd){x,y,z};
}
bool cmp(nd u,nd v){
	return u.val<v.val;
}
int u;
signed main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d",&u);
		add(n+1,i,u);add(i,n+1,u);
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			scanf("%d",&u);
			if(i!=j)add(i,j,u);
		}
	}
	for(int i=1;i<=n+1;i++)f[i]=i;
	sort(e+1,e+tot+1,cmp);
	for(int i=1;i<=tot;i++){
		x=fd(e[i].x);y=fd(e[i].y);
		if(x!=y){
			sum+=e[i].val;
			mrg(x,y);cnt++;
			if(cnt==n){
				printf("%d",sum);
				return 0;
			}
		}
	}
}
