#include<bits/stdc++.h>
#define int long long
#define mod 1000000007ll
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
const int maxn=14;
const int inf=1e9;
bool mbe;

int n;
int a[maxn+2][maxn+2];
char s[maxn+2];
pii f[maxn+2][maxn+2][1<<maxn];
int g[maxn+2][maxn+2][maxn+2][maxn+2];
pii val(int a,int b=1){return {a,a*b%mod};}
pii operator+(pii u,pii v){return {(u.fi+v.fi)%mod,(u.se+v.se)%mod};}
pii operator*(pii u,pii v){return {u.fi*v.fi%mod,(u.fi*v.se+u.se*v.fi)%mod};}
int pw[maxn*maxn];
void work(){
    n=read();
    for(int i=1;i<=n;i++){
        scanf("%s",s);
        for(int j=1;j<=n;j++)a[i][j]=s[j-1]-'0';
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++)a[i][j]+=a[i-1][j]+a[i][j-1]-a[i-1][j-1];
    }
    auto que=[&](int l,int r,int p,int q){
        return a[r][q]+a[l-1][p-1]-a[l-1][q]-a[r][p-1];
    };
    pw[0]=1;for(int i=1;i<=n*n;i++)pw[i]=pw[i-1]*2%mod;
    for(int i=1;i<=n+1;i++){
        for(int s=0;s<(1<<n);s++)f[i][i-1][s]={1,0};
    }
    for(int l=n;l;l--){
        for(int r=l;r<=n;r++){
            for(int i=n;i;i--){
                for(int j=i;j<=n;j++){
                    g[l][r][i][j]=pw[que(l,r,i,j)]-1;
                    for(int a=l;a<=r;a++){
                        for(int b=a;b<=r;b++){
                            for(int c=i;c<=j;c++){
                                for(int d=c;d<=j;d++)if(g[a][b][c][d]){
                                	if(a==l&&b==r&&c==i&&d==j)continue;
                                    (g[l][r][i][j]+=mod-g[a][b][c][d]*f[b+1][r][(1<<c-1)-(1<<i-1)+(1<<j)-(1<<d)].fi%mod)%=mod;
                                }
                            }
                        }
                    }
                    // if(g[l][r][i][j])cout<<l<<" "<<r<<" "<<i<<" "<<j<<" "<<g[l][r][i][j]<<"\n";
                }
            }
            for(int s=0;s<(1<<n);s++){
                f[l][r][s]=f[l+1][r][s];
                for(int p=l;p<=r;p++){
                    for(int a=1;a<=n;a++){
                        for(int b=a;b<=n;b++)if((s&((1<<b)-(1<<a-1)))==((1<<b)-(1<<a-1))&&g[l][p][a][b]){
                        	f[l][r][s]=f[l][r][s]+f[p+1][r][s^((1<<b)-(1<<a-1))]*val(g[l][p][a][b]);
                        	// cout<<l<<" "<<p<<" "<<r<<" "<<a<<" "<<b<<" "<<f[l][r][s].fi<<"\n";
                        }
                    }
                }
                // if(f[l][r][s].se)cout<<l<<" "<<r<<" "<<s<<" "<<f[l][r][s].fi<<" "<<f[l][r][s].se<<"\n";
            }
        }
    }
    printf("%lld\n",f[1][n][(1<<n)-1].se);
}

bool med;
int T;
signed main(){
    // freopen("A.in","r",stdin);
    // freopen(".out","w",stdout);
    
    // cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
    
    T=read();
    while(T--)work();
}