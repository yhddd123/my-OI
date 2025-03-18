---
title: '模板'
date: 2024-11-29 21:50:55
tags: []
published: true
hideInList: false
feature: 
isTop: false
---
## 杂项

### qsy

```cpp
#include<bits/stdc++.h>
#define int long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define mems(x,y) memset(x,y,sizeof(x))
#define pb push_back
#define db double
using namespace std;
const int maxn=200010;
const int inf=1e18;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}
bool Mbe;

int n;
void work(){
	n=read();
}

// \
444

bool Med;
int T;
signed main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	
//	ios::sync_with_stdio(0);
//	cin.tie(0);cout.tie(0);
	
//	cerr<<(&Mbe-&Med)/1048576.0<<" MB\n";
	
	T=1;
	while(T--)work();
}
```

### fastio

```cpp
static char buf[1000000],*p1=buf,*p2=buf;
#define getchar() p1==p2&&(p2=(p1=buf)+fread(buf,1,1000000,stdin),p1==p2)?EOF:*p1++
inline int read(){int x=0,f=1;char c=getchar();while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}while(c>='0'&&c<='9'){x=(x<<3)+(x<<1)+c-48;c=getchar();}return x*f;}
inline void write(int x){static char buf[20];static int len=-1;if(x<0)putchar('-'),x=-x;do buf[++len]=x%10,x/=10;while(x);while(len>=0)putchar(buf[len--]+48);}
#define put() putchar(' ')
#define endl puts("")
```

## 字符串

### kmp

```cpp
char s[maxn],q[maxn];
int n,m,nxt[maxn];
int main(){
	scanf("%s%s",s+1,q+1);n=strlen(s+1),m=strlen(q+1);
	for(int i=2,j=0;i<=m;i++){
		while(j&&q[i]!=q[j+1])j=nxt[j];
		if(q[i]==q[j+1])j++;
		nxt[i]=j;
	}
	for(int i=1,j=0;i<=n;i++){
		while(j&&s[i]!=q[j+1])j=nxt[j];
		if(s[i]==q[j+1])j++;
		if(j==m){
			printf("%d\n",i-m+1);
			j=nxt[j];
		}
	}
	for(int i=1;i<=m;i++)printf("%d ",nxt[i]);
}
```

### manacher

```cpp
int n,ans;
char s[maxn],a[maxn<<1];
int len[maxn<<1];
void change(){
	a[0]='#';a[1]='#';
	for(int i=1;i<=n;i++)a[i<<1]=s[i],a[i<<1|1]='#';
	n=n<<1|1;
}
void manacher(){
	int maxr=0,mid=0;
	for(int i=1;i<=n;i++){
		if(i<maxr)len[i]=min(len[mid*2-i],len[mid]+mid-i);
		else len[i]=1;
		while(a[i+len[i]]==a[i-len[i]])++len[i];
		if(len[i]+i>maxr){
			maxr=len[i]+i;
			mid=i;
		}
	}
}
signed main(){
	scanf("%s",s+1);n=strlen(s+1);
	change();manacher();
	for(int i=1;i<=n;i++)ans=max(ans,len[i]);
	printf("%d",ans-1);
}
```

### Z 函数

```cpp
int n,z[maxn];
char s[maxn];
void work(){
	scanf("%s",s);n=strlen(s);
	for(int i=1,l=0,r=0;i<n;i++){
		z[i]=max(0ll,min(z[i-l],r-i+1));
		while(i+z[i]<n&&s[z[i]]==s[i+z[i]])z[i]++;
		if(i+z[i]-1>r)l=i,r=i+z[i]-1;
	}
	for(int i=0;i<n;i++)printf("%lld ",z[i]);
}
```

### SAM

