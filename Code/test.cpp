#include<bits/stdc++.h>
using namespace std;

#define rep(i,l,r) for(int i=(l);i<=(r);++i)
#define per(i,l,r) for(int i=(r);i>=(l);--i)
#define pr pair<int,int>
#define fi first
#define se second
#define pb push_back
#define all(x) (x).begin(),(x).end()
#define sz(x) (int)(x).size()
#define bg(x) (x).begin()
#define ed(x) (x).end()

#define N 102508
#define int long long

int n,m,a[N][2],rt=1;

struct node{
    int f00,f01,f10,f11;
};

map<int,node>e[N];

inline void add(int u,int v,int f00,int f01,int f10,int f11){
    if(e[u].count(v)){
        node &re=e[u][v];

        re.f00+=f00;
        re.f01+=f01;
        re.f10+=f10;
        re.f11+=f11;

        e[v][u]=re;
        swap(e[v][u].f01,e[v][u].f10);

        return;
    }

    e[u][v]={f00,f01,f10,f11};
    e[v][u]={f00,f10,f01,f11};
}

signed main(){
    // freopen(".in","r",stdin);
    // freopen(".out","w",stdout);
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);

    cin>>n>>m;

    rep(i,1,n){
        a[i][0]=0;
        a[i][1]=1;
    }

    rep(i,1,m){
        int u,v;
        cin>>u>>v;

        add(u,v,0,0,0,-1e5);
    }

    queue<int>q;

    rep(i,1,n){
        if(sz(e[i])<3){
            q.push(i);
        }
    }

    while(!q.empty()){
        int u=q.front();
        q.pop();

        if(sz(e[u])==1){
            auto tmp=*e[u].begin();
            int v=tmp.fi;
            node re=tmp.se;

            a[v][1]+=max(a[u][0]+re.f01,a[u][1]+re.f11);
            a[v][0]+=max(a[u][0]+re.f00,a[u][1]+re.f10);

            rt=v;
        }

        if(sz(e[u])==2){
            auto tx=*e[u].begin(),ty=*next(e[u].begin());
            int x=tx.fi,y=ty.fi;
            node rx=tx.se,ry=ty.se;

            int f00=0,f01=0,f10=0,f11=0;

            f00=max(rx.f10+a[u][1]+ry.f10,rx.f00+a[u][0]+ry.f00);
            f01=max(rx.f10+a[u][1]+ry.f11,rx.f00+a[u][0]+ry.f01);
            f10=max(rx.f11+a[u][1]+ry.f10,rx.f01+a[u][0]+ry.f00);
            f11=max(rx.f11+a[u][1]+ry.f11,rx.f01+a[u][0]+ry.f01);

            add(x,y,f00,f01,f10,f11);
        }

        for(auto v:e[u]){
            int x=v.fi;
            e[x].erase(u);

            if(sz(e[x])<3){
                q.push(x);
            }
        }

        e[u].clear();
    }

    cout<<max(a[rt][0],a[rt][1]);

    return 0;
}
