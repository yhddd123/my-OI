#include<bits/stdc++.h>
#define db long double
using namespace std;
const int maxn=1010;

int n;db p;
db dp[maxn][maxn],pw[maxn];
int pre[maxn];

// bool a[maxn];int times;
bool ask(int l,int r) {
    putchar('Q');putchar(' ');
    for (int i = 1; i <= n; i++)putchar((l<=i&&i<=r) ? '1' : '0');
    fflush(stdout);
    char answer;scanf(" %c", &answer);
    return answer == 'P';

	// ++times;
    // for(int i=l;i<=r;i++)if(a[i])return 1;
    // return 0;
}
vector<bool> work(){
    vector<bool> ans(n);
    int i=n,j=0;
    while(i){
    	// cout<<i<<" "<<j<<"\n";
        if(j==1)ans[i-1]=1,i--,j=0;
        else if(j>=2){
            if(ask(i-j/2+1,i))j=j/2;
            else i-=j/2,j-=j/2;
        }
        else{
            if(ask(i-pre[i]+1,i))j=pre[i];
            else i-=pre[i];
        }
    }
    return ans;
}
mt19937 rnd(1);
signed main(){
    int T;scanf("%d%Lf%d",&n,&p,&T);

    pw[0]=1;for(int i=1;i<=n;i++)pw[i]=pw[i-1]*(1-p);
    for(int i=0;i<=n;i++){
    	for(int j=0;j<=i;j++)dp[i][j]=1000000;
    }
    dp[0][0]=0;
    for(int i=1;i<=n;i++){
        dp[i][1]=dp[i-1][0];
        for(int j=2;j<=i;j++){
        	db p=(pw[j/2]-pw[j])/(1-pw[j]);
            db val=dp[i-j/2][j-j/2]*p+dp[i][j/2]*(1-p)+1;
            if(val<dp[i][j])dp[i][j]=val;
        }
        for(int k=1;k<=i;k++){
            db val=dp[i-k][0]*pw[k]+dp[i][k]*(1-pw[k])+1;
            if(val<dp[i][0])dp[i][0]=val,pre[i]=k;
        }
        // for(int j=0;j<=i;j++)cout<<dp[i][j]<<" ";cout<<"\n";
    }
    // cout<<dp[n][0]<<"\n";

    int sum=0;
    for(int t=1;t<=T;t++){
        // for(int i=1;i<=n;i++){
            // db v=1.0*(rnd()%10000000)/10000000;
            // a[i]=v<p;
        // }
        // for(int i=1;i<=n;i++)cout<<a[i];cout<<"\n";
        // times=0;
        
        vector<bool> ans=work();
        putchar('A');putchar(' ');for(bool v:ans)putchar(v+'0');puts("");
        fflush(stdout);
        
        // for(int i=0;i<n;i++)assert(a[i+1]==ans[i]);

        // cout<<times<<"\n";
        // sum+=times;

        char verdict;scanf(" %c", &verdict);
        if (verdict == 'W')exit(0);
    }
    // cout<<sum<<" "<<1.0*sum/T<<"\n";
}