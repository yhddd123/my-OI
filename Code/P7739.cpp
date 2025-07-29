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
bool mbe;

int n,q;
char s[maxn],op[10];
struct mat{
    int a00,a01,a10,a11;
    // void out(){
    // 	cout<<a00<<" "<<a01<<" "<<a10<<" "<<a11<<"\n";
    // }
};
mat a,b,I;
inline mat operator*(mat u,mat v){
    mat res;
    res.a00 = (u.a00 * v.a00 + u.a01 * v.a10) % mod;
    res.a01 = (u.a00 * v.a01 + u.a01 * v.a11) % mod;
    res.a10 = (u.a10 * v.a00 + u.a11 * v.a10) % mod;
    res.a11 = (u.a10 * v.a01 + u.a11 * v.a11) % mod;
    return res;
}
mt19937 rnd(1);
int lc[maxn],rc[maxn],w[maxn],siz[maxn],rt,idx;
bool tagf[maxn],tagr[maxn];
mat val[maxn],fval[maxn],mul[maxn],fmul[maxn],rev[maxn],frev[maxn];
int newnode(int k){
    int nd=++idx;
    w[nd]=rnd(),siz[nd]=1;
    if(!k){
        val[nd]=a,fval[nd]=b;
        mul[nd]=a,fmul[nd]=b;
        rev[nd]=a,frev[nd]=b;
    }
    else{
        val[nd]=b,fval[nd]=a;
        mul[nd]=b,fmul[nd]=a;
        rev[nd]=b,frev[nd]=a;
    }
    return nd;
}
void up(int u){
    siz[u]=siz[lc[u]]+siz[rc[u]]+1;
    mul[u]=mul[lc[u]]*val[u]*mul[rc[u]];
    fmul[u]=fmul[lc[u]]*fval[u]*fmul[rc[u]];
    rev[u]=rev[rc[u]]*val[u]*rev[lc[u]];
    frev[u]=frev[rc[u]]*fval[u]*frev[lc[u]];
}
void updf(int u){
    swap(val[u],fval[u]),swap(mul[u],fmul[u]),swap(rev[u],frev[u]);
    tagf[u]^=1;
}
void updr(int u){
    swap(mul[u],rev[u]),swap(fmul[u],frev[u]);
    tagr[u]^=1;
}
void down(int u){
    if(tagf[u])updf(lc[u]),updf(rc[u]),tagf[u]=0;
    if(tagr[u])updr(lc[u]),updr(rc[u]),tagr[u]=0;
}
int merge(int u,int v){
    if(!u||!v)return u|v;
    down(u),down(v);
    if(w[u]<w[v]){
        rc[u]=merge(rc[u],v);
        up(u);return u;
    }
    else{
        lc[v]=merge(u,lc[v]);
        up(v);return v;
    }
}
pii split(int u,int k){
    if(!u)return {0,0};
    down(u);
    if(siz[lc[u]]+1<=k){
        pii t=split(rc[u],k-siz[lc[u]]-1);
        rc[u]=t.fi;up(u);return {u,t.se};
    }
    else{
        pii t=split(lc[u],k);
        lc[u]=t.se;up(u);return {t.fi,u};
    }
}
void work(){
    n=read();q=read();scanf("%s",s+1);
    I.a00=I.a11=1,I.a01=I.a10=0;
    a.a00=a.a01=a.a11=1,a.a10=0;
    b.a00=0,b.a01=mod-1,b.a10=1,b.a11=2;
    val[0]=fval[0]=mul[0]=fmul[0]=rev[0]=frev[0]=I;
    for(int i=1;i<=n;i++)rt=merge(rt,newnode(s[i]=='W'?0:1));
    mat res=a*mul[rt];
    printf("%lld %lld\n",res.a11,res.a01);
    while(q--){
    	scanf("%s",op);
    	if(op[0]=='A'){
    		char ch=getchar();while(ch!='W'&&ch!='E')ch=getchar();
    		rt=merge(rt,newnode(ch=='W'?0:1));
    	}
    	else if(op[0]=='F'){
    		int l=read(),r=read(),x,y,z;
    		pii t=split(rt,l-1);x=t.fi,y=t.se;
    		t=split(y,r);y=t.fi,z=t.se;
    		updf(y);
    		rt=merge(x,merge(y,z));
    	}
    	else{
    		int l=read(),r=read(),x,y,z;
    		pii t=split(rt,l-1);x=t.fi,y=t.se;
    		t=split(y,r);y=t.fi,z=t.se;
    		updr(y);
    		rt=merge(x,merge(y,z));
    	}
    	mat res=a*mul[rt];
    	printf("%lld %lld\n",res.a11,res.a01);
    }
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