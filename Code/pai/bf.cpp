#include<stdio.h>
#include<algorithm>
#include<cstring>
#include<utility>
#include<map>
typedef unsigned int uint;
typedef unsigned long long ull;
constexpr int N(100000),K(20),Q(500000);
struct edge {
    int v,next;
};
edge e[(N<<1)+5];
int en,last[N+5];
inline void add_edge(const int &u,const int &v) {
    e[++en]={v,last[u]};
    last[u]=en;
}
int fa[N+5];
int bfn[N+5];
int que[N+5];
int lp[N+5][K+1],rp[N+5][K+1];
struct qry {
    int id,l,r;
};
qry qq[Q+5];
int ans[Q+5];
namespace BIT {
    int sum[N+5];
    inline void clear(const int &n) {
        std::memset(sum+1,0,n*sizeof(int));
    }
    inline void modify(int x,const int &y) {
        while(x) {
            sum[x]+=y;
            x-=x&-x;
        }
    }
    inline int query(const int &n,int x) {
        int y(0);
        while(x<=n) {
            y+=sum[x];
            x+=x&-x;
        }
        return y;
    }
}
namespace ODT {
    namespace MAP {
        std::pair<int,int> val[N+5];
        ull a1[(N>>6)+1],a2[(N>>12)+1],a3;
        inline void clear(const int &n) {
            std::memset(a1,0,((n>>6)+1)*sizeof(ull));
            std::memset(a2,0,((n>>12)+1)*sizeof(ull));
            a3=0;
        }
        inline void set(const uint &x) {
            a1[x>>6]|=1ull<<(x&63);
            a2[x>>12]|=1ull<<(x>>6&63);
            a3|=1ull<<(x>>12);
        }
        inline void reset(const uint &x) {
            (a1[x>>6]&=~(1ull<<(x&63)))||
            (a2[x>>12]&=~(1ull<<(x>>6&63)))||
            (a3&=~(1ull<<(x>>12)));
        }
        inline uint prev(uint x) {
            ull y(a1[x>>6]&(1ull<<(x&63))-1);
            if(y) {
                return (x&-1u<<6)|63-__builtin_clzll(y);
            }
            y=a2[x>>12]&(1ull<<(x>>6&63))-1;
            if(y) {
                x=(x&-1u<<12)|63-__builtin_clzll(y)<<6;
                return x|63-__builtin_clzll(a1[x>>6]);
            }
            y=a3&(1ull<<(x>>12))-1;
            if(y) {
                x=63-__builtin_clzll(y)<<12;
                x=x|63-__builtin_clzll(a2[x>>12])<<6;
                return x|63-__builtin_clzll(a1[x>>6]);
            }
            return -1u;
        }
        inline uint next(uint x) {
            ull y(a1[x>>6]&-2ull<<(x&63));
            if(y) {
                return (x&-1u<<6)|__builtin_ctzll(y);
            }
            y=a2[x>>12]&-2ull<<(x>>6&63);
            if(y) {
                x=(x&-1u<<12)|__builtin_ctzll(y)<<6;
                return x|__builtin_ctzll(a1[x>>6]);
            }
            y=a3&-2ull<<(x>>12);
            if(y) {
                x=__builtin_ctzll(y)<<12;
                x=x|__builtin_ctzll(a2[x>>12])<<6;
                return x|__builtin_ctzll(a1[x>>6]);
            }
            return -1u;
        }
        inline std::pair<int,int> &at(const uint &x) {
            return val[x];
        }
        inline void emplace(const uint &x,const std::pair<int,int> &y) {
            set(x),val[x]=y;
        }
        inline void erase(const uint &x) {
            reset(x);
        }
    }
    inline void clear(const int &n) {
        MAP::clear(n);
    }
    inline void erase(const int &l,const int &r,const int &c) {
        BIT::modify(c,-(r-l+1));
    }
    inline void color(const int &l,const int &r,const int &c) {
        BIT::modify(c,r-l+1);
    }
    inline void cover(const int &l,const int &r,const int &c) {
        if(l>r) {
            return;
        }
        // segments crossing left boundary
        uint it(MAP::prev(l+1));
        if(it!=-1u) {
            if(MAP::at(it).first>=r) {
                erase(l,r,MAP::at(it).second);
                if(MAP::at(it).first>r) {
                    MAP::emplace(r+1,MAP::at(it));
                }
            }
            else if(MAP::at(it).first>=l) {
                erase(l,MAP::at(it).first,MAP::at(it).second);
            }
            if(it<l) {
                MAP::at(it).first=l-1;
            }
            else {
                MAP::erase(it);
            }
        }
        // segments crossing right boundary
        it=MAP::prev(r+1);
        if(it!=-1u) {
            if(it>l) {
                erase(it,r,MAP::at(it).second);
                if(MAP::at(it).first>r) {
                    MAP::emplace(r+1,MAP::at(it));
                }
                MAP::erase(it);
            }
        }
        // segments inside
        for(it=MAP::next(l-1);it!=-1u&&it<=r;MAP::erase(it),it=MAP::next(it)) {
            erase(it,MAP::at(it).first,MAP::at(it).second);
        }
        // insert the new segment
        color(l,r,c);
        MAP::emplace(l,std::make_pair(r,c));
    }
}
void solve() {
    int n,k,q;
    scanf("%d%d%d",&n,&k,&q);
    std::memset(last+1,0,n*sizeof(int)),en=0;
    for(int i=1;i<n;i++) {
        int u,v;
        scanf("%d%d",&u,&v);
        add_edge(u,v);
        add_edge(v,u);
    }
    int cnt(0);
    int qb(1),qe(1);
    fa[1]=0,que[1]=1;
    while(qb<=qe) {
        const int u(que[qb++]);
        bfn[u]=++cnt;
        for(int i=last[u];i;i=e[i].next) {
            const int v(e[i].v);
            if(v==fa[u]) {
                continue;
            }
            fa[v]=u,que[++qe]=v;
        }
    }
    for(int i=n;i>=1;i--) {
        const int u(que[i]);
        lp[u][0]=rp[u][0]=bfn[u];
        for(int j=1;j<=k;j++) {
            lp[u][j]=n+1,rp[u][j]=0;
        }
        for(int j=last[u];j;j=e[j].next) {
            const int v(e[j].v);
            if(v==fa[u]) {
                continue;
            }
            for(int l=1;l<=k;l++) {
                lp[u][l]=std::min(lp[u][l],lp[v][l-1]);
                rp[u][l]=std::max(rp[u][l],rp[v][l-1]);
            }
        }
    }
    for(int i=1;i<=q;i++) {
        scanf("%d%d",&qq[i].l,&qq[i].r);
        qq[i].id=i;
    }
    std::sort(qq+1,qq+q+1,[](const qry &x,const qry &y)->bool {
        return x.r<y.r;
    });
    BIT::clear(n);
    ODT::MAP::emplace(1,{n,0});
    for(int i=1,j=1;i<=n;i++) {
        for(int j=0,u=i;j<=k;j++,u=fa[u]) {
            if(u==0) {
                for(int l=k-j-1;l>=0;l--) {
                    ODT::cover(lp[1][l],rp[1][l],i);
                }
                break;
            }
            ODT::cover(bfn[u],bfn[u],i);
            ODT::cover(lp[u][k-j],rp[u][k-j],i);
            if(j<k) {
                ODT::cover(lp[u][k-j-1],rp[u][k-j-1],i);
            }
        }
        while(j<=q&&qq[j].r==i) {
            ans[qq[j].id]=BIT::query(n,qq[j].l);
            ++j;
        }
    }
    ODT::clear(n);
    for(int i=1;i<=q;i++) {
        printf("%d\n",ans[i]);
    }
}
int main() {
    int t;
    scanf("%d",&t);
    while(t--) {
        solve();
    }
    return 0;
}