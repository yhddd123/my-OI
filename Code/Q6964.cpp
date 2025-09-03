#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x=0,fl=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')fl=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*fl;
}
const int maxn=2100010;
const int inf=1e9;

int n,m;
int st[maxn],tp;
void dfs(int d,int lst,int sum){
    if(d==n){st[++tp]=sum;return ;}
    for(int i=lst;i<m;i++)dfs(d+1,i,(sum+i)%m);
}
void work(){
    n=read();m=read();
    tp=0;dfs(1,0,0);
    for(int i=1;i<=n;i++){
        for(int j=1;j<=tp;j++)printf("%d ",(i%m-st[j]+m)%m+1);puts("");
    }
}

int T;
signed main(){
    // freopen(".in","r",stdin);
    // freopen(".out","w",stdout);
    
    T=read();
    while(T--)work();
}