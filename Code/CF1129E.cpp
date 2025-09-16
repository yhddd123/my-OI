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
const int maxn=510;
const int inf=1e9;
bool mbe;

int n,siz[maxn],id[maxn],fa[maxn];
int ask(vector<int> a,vector<int> b,int p){
    if(!a.size()||!b.size())return 0;
    cout<<a.size()<<endl;for(int u:a)cout<<u<<" ";cout<<endl;
    cout<<b.size()<<endl;for(int u:b)cout<<u<<" ";cout<<endl;
    cout<<p<<endl;
    return read();
}
void work(){
    n=read();
    vector<int> que;for(int j=2;j<=n;j++)que.pb(j);
    siz[1]=n;for(int i=2;i<=n;i++)siz[i]=ask({1},que,i);
    for(int i=1;i<=n;i++)id[i]=i;
    sort(id+1,id+n+1,[&](int u,int v){return siz[u]<siz[v];});
    que.clear();
    for(int i=1;i<=n;i++){
        int num=ask({1},que,id[i]);
        while(num--){
            int l=0,r=que.size()-1,res=-1;
            while(l<=r){
                int mid=l+r>>1;
                vector<int> tmp=que;
                tmp.resize(mid+1);
                if(!ask({1},tmp,id[i]))res=mid,l=mid+1;
                else r=mid-1;
            }
            fa[que[res+1]]=id[i];
            que[res+1]=que.back(),que.pop_back();
        }
        que.pb(id[i]);
    }
    cout<<"ANSWER"<<endl;
    for(int i=2;i<=n;i++)cout<<i<<" "<<fa[i]<<endl;
}

bool med;
int T;
signed main(){
    // freopen(".in","r",stdin);
    // freopen(".out","w",stdout);

    ios::sync_with_stdio(false),cin.tie(0);
    
    // cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
    
    T=1;
    while(T--)work();
}