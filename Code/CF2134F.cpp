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
const int maxn=810;
const int inf=1e9;

int a,b,c,d;
int f[maxn][maxn],g[maxn][maxn],ans[maxn];
inline int ksm(int a,int b=mod-2){
    int ans=1;
    while(b){
        if(b&1)ans=ans*a%mod;
        a=a*a%mod;
        b>>=1;
    }
    return ans;
}
int fac[maxn],inv[maxn];
int C(int m,int n){
    if(m<0||n<0||m<n)return 0;
    return fac[m]*inv[n]%mod*inv[m-n]%mod;
}
void work(){
    a=read();b=read();c=read();d=read();
    for(int i=1;i<=a+c;i++){
        for(int j=0;j<a+c;j++)f[i][j]=0;
    }
    for(int i=1,j=1;i<=a&&j<=c;i++,j++){
        for(int k=0;k<=a+c-i-j;k++){
            for(int l=0;l<=i+j-1;l++){
                (f[k+l+1][i+j-1-l]+=2*C(a-1,i-1)*C(c-1,j-1)%mod*C(a+c-i-j,k)%mod*C(i+j-1,l))%=mod;
            }
        }
    }
    for(int i=1,j=2;i<=a&&j<=c;i++,j++){
        for(int k=0;k<=a+c-i-j;k++){
            for(int l=0;l<=i+j-1;l++){
                (f[k+l+1][i+j-1-l]+=C(a-1,i-1)*C(c-1,j-1)%mod*C(a+c-i-j,k)%mod*C(i+j-1,l))%=mod;
            }
        }
    }
    for(int i=2,j=1;i<=a&&j<=c;i++,j++){
        for(int k=0;k<=a+c-i-j;k++){
            for(int l=0;l<=i+j-1;l++){
                (f[k+l+1][i+j-1-l]+=C(a-1,i-1)*C(c-1,j-1)%mod*C(a+c-i-j,k)%mod*C(i+j-1,l))%=mod;
            }
        }
    }
    for(int i=1;i<=b+d;i++){
        for(int j=0;j<b+d;j++)g[i][j]=0;
    }
    for(int i=1,j=1;i<=b&&j<=d;i++,j++){
        for(int k=0;k<=b+d-i-j;k++){
            for(int l=0;l<=i+j-1;l++){
                (g[k+l+1][i+j-1-l]+=2*C(b-1,i-1)*C(d-1,j-1)%mod*C(b+d-i-j,k)%mod*C(i+j-1,l))%=mod;
            }
        }
    }
    for(int i=1,j=2;i<=b&&j<=d;i++,j++){
        for(int k=0;k<=b+d-i-j;k++){
            for(int l=0;l<=i+j-1;l++){
                (g[k+l+1][i+j-1-l]+=C(b-1,i-1)*C(d-1,j-1)%mod*C(b+d-i-j,k)%mod*C(i+j-1,l))%=mod;
            }
        }
    }
    for(int i=2,j=1;i<=b&&j<=d;i++,j++){
        for(int k=0;k<=b+d-i-j;k++){
            for(int l=0;l<=i+j-1;l++){
                (g[k+l+1][i+j-1-l]+=C(b-1,i-1)*C(d-1,j-1)%mod*C(b+d-i-j,k)%mod*C(i+j-1,l))%=mod;
            }
        }
    }
    for(int i=0;i<=2*(a+b+c+d);i++)ans[i]=0;
    for(int i=1,j=1;i<=a+c&&j<=b+d;i++,j++){
        for(int k=0;k<a+c;k++){
            for(int l=0;l<b+d;l++)(ans[2*(k+l)+i+j-1]+=2*f[i][k]*g[j][l])%=mod;
        }
    }
    for(int i=1,j=2;i<=a+c&&j<=b+d;i++,j++){
        for(int k=0;k<a+c;k++){
            for(int l=0;l<b+d;l++)(ans[2*(k+l)+i+j-1]+=f[i][k]*g[j][l])%=mod;
        }
    }
    for(int i=2,j=1;i<=a+c&&j<=b+d;i++,j++){
        for(int k=0;k<a+c;k++){
            for(int l=0;l<b+d;l++)(ans[2*(k+l)+i+j-1]+=f[i][k]*g[j][l])%=mod;
        }
    }
    for(int i=0;i<=2*(a+b+c+d-1);i++)printf("%lld ",ans[i]);puts("");
}

int T;
signed main(){
    // freopen("A.in","r",stdin);
    // freopen("A.out","w",stdout);

    int n=800;
    fac[0]=1;for(int i=1;i<=n;i++)fac[i]=fac[i-1]*i%mod;
    inv[n]=ksm(fac[n]);for(int i=n-1;~i;i--)inv[i]=inv[i+1]*(i+1)%mod;

    T=read();
    while(T--)work();
}