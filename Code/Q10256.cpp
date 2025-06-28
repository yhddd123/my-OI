#include<bits/stdc++.h>
// #define int long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
#define mkp make_pair
#define mems(a,x) memset((a),(x),sizeof(a))
using namespace std;
inline int read(){int x=0,f=1;char c=getchar();while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}while(c>='0'&&c<='9'){x=(x<<3)+(x<<1)+c-48;c=getchar();}return x*f;}
inline int readc(){char ch=getchar();while(ch<'a'||ch>'z')ch=getchar();return ch;}
const int maxn=100010;
const int maxm=500010;
const int B=1000;
const int inf=1e9;
bool mbe;

int n,q;
int t[maxn],id[maxn],pos[maxn],idx,tmp[maxn];
void upd(int p,int w){
	t[p]+=w;
	if(t[p]==w)id[++idx]=p,pos[p]=idx;
	if(t[p]==0)pos[id[idx]]=pos[p],id[pos[p]]=id[idx],idx--;
}
void clr(){
	while(idx)t[id[idx]]=0,idx--;
}
int calc(){
	for(int i=1;i<=idx;i++)tmp[i]=id[i];
	sort(tmp+1,tmp+idx+1);
	int ans=0;
	for(int i=idx,op=0;i;i--)if(t[tmp[i]]&1){
		ans+=tmp[i]*(!op?1:-1),op^=1;
	}
	return ans;
}
int f[maxn],siz[maxn];
int fd(int x){
	if(f[x]==x)return x;
	return fd(f[x]);
}
int st[maxm],tp;
void merge(int u,int v){
	u=fd(u),v=fd(v);
	if(u==v){st[++tp]=0;return ;}
	if(siz[u]<siz[v])swap(u,v);
	upd(siz[u],-1),upd(siz[v],-1);
	st[++tp]=v;f[v]=u,siz[u]+=siz[v];
	upd(siz[u],1);
}
void del(){
	int v=st[tp],u=f[st[tp]];tp--;
	if(!v)return ;
	upd(siz[u],-1);
	f[v]=v,siz[u]-=siz[v];
	upd(siz[u],1),upd(siz[v],1);
}
tuple<int,int,int> e[maxm],e1[maxm],e2[maxm];int m,m1,m2;
set<tuple<int,int,int>> s;
void init(){
	for(int i=1;i<=n;i++)f[i]=i,siz[i]=1;tp=0;
	clr();upd(1,n);
}
void rebuild(){
	// cout<<m<<" "<<s.size()<<" r\n";
	m1=0;for(auto p:s)e1[++m1]=p;
	m2=0;for(int i=1;i<=m;i++)e2[++m2]=e[i];
	s.clear();
	int p=1,q=1;m=0;
	while(p<=m1&&q<=m2){
		if(e1[p]<=e2[q])e[++m]=e1[p++];
		else e[++m]=e2[q++];
	}
	while(p<=m1)e[++m]=e1[p++];
	while(q<=m2)e[++m]=e2[q++];
	init();
	for(int i=1;i<=m;i++)merge(get<1>(e[i]),get<2>(e[i]));
}
void work(){
	n=read();q=read();init();
	while(q--){
		char op=readc();
		if(op=='a'){
			int u=read(),v=read(),w=read();
			s.insert({w,u,v});
		}
		if(op=='r'){
			if(!s.size()||(*--s.end())<=e[m])del(),m--;
			else s.erase(--s.end());
		}
		if(op=='d'){
			if(s.size()>B)rebuild();
			int lst=tp;
			for(auto[w,u,v]:s)merge(u,v);
			printf("%d\n",calc());fflush(stdout);
			while(tp>lst)del();
		}
	}
}

bool med;
int T;
signed main(){
	// freopen(".in","r",stdin);
	// freopen(".out","w",stdout);
	
	// cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
	
	T=1;
	while(T--)work();
}