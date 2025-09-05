#include<bits/stdc++.h>
// #define int long long
#define ull unsigned long long
#define mod 1000000007ll
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
using namespace std;
static char buf[1000000],*p1=buf,*p2=buf;
#define getchar() p1==p2&&(p2=(p1=buf)+fread(buf,1,1000000,stdin),p1==p2)?EOF:*p1++
inline int read(){int x=0,f=1;char c=getchar();while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}while(c>='0'&&c<='9'){x=(x<<3)+(x<<1)+c-48;c=getchar();}return x*f;}
const int maxn=300010;
const int maxm=1000100;

int n,a[maxn];
mt19937_64 rnd(1);
ull val[maxm],sum[maxm];
struct ds{
    bitset<maxm> vis;
    int st[maxm],tp;
    ull hsh;int pl,pr;
    void init(){
        pl=maxm,pr=0;hsh=0;
        while(tp)vis[st[tp--]]=0;
    }
    void ins(int v){
        if(pl==v)pl=maxm;
        while(vis[v])hsh-=val[v],vis[v]=0,v++;
        hsh+=val[v],vis[v]=1;pl=min(pl,v),pr=max(pr,v);st[++tp]=v;
    }
}t;
int dp[maxn];
ull h[maxn],hh[maxn];
struct hsh_table{
	int st[maxn],tp;
	int head[maxn],tot;
	struct nd{
		int nxt;
		ull key;
		int val;
	}e[maxn];
	inline int hsh(ull u){return u%maxn;}
	int que(ull key){
		int u=hsh(key);
		for(int i=head[u];i;i=e[i].nxt){
			if(e[i].key==key)return e[i].val;
		}
		return 0;
	}
	inline int &operator[](ull key){
		int u=hsh(key);
		if(!head[u])st[++tp]=u;
		for(int i=head[u];i;i=e[i].nxt){
			if(e[i].key==key)return e[i].val;
		}
		e[++tot]={head[u],key,0};head[u]=tot;
		return e[tot].val;
	}
	void clear(){
		while(tp)head[st[tp--]]=0;tot=0;
	}
}mp;
struct hsh_table1{
	int head[maxm],tot;
	struct nd{
		int nxt;
		ull key;
		bool val;
	}e[maxm];
	inline int hsh(ull u){return u%maxm;}
	bool que(ull key){
		int u=hsh(key);
		for(int i=head[u];i;i=e[i].nxt){
			if(e[i].key==key)return 1;
		}
		return 0;
	}
	inline bool &operator[](ull key){
		int u=hsh(key);
		for(int i=head[u];i;i=e[i].nxt){
			if(e[i].key==key)return e[i].val;
		}
		e[++tot]={head[u],key,0};head[u]=tot;
		return e[tot].val;
	}
}vis;
inline void inc(int &u,int v){((u+=v)>=mod)&&(u-=mod);}
void sovle(int l,int r){
    if(l==r){inc(dp[l],dp[l-1]);return ;}
    int mid=l+r>>1;
    sovle(l,mid);
    t.init();
    for(int i=mid+1;i<=r;i++)t.ins(a[i]),h[i]=t.hsh,hh[i]=sum[t.pr]-sum[t.pl-1]+val[t.pl]-h[i];
    t.init();
    for(int i=mid;i>=l;i--)t.ins(a[i]),h[i]=t.hsh,hh[i]=sum[t.pr]-sum[t.pl-1]+val[t.pl]-h[i];
    // cout<<l<<" "<<r<<" s\n";
    // for(int i=l;i<=r;i++){
    	// cout<<i<<" "<<h[i]<<" "<<pl[i]<<" "<<pr[i]<<"\n";
    // }
    for(int i=l;i<=mid;i++)mp[h[i]]=dp[i-1];
    for(int i=mid+1;i<=r;i++)inc(dp[i],mp.que(hh[i]));
    for(int i=mid+1;i<=r;i++)if(vis.que(h[i]))inc(dp[i],mod-mp.que(h[i]));
    mp.clear();
    for(int i=l;i<=mid;i++)inc(mp[hh[i]],dp[i-1]);
    for(int i=mid+1;i<=r;i++)inc(dp[i],mp.que(h[i]));
    mp.clear();
    sovle(mid+1,r);
}
void work(){
    for(int i=0;i<maxm;i++){
    	val[i]=rnd();
    	while(vis.que(val[i]))val[i]=rnd();
    	vis[val[i]]=1;
    }
    for(int i=1;i<maxm;i++)sum[i]=sum[i-1]+val[i];
    n=read();
    for(int i=1;i<=n;i++)a[i]=read()+1;
    dp[0]=1;sovle(1,n);
    // for(int i=1;i<=n;i++)cout<<dp[i]<<" ";cout<<"\n";
    printf("%d\n",dp[n]);
}

int T;
signed main(){
    // freopen("A.in","r",stdin);
    // freopen(".out","w",stdout);
    
    T=1;
    while(T--)work();
}