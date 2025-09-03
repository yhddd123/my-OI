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
const int maxn=200010;
const int inf=1e9;

int n;
multiset<int> s1;
int sum[1<<20];
void work(){
    n=read();
    s1.clear();for(int i=1;i<(1<<n);i++)s1.insert(read());
    for(int i=0;i<n;i++){
        int v=*s1.begin();
        for(int s=0;s<(1<<i+1);s++)if(s&(1<<i)){
            sum[s]=sum[s^(1<<i)]^v;
            auto it=s1.find(sum[s]);
            if(it==s1.end()){puts("-1");return ;}
            s1.erase(s1.find(sum[s]));
        }
    }
    for(int i=0;i<n;i++)printf("%d ",sum[1<<i]);puts("");
}

int T;
signed main(){
    // freopen("A.in","r",stdin);
    // freopen(".out","w",stdout);
    
    T=read();
    while(T--)work();
}