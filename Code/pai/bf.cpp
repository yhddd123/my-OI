#include<bits/stdc++.h>
using namespace std;
namespace AfterTheRainStops{//雨停酱可爱捏~ 最喜欢雨停姐姐了！！！
const int mod=998244353;
int sum(int x,int y){return mod-x>y?x+y:y-(mod-x);}
int dif(int x,int y){return x<y?mod-(y-x):x-y;}
int pro(int x,int y){return 1ll*x*y%mod;}
void fmt(int f[1<<20][21],int n,int op){
    for(int i=0;i<n;++i)
        for(int s=0;s<(1<<n);++s)
            if((s>>i)&1)
                if(op){
                    for(int j=0;j<=n;++j)
                        f[s][j]=dif(f[s][j],f[s^(1<<i)][j]);
                }else{
                    for(int j=0;j<=n;++j)
                        f[s][j]=sum(f[s][j],f[s^(1<<i)][j]);
                }
}
int f[1<<20][21],g[1<<20][21],tmp1[21],tmp2[21];
void main(){
    int n;
    scanf("%d",&n);
    for(int i=0;i<(1<<n);++i)scanf("%d",&f[i][__builtin_popcount(i)]);
    fmt(f,n,0);
    for(int i=0;i<(1<<n);++i)g[i][0]=1;
    for(int i=0;i<n;++i){
        for(int s=1;s<(1<<n);++s)
            if((s&-s)==(1<<i)){
                memcpy(tmp1,g[s],sizeof(tmp1)),memset(g[s],0,sizeof(g[s]));
                for(int j=0;j<=n;++j)tmp2[j]=dif(f[s][j],f[s^(1<<i)][j]);
                tmp2[0]=sum(tmp2[0],1);
                for(int x=0;x<=n;++x)
                    for(int y=0;x+y<=n;++y)
                        g[s][x+y]=sum(g[s][x+y],pro(tmp1[x],tmp2[y]));
            }
    }
    for(int s=1;s<(1<<n);++s)
        for(int i=0;!((s>>i)&1);++i){
            memcpy(tmp1,g[s|(1<<i)],sizeof(tmp1)),memset(g[s|(1<<i)],0,sizeof(g[s|(1<<i)]));
            for(int x=0;x<=n;++x)
                for(int y=0;x+y<=n;++y)
                    g[s|(1<<i)][x+y]=sum(g[s|(1<<i)][x+y],pro(tmp1[x],g[s][y]));
        }
    fmt(g,n,1);
    for(int i=0;i<(1<<n);++i)printf("%d ",g[i][__builtin_popcount(i)]);
}
}
int main(){
    AfterTheRainStops::main();
    return 0;
}
