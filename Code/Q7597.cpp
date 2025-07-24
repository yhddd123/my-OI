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
const int maxn=31;
const int inf=1e18;

int n,m,l,r,ans=inf;
int a[2][maxn][maxn];
int dp[2][maxn][maxn][maxn][maxn][maxn],pre[2][maxn][maxn][maxn][maxn][maxn];
int du[2][maxn];
void work(){
    n=read();m=read();l=read();r=read();
    for(int op=0;op<2;op++){
        for(int i=1;i<=n;i++){
            for(int j=0;j<=m;j++)a[op][i][j]=read();
        }
    }
    memset(dp,0x3f,sizeof(dp));
    for(int op=0;op<2;op++){
        dp[op][0][0][0][0][0]=0;
        for(int i=1;i<=n;i++){
            for(int a=0;a<i;a++){
                for(int b=0;b<=a;b++){
                    for(int c=0;c<=m;c++){
                        for(int d=0;c+d<=m;d++){
                            for(int j=0;c+d+j<=m;j++){
                                int val=dp[op][i-1][a][b][c][d]+::a[op][i][j];
                                if(val<dp[op][i][a][b][c][d+j]){
                                    dp[op][i][a][b][c][d+j]=val;
                                    pre[op][i][a][b][c][d+j]=j*3;
                                }
                                if(j&&val<dp[op][i][a+1][b+1][c+j][d]){
                                    dp[op][i][a+1][b+1][c+j][d]=val;
                                    pre[op][i][a+1][b+1][c+j][d]=j*3+1;
                                }
                                if(j&&val<dp[op][i][a+1][b][c][d+j]){
                                    dp[op][i][a+1][b][c][d+j]=val;
                                    pre[op][i][a+1][b][c][d+j]=j*3+2;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    int na=-1,nb=-1,nl=-1,nr=-1;
    for(int a=l;a<=r;a++){
        for(int b=0;b<=a;b++){
            for(int d=0;d<=m;d++){
                for(int dd=0;d+dd<=m;dd++){
                    int val=dp[0][n][a][b][m-d][d]+dp[1][n][a][a-b][m-dd][dd];
                    if(ans>val){
                        ans=val;
                        na=a,nb=b,nl=m-d,nr=m-dd;
                    }
                }
            }
        }
    }
    // cout<<na<<" "<<nb<<" "<<nl<<" "<<nr<<" "<<dp[0][n][na][nb][nl][m-nl]<<" "<<dp[1][n][na][na-nb][nr][m-nr]<<"\n";
    if(ans==inf){puts("DEFEAT");return ;}
    printf("%lld\n",ans);
    vector<int> id1[2],id2[2],id3[2];
    auto sovle=[&](int op,int a,int b,int c,int d){
        for(int i=n;i;i--){
            int j=pre[op][i][a][b][c][d]/3;du[op][i]=j;
            int opt=pre[op][i][a][b][c][d]%3;
            if(opt==0){
                d-=j;
                id3[op].pb(i);
            }
            if(opt==1){
                a--,b--,c-=j;du[op][i]--;
                id1[op].pb(i);
            }
            if(opt==2){
                a--,d-=j;du[op][i]--;
                id2[op].pb(i);id3[op].pb(i);
            }
        }
    };
    sovle(0,na,nb,nl,m-nl);
    sovle(1,na,na-nb,nr,m-nr);
    for(int i=0;i<id2[1].size();i++)printf("%lld %lld\n",id1[0][i],id2[1][i]+n);
    for(int i=0;i<id2[0].size();i++)printf("%lld %lld\n",id2[0][i],id1[1][i]+n);
    int p=0;for(int i:id1[0]){
        while(du[0][i]){
            while(p<id3[1].size()&&!du[1][id3[1][p]])p++;
            if(p==id3[1].size())break;
            printf("%lld %lld\n",i,id3[1][p]+n);
            du[0][i]--,du[1][id3[1][p]]--;
        }
    }
    p=0;for(int i:id1[1]){
        while(du[1][i]){
            while(p<id3[0].size()&&!du[0][id3[0][p]])p++;
            if(p==id3[0].size())break;
            printf("%lld %lld\n",id3[0][p],i+n);
            du[1][i]--,du[0][id3[0][p]]--;
        }
    }
    for(int i:id1[0]){
        for(int j:id1[1]){
            while(du[0][i]&&du[1][j]){
                printf("%lld %lld\n",i,j+n);
                du[0][i]--,du[1][j]--;
            }
        }
    }
}

int T;
signed main(){
    freopen("A.in","r",stdin);
    freopen("A.out","w",stdout);
    
    T=1;
    while(T--)work();
}