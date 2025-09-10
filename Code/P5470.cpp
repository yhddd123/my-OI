#include<bits/stdc++.h>
#include <cstdio>
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

int n,m,k,ans;
int a[maxn],b[maxn];
bool visa[maxn],visb[maxn];
priority_queue<pii> qa,qa1,qb,qb1,q;
void upda(int p){
    visa[p]=1;if(!visb[p])qb1.push({b[p],p});
}
void updb(int p){
    visb[p]=1;if(!visa[p])qa1.push({a[p],p});
}
void work(){
    n=read();m=read();k=m-read();ans=0;
    for(int i=1;i<=n;i++)a[i]=read();
    for(int i=1;i<=n;i++)b[i]=read();
    for(int i=1;i<=n;i++)visa[i]=visb[i]=0;
    while(!q.empty())q.pop();
    while(!qa.empty())qa.pop();
    while(!qb.empty())qb.pop();
    while(!qa1.empty())qa1.pop();
    while(!qb1.empty())qb1.pop();
    for(int i=1;i<=n;i++){
        qa.push({a[i],i}),qb.push({b[i],i}),q.push({a[i]+b[i],i});
    }
    for(int i=1;i<=m;i++){
        while(q.size()&&(visa[q.top().se]||visb[q.top().se]))q.pop();
        while(qa.size()&&visa[qa.top().se])qa.pop();
        while(qb.size()&&visb[qb.top().se])qb.pop();
        while(qa1.size()&&visa[qa1.top().se])qa1.pop();
        while(qb1.size()&&visb[qb1.top().se])qb1.pop();
        pii mx={0,0};
        if(q.size())mx=max(mx,{q.top().fi,5});
        if(k&&qa.size()&&qb.size())mx=max(mx,{qa.top().fi+qb.top().fi,1});
        if(qa1.size()&&qb1.size())mx=max(mx,{qa1.top().fi+qb1.top().fi,4});
        if(qa1.size()&&qb.size())mx=max(mx,{qa1.top().fi+qb.top().fi,3});
        if(qa.size()&&qb1.size())mx=max(mx,{qa.top().fi+qb1.top().fi,2});
        ans+=mx.fi;
        if(mx.se==5){
            int u=q.top().se,v=u;q.pop();
            upda(u),updb(v);
        }
        else if(mx.se==1){
            int u=qa.top().se,v=qb.top().se;qa.pop(),qb.pop();k--;
            upda(u),updb(v);
        }
        else if(mx.se==4){
            int u=qa1.top().se,v=qb1.top().se;qa1.pop(),qb1.pop();k++;
            upda(u),updb(v);
        }
        else if(mx.se==3){
            int u=qa1.top().se,v=qb.top().se;qa1.pop(),qb.pop();
            upda(u),updb(v);
        }
        else if(mx.se==2){
            int u=qa.top().se,v=qb1.top().se;qa.pop(),qb1.pop();
            upda(u),updb(v);
        }
        else assert(0);
    }
    printf("%lld\n",ans);
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