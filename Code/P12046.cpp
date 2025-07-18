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
const int maxn=200010;
const int inf=1e9;

int n,k,t;
struct mat{
    int e[3][3];
    mat(){memset(e,0,sizeof(e));}
    mat operator*(const mat&tmp)const{
        mat res;
        for(int i=0;i<=2;i++){
            for(int k=0;k<=2;k++){
                for(int j=0;j<=2;j++)(res.e[i][j]+=e[i][k]*tmp.e[k][j])%=mod;
            }
        }
        return res;
    }
}a,b;
mat one(){
    mat res;
    for(int i=0;i<=2;i++)res.e[i][i]=1;
    return res;
}
mat ksm(mat a,int b){
    mat ans=one();
    while(b){
        if(b&1)ans=ans*a;
        a=a*a;
        b>>=1;
    }
    return ans;
}
int f[maxn];
void work(){
    n=read();k=read();t=n/k;k%=mod;
    // for(int i=1;i<=n;i++){
    //     f[i]=i*i*k;
    //     for(int j=1;j<i;j++)f[i]+=(i-j)*k*f[j];
    // }
    // for(int i=1;i<=t;i++)cout<<f[i]<<" ";cout<<"\n";
    // f[1]=k,f[2]=4*k+k*k;
    // for(int i=3;i<=n/k;i++){
    //     f[i]=(2*k+(k+2)*f[i-1]-f[i-2])%mod;
    // }
    // for(int i=1;i<=t;i++)cout<<f[i]<<" ";cout<<"\n";
    if(t==1){printf("%lld\n",k);return ;}
    int f1=k,f2=(4*k+k*k)%mod;
    a.e[0][0]=(k+2)%mod,a.e[0][1]=1;
    a.e[1][0]=mod-1;
    a.e[2][0]=2*k%mod,a.e[2][2]=1;
    a=ksm(a,t-2);
    b.e[0][0]=f2,b.e[0][1]=f1,b.e[0][2]=1;
    b=b*a;
    printf("%lld\n",b.e[0][0]);
}

int T;
signed main(){
    // freopen("A.in","r",stdin);
    // freopen(".out","w",stdout);
    
    T=1;
    while(T--)work();
}