```cpp
int n,ans;
char s[maxn];
int len[maxn],lnk[maxn];
int a[maxn][26];
int p=1,cur=1;
int siz[maxn];
void insert(int c){
	int nd=++cur;
	len[nd]=len[p]+1;siz[nd]=1;
	while(p&&!a[p][c])a[p][c]=nd,p=lnk[p];
	if(!p){lnk[p=nd]=1;return ;}
	int q=a[p][c];
	if(len[p]+1==len[q])lnk[nd]=q;
	else{
		int cl=++cur;
		len[cl]=len[p]+1,lnk[cl]=lnk[q];
		memcpy(a[cl],a[q],sizeof(a[q]));
		lnk[nd]=lnk[q]=cl;
		while(p&&a[p][c]==q)a[p][c]=cl,p=lnk[p];
	}
	p=nd;
}
int head[maxn],tot;
struct nd{
	int nxt,to;
}e[maxn];
void add(int u,int v){e[++tot]={head[u],v};head[u]=tot;}
void dfs(int u){
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;
		dfs(v),siz[u]+=siz[v];
	}
}
void work(){
	scanf("%s",s+1),n=strlen(s+1);
	for(int i=1;i<=n;i++)insert(s[i]-'a');
	for(int i=2;i<=cur;i++)add(lnk[i],i);
	dfs(1);
	for(int i=2;i<=cur;i++)if(siz[i]>1)ans=max(ans,siz[i]*len[i]);
	printf("%lld\n",ans);
}
```

### 带通配符字符串匹配

ntt 部分略。要求 $n$ 不能过大超过 $mod$，否则使用 fft。

```cpp
int n,m;
char s[maxn],t[maxn];
int f[maxn],g[maxn],res[maxn];
vector<int> ans;
void work(){
	m=read();n=read();
	scanf("%s%s",t,s);
	reverse(t,t+m);
	int lim=1;while(lim<n)lim<<=1;
	for(int i=0;i<lim;i++)to[i]=(to[i>>1]>>1)|((i&1)?lim>>1:0);
	for(int i=0;i<m;i++)if(t[i]!='*')f[i]=(t[i]-'a')*(t[i]-'a');
	for(int i=0;i<n;i++)if(s[i]!='*')g[i]=1;
	ntt(f,lim,1),ntt(g,lim,1);
	for(int i=0;i<lim;i++)res[i]=f[i]*g[i]%mod,f[i]=g[i]=0;
	for(int i=0;i<m;i++)if(t[i]!='*')f[i]=t[i]-'a';
	for(int i=0;i<n;i++)if(s[i]!='*')g[i]=s[i]-'a';
	ntt(f,lim,1),ntt(g,lim,1);
	for(int i=0;i<lim;i++)(res[i]+=mod-2*f[i]*g[i]%mod)%=mod,f[i]=g[i]=0;
	for(int i=0;i<m;i++)if(t[i]!='*')f[i]=1;
	for(int i=0;i<n;i++)if(s[i]!='*')g[i]=(s[i]-'a')*(s[i]-'a');
	ntt(f,lim,1),ntt(g,lim,1);
	for(int i=0;i<lim;i++)(res[i]+=f[i]*g[i])%=mod,f[i]=g[i]=0;
	ntt(res,lim,-1);
	for(int i=m-1;i<n;i++)if(!res[i])ans.pb(i-m+2);
	printf("%lld\n",(int)ans.size());
	for(int i:ans)printf("%lld ",i);
}
```

## 图论

### 边双

```cpp
int n,m;
int head[maxn],tot=1;
struct nd{
	int nxt,to;
}e[maxn<<1];
void add(int u,int v){e[++tot]={head[u],v};head[u]=tot;}
int dfn[maxn],lw[maxn],idx;
int st[maxn],tp;
vector<int> g[maxn];
int num;
bool vis[maxn];
void tar(int u,int fl){
	dfn[u]=lw[u]=++idx;st[++tp]=u;
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;
		if(i==(fl^1))continue;
		if(!dfn[v]){
			tar(v,i);
			lw[u]=min(lw[u],lw[v]);
		}
		else lw[u]=min(lw[u],dfn[v]);
	}
	if(lw[u]==dfn[u]){
		++num;
		g[num].push_back(st[tp]);
		while(st[tp--]!=u){
			g[num].push_back(st[tp]);
		}
	}
}
void work(){
	n=read();m=read();
	for(int i=1;i<=m;i++){
		int u=read(),v=read();
		add(u,v),add(v,u);
	}
	for(int i=1;i<=n;i++)if(!dfn[i])tar(i,0);
	printf("%lld\n",num);
	for(int i=1;i<=num;i++){
		printf("%lld ",g[i].size());
		for(int j:g[i])printf("%lld ",j);
		printf("\n");
	}
}
```

### 点双

