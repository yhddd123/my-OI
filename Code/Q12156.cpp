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

int a,b,n;
int sum[maxn],suf[maxn];
vector<int> pos[maxn];
bitset<maxn> f;
void work(){
    a=read(),b=read(),n=read();
    for(int i=1;i<=b;i++)sum[i]=0,pos[i].clear();
    for(int i=1;i<=n;i++){
        int c=read(),d=read();
        if(d==b)a-=c;
        else pos[d].pb(c),sum[d]+=c;
    }
    if(a<0){puts("NIE");return ;}
    suf[b+1]=0;for(int i=b;i;i--)suf[i]=suf[i+1]+sum[i];
    if((b&1)&&suf[(b+1)/2]>a){puts("NIE");return ;}
    f.reset();f[0]=1;
    for(int i=b/2,s=0;i;i--)if(sum[i]||sum[b-i]){
        s+=sum[i];for(int j:pos[i])f=f|(f<<j);
        if(2*i!=b){
            s+=sum[b-i];for(int j:pos[b-i])f=f|(f<<j);
        }
        int l=s-a+suf[b-i+1],r=a-suf[b-i+1];
        l=max(0ll,l),r=min(a,r);
        if(l>r){puts("NIE");return ;}
        f=(f>>l)<<l;
        f=f<<(maxn-1-r)>>(maxn-1-r);
    }
    if(f.count())puts("TAK");
    else puts("NIE");
}

int T;
signed main(){
    // freopen("A.in","r",stdin);
    // freopen("A.out","w",stdout);
    
    T=read();
    while(T--)work();
}