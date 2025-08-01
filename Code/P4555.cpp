#include <algorithm>
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
const int maxn=200010;
const int inf=1e9;
bool mbe;

int n,ans;
char ss[maxn],s[maxn];
int len[maxn],pl[maxn],pr[maxn];
void manacher(int *fr){
    for(int i=1,r=0,mid=0,p=0;i<=n;i++){
        if(i<r)len[i]=min(len[2*mid-i],len[mid]+mid-i);
        else len[i]=1;
        while(s[i+len[i]]==s[i-len[i]])++len[i];
        if(i+len[i]>r){
            r=i+len[i];
            mid=i;
        }
        while(p<i+len[i]){
            ++p;
            fr[p]=2*i-p;
        }
    }
}
void work(){
    scanf("%s",ss+1);n=strlen(ss+1);
    for(int i=1;i<=n;i++)s[2*i-1]='#',s[2*i]=ss[i];s[2*n+1]='#';n=2*n+1;
    manacher(pl);
    reverse(s+1,s+n+1);
    manacher(pr);
    reverse(s+1,s+n+1);
    reverse(pr+1,pr+n+1);
    for(int i=1;i<=n;i++)pr[i]=n-pr[i]+1;
    for(int i=1;i<=n;i++)ans=max(ans,pl[i]+pr[i+1]);
    printf("%lld\n",ans/2);
}

bool med;
int T;
signed main(){
    // freopen("A.in","r",stdin);
    // freopen("A.out","w",stdout);
    
    // cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
    
    T=1;
    while(T--)work();
}