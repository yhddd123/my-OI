#include<bits/stdc++.h>
#define int long long
#define db double
#define mod 1000000007
using namespace std;
const int maxn=200010;
const int inf=1e9;
const db eps=1e-9;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}

int m;
int idx,tree[maxn*60][2],sum[maxn*60][2];
void insert(int u,int v,int w){
	int nd=1;
	for(int i=60;i>=0;i--){
		int v1=((u^v)>>i)&1ll,v2=(u>>i)&1ll;
		if(!tree[nd][v1])tree[nd][v1]=++idx;
		sum[tree[nd][v1]][v2]+=w;
		nd=tree[nd][v1];
	}
}
int query(int u,int v){
	int nd=1,ans=0;
	for(int i=60;i>=0;i--){
		int v1=((u^v)>>i)&1ll,v2=(v>>i)&1ll;
		if(tree[nd][1-v1])ans+=sum[tree[nd][1-v1]][1-v2];
		if(tree[nd][v1])nd=tree[nd][v1];
		else break;
	}
	return ans;
}

int T;
signed main(){
	//	freopen(".in","r",stdin);
	//	freopen(".out","w",stdout);
	
	m=read();idx=1;
	while(m--){
		int opt=read(),x=read(),y=read();
		if(opt==1)insert(x,y,1);
		if(opt==2)insert(x,y,-1);
		if(opt==3)printf("%lld\n",query(y,x));
	}
}
