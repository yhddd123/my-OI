#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn=100010;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}

int n,m;
struct ask{
	int x,y;
	int id;
}q[maxn<<2];
bool cmp(ask u,ask v){
	if(u.x!=v.x)return u.x<v.x;
	return u.y<v.y;
}
int ans[maxn<<2];
struct nd{
	int x,y,w;
}a[maxn];
bool cmp1(nd u,nd v){
	if(u.x!=v.x)return u.x<v.x;
	return u.y<v.y;
}
int b[maxn*5],cnt;
int tree[maxn*5];
int lowbit(int x){return x&(-x);}
void updata(int x,int w){
	while(x<=maxn*5-10){
		tree[x]+=w;
		x+=lowbit(x);
	}
}
int query(int x){
	int res=0;
	while(x){
		res+=tree[x];
		x-=lowbit(x);
	}
	return res;
}

int T;
signed main(){
	//	freopen(".in","r",stdin);
	//	freopen(".out","w",stdout);
	
	n=read();m=read();
	for(int i=1;i<=n;i++){
		a[i].x=read();a[i].y=read();a[i].w=read();
		b[++cnt]=a[i].y;
	}
	sort(a+1,a+n+1,cmp1);
	for(int i=1;i<=m;i++){
		int u,v,uu,vv;
		u=read();v=read();uu=read();vv=read();
		b[++cnt]=v-1;b[++cnt]=vv;
		q[i*4-3]={uu,vv,i*4-3};q[i*4-2]={u-1,v-1,i*4-2};
		q[i*4-1]={uu,v-1,i*4-1};q[i*4]={u-1,vv,i*4};
	}
	sort(q+1,q+4*m+1,cmp);
	sort(b+1,b+cnt+1);
	cnt=unique(b+1,b+cnt+1)-b-1;
	for(int i=1;i<=n;i++)a[i].y=lower_bound(b+1,b+cnt+1,a[i].y)-b;
	for(int i=1;i<=4*m;i++)q[i].y=lower_bound(b+1,b+cnt+1,q[i].y)-b;
	for(int i=1,j=1;i<=4*m;i++){
		while(j<=n&&a[j].x<=q[i].x){
			updata(a[j].y,a[j].w);j++;
		}
		ans[q[i].id]=query(q[i].y);
	}
	for(int i=1;i<=m;i++)printf("%lld\n",ans[i*4-3]+ans[i*4-2]-ans[i*4-1]-ans[i*4]);
}
