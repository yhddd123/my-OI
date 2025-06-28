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

int n,ans;
vector<pii> a;
pii operator-(pii a,pii b){return {a.fi-b.fi,a.se-b.se};}
int cross(pii a,pii b){return a.fi*b.se-a.se*b.fi;}
vector<int> tubao(vector<pii> a){
    if(a.size()==1) return {0};
    if(a.size()==2)return {0,1};
    vector<int> id;
    sort(a.begin(),a.end());
    for(int i=0;i<a.size();i++){
        while(id.size()>=2&&cross(a[id.back()]-a[id[id.size()-2]],a[i]-a[id.back()])>=0)id.pop_back();
        id.pb(i);
    }
    int m=id.size();
    for(int i=a.size()-2;i>=0;i--){
        while(id.size()>=m+1&&cross(a[id.back()]-a[id[id.size()-2]],a[i]-a[id.back()])>=0)id.pop_back();
        id.pb(i);
    }
    id.pop_back();
    return id;
}
void work(){
    n=read();
    if(n==1){puts("Bara");return ;}
    if(n==2){puts("Alenka");return ;}
    for(int i=1;i<=n;i++)a.pb({read(),read()});
    vector<int> id=tubao(a);
    ans=id.size()+id.size()-3+(n-id.size())*3;
    // cout<<id.size()<<" "<<ans<<endl;
    if(ans&1)puts("Alenka");
    else puts("Bara");
}

int T;
signed main(){
    // freopen("P10876.in","r",stdin);
    // freopen(".out","w",stdout);
    
    T=1;
    while(T--)work();
}