```cpp
int n,m,num;
vector<int> e[maxn],g[maxn];
int dfn[maxn],idx,lw[maxn];
int st[maxn],tp;
void tar(int u){
	dfn[u]=lw[u]=++idx;st[++tp]=u;
	for(int v:e[u]){
		if(!dfn[v]){
			tar(v);
			lw[u]=min(lw[u],lw[v]);
			if(lw[v]>=dfn[u]){
				g[++num].push_back(st[tp]);
				while(st[tp--]!=v)g[num].push_back(st[tp]);
				g[num].push_back(u);
			}
		}
		else lw[u]=min(lw[u],dfn[v]);
	}
}
void work(){
	n=read();m=read();
	for(int i=1;i<=m;i++){
		int u=read(),v=read();
		e[u].push_back(v),e[v].push_back(u);
	}
	for(int i=1;i<=n;i++)if(!dfn[i]){
		int lst=idx;tar(i);
		if(idx==lst+1)g[++num].push_back(i);
	}
	printf("%lld\n",num);
	for(int i=1;i<=num;i++){
		printf("%lld ",(int)g[i].size());
		for(int j:g[i])printf("%lld ",j);printf("\n");
	}
}
```

### 无向图四元环计数

```cpp
int n,m;
int d[maxn],cnt[maxn],ans;
vector<int> e[maxn],g[maxn];
void work(){
	n=read();m=read();
	for(int i=1;i<=m;i++){
		int u=read(),v=read();
		e[u].push_back(v),e[v].push_back(u);
		d[u]++,d[v]++;
	}
	for(int u=1;u<=n;u++){
		for(int v:e[u])if(d[u]>d[v]||(d[u]==d[v]&&u>v))g[u].push_back(v);
	}
	for(int i=1;i<=n;i++){
		for(int j:g[i]){
			for(int k:e[j])if(d[i]>d[k]||(d[i]==d[k]&&i>k))ans+=cnt[k]++;
		}
		for(int j:g[i])for(int k:e[j])cnt[k]=0;
	}
	printf("%lld\n",ans);
}
```

## 数据结构

### 李超线段树

```cpp
struct line{
	db k,b;
}p[maxn];
db calc(int u,int x){return 1.0*(x*p[u].k+p[u].b);}
int tree[maxn<<1];
#define ls nd<<1
#define rs nd<<1|1
#define mid (l+r>>1)
void upd(int nd,int l,int r,int id){
	if(l==r){
		if(calc(id,l)-calc(tree[nd],l)>eps)tree[nd]=id;
		return ;
	}
	if(calc(id,mid)-calc(tree[nd],mid)>eps)swap(tree[nd],id);
	if(calc(id,l)-calc(tree[nd],l)>eps)upd(ls,l,mid,id);
	else upd(rs,mid+1,r,id);
}
void updata(int nd,int l,int r,int ql,int qr,int id){
	if(l>=ql&&r<=qr){
		upd(nd,l,r,id);
		return ;
	}
	if(ql<=mid)updata(ls,l,mid,ql,qr,id);
	if(qr>mid)updata(rs,mid+1,r,ql,qr,id);
}
int query(int nd,int l,int r,int p){
	if(l==r)return tree[nd];
	int res;
	if(p<=mid)res=query(ls,l,mid,p);
	else res=query(rs,mid+1,r,p);
	if(calc(tree[nd],p)-calc(res,p)>eps)return tree[nd];
	if(calc(tree[nd],p)-calc(res,p)<-eps)return res;
	return min(tree[nd],res);
}
```

### fhq treap

```cpp
struct fhq{
	int w[maxn],ls[maxn],rs[maxn],idx,rt;
	int siz[maxn],sz[maxn];
	void up(int u){
		siz[u]=siz[ls[u]]+siz[rs[u]]+sz[u];
	}
	int merge(int u,int v){
		if(!u||!v)return u|v;
		if(w[u]<w[v]){
			rs[u]=merge(rs[u],v);
			up(u);
			return u;
		}
		else{
			ls[v]=merge(u,ls[v]);
			up(v);
			return v;
		}
	}
	pii split(int u,int k){
		if(!u)return {0,0};
		if(siz[ls[u]]+sz[u]>k){
			pii t=split(ls[u],k);
			ls[u]=t.se;
			up(u);
			return {t.fi,u};
		}
		else{
			pii t=split(rs[u],k-siz[ls[u]]-sz[u]);
			rs[u]=t.fi;
			up(u);
			return {u,t.se};
		}
	}
	int newnode(int s,int v){
		w[++idx]=rnd();siz[idx]=sz[idx]=s,val[idx]=num[idx]=v;
		return idx;
	}
}t;
```

### 线段树分裂

