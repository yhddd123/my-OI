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

int n,m,a[10][10],pw[10],cnt[10];
char s[10],t[10];
int calc(int n){return n<=9?0:calc(n/10)+1;}
bool check(){
    for(int s=1;s<(1<<m+1);s++){
        int s1=0,s2=0;
        for(int i=0;i<=m;i++)if(s&(1<<i)){
            s1+=cnt[i];
            for(int j=i;j<=m;j++)if(s&(1<<j))s2+=a[i][j];
        }
        if(s1&&s1<=s2)return 0;
    }
    return 1;
}
void work(){
    n=read();m=calc(n);
    for(int i=1;i<=n;i++)cnt[calc(i)]++;
    pw[0]=1;for(int i=1;i<=m;i++)pw[i]=pw[i-1]*10;
    for(int i=1;i<n;i++){
        scanf("%s%s",s,t);
        a[min(strlen(s)-1,strlen(t)-1)][max(strlen(s)-1,strlen(t)-1)]++;
    }
    if(!check()){puts("-1");return ;}
    while(1){
        bool fl=0;
        for(int i=0;i<=m;i++){
            for(int j=i;j<=m;j++)if(a[i][j]){
                a[i][j]--;
                if(cnt[i]){
                    cnt[i]--;
                    if(check()){
                        printf("%d %d\n",pw[i]+cnt[i],pw[j]);
                        fl=1;break;
                    }
                    cnt[i]++;
                }
                if(cnt[j]){
                    cnt[j]--;
                    if(check()){
                        printf("%d %d\n",pw[i],pw[j]+cnt[j]);
                        fl=1;break;
                    }
                    cnt[j]++;
                }
                a[i][j]++;
            }
            if(fl)break;
        }
        if(!fl)break;
    }
    for(int i=0;i<=m;i++){
        for(int j=i;j<=m;j++)if(a[i][j])printf("%d %d\n",pw[i],pw[j]);
    }
}

int T;
signed main(){
    // freopen("A.in","r",stdin);
    // freopen(".out","w",stdout);
    
    T=1;
    while(T--)work();
}