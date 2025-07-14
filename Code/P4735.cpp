#include<bits/stdc++.h>
#define int long long
#define mod 1000000007
using namespace std;
const int maxn=600010;
const int inf=1e9;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}

int n,m,s;
int rt[maxn],idx;
int tree[maxn<<5][2],val[maxn<<5];
void upd(int nd,int nd1,int v){
	for(int i=25;i>=0;i--){
		int u=(v>>i)&1;
		tree[nd][!u]=tree[nd1][!u];
		tree[nd][u]=++idx;
		val[tree[nd][u]]=val[tree[nd1][u]]+1;
		nd=tree[nd][u];nd1=tree[nd1][u];
	}
}
int query(int nd,int nd1,int w){
	int res=0;
	for(int i=25;i>=0;i--){
		int u=(w>>i)&1;
		if(val[tree[nd1][!u]]>val[tree[nd][!u]]){
			nd=tree[nd][!u];nd1=tree[nd1][!u];
			res+=(1<<i);
		}
		else nd=tree[nd][u],nd1=tree[nd1][u];
	}
	return res;
}

signed main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	
	n=read();m=read();
	rt[0]=++idx;upd(rt[0],0,0);
	for(int i=1;i<=n;i++){
		int u=read();s^=u;
		rt[i]=++idx;upd(rt[i],rt[i-1],s);
	}
	for(int i=1;i<=m;i++){
		char ch=getchar();
		while(ch<'A'||ch>'Z')ch=getchar();
		if(ch=='A'){
			int u=read();s^=u;++n;
			rt[n]=++idx;upd(rt[n],rt[n-1],s);
		}
		else{
			int u,v,w;
			u=read()-1;v=read()-1;w=read();
			if(!u)printf("%lld\n",query(0,rt[v],s^w));
			else printf("%lld\n",query(rt[u-1],rt[v],s^w));
		}
	}
}
