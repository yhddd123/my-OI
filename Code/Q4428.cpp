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
const int maxn=1000010;
const int inf=1e9;
bool mbe;

int n,m,a[maxn];
int pre[maxn],nxt[maxn];
vector<int> pos[maxn];
int sum[2][maxn];
void work(){
    n=read();m=0;
    for(int i=1;i<=n;i++)a[i]=read(),m=max(m,a[i]);
    for(int i=1;i<=n;i++)pre[i]=i-1,nxt[i]=i+1;nxt[0]=1,pre[n+1]=n,nxt[n+1]=n+1;
    for(int i=1;i<=m;i++)pos[i].clear();
    for(int i=1;i<=n;i++)pos[a[i]].pb(i);
    for(int i=1;i<=n;i++)sum[0][i]=sum[0][i-1],sum[1][i]=sum[1][i-1],sum[i&1][i]+=a[i];
    for(int i=1;i<=m;i++){
        int ans=0;
        for(int j=nxt[0],k=0,fl=0;j<=n+1;k=j,j=nxt[j]){
            if(k+1<=j-1){
                ans+=sum[fl^((k+1)&1)][j-1]-sum[fl^((k+1)&1)][k];
                fl^=(j-1-(k+1)+1)&1;
            }
            if(j==n+1)break;
            int d=a[j]/i;
            if(fl)d--,fl=0;
            ans+=d/2*i;
            if(d&1){
            	if(!fl)ans+=i;
            	fl^=1;
            }
            if(a[j]%i){
                if(!fl)ans+=a[j]%i;
                fl^=1;
            }
            // cout<<j<<" "<<fl<<" "<<ans<<"\n";
        }
        printf("%lld\n",ans);
        for(int j:pos[i])nxt[pre[j]]=nxt[j],pre[nxt[j]]=pre[j];
    }
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