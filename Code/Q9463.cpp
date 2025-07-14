#include<bits/stdc++.h>
#define ll unsigned
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define mems(x,y) memset(x,y,sizeof(x))
#define pb push_back
#define db double
using namespace std;
const int maxn=65;
const int inf=1e18;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}
bool Mbe;

int n;
char s1[maxn],s2[maxn],s[maxn*3];
ll dp[maxn][maxn][maxn][2][2],ans;
void work(bool fl=0){
	n=read();scanf("%s%s%s",s1,s2,s+1);
	if(fl){
		puts("-1");
		return ;
	}
	for(int mxa=0;mxa<=n;mxa++){
		for(int mxb=0;mxa+mxb<=n;mxb++){
			int mxc=0,fl=0;
			for(int va=mxa;va<=n;va++){
				for(int vb=mxb;vb<=n-va;vb++)if(s1[va]=='1'&&s2[vb]=='1')mxc=max(mxc,n-va-vb),fl=1;
			}
			if(!fl)continue;
			// cout<<mxa<<" "<<mxb<<" "<<mxc<<" s\n";
			mems(dp,0);
			dp[0][0][0][mxa==0][mxb==0]=1;
			for(int a=0;a<=n;a++){
				for(int b=0;b<=min(n,a+mxb);b++){
					for(int c=max(0,a-mxa);c<=min(n,b+mxc);c++){
						// cout<<a<<" "<<b<<" "<<c<<"\n";
						int i=a+b+c+1;
						if(i>3*n)break;
						ll dp00=dp[a][b][c][0][0],dp01=dp[a][b][c][0][1],dp10=dp[a][b][c][1][0],dp11=dp[a][b][c][1][1];
						if(s[i]=='A'||s[i]=='?'){
							if(a+1-c<=mxa){
								dp[a+1][b][c][a+1-c==mxa][0]+=dp00;
								dp[a+1][b][c][1][0]+=dp10;
								dp[a+1][b][c][a+1-c==mxa][1]+=dp01;
								dp[a+1][b][c][1][1]+=dp11;
							}
						}
						if(s[i]=='B'||s[i]=='?'){
							if(b+1-a<=mxb){
								dp[a][b+1][c][0][b+1-a==mxb]+=dp00;
								dp[a][b+1][c][0][1]+=dp01;
								dp[a][b+1][c][1][b+1-a==mxb]+=dp10;
								dp[a][b+1][c][1][1]+=dp11;
							}
						}
						if(s[i]=='C'||s[i]=='?'){
							if(c+1-b<=mxc){
								dp[a][b][c+1][0][0]+=dp00;
								dp[a][b][c+1][1][0]+=dp10;
								dp[a][b][c+1][0][1]+=dp01;
								dp[a][b][c+1][1][1]+=dp11;
							}
						}
					}
				}
			}
			ans+=dp[n][n][n][1][1];
		}
	}
	printf("%u\n",ans);ans=0;
}

// \
444

bool Med;
int T,id;
signed main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	
//	ios::sync_with_stdio(0);
//	cin.tie(0);cout.tie(0);
	
//	cerr<<(&Mbe-&Med)/1048576.0<<" MB\n";
	
	T=read();id=read();
	if(!id){
		while(T--)work();
	}
	else{
		T--;
		while(T--)work(1);
		work();
	}
}
