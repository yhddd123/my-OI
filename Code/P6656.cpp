#include<bits/stdc++.h>
#define ll long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
using namespace std;
inline void write(int x){static char buf[20];static int len=-1;if(x<0)putchar('-'),x=-x;do buf[++len]=x%10,x/=10;while(x);while(len>=0)putchar(buf[len--]+48);}
const int maxn=1000010;
bool mbe;

int n;
char s[maxn];
struct SA{
int sa[maxn],rk[maxn<<1],tmp[maxn<<1];
int t[maxn],id[maxn];
int ht[maxn],st[20][maxn];
inline int que(int l,int r){
    l=rk[l],r=rk[r];
    if(l>r)swap(l,r);l++;
    int k=31-__builtin_clz(r-l+1);
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
        while(max(i+l,sa[rk[i]-1]+l)<=n&&s[i+l]==s[sa[rk[i]-1]+l])l++;
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
vector<tuple<int,int,int>> res;
const int maxm=1<<22;
struct hsh_table{
	int head[maxm],tot;
	struct nd{
		int nxt;
		ll key;
		bool val;
	}e[maxn];
	inline int hsh(ll u){return u&(maxm-1);}
	inline bool chk(ll key){
		int u=hsh(key);
		for(int i=head[u];i;i=e[i].nxt)if(e[i].key==key)return 0;
		e[++tot]={head[u],key,1};head[u]=tot;
		return 1;
	}
}mp;
ll id(int l,int r){return 1ll*l*n+r;}
void work(){
    scanf("%s",s+1);n=strlen(s+1);
    t1.init(s);
    reverse(s+1,s+n+1);
    t2.init(s);
    reverse(s+1,s+n+1);
    for(int i=1;i<=n/2;i++){
        for(int j=i;j<=n-i;j+=i){
            int lp=lcp(j,j+i),ls=lcs(j,j+i);
            if(lp+ls-1>=i){
                ll v=id(j-ls+1,j+i+lp-1);
                if(mp.chk(v))res.pb({j-ls+1,j+i+lp-1,i});
            }
        }
    }
    sort(res.begin(),res.end());
    write(res.size()),puts("");
    for(auto[l,r,p]:res)write(l),putchar(' '),write(r),putchar(' '),write(p),puts("");
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