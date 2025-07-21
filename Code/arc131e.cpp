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
const int maxn=55;
const int inf=1e9;

int n;
char ans[maxn][maxn];
void sovle(int n){
    if(n==6){
        for(int i:{1,2,5}){
            for(int j=1;j<i;j++)ans[j][i]='R';
        }
        for(int i:{3,4}){
            for(int j=1;j<i;j++)ans[j][i]='B';
        }
        for(int i:{6}){
            for(int j=1;j<i;j++)ans[j][i]='W';
        }
        return ;
    }
    if(n==7){
        for(int i:{1,2,7}){
            for(int j=1;j<i;j++)ans[j][i]='R';
        }
        for(int i:{4,5}){
            for(int j=1;j<i;j++)ans[j][i]='B';
        }
        for(int i:{3,6}){
            for(int j=1;j<i;j++)ans[j][i]='W';
        }
        return ;
    }
    if(n==9){
        for(int i:{1,2,3,4,7}){
            for(int j=1;j<i;j++)ans[j][i]='R';
        }
        for(int i:{6,8}){
            for(int j=1;j<i;j++)ans[j][i]='B';
        }
        for(int i:{5,9}){
            for(int j=1;j<i;j++)ans[j][i]='W';
        }
        return ;
    }
    if(n==10){
        for(int i:{1,2,3,4,5,6}){
            for(int j=1;j<i;j++)ans[j][i]='R';
        }
        for(int i:{8,9}){
            for(int j=1;j<i;j++)ans[j][i]='B';
        }
        for(int i:{7,10}){
            for(int j=1;j<i;j++)ans[j][i]='W';
        }
        return ;
    }
    sovle(n-6);
    for(int i:{n-3,n-2}){
        for(int j=1;j<i;j++)ans[j][i]='R';
    }
    for(int i:{n-4,n-1}){
        for(int j=1;j<i;j++)ans[j][i]='B';
    }
    for(int i:{n-5,n}){
        for(int j=1;j<i;j++)ans[j][i]='W';
    }
}
void work(){
    n=read();
    if(n<=4||n%3==2){puts("No");return ;}
    sovle(n);
    puts("Yes");
    for(int i=1;i<=n;i++){
        for(int j=i+1;j<=n;j++)printf("%c",ans[i][j]);puts("");
    }
}

int T;
signed main(){
    // freopen(".in","r",stdin);
    // freopen(".out","w",stdout);
    
    T=1;
    while(T--)work();
}