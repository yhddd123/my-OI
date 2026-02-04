#include<bits/stdc++.h>
#define int long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
#define db long double
#define mems(a,x) memset((a),(x),sizeof(a))
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


int bf(int n,int m,int l,int r,int k_target){
	static long long dp[25][25][45][2]; 
	mems(dp,0);
    auto is_invalid = [&](int x, int y) {
        return y == x + l||y==x+r;
    };

    // 初始位置检查
    if (is_invalid(0, 0)) {
        return 0;
    }

    // 初始化起点
    // dp[x][y][k][dir] -> dir 0: 向右移动到达, 1: 向上移动到达
    if (n >= 1 && !is_invalid(1, 0)) dp[1][0][0][0] = 1;
    if (m >= 1 && !is_invalid(0, 1)) dp[0][1][0][1] = 1;

    for (int i = 0; i <= n; ++i) {
        for (int j = 0; j <= m; ++j) {
            if (is_invalid(i, j)) continue;
            for (int k = 0; k <= k_target; ++k) {
                
                // 1. 尝试向右走 (更新 dir = 0)
                if (i > 0) {
                    // 同向：从 (i-1, j) 向右走过来
                    dp[i][j][k][0] = (dp[i][j][k][0] + dp[i-1][j][k][0]) % mod;
                    // 换向：从 (i-1, j) 原本向上的状态拐弯
                    if (k > 0) {
                        dp[i][j][k][0] = (dp[i][j][k][0] + dp[i-1][j][k-1][1]) % mod;
                    }
                }

                // 2. 尝试向上走 (更新 dir = 1)
                if (j > 0) {
                    // 同向：从 (i, j-1) 向上走过来
                    dp[i][j][k][1] = (dp[i][j][k][1] + dp[i][j-1][k][1]) % mod;
                    // 换向：从 (i, j-1) 原本向右的状态拐弯
                    if (k > 0) {
                        dp[i][j][k][1] = (dp[i][j][k][1] + dp[i][j-1][k-1][0]) % mod;
                    }
                }
            }
        }
    }

    long long ans = (dp[n][m][k_target][0] + dp[n][m][k_target][1]) % mod;
    return ans;
}

inline int ksm(int a,int b=mod-2){
    int ans=1;
    while(b){
        if(b&1)ans=1ll*ans*a%mod;
        a=1ll*a*a%mod;
        b>>=1;
    }
    return ans;
}
int fac[maxn],inv[maxn];
int C(int m,int n){
    if(n<0||m<0||m<n)return 0;
    return 1ll*fac[m]*inv[n]%mod*inv[m-n]%mod;}
