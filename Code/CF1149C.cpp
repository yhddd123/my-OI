#include<bits/stdc++.h>
#define int long long
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
const int maxn=200010;
const int inf=1e9;

int n,q;
char s[maxn];
#define mid ((l+r)>>1)
#define ls nd<<1
#define rs nd<<1|1
#define all 1,1,2*n-2
int mn[maxn<<2],mx[maxn<<2],tag[maxn<<2],ab[maxn<<2],bc[maxn<<2],abc[maxn<<2];
void upd(int nd,int w){mn[nd]+=w,mx[nd]+=w,ab[nd]-=w,bc[nd]-=w,tag[nd]+=w;}
void down(int nd){upd(ls,tag[nd]),upd(rs,tag[nd]);tag[nd]=0;}
void up(int nd){
	mn[nd]=min(mn[ls],mn[rs]);mx[nd]=max(mx[ls],mx[rs]);
	ab[nd]=max({ab[ls],ab[rs],mx[ls]-2*mn[rs]});
	bc[nd]=max({bc[ls],bc[rs],-2*mn[ls]+mx[rs]});
	abc[nd]=max({abc[ls],abc[rs],ab[ls]+mx[rs],mx[ls]+bc[rs]});	
}
void updata(int nd,int l,int r,int ql,int qr,int w){
	if(l>=ql&&r<=qr){upd(nd,w);return ;}
	if(tag[nd])down(nd);
	if(ql<=mid)updata(ls,l,mid,ql,qr,w);
	if(qr>mid)updata(rs,mid+1,r,ql,qr,w);
	up(nd);
}
void work(){
    n=read();q=read();scanf("%s",s+1);
    for(int i=1;i<=2*n-2;i++)updata(all,i,2*n-1,s[i]=='('?1:-1);
    printf("%lld\n",abc[1]);
    while(q--){
        int u=read(),v=read();
        if(s[u]!=s[v]){
            updata(all,u,2*n-2,s[u]=='('?-2:2);
            updata(all,v,2*n-2,s[v]=='('?-2:2);
            swap(s[u],s[v]);
        }
        printf("%lld\n",abc[1]);
    }
}

int T;
signed main(){
    // freopen("A.in","r",stdin);
    // freopen(".out","w",stdout);
    
    T=1;
    while(T--)work();
}