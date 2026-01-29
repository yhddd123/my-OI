#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<cmath>
#include<vector>
#include<unordered_map>
using namespace std;
const int M=1200000,K=19,mod1=998244353,mod2=1000000007;
struct info
{
    int a,b;
};
int n,op[M],f[K][M],p[M],head[M],nxt[M],tot,to[M],s[M],son[M],l[M],pos[M],t,top[M],r[M],inv[M],id[M];
unordered_map<int,int>c[M];
int rand2()
{
    return rand()&32767;
}
int rand1()
{
    return (rand2()<<15^rand2())%mod2;
}
info merge(info x,info y)
{
    info z;
    z.a=(long long)x.a*y.a%mod2;
    z.b=((long long)x.a*y.b%mod2+x.b)%mod2;
    return z;
}
int power(int x,int y)
{
    int a,b,i;
    a=1;
    b=x;
    for (i=y-2;i;i>>=1)
    {
        if (i&1) a=(long long)a*b%y;
        b=(long long)b*b%y;
    }
    return a;
}
struct hash
{
    int a,b,dp1[M],dp2[M];
    info val[M];
    void build(int x,int l,int r)
    {
        int mid;
        val[x].b=1;
        if (l==r) return;
        mid=l+r>>1;
        build(x<<1,l,mid);
        build(x<<1^1,mid+1,r);
    }
    void modify2(int x,int l,int r,int p,int y)
    {
        int mid;
        if (l==r)
        {
            val[x].a=y;
            val[x].b=b;
            return;
        }
        mid=l+r>>1;
        if (p<=mid) modify2(x<<1,l,mid,p,y);
        else modify2(x<<1^1,mid+1,r,p,y);
        val[x]=merge(val[x<<1],val[x<<1^1]);
    }
    info ask2(int x,int l,int r,int ll,int rr)
    {
        int mid;
        if (l>=ll&&r<=rr) return val[x];
        mid=l+r>>1;
        if (ll<=mid&&rr>mid) return merge(ask2(x<<1,l,mid,ll,rr),ask2(x<<1^1,mid+1,r,ll,rr));
        if (ll<=mid) return ask2(x<<1,l,mid,ll,rr);
        return ask2(x<<1^1,mid+1,r,ll,rr);
    }
    int ask1(int u)
    {
        info x;
        x=ask2(1,1,n,l[u],pos[top[u]]);
        return (x.a+x.b)%mod2;
    }
    void modify1(int u)
    {
        int i;
        dp2[u]=a;
        for (i=u;;i=f[0][i])
        {
            modify2(1,1,n,l[i],dp2[i]);
            i=top[i];
            if (i==1) break;
            dp2[f[0][i]]=(long long)dp2[f[0][i]]*power(dp1[i],mod2)%mod2;
            dp1[i]=ask1(i);
            dp2[f[0][i]]=(long long)dp2[f[0][i]]*dp1[i]%mod2;
        }
    }
    void init()
    {
        int i;
        a=rand1()%mod2;
        b=rand1()%mod2;
        for (i=1;i<=n;i++) dp1[i]=1;
        build(1,1,n);
        modify1(1);
    }
}hash1;
struct bit1
{
    int val[M];
    void add(int u)
    {
        int i;
        for (i=l[u];i<=n;i+=i&-i) val[i]++;
    }
    void init()
    {
        add(1);
    }
    int ask2(int p)
    {
        int x,i;
        x=0;
        for (i=p;i;i-=i&-i) x+=val[i];
        return x;
    }
    int ask1(int u)
    {
        return ask2(r[u])-ask2(l[u]-1);
    }
}bit2;
struct bit3
{
    int val[M];
    void init()
    {
        int i;
        for (i=1;i<=n;i++) val[i]=1;
    }
    void add(int u,int x)
    {
        int i;
        for (i=l[u];i<=n;i+=i&-i) val[i]=(long long)val[i]*x%mod1;
    }
    int ask2(int p)
    {
        int x,i;
        x=1;
        for (i=p;i;i-=i&-i) x=(long long)x*val[i]%mod1;
        return x;
    }
    int ask1(int u)
    {
        return (long long)ask2(r[u])*power(ask2(l[u]-1),mod1)%mod1;
    }
}bit4;
void add(int u,int v)
{
    nxt[tot]=head[u];
    to[tot]=v;
    head[u]=tot++;
}
void dfs1(int u)
{
    int i,v;
    s[u]=1;
    for (i=head[u];i>-1;i=nxt[i])
    {
        v=to[i];
        dfs1(v);
        s[u]+=s[v];
//        if (s[v]>s[son[u]]) son[u]=v;
    }
}
void dfs2(int u,int x)
{
    int i,v;
    l[u]=pos[x]=++t;
    top[u]=x;
    if (son[u]) dfs2(son[u],x);
    for (i=head[u];i>-1;i=nxt[i])
    {
        v=to[i];
        if (v==son[u]) continue;
        dfs2(v,v);
    }
    r[u]=t;
}
int main()
{
    int m,i,j,k,u,x,l;
    scanf("%d",&m);
    n=1;
    for (i=0;i<m;i++)
    {
        scanf("%d",&op[i]);
        if (!op[i]) scanf("%d",&f[0][++n]);
        else scanf("%d",&p[i]);
    }
    for (i=1;i<=n;i++) head[i]=-1;
    for (i=2;i<=n;i++) add(f[0][i],i);
    dfs1(1);
    dfs2(1,1);
    for (i=1;i<K;i++) for (j=1;j<=n;j++) f[i][j]=f[i-1][f[i-1][j]];
    inv[1]=1;
    for (i=2;i<=n;i++) inv[i]=(long long)inv[mod1%i]*(mod1-mod1/i)%mod1;
    hash1.init();
    bit2.init();
    bit4.init();
    k=1;
    for (i=0;i<m;i++) if (!op[i])
    {
        for (j=++k;;j=u)
        {
            x=bit2.ask1(j);
            for (l=K-1;l>=0;l--) if (f[l][j]&&bit2.ask1(f[l][j])<x*2) j=f[l][j];
            if (j==1) break;
            u=f[0][j];
            if (bit2.ask1(u)<bit2.ask1(j)*2) continue;
            if (j<k) bit4.add(u,inv[c[u][hash1.ask1(j)]--]);
            if (id[u]&&bit2.ask1(u)+1>=bit2.ask1(id[u])*2)
            {
                c[u][hash1.ask1(id[u])]=1;
                id[u]=0;
            }
            if (bit2.ask1(u)<=bit2.ask1(j)*2)  id[u]=j;
        }
        hash1.modify1(k);
        bit2.add(k);
        for (j=k;;j=u)
        {
            x=bit2.ask1(j);
            for (l=K-1;l>=0;l--) if (f[l][j]&&bit2.ask1(f[l][j])<x*2) j=f[l][j];
            if (j==1) break;
            u=f[0][j];
            if (bit2.ask1(u)<bit2.ask1(j)*2) continue;;
            bit4.add(u,++c[u][hash1.ask1(j)]);
        }
    }
    else
    {
        printf("%d\n",bit4.ask1(p[i]));
    }
    return 0;
}