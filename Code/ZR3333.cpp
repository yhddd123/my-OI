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
const int maxn=2000010;
const int inf=1e9;
bool mbe;

int n,a[maxn];
int pos[maxn];
void work(){
    n=read();
    for(int i=0;i<=2*n;i++)pos[i]=-1;
    pos[0+n]=0;
    for(int i=1,s=0;i<=2*n;i++){
        a[i]=read();
        if(s>0)a[i]=-a[i];
        s+=a[i];
        if(~pos[s+n]){
            printf("%d %d\n",pos[s+n]+1,i);
            for(int j=pos[s+n]+1;j<=i;j++)putchar(a[j]>0?'1':'0');puts("");
            return ;
        }
        pos[s+n]=i;
    }
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