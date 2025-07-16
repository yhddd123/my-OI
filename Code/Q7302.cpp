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
const int maxn=1010;
const int inf=1e9;

int n,m,ans;
bitset<maxn> e[maxn];
char s[maxn];
int d[maxn],num[maxn][maxn];
void work(){
    m=ans=0;
    for(int i=1;i<=n;i++)e[i].reset(),d[i]=0;
    for(int i=1;i<=n;i++){
        scanf("%s",s+1);
        for(int j=i+1;j<=n;j++)if(s[j]=='1')e[i][j]=e[j][i]=1,d[i]++,d[j]++,m++;
    }
    for(int i=1;i<=n;i++){
        for(int j=i+1;j<=n;j++)num[i][j]=num[j][i]=(e[i]&e[j]).count();
    }
    //u-v-u-v-u-v
    int cnt1=m;
    ans+=cnt1*2;
    //u-v-w-u-v-w
    int cnt2=0;
    for(int i=1;i<=n;i++){
        for(int j=i+1;j<=n;j++)if(e[i][j])cnt2+=num[i][j];
    }
    cnt2/=3;
    ans+=cnt2*24;
    //u-v-w-x
    int cnt3=0;
    for(int i=1;i<=n;i++){
        for(int j=i+1;j<=n;j++)cnt3+=num[i][j]*(num[i][j]-1)/2;
    }
    cnt3/=2;
    ans+=cnt3*48;
    //u-v-w-v-u
    int cnt4=0;
    for(int i=1;i<=n;i++)cnt4+=d[i]*(d[i]-1)/2;
    ans+=cnt4*12;
    //u-v-w-x-w-v-u
    int cnt5=0;
    for(int i=1;i<=n;i++){
        for(int j=i+1;j<=n;j++)if(e[i][j])cnt5+=(d[i]-1)*(d[j]-1);
    }
    cnt5-=3*cnt2;
    ans+=cnt5*6;
    //u-v-u-w-u-x
    int cnt6=0;
    for(int i=1;i<=n;i++)cnt6+=d[i]*(d[i]-1)*(d[i]-2)/6;
    ans+=cnt6*12;
    //u-v-w-x-u-w-u
    int cnt7=0;
    for(int i=1;i<=n;i++){
        for(int j=i+1;j<=n;j++)if(e[i][j])cnt7+=num[i][j]*(num[i][j]-1)/2;
    }
    ans+=cnt7*36;
    //u-v-w-x-u-y-u
    int cnt8=0;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++)cnt8+=num[i][j]*(num[i][j]-1)/2*(d[i]-e[i][j]-2);
    }
    ans+=cnt8*12;
    //u-v-w-u-x-y-u
    int cnt9=0;
    for(int i=1;i<=n;i++){
        int cnt=0;
        for(int j=1;j<=n;j++)if(e[i][j])cnt+=num[i][j];
        cnt/=2;
        cnt9+=cnt*(cnt-1)/2;
    }
    cnt9-=2*cnt7;
    ans+=cnt9*24;
    // cout<<cnt1<<" "<<cnt2<<" "<<cnt3<<" "<<cnt4<<" "<<cnt5<<" "<<cnt6<<" "<<cnt7<<" "<<cnt8<<" "<<cnt9<<" "<<ans<<endl;
    printf("%lld\n",ans);
}

int T;
signed main(){
    // freopen("A.in","r",stdin);
    // freopen(".out","w",stdout);
    
    T=1;
    while(~scanf("%lld",&n))work();
}