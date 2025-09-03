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
const int maxk=6;
const int B=1000;

int n,m,l=5;
struct mat{
    int e[maxk][maxk];
    mat(){memset(e,0,sizeof(e));}
}bas,val[4],pw0[B],pw1[B],pw2[B],pw3[B],pw4[B],pw5[B];
mat one(){
    mat res;
    for(int i=0;i<=l;i++)res.e[i][i]=1;
    return res;
}
mat operator*(mat u,mat v){
    mat res;
    for(int i=0;i<=l;i++){
        for(int k=0;k<=l;k++){
            for(int j=0;j<=l;j++)(res.e[i][j]+=u.e[i][k]*v.e[k][j])%=mod;
        }
    }
    return res;
}
struct vec{
    int e[maxk];
    vec(){memset(e,0,sizeof(e));}
};
vec operator*(mat u,vec v){
    vec res;
    for(int i=0;i<=l;i++){
        for(int j=0;j<=l;j++)(res.e[i]+=u.e[i][j]*v.e[j])%=mod;
    }
    return res;
}
void mul(vec &u,int n){
	if(n==1e18)u=bas*u,n--;
    u=pw0[n%B]*u,n/=B;
    u=pw1[n%B]*u,n/=B;
    u=pw2[n%B]*u,n/=B;
    u=pw3[n%B]*u,n/=B;
    u=pw4[n%B]*u,n/=B;
    u=pw5[n%B]*u,n/=B;
}
int x[1010],op[1010];
void work(){
    n=read();m=read();
    for(int i=1;i<=m;i++)x[i]=read(),op[i]=read();
    for(int i=1;i<=m;i++)if(op[i]>3){puts("0");return ;}
    vec ans;ans.e[0]=1;
    int lst=0;
    for(int i=1;i<=m;i++){
        mul(ans,x[i]-lst-1);
        // for(int j=0;j<=l;j++)cout<<ans.e[j]<<" ";cout<<"\n";
        ans=val[op[i]]*ans;
        lst=x[i];
    }
    mul(ans,n-lst);
    printf("%lld\n",ans.e[0]);
}

int T;
signed main(){
    // freopen(".in","r",stdin);
    // freopen(".out","w",stdout);
    
    bas.e[0][0]=val[2].e[0][0]=1;
    bas.e[0][3]=val[1].e[0][3]=1;
    bas.e[1][0]=val[1].e[1][0]=1;
    bas.e[2][1]=val[2].e[2][1]=1;
    bas.e[2][2]=val[1].e[2][2]=1;
    bas.e[3][1]=val[3].e[3][1]=1;
    bas.e[3][2]=val[2].e[3][2]=1;
    bas.e[3][5]=val[1].e[3][5]=1;
    bas.e[4][1]=val[1].e[4][1]=1;
    bas.e[5][4]=val[2].e[5][4]=1;
    
    pw0[0]=one(),pw0[1]=bas;for(int i=2;i<B;i++)pw0[i]=pw0[i-1]*pw0[1];
    pw1[0]=one(),pw1[1]=pw0[B-1]*pw0[1];for(int i=2;i<B;i++)pw1[i]=pw1[i-1]*pw1[1];
    pw2[0]=one(),pw2[1]=pw1[B-1]*pw1[1];for(int i=2;i<B;i++)pw2[i]=pw2[i-1]*pw2[1];
    pw3[0]=one(),pw3[1]=pw2[B-1]*pw2[1];for(int i=2;i<B;i++)pw3[i]=pw3[i-1]*pw3[1];
    pw4[0]=one(),pw4[1]=pw3[B-1]*pw3[1];for(int i=2;i<B;i++)pw4[i]=pw4[i-1]*pw4[1];
    pw5[0]=one(),pw5[1]=pw4[B-1]*pw4[1];for(int i=2;i<B;i++)pw5[i]=pw5[i-1]*pw5[1];

    T=read();
    while(T--)work();
}