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

int n,a[maxn];
vector<int> id[maxn];
int f[maxn];
int fd(int x){
    if(f[x]==x)return x;
    return f[x]=fd(f[x]);
}
char s[maxn],t[maxn];
void work(){
    n=read();
    for(int i=1;i<=n;i++)f[i]=i;
    vector<pii> que;
    for(int i=1;i+1<=n;i+=2)que.pb({i,i+1});
    if(que.size()){
        cout<<"Q "<<que.size()<<" ";for(pii p:que)cout<<p.fi<<" "<<p.se<<" ";cout<<endl;
        scanf("%s",s);
        for(int i=0;i<que.size();i++)if(s[i]=='1')f[fd(que[i].fi)]=fd(que[i].se);
        que.clear();
    }
    for(int i=2;i+1<=n;i+=2)que.pb({i,i+1});
    if(que.size()){
        cout<<"Q "<<que.size()<<" ";for(pii p:que)cout<<p.fi<<" "<<p.se<<" ";cout<<endl;
        scanf("%s",s);
        for(int i=0;i<que.size();i++)if(s[i]=='1')f[fd(que[i].fi)]=fd(que[i].se);
        que.clear();
    }
    vector<int> id;
    for(int i=1;i<=n;i++)if(f[i]==i)id.pb(i);id.pb(0);
    vector<bool> res(id.size());
    for(int i=0;i<id.size()-1;i+=4){
        if(i+2<id.size()-1)que.push_back({i,i+2});
        if(i+3<id.size()-1)que.push_back({i+1,i+3});
    }
    if(que.size()){
        cout<<"Q "<<que.size()<<" ";for(pii p:que)cout<<id[p.fi]<<" "<<id[p.se]<<" ";cout<<endl;
        scanf("%s",s);
        for(int i=0;i<que.size();i++)if(s[i]=='1')res[que[i].fi]=1;
        que.clear();
    }
    for(int i=2;i<id.size()-1;i+=4){
        if(i+2<id.size()-1)que.push_back({i,i+2});
        if(i+3<id.size()-1)que.push_back({i+1,i+3});
    }
    if(que.size()){
        cout<<"Q "<<que.size()<<" ";for(pii p:que)cout<<id[p.fi]<<" "<<id[p.se]<<" ";cout<<endl;
        scanf("%s",s);
        for(int i=0;i<que.size();i++)if(s[i]=='1')res[que[i].fi]=1;
        que.clear();
    }
    a[id[0]]=1,a[id[1]]=2;
    for(int i=2;i+1<id.size();i++){
        if(res[i-2])a[id[i]]=a[id[i-2]];
        else a[id[i]]=1^2^3^a[id[i-2]]^a[id[i-1]];
    }
    for(int i=1;i<=n;i++)a[i]=a[fd(i)];
    vector<int> pos[3];
    for(int i=1;i<=n;i++)pos[a[i]-1].pb(i);
    cout<<"A "<<pos[0].size()<<" "<<pos[1].size()<<" "<<pos[2].size()<<endl;
    for(int u:pos[0])cout<<u<<" ";cout<<endl;
    for(int u:pos[1])cout<<u<<" ";cout<<endl;
    for(int u:pos[2])cout<<u<<" ";cout<<endl;
}

bool med;
int T;
signed main(){
    // freopen(".in","r",stdin);
    // freopen(".out","w",stdout);

    ios::sync_with_stdio(false);cin.tie(0),cout.tie(0);
    
    // cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
    
    T=read();
    while(T--)work();
}