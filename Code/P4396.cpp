#include<bits/stdc++.h>
using namespace std;
const int maxn=100010;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}

int n,m,a[maxn],s;
struct bit{
	int tree[maxn];
	int lowbit(int x){return x&(-x);}
	void updata(int x,int w){
		while(x<=maxn-10){
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
}T1,T2;
struct ask{
	int l,r,a,b,id;
}p[maxn];
bool cmp(ask u,ask v){
	if(u.l/s==v.l/s){
		if((u.l/s)&1)return u.r<v.r;
		return u.r>v.r;
	}
	return u.l<v.l;
}
int ans[maxn][2];
int l=1,r,t[maxn];
void add(int x){
	T1.updata(x,1);
	if(++t[x]==1)T2.updata(x,1);
}
void del(int x){
	T1.updata(x,-1);
	if(--t[x]==0)T2.updata(x,-1);
}

signed main(){
	n=read();m=read();s=sqrt(n);
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<=m;i++)p[i]={read(),read(),read(),read(),i};
	sort(p+1,p+m+1,cmp);
	for(int i=1;i<=m;i++){
		while(l>p[i].l)add(a[--l]);
		while(r<p[i].r)add(a[++r]);
		while(l<p[i].l)del(a[l++]);
		while(r>p[i].r)del(a[r--]);
		ans[p[i].id][0]=T1.query(p[i].b)-T1.query(p[i].a-1);
		ans[p[i].id][1]=T2.query(p[i].b)-T2.query(p[i].a-1);
	}
	for(int i=1;i<=m;i++)printf("%d %d\n",ans[i][0],ans[i][1]);
}
