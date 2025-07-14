#include<bits/stdc++.h>
#define int long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define mems(x,y) memset(x,y,sizeof(x))
using namespace std;
const int maxn=45;
const int maxm=2510;
const int inf=1e18;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}
bool Mbe;

int n,m;
char s[maxn];
bitset<maxm> f[maxn][maxn][maxn];
char ans[maxn];
void work(){
	n=read();m=read();scanf("%s",s+1);
	for(int i=0;i<=n;i++)f[0][0][i][0]=1;
	for(int i=1;i<=n;i++){
		for(int j=0;j<i;j++){
			for(int k=0;k<=n-i+1;k++){
				if(s[i]=='N'||s[i]=='?'){
					f[i][j+1][k]|=f[i-1][j][k];
				}
				if(s[i]=='A'||s[i]=='?'){
					f[i][j][k]|=f[i-1][j][k]<<(j*k);
				}
				if(s[i]=='C'||s[i]=='?'){
					if(k)f[i][j][k-1]|=f[i-1][j][k];
				}
				if((s[i]!='N'&&s[i]!='A'&&s[i]!='C')||s[i]=='?'){
					f[i][j][k]|=f[i-1][j][k];
				}
			}
		}
	}
	for(int num=0;num<=n;num++)if(f[n][num][0][m]){
		for(int i=n,j=num,k=0,cnt=m;i;i--){
			if(s[i]=='N'||(s[i]=='?'&&j&&f[i-1][j-1][k][cnt])){
				ans[i]='N';
				j--;
			}
			else if(s[i]=='A'||(s[i]=='?'&&cnt>=j*k&&f[i-1][j][k][cnt-j*k])){
				ans[i]='A';
				cnt-=j*k;
			}
			else if(s[i]=='C'||(s[i]=='?'&&f[i-1][j][k+1][cnt])){
				ans[i]='C';
				k++;
			}
			else if(s[i]=='?')ans[i]='O';
			else ans[i]=s[i];
		}
		for(int i=1;i<=n;i++)printf("%c",ans[i]);
		return ;
	}
	puts("-1");
	
}

// \
444

bool Med;
int T;
signed main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	
//	ios::sync_with_stdio(0);
//	cin.tie(0);cout.tie(0);
	
//	cerr<<(&Mbe-&Med)/1048576.0<<" MB\n";
	
	T=1;
	while(T--)work();
}
