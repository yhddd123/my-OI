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
const int maxn=50010;
const int inf=1e18;
bool mbe;

int n,ans;
struct node{
    int a[maxn];
    int pmn[maxn],pse[maxn],smn[maxn],sse[maxn];
    int v1,v2,v3;
    void init(){
        pmn[1]=pse[1]=inf;
        for(int i=2;i<n;i++){
        	pmn[i]=pmn[i-1],pse[i]=pse[i-1];
            if(a[i]<pmn[i])pse[i]=pmn[i],pmn[i]=a[i];
            else if(a[i]<pse[i])pse[i]=a[i];
        }
        smn[n]=sse[n]=inf;
        for(int i=n-1;i>=2;i--){
        	smn[i]=smn[i+1],sse[i]=sse[i+1];
            if(a[i]<smn[i])sse[i]=smn[i],smn[i]=a[i];
            else if(a[i]<sse[i])sse[i]=a[i];
        }
        v1=pmn[n-1],v2=pmn[n-1]+pse[n-1];
        v3=inf;for(int i=2,fl1=0,fl2=0;i<n;i++){
            if(!fl1&&a[i]==pmn[n-1])fl1=1;
            else if(!fl2&&a[i]==pse[n-1])fl2=1;
            else v3=min(v3,a[i]);
        }
        v3+=pmn[n-1]+pse[n-1];
    }
}a1,a2,a3,a4;
void work(){
    n=read();ans=inf;
    for(int i=2;i<n;i++)a1.a[i]=read();
    for(int i=2;i<n;i++)a2.a[i]=read();
    for(int i=2;i<n;i++)a3.a[i]=read();
    for(int i=2;i<n;i++)a4.a[i]=read();
    a1.init(),a2.init(),a3.init(),a4.init();
    ans=min(ans,a1.v2+a2.v2+a3.v3+a4.v3);
    ans=min(ans,a3.v2+a4.v2+a1.v3+a2.v3);
    for(int i=2;i+1<n;i++){
        ans=min(ans,a1.pmn[i]+a1.smn[i+1]+a2.pmn[i]+a2.smn[i+1]+a3.v2+a4.v2);
        ans=min(ans,a1.pmn[i-1]+a1.a[i]+a2.a[i]+a2.smn[i+1]+a3.v2+a4.v2);
        ans=min(ans,a1.smn[i+1]+a1.a[i]+a2.a[i]+a2.pmn[i-1]+a3.v2+a4.v2);
        ans=min(ans,a3.pmn[i]+a3.smn[i+1]+a4.pmn[i]+a4.smn[i+1]+a1.v2+a2.v2);
        ans=min(ans,a3.pmn[i-1]+a3.a[i]+a4.a[i]+a4.smn[i+1]+a1.v2+a2.v2);
        ans=min(ans,a3.smn[i+1]+a3.a[i]+a4.a[i]+a4.pmn[i-1]+a1.v2+a2.v2);
    }
    for(int i=3;i+2<n;i++){
    	ans=min(ans,a1.pmn[i-1]+a1.a[i]+a2.a[i+1]+a2.smn[i+2]+a3.v2+a4.v2);
    	ans=min(ans,a2.pmn[i-1]+a2.a[i]+a1.a[i+1]+a1.smn[i+2]+a3.v2+a4.v2);
    	ans=min(ans,a3.pmn[i-1]+a3.a[i]+a4.a[i+1]+a4.smn[i+2]+a1.v2+a2.v2);
    	ans=min(ans,a4.pmn[i-1]+a4.a[i]+a3.a[i+1]+a3.smn[i+2]+a1.v2+a2.v2);
    }
    int v1=inf,v2=inf;
    for(int i=3;i+2<n;i++){
        v1=min(v1,a1.pmn[i]+a1.pse[i]+a2.smn[i+1]+a2.sse[i+1]);
        v2=min(v2,a3.pmn[i]+a3.pse[i]+a4.smn[i+1]+a4.sse[i+1]);
    }
    ans=min(ans,v1+v2);
    v1=inf,v2=inf;
    for(int i=3;i+2<n;i++){
        v1=min(v1,a2.pmn[i]+a2.pse[i]+a1.smn[i+1]+a1.sse[i+1]);
        v2=min(v2,a4.pmn[i]+a4.pse[i]+a3.smn[i+1]+a3.sse[i+1]);
    }
    ans=min(ans,v1+v2);
    printf("%lld\n",ans);
}

bool med;
int T;
signed main(){
    // freopen(".in","r",stdin);
    // freopen(".out","w",stdout);
    
    // cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
    
    T=read();
    while(T--)work();
}