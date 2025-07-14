#include<bits/stdc++.h>
#define int long long
#define mod 1000000007
using namespace std;
const int maxn=200010;
const int inf=1e9;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}

int n,ans,tp;
struct nd{
	int a,b,c,d;
	int fl,id,w,dp;
}e[maxn],tmp[maxn];
bool cmp1(nd u,nd v){
	if(u.a==v.a){if(u.b==v.b){if(u.c==v.c)return u.d<v.d;return u.c<v.c;}return u.b<v.b;}
	return u.a<v.a;
}
bool cmp2(nd u,nd v){
	if(u.b==v.b){if(u.a==v.a){if(u.c==v.c)return u.d<v.d;return u.c<v.c;}return u.a<v.a;}
	return u.b<v.b;
}
bool cmp3(nd u,nd v){
	if(u.c==v.c)return u.d<v.d;
	return u.c<v.c;
}
int b[maxn],len;
int p1[maxn],p2[maxn];
int tree[maxn];
int lowbit(int x){return x&(-x);}
void upd(int x,int w){
	for(int i=x;i<=n;i+=lowbit(i))tree[i]=max(tree[i],w);
}
int query(int x){
	int res=0;
	for(int i=x;i;i-=lowbit(i))res=max(res,tree[i]);
	return res;
}
void clear(int x){
	for(int i=x;i<=n;i+=lowbit(i))tree[i]=0;
}
void cdq2(int l,int r){
	if(l==r)return ;
	int mid=l+r>>1;
	cdq2(l,mid);
	sort(e+l,e+mid+1,cmp3);sort(e+mid+1,e+r+1,cmp3);
	int h=l;
	for(int i=mid+1;i<=r;i++){
		while(e[h].c<=e[i].c&&h<=mid){
			if(!e[h].fl)upd(e[h].d,e[h].dp);
			h++;
		}
		if(e[i].fl)e[i].dp=max(e[i].dp,query(e[i].d)+e[i].w);
	}
	for(int i=l;i<h;i++)if(!e[i].fl)clear(e[i].d);
	for (int i=l;i<=r;i++)tmp[p2[e[i].id]]=e[i];
	for (int i=l;i<=r;i++)e[i]=tmp[i];
	cdq2(mid+1,r);
}
void cdq1(int l,int r){
	if(l==r)return ;
	int mid=l+r>>1;
	cdq1(l,mid);
	for(int i=l;i<=mid;i++)e[i].fl=0;
	for(int i=mid+1;i<=r;i++)e[i].fl=1;
	sort(e+l,e+r+1,cmp2);
	for(int i=l;i<=r;i++)p2[e[i].id]=i;
	cdq2(l,r);
	for (int i=l;i<=r;i++)tmp[p1[e[i].id]]=e[i];
	for (int i=l;i<=r;i++)e[i]=tmp[i];
	cdq1(mid+1,r);
}

int T;
signed main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	
	n=read();
	for(int i=1;i<=n;i++){
		e[i].a=read();e[i].b=read();e[i].c=read();e[i].d=read();
		b[++len]=e[i].d;e[i].w=1;
	}
	sort(b+1,b+len+1);len=unique(b+1,b+len+1)-b-1;
	for(int i=1;i<=n;i++)e[i].d=lower_bound(b+1,b+len+1,e[i].d)-b;
	sort(e+1,e+n+1,cmp1);tp=1;
	for(int i=2;i<=n;i++){
		if(e[i].a!=e[i-1].a||e[i].b!=e[i-1].b||e[i].c!=e[i-1].c||e[i].d!=e[i-1].d)e[++tp]=e[i];
		else e[tp].w+=e[i].w;
	}
	for(int i=1;i<=tp;i++)e[i].id=i,e[i].dp=e[i].w,p1[i]=i;
	cdq1(1,tp);
	for(int i=1;i<=n;i++)ans=max(ans,e[i].dp);
	printf("%lld\n",ans);
}
