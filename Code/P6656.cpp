// Problem: P6656 【模板】Runs
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P6656
// Memory Limit: 256 MB
// Time Limit: 2000 ms
// Written by yhm.
// Start codeing:2026-02-01 11:08:02
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define ll long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
using namespace std;
inline int read(){
    int x=0,fl=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')fl=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*fl;
}
inline void write(int x){static char buf[20];static int len=-1;if(x<0)putchar('-'),x=-x;do buf[++len]=x%10,x/=10;while(x);while(len>=0)putchar(buf[len--]+48);}
const int maxn=1000010;
bool mbe;

int n;
char s[maxn];
struct SA{
int sa[maxn],rk[maxn<<1],tmp[maxn<<1],ht[maxn],t[maxn],id[maxn];
int st[20][maxn];
inline int que(int l,int r){
    l=rk[l],r=rk[r];
    if(l>r)swap(l,r);l++;
    int k=__lg(r-l+1);
    return min(st[k][l],st[k][r-(1<<k)+1]);
}
void init(char *s){
	int w=26;
	for(int i=1;i<=n;i++)++t[rk[i]=s[i]-'a'+1];
	for(int i=1;i<=w;i++)t[i]+=t[i-1];
	for(int i=n;i;i--)sa[t[rk[i]]--]=i;
    for(int len=1;len<n;len<<=1){
    	int cur=0;for(int i=n-len+1;i<=n;i++)id[++cur]=i;
    	for(int i=1;i<=n;i++)if(sa[i]>len)id[++cur]=sa[i]-len;
    	for(int i=1;i<=w;i++)t[i]=0;
    	for(int i=1;i<=n;i++)t[rk[i]]++;
    	for(int i=1;i<=w;i++)t[i]+=t[i-1];
    	for(int i=n;i;i--)sa[t[rk[id[i]]]--]=id[i];
        for(int i=1;i<=n;i++)tmp[i]=rk[i];
    	int p=0;
        for(int i=1;i<=n;i++){
            if(tmp[sa[i]]==tmp[sa[i-1]]&&tmp[sa[i]+len]==tmp[sa[i-1]+len])rk[sa[i]]=p;
            else rk[sa[i]]=++p;
        }
        w=p;
        if(w==n)break;
    }
    ht[1]=0;
    for(int i=1,l=0;i<=n;i++){
        if(rk[i]==1)continue;
        if(l)l--;
        while(min(i+l,sa[rk[i]-1]+l)<=n&&s[i+l]==s[sa[rk[i]-1]+l])l++;
        ht[rk[i]]=l;
    }
    for(int i=1;i<=n;i++)st[0][i]=ht[i];
    for(int j=1;j<20;j++){
        for(int i=1;i+(1<<j)-1<=n;i++)st[j][i]=min(st[j-1][i],st[j-1][i+(1<<j-1)]);
    }
}
}t1,t2;
inline int lcp(int p,int q){return t1.que(p,q);}
inline int lcs(int p,int q){return t2.que(n-p+1,n-q+1);}
const int maxm=1<<22;
struct hsh_table{
	int head[maxm],tot;
	struct nd{
		int nxt;
		ll key;
		bool val;
	}e[maxn<<1];
	inline int hsh(ll u){return u&(maxm-1);}
	bool find(ll key){
		int u=hsh(key);
		for(int i=head[u];i;i=e[i].nxt){
			if(e[i].key==key)return 1;
		}
		return 0;
	}
	inline bool &operator[](ll key){
		int u=hsh(key);
		for(int i=head[u];i;i=e[i].nxt){
			if(e[i].key==key)return e[i].val;
		}
		e[++tot]={head[u],key,0};head[u]=tot;
		return e[tot].val;
	}
}mp;
ll id(int l,int r){return 1ll*l*n+r;}
struct node{
	int l,r,p;
}res[maxn<<1];int tp;
void work(){
    scanf("%s",s+1);n=strlen(s+1);
    t1.init(s);
    reverse(s+1,s+n+1);
    t2.init(s);
    for(int i=1;i<=n/2;i++){
        for(int j=i;j<=n-i;j+=i){
            int lp=lcp(j,j+i),ls=lcs(j,j+i);
            if(lp+ls-1>=i){
                ll v=id(j-ls+1,j+i+lp-1);
                bool &fl=mp[v];
                if(!fl)fl=1,res[++tp]={j-ls+1,j+i+lp-1,i};
            }
        }
    }
    sort(res+1,res+tp+1,[&](node u,node v){return u.l<v.l||(u.l==v.l&&u.r<v.r);});
    write(tp);puts("");
    for(int i=1;i<=tp;i++)write(res[i].l),putchar(' '),write(res[i].r),putchar(' '),write(res[i].p),puts("");
}

bool med;
int T;
signed main(){
    // freopen("A.in","r",stdin);
    // freopen("A.out","w",stdout);
    
    // cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
    
    T=1;
    while(T--)work();
}