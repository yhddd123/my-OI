#include<bits/stdc++.h>
#define int long long
#define mod 1000000007
using namespace std;
const int maxn=150010;
const int maxm=1000010;
const int inf=1e9;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}

int n,m,s,a[maxn];
struct ask{
	int x,y,pre,id;
}p[maxn];
bool cmp(ask u,ask v){
	if(u.x/s==v.x/s){
		if(u.y/s==v.y/s)return u.pre/s<v.pre/s;
		return u.y<v.y;
	}
	return u.x<v.x;
}
int ans[maxn],cnt,tim;
struct nd{
	int pos,val;
}c[maxn];
int l=1,r,nw,res,t[maxm];
void add(int x){if(++t[x]==1)++res;}
void del(int x){if(--t[x]==0)--res;}
void work(int num,int id){
	if(c[num].pos>=p[id].x&&c[num].pos<=p[id].y){
		del(a[c[num].pos]);
		add(c[num].val);
	}
	swap(c[num].val,a[c[num].pos]);
}

int T;
signed main(){
	//	freopen(".in","r",stdin);
	//	freopen(".out","w",stdout);
	
	n=read();m=read();s=pow(n,2.0/3.0);
	for(int i=1;i<=n;i++)a[i]=read();
	while(m--){
		char opt[5];
		scanf("%s",opt+1);
		if(opt[1]=='Q')p[++cnt]={read(),read(),tim,cnt};
		else c[++tim]={read(),read()};
	}
	sort(p+1,p+cnt+1,cmp);
	for(int i=1;i<=cnt;i++){
		while(l>p[i].x)add(a[--l]);
		while(r<p[i].y)add(a[++r]);
		while(l<p[i].x)del(a[l++]);
		while(r>p[i].y)del(a[r--]);
		while(nw<p[i].pre)work(++nw,i);
		while(nw>p[i].pre)work(nw--,i);
		ans[p[i].id]=res;
	}
	for(int i=1;i<=cnt;i++)printf("%lld\n",ans[i]);
}
