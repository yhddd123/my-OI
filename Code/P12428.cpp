#include<bits/stdc++.h>

namespace my{
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
#define mkp make_pair
using namespace std;
const int maxn=510;

int A[maxn],B[maxn];
int n;
map<vector<int>,vector<pii>> mp;
vector<pii> ask(int u,int v,int w){
    vector<int> a={u,v,w};
    sort(a.begin(),a.end());
    if(mp.find(a)!=mp.end())return mp[a];
    cout<<"? "<<u<<" "<<v<<" "<<w<<endl;
    vector<pii> res;
    int x;cin>>x;
    for(int i=1;i<=x;i++){
        int u,v;cin>>u>>v;
        res.pb({u,v});
        res.pb({v,u});
    }
    return mp[a]=res;
    // int val[3];
    // val[0]=min(abs(A[u]-A[v]),n-abs(A[u]-A[v]));
    // val[1]=min(abs(A[u]-A[w]),n-abs(A[u]-A[w]));
    // val[2]=min(abs(A[v]-A[w]),n-abs(A[v]-A[w]));
    // int mn=min({val[0],val[1],val[2]});
    // if(mn==val[0])res.pb({u,v}),res.pb({v,u});
    // if(mn==val[1])res.pb({u,w}),res.pb({w,u});
    // if(mn==val[2])res.pb({v,w}),res.pb({w,v});
    // return res;
}
namespace sub1{
    bool vis[maxn];
    void sovle(){
        vector<int> a;a.pb(0);
        for(int i=1;i<n;i++)vis[i]=0;
        for(int i=1;i<n;i++){
            bool fl=1;
            for(int j=1;j<n;j++)if(i!=j){
                vector<pii> res=ask(0,i,j);
                if(find(res.begin(),res.end(),mkp(0, i))==res.end()){fl=0;break;}
            }
            if(fl){vis[i]=1,a.pb(i);break;}
        }
        for(int i=2;i<n;i++){
            for(int j=1;j<n;j++)if(!vis[j]){
                vector<pii> res=ask(a[i-2],a[i-1],j);
                if(res.size()>=4&&find(res.begin(),res.end(),mkp(a[i-1],j))!=res.end()){vis[j]=1,a.pb(j);break;}
            }
        }
        cout<<"! ";for(int v:a)cout<<v<<" ";cout<<endl;
    }
}
void work(){
    cin>>n;
    // for(int i=0;i<n;i++)cin>>B[i],A[B[i]]=i;
    return sub1::sovle();
}
}

int T,k;
signed main(){
    // freopen("A.in", "r", stdin);
    std::cin>>T>>k;
    while(T--)my::work();
}