#include<bits/stdc++.h>
#define int long long
// #define mod 998244353ll
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

int n,m,mod;
struct mat{
    int e[5][5];
    mat(){memset(e,0,sizeof(e));}
    mat operator*(const mat &b)const{
        mat c;
        for(int i=0;i<m;i++){
            for(int k=0;k<m;k++){
                for(int j=0;j<m;j++)(c.e[i][j]+=e[i][k]*b.e[k][j])%=mod;
            }
        }
        return c;
    }
}a,b,c;
mat one(){
    mat res;
    for(int i=0;i<m;i++)res.e[i][i]=1;
    return res;
}
mat f[maxn],g[maxn];int p,q;
void work(){
    for(int i=0;i<m;i++){
        for(int j=0;j<m;j++)a.e[i][j]=read();
    }
    for(int i=0;i<m;i++){
        for(int j=0;j<m;j++)b.e[i][j]=read();
    }
    p=q=0;c=mat();
    g[0]=one();f[++p]=c=a;
    for(int i=1,j=0;i<=n;i++){
        int pos=read();
        while(j<pos){
            if(q)q--;
            else{
                for(int k=1;k<=p;k++)g[p-k+1]=f[k];q=p,p=0;c=one();
                for(int k=2;k<=q;k++)g[k]=g[k]*g[k-1];
                q--;
            }
            j++;
        }
        f[++p]=g[q]*c*b;c=c*f[p];
        // cout<<i<<" "<<p<<" "<<q<<"\n";
        // for(int j=0;j<m;j++){
        //     for(int k=0;k<m;k++)cout<<f[p].e[j][k]<<" ";cout<<endl;
        // }
    }
    for(int i=0;i<m;i++){
        for(int j=0;j<m;j++)printf("%lld ",f[p].e[i][j]);puts("");
    }
}

int T;
signed main(){
    // freopen("A.in","r",stdin);
    // freopen(".out","w",stdout);
    
    T=1;
    while(~scanf("%lld%lld%lld",&n,&m,&mod))work();
}