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

int n;
vector<int> e[1<<7];
vector<int> g[1<<7];
int tim=0;
bool ask(int p){
    if(e[p].size())return 0;
    cout<<"? "<<p<<endl;int k=read();
    if(!k)exit(0);
    for(int i=0;i<k;i++)e[p].pb(read());
    return k==2;
    // e[p]=g[p];++tim;
    // assert(tim<=16);
    // return g[p].size()==2;
}
vector<int> id;
int dfs(int u){
    if(ask(u))return u;
    id.pb(u);
    for(int v:e[u])if(!e[v].size())return dfs(v);
    return 0;
}
// int idx[1<<7];
// mt19937 rnd(time(0));
void work(){
    n=read();tim=0;
    if(!n)exit(0);
    // for(int i=1;i<(1<<n);i++)idx[i]=i;
    // shuffle(idx+1,idx+(1<<n),rnd);
    // cout<<idx[1]<<"\n";
    // for(int i=1;i<(1<<n);i++)g[i].clear();
    // for(int i=2;i<(1<<n);i++)g[idx[i>>1]].pb(idx[i]),g[idx[i]].pb(idx[i>>1]);
    // for(int i=2;i<(1<<n);i++)cout<<idx[i>>1]<<" "<<idx[i]<<"\n";
    for(int i=1;i<(1<<n);i++)e[i].clear();
    int p=1,d=n;if(ask(p)){cout<<"! "<<p<<endl;return ;}
    if(e[p].size()==3){
        vector<int> id1,id2;
        for(int v:e[p]){
            id.clear();
            int pp=dfs(v);
            if(pp){cout<<"! "<<pp<<endl;return ;}
            if(!id1.size())id1=id;
            else{
                id2=id;
                if(id1.size()<id2.size())swap(id1,id2);
                if(id1.size()!=id2.size())p=id1[(id1.size()+id2.size())/2-id2.size()-1];
                d=n-(id1.size()+id2.size())/2;
                break;
            }
        }
    }
    while(d>4){
        id.clear();
        int pp=dfs(p);
        if(pp){cout<<"! "<<pp<<endl;return ;}
        // cout<<d<<" "<<p<<" "<<id.size()<<endl;
        if(id.size()!=n-d+1)p=id[(n-d+id.size())/2-(n-d)];
        d=n-(n-d+id.size())/2;
    }
    for(int u:e[p])if(!e[u].size()){
        if(ask(u)){cout<<"! "<<u<<endl;return ;}
        p=u;
        break;
    }
    vector<int> id;
    for(int u:e[p])if(!e[u].size()){
        if(ask(u)){cout<<"! "<<u<<endl;return ;}
        for(int v:e[u])if(!e[v].size())id.pb(v);
    }
    for(int i=0;i+1<id.size();i++)if(ask(id[i])){cout<<"! "<<id[i]<<endl;return ;}
    cout<<"! "<<id.back()<<endl;
}

bool med;
int T;
signed main(){
    // freopen("A.in","r",stdin);
    // freopen("A.out","w",stdout);
    
    // cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
    
    T=read();
    while(T--)work();
}