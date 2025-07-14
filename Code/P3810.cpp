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

int n,m,ans[maxn];
struct nd{
	int a,b,c;
	int w,res;
}e[maxn],p[maxn];
bool cmp(nd u,nd v){
	if(u.a==v.a){
		if(u.b==v.b)return u.c<v.c;
		return u.b<=v.b;
	}
	return u.a<v.a;
}
bool cmp1(nd u,nd v){
	if(u.b==v.b)return u.c<v.c;
	return u.b<v.b;
}
int num,idx;
int tree[maxn];
int lowbit(int x){return x&(-x);}
void updata(int x,int w){
	while(x<=m){
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
void cdq(int l,int r){
	if(l==r)return ;
	int mid=l+r>>1;
	cdq(l,mid);cdq(mid+1,r);
	sort(p+l,p+mid+1,cmp1);
	sort(p+mid+1,p+r+1,cmp1);
	int h=l,t=mid+1;
	while(t<=r){
		while(p[h].b<=p[t].b&&h<=mid)updata(p[h].c,p[h].w),h++;
		p[t].res+=query(p[t].c);t++;
	}
	for(int i=l;i<h;i++)updata(p[i].c,-p[i].w);
}

int T;
signed main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	
	n=read();m=read();
	for(int i=1;i<=n;i++)e[i].a=read(),e[i].b=read(),e[i].c=read();
	sort(e+1,e+n+1,cmp);
	for(int i=1;i<=n;i++){
		num++;
		if(e[i].a!=e[i+1].a||e[i].b!=e[i+1].b||e[i].c!=e[i+1].c){
			p[++idx]=e[i];
			p[idx].w=num;num=0;
		}
	}
	cdq(1,idx);
	for(int i=1;i<=idx;i++)ans[p[i].res+p[i].w-1]+=p[i].w;
	for(int i=0;i<n;i++)printf("%lld\n",ans[i]);
}