```cpp
int rt[maxn],cnt;
#define mid (l+r>>1)
#define ls lc[nd]
#define rs rc[nd]
ll tree[maxn<<5];
int lc[maxn<<5],rc[maxn<<5],idx;
int st[maxn<<5],tp;
int newnode(){
	if(tp)return st[tp--];
	return ++idx;
}
void clr(int nd){
	tree[nd]=0,ls=rs=0;
	st[++tp]=nd;
}
void updata(int &nd,int l,int r,int p,int w){
	if(!nd)nd=newnode();
	tree[nd]+=w;
	if(l==r)return ;
	if(p<=mid)updata(ls,l,mid,p,w);
	else updata(rs,mid+1,r,p,w);
	tree[nd]=tree[ls]+tree[rs];
}
ll query(int nd,int l,int r,int ql,int qr){
	if(!nd||ql>qr)return 0;
	if(l>=ql&&r<=qr)return tree[nd];
	if(qr<=mid)return query(ls,l,mid,ql,qr);
	if(ql>mid)return query(rs,mid+1,r,ql,qr);
	return query(ls,l,mid,ql,qr)+query(rs,mid+1,r,ql,qr);
}
int fdkth(int nd,int l,int r,ll k){
	if(tree[nd]<k)return -1;
	if(l==r)return l;
	if(tree[ls]>=k)return fdkth(ls,l,mid,k);
	return fdkth(rs,mid+1,r,k-tree[ls]);
}
int merge(int u,int v,int l,int r){
	if(!u||!v)return u|v;
	if(l==r){tree[u]+=tree[v];clr(v);return u;}
	lc[u]=merge(lc[u],lc[v],l,mid);
	rc[u]=merge(rc[u],rc[v],mid+1,r);
	tree[u]=tree[lc[u]]+tree[rc[u]];clr(v);
	return u;
}
int split(int nd,int l,int r,ll k){
	if(!nd)return 0;
	int u=newnode();
	if(k>tree[ls])rc[u]=split(rs,mid+1,r,k-tree[ls]);
	else rc[u]=rs,rs=0;
	if(k<tree[ls])lc[u]=split(ls,l,mid,k);
	tree[nd]=tree[ls]+tree[rs],tree[u]=tree[lc[u]]+tree[rc[u]];
	return u;
}
```

### 手写 bitset

```cpp
#define ull unsigned long long
ull pw[65];
struct bs{
	vector<ull> a;
	int len,n;
	void init(int _n){
		n=_n,len=(n+63)/64;a.resize(len+1,0);
	}
	void set0(int x){a[x>>6]&=~pw[x&63];}
	void set1(int x){a[x>>6]|=pw[x&63];}
	bool operator[](int x){return (a[x>>6]>>(x&63))&1;}
	bs operator|(const bs&b)const{
		bs c;c.init(max(n,b.n));
		for(int i=0;i<c.len;i++)c.a[i]=a[i]|b.a[i];
		return c;
	}
	bs operator&(const bs&b)const{
		bs c;c.init(min(n,b.n));
		for(int i=0;i<c.len;i++)c.a[i]=a[i]&b.a[i];
		return c;
	}
	void operator|=(const bs&b){
		for(int i=0;i<max(len,b.len);i++)a[i]|=b.a[i];
	}
	void operator&=(const bs&b){
		for(int i=0;i<min(len,b.len);i++)a[i]&=b.a[i];
	}
	bs operator<<(int x)const{
		bs res;res.init(n);
		int y=x>>6,z=x&63;
		ull lst=0;
		for(int i=0;i+y<res.len;i++){
			res.a[i+y]=lst|(a[i]<<z);
			if(z)lst=a[i]>>(64ll-z);
		}
		return res;
	}
}
```

### 哈希表

```cpp
struct hsh_table{
	int head[maxn],tot;
	struct nd{
		int nxt;
		ull key;
		int val;
	}e[maxn];
	int hsh(ull u){return u%maxn;}
	bool find(ull key){
		int u=hsh(key);
		for(int i=head[u];i;i=e[i].nxt){
			if(e[i].key==key)return 1;
		}
		return 0;
	}
	int &operator[](ull key){
		int u=hsh(key);
		for(int i=head[u];i;i=e[i].nxt){
			if(e[i].key==key)return e[i].val;
		}
		e[++tot]={head[u],key,0};head[u]=tot;
		return e[tot].val;
	}
	void clear(){
		tot=0;
		for(int i=0;i<maxn;i++)head[i]=0;
	}
}mp;
```
## 数学 

