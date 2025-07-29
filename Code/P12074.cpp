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
const int maxn=300010;
const int inf=1e9;
bool mbe;

int n,m,a[maxn];
multiset<int> s;
void work(){
    n=read();m=read();
    for(int i=1;i<=m;i++)a[i]=read();
    reverse(a+1,a+m+1);
    int val=0;s.clear();
    for(int i=1;i<=m;i++){
        if(i&1){
            s.insert(2*a[i]);
        	if(s.size())val+=*s.rbegin(),s.erase(--s.end());
        }
        else{
            s.insert(2*a[i]);
        }
        while(2*s.size()+(i&1)>n)s.erase(s.begin());
    }
    int ans=val;
    while(s.size()){
        val+=*s.rbegin();s.erase(--s.end());
        ans=max(ans,val);
    }
    for(int i=1;i<=m;i++)ans-=a[i];
    printf("%lld\n",ans);
}

bool med;
int T;
signed main(){
    // freopen("A.in","r",stdin);
    // freopen("A.out","w",stdout);
    
    // cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
    
    T=read();
    while(T--)work();
}