void init(int n){
    fac[0]=1;for(int i=1;i<=n;i++)fac[i]=1ll*fac[i-1]*i%mod;
    inv[n]=ksm(fac[n]);for(int i=n-1;~i;i--)inv[i]=1ll*inv[i+1]*(i+1)%mod;
}
inline void inc(int &u,int v){((u+=v)>=mod)&&(u-=mod);}
int calc(int n,int m,int k){
	if(n<0||m<0)return 0;
	if((!n||!m))return !k;
	if(k&1){
		return 2*C(n-1,(k+1)/2-1)*C(m-1,(k+1)/2-1)%mod;
	}
	else{
		return (C(n-1,k/2)*C(m-1,k/2-1)+C(n-1,k/2-1)*C(m-1,k/2))%mod;
	}
}
int calc(int n,int m,int b,int k){
	if(b<=0||m>=n+b)return 0;
	if(k&1){
		return (2*C(n-1,(k+1)/2-1)*C(m-1,(k+1)/2-1)%mod+2*mod-C(n+b-2,((k-1)/2))*C(m-b,((k-1)/2))%mod-C(n+b-2,((k-1)/2)-1)*C(m-b,((k-1)/2)+1)%mod)%mod;
	}
	else{
		return (C(n-1,(k/2))*C(m-1,(k/2)-1)+C(n-1,(k/2)-1)*C(m-1,(k/2))+mod-2*C(n+b-2,(k/2)-1)*C(m-b,(k/2))%mod)%mod;
	}
	// int res=calc(n,m,k);
	// for(int i=0;b+i<=m;i++)(res+=mod-calc(n+b-1,m-b-i,k-1))%=mod;
	// return res;
}
int calcn(int n,int m,int k){
	if(n<0||m<0)return 0;
	if(k&1)return 2*C(n,(k+1)/2-1)*C(m,(k+1)/2)%mod;
	else return (C(n,k/2)*C(m,k/2)+C(n,(k/2)-1)*C(m,(k/2)+1))%mod;
}
int calc(int n,int m,int l,int r,int k){
	if(l>=0||r<=0||m<=n+l||m>=n+r)return 0;
	if(!n||!m)return !k;
	int res=calc(n,m,k);
	if(k&1){
		int x=0,y=0,o=0;
		while(x<=max(n,m)+5&&y<=max(n,m)+5&&o<=k){
			if(x||y){
				if(o&1){
					(res+=mod-calcn(n-x-o*2,m-y,k-o))%=mod;
				}
				else{
					(res+=calc(m-y-o*2,n-x,k-o))%=mod;
				}
			}
			cout<<x<<" "<<y<<" "<<res<<" a\n";
			swap(x,y);
			if(!(o&1))x-=r,y+=r;
			else x-=l,y+=l;
			o++;
		}
		x=0,y=0,o=0;
		while(x<=max(n,m)+5&&y<=max(n,m)+5&&o<=k){
			if(x||y){
				if(o&1){
					(res+=mod-calcn(m-y-o*2,n-x,k-o))%=mod;
				}
				else{
					(res+=calc(n-x-o*2,m-y,k-o))%=mod;
				}
			}
			cout<<x<<" "<<y<<" "<<res<<" b\n";
			swap(x,y);
			if(!(o&1))x-=l,y+=l;
			else x-=r,y+=r;
			o++;
		}
		return res;
	}
	else{
		return bf(n,m,l,r,k);
		// k=k/2;
		// int x=0,y=0,o=1;
		// while(x<=max(n,m)+5&&y<=max(n,m)+5){
			// if(x||y){
				// if(o==mod-1){
					// (res+=2*mod-2*C(n-x-2,k-1)*C(m-y,k)%mod)%=mod;
				// }
				// else{
					// (res+=2*C(n-x,k)*C(m-y-2,k-1))%=mod;
				// }
			// }
			// swap(x,y);
			// if(o==1)x-=r,y+=r;
			// else x-=l,y+=l;
			// o=mod-o;
		// }
		// x=0,y=0,o=1;
		// while(x<=max(n,m)+5&&y<=max(n,m)+5){
			// if(x||y){
				// if(o==mod-1){
					// (res+=2*mod-2*C(n-x,k)*C(m-y-2,k-1)%mod)%=mod;
				// }
				// else{
					// (res+=2*C(n-x-2,k-1)*C(m-y,k))%=mod;
				// }
			// }
			// swap(x,y);
			// if(o==1)x-=l,y+=l;
			// else x-=r,y+=r;
			// o=mod-o;
		// }
		return res;
	}
	return 0;
}
int n;
void work(){
	n=10;init(maxn-10);
	cout<<calc(4,4,-1,1,3)<<"\n";
	// cout<<calc(4,5,-1,2,3)<<"\n";
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			for(int l=-i-1;l<0&&l<j-i;l++){
				for(int r=max(1ll,j-i+1);r<=j+1;r++){
					for(int k=1;k<=2*min(i,j);k++){
						int v1=bf(i,j,l,r,k),v2=calc(i,j,l,r,k);
						if(v1!=v2){
							cerr<<i<<" "<<j<<" "<<l<<" "<<r<<" "<<k<<" "<<v1<<" "<<v2<<"\n";
						}
					}
				}
			}
		}
	}
}

bool med;
int T;
signed main(){
	// freopen(".in","r",stdin);
	// freopen(".out","w",stdout);
	
	cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
	
	T=1;
	while(T--)work();
}