### 拉格朗日插值

```cpp
void work(){
	n=read();k=read();
	for(int i=1;i<=n;i++)x[i]=read(),y[i]=read();
	// for(int i=1;i<=n;i++){
		// int mul=y[i];
		// for(int j=1;j<=n;j++)if(i!=j){
			// mul=mul*(k-x[j]+mod)%mod*ksm(x[i]-x[j]+mod)%mod;
		// }
		// (ans+=mul)%=mod;
	// }
    int g=1;
	for(int i=1;i<=n;i++){
		g=g*(k-x[i]+mod)%mod;
		t[i]=y[i];for(int j=1;j<i;j++)t[i]=t[i]*ksm(x[i]-x[j]+mod)%mod;
		for(int j=1;j<i;j++)t[j]=t[j]*ksm(x[j]-x[i]+mod)%mod;
	}
	
	// pre[0]=x;for(int i=1;i<=n;i++)pre[i]=pre[i-1]*(x-i)%mod;
	// suf[n]=x-n;for(int i=n-1;~i;i--)suf[i]=suf[i+1]*(x-i)%mod;
	// int val=0;
	// for(int i=0;i<=n;i++){
		// (val+=y[i]*(i?pre[i-1]:1)%mod*(i<n?suf[i+1]:1)*inv[i]%mod*inv[n-i]%mod*(((n-i)&1)?mod-1:1))%=mod;
	// }
	
	for(int i=1;i<=n;i++)(ans+=t[i]*ksm(k-x[i]+mod))%=mod;ans=ans*g%mod;
	printf("%lld\n",ans);
}
```

### 矩阵求逆

```cpp
void work(){
	n=read();
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++)a[i][j]=read();a[i][i+n]=1;
	}
	for(int i=1;i<=n;i++){
		if(!a[i][i]){
			for(int j=i+1;j<=n;j++)if(a[j][i]){
				swap(a[i],a[j]);
				break;
			}
		}
		if(!a[i][i]){puts("No Solution");return ;}
		int inv=ksm(a[i][i]);
		for(int j=1;j<=n;j++)if(i!=j){
			int d=a[j][i]*inv%mod;
			for(int k=i;k<=(n<<1);k++)(a[j][k]+=mod-a[i][k]*d%mod)%=mod;
		}
		for(int j=i;j<=(n<<1);j++)a[i][j]=a[i][j]*inv%mod;
	}
	for(int i=1;i<=n;i++){
		for(int j=n+1;j<=(n<<1);j++)printf("%lld ",a[i][j]);puts("");
	}
}
```

### [快速离散对数](https://yhddd123.github.io/post/p11175-ti-jie/)

```cpp
int mod,g,n,q;
int B,bas,h0;
struct hsh_table{
}mp;
int bsgs(int v){
	int mul=v;
	for(int i=0;i<=mod/B;i++){
		if(mp.find(mul))return i*B+mp[mul];
		mul=1ll*mul*bas%mod;
	}
}
/*
mod=ba+c
log(a)=log(-c)-log(b)=log(mod-1)+log(c)-log(b)
log(a)=log(a-c)-log(b+1)
min(c,a-c)<=a/2
*/
int h[maxn];
int sovle(int a){
	int b=mod/a,c=mod%a;
	if(a<=n)return h[a];
	if(c<a-c)return inc(inc(h0,sovle(c)),(mod-1-h[b]));
	else return inc(sovle(a-c),mod-1-h[b+1]);
}
bool vis[maxn];
int pre[maxn],cnt;
void work(){
	mod=read();g=read();n=sqrt(mod)+1;B=sqrt(1ll*mod*n/log2(n));
	// cout<<n<<" "<<B<<"\n";
	int mul=1;for(int i=0;i<B;i++){
		mp[mul]=i;
		mul=1ll*mul*g%mod;
	}
	bas=ksm(ksm(g,B));h0=bsgs(mod-1);h[1]=0;
	for(int i=2;i<=n;i++){
		if(!vis[i]){
			h[i]=bsgs(i);
			pre[++cnt]=i;
		}
		for(int j=1;j<=cnt&&1ll*i*pre[j]<=n;j++){
			vis[i*pre[j]]=0;
			h[i*pre[j]]=(h[i]+h[pre[j]])%(mod-1);
			if(i%pre[j]==0)break;
		}
	}
	q=read();
	while(q--){
		int x=read();
		printf("%lld\n",sovle(x));
	}
}
```