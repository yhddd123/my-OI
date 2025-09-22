#include<bits/stdc++.h>
// #define int long long
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
const int maxn=531441;
const int inf=1e9;
bool mbe;

int n,a[maxn],pw[13];
void work(){
    n=read();
    pw[0]=1;for(int i=1;i<=n;i++)pw[i]=pw[i-1]*3;
    for(int i=0;i<pw[n];i++)a[i]=read();
    for(int i=0;i<n;i++){
        for(int j=0;j<pw[n];j+=pw[i+1]){
            for(int k=j;k<j+pw[i];k++){
                int a0=a[k],a1=a[k+pw[i]],a2=a[k+2*pw[i]];
                int b0=a1-a2,b2=a1-a0,b1=a0+a2-a1;
                a[k]=b0,a[k+pw[i]]=b1,a[k+2*pw[i]]=b2;
            }
        }
    }
    for(int i=0;i<pw[n];i++)printf("%d ",a[i]);
}

bool med;
int T;
signed main(){
    // freopen(".in","r",stdin);
    // freopen(".out","w",stdout);
    
    // cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
    
    T=1;
    while(T--)work();
}