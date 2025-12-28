#include<bits/stdc++.h>
// #define int long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
using namespace std;
static char buf[1000000],*p1=buf,*p2=buf;
#define getchar() p1==p2&&(p2=(p1=buf)+fread(buf,1,1000000,stdin),p1==p2)?EOF:*p1++
inline int read(){int x=0,f=1;char c=getchar();while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}while(c>='0'&&c<='9'){x=(x<<3)+(x<<1)+c-48;c=getchar();}return x*f;}
inline void write(int x){static char buf[20];static int len=-1;if(x<0)putchar('-'),x=-x;do buf[++len]=x%10,x/=10;while(x);while(len>=0)putchar(buf[len--]+48);}
const int maxn=100010;
const int BB=18;

bool mbe;

#define ull unsigned long long
const ull U=-1ull;
ull pw[65];
struct bs{
	vector<ull> a;
	int len,n;
	void init(int _n,ull w=0){
		n=_n,len=(n+63)/64;a.resize(len+1,0);
        if(w==1)w=-1ull;
        for(ull &v:a)v=w;
	}
	inline void set0(int x){a[x>>6]&=~pw[x&63];}
	inline void set1(int x){a[x>>6]|=pw[x&63];}
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
	int count(){
		int res=0;for(int i=0;i<len;i++)res+=__builtin_popcountll(a[i]);
		return res;
	}
    int mex(){
        for(int i=0;i<a.size();i++){
            if(a[i]!=U){
                return (i<<6)+__builtin_ctzll(~a[i]);
            }
        }
    }
    inline void split(bs &b,int l,int r){
    	r=min(r,n);
        int pl=l>>6,pr=r>>6,p1=l&63,p2=(r&63);
        for(int i=pl;i<pr-(p1>p2);i++)if(b.a[i-pl]){
            b.a[i-pl]&=(a[i]>>p1)|(p1?(a[i+1]<<64ll-p1):0);
        }
        if(p1<=p2)b.a[pr-pl]&=(a[pr]&(pw[p2+1]-1))>>p1;
        else b.a[pr-1-pl]&=(a[pr-1]>>p1)|((a[pr]&(pw[p2+1]-1))<<64ll-p1);
        for(int i=pr-pl-(p1>p2)+1;i<b.a.size();i++)b.a[i]=0;
    }
}f[BB+1],g;
int n,q,a[maxn];
struct node{
    int l,r,id,b;
};
const int B=310;
vector<node> que,ask[maxn];
bool cmp(node u,node v){
    if(u.l/B==v.l/B)return ((u.l/B)&1)?u.r>v.r:u.r<v.r;
    return u.l<v.l;
}
int vis[maxn];
int ans[maxn];
void work(){
    n=read();
    for(int i=1;i<=n;i++)a[i]=read();
    pw[0]=1;for(int i=1;i<=64;i++)pw[i]=pw[i-1]*2;
    q=read();
    for(int i=1;i<=q;i++){
        int l=read(),r=read(),b=read();
        if(b<=BB)ask[b].pb({l,r,i,0});
        else que.pb({l,r,i,b});
    }
    for(int j=0;j<BB;j++)f[j].init(maxn+5);
    for(int i=1;i<=BB;i++)if(ask[i].size()){
        sort(ask[i].begin(),ask[i].end(),cmp);
        auto add=[&](int p){++vis[a[p]];if(vis[a[p]]==1)f[a[p]%i].set1(a[p]/i);};
        auto del=[&](int p){--vis[a[p]];if(!vis[a[p]])f[a[p]%i].set0(a[p]/i);};
        int l=1,r=0;
        for(auto[ql,qr,id,_]:ask[i]){
            while(l>ql)add(--l);
            while(r<qr)add(++r);
            while(l<ql)del(l++);
            while(r>qr)del(r--);
            for(int j=0;j<i;j++){
                ans[id]=max(ans[id],f[j].mex());
                // cout<<l<<" "<<r<<" "<<j<<" "<<f[j].count()<<" "<<f[j].mex()<<" "<<f[j][96]<<"\n";
            }
        }
        for(int i=l;i<=r;i++)del(i);
    }
    sort(que.begin(),que.end(),cmp);
    bs g;g.init(maxn+5);
    auto add=[&](int p){++vis[a[p]];if(vis[a[p]]==1)g.set1(a[p]);};
    auto del=[&](int p){--vis[a[p]];if(!vis[a[p]])g.set0(a[p]);};
    int l=1,r=0;
    for(auto[ql,qr,id,b]:que){
        while(l>ql)add(--l);
        while(r<qr)add(++r);
        while(l<ql)del(l++);
        while(r>qr)del(r--);
        bs h;h.init(b,1);
        // cout<<l<<" "<<r<<endl;
        // for(int i=l;i<=r;i++)cout<<a[i]<<" ";cout<<"\n";
        ans[id]=maxn/b+1;
        for(int t=0;t<=maxn/b;t++){
        	g.split(h,b*t,b*(t+1)-1);
            if(!h.count()){ans[id]=t;break;}
        }
    }
    for(int i=1;i<=q;i++)write(ans[i]),puts("");
}

bool med;
int T;
signed main(){
    // freopen("A.in","r",stdin);
    // freopen(".out","w",stdout);
    
    // cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
    
    T=1;
    while(T--)work();
}