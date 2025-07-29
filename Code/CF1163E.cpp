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

int n,a[maxn],x;
int b[20],c[20];
void insert(int x,int s=0){
    for(int i=19;~i;i--)if(x&(1<<i)){
        if(!b[i]){b[i]=x,c[i]=s;break;}
        x^=b[i],s^=c[i];
    }
}
int ask(int x){
    int s=0;
    for(int i=19;~i;i--)if(x&(1<<i)){
        if(!b[i])return 0;
        x^=b[i],s^=c[i];
    }
    return !s?1:s;
}
int val[1<<20];
int st[1<<20],tp;
void work(){
    n=read();
    for(int i=1;i<=n;i++)a[i]=read();
    sort(a+1,a+n+1);
    for(int i=1,j=0,k=0;i<20;i++){
        while(j<n&&a[j+1]<(1<<i)){
            j++;
            if(!ask(a[j]))insert(a[j]),++k;
        }
        if(i==k)x=i;
        // cout<<i<<" "<<j<<" "<<k<<"\n";
    }
    for(int i=0;i<20;i++)b[i]=c[i]=0;
    for(int i=1,k=0;i<=n;i++)if(a[i]<(1<<x)){
        if(!ask(a[i])){
            insert(a[i],1<<k),k++;
        }
    }
    for(int s=0;s<(1<<x);s++)val[ask(s)]=s;
    st[++tp]=0;
    for(int i=1;i<=x;i++){
        int lst=tp;
        for(int j=lst;j;j--)st[++tp]=st[j]^(1<<i-1);
    }
    printf("%lld\n",x);
    for(int i=1;i<=tp;i++)printf("%lld ",val[st[i]]);

}

bool med;
int T;
signed main(){
    // freopen("A.in","r",stdin);
    // freopen("A.out","w",stdout);
    
    // cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
    
    T=1;
    while(T--)work();
}