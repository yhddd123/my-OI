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
const int maxn=110;
const int inf=1e9;
bool mbe;

int n,m,c,a[maxn][maxn];
int ans[maxn][maxn];
char s[maxn];
void work(){
	n=read();m=read();c=read();read();
	for(int i=1;i<=n;i++){
		scanf("%s",s+1);
		for(int j=1;j<=m;j++)a[i][j]=(s[j]=='G')+(s[j]=='B')*2;
	}
	if(c==2){
		for(int op=0;op<2;op++){
			int num=0;
			for(int i=1;i<=n;i++){
				for(int j=1;j<=m;j++){
					if((i+j)&1)num+=(a[i][j]!=op);
					else num+=(a[i][j]!=1-op);
				}
			}
			if(num<=n*m/2){
				for(int i=1;i<=n;i++){
					for(int j=1;j<=m;j++){
						if((i+j)&1)ans[i][j]=op;
						else ans[i][j]=1-op;
					}
				}
				break;
			}
		}
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++)putchar(ans[i][j]==0?'R':(ans[i][j]==1?'G':'B'));
			puts("");
		}
	}
	else{
		for(int op=0;op<2;op++){
			int num=0;
			for(int i=1;i<=n;i++){
				for(int j=1;j<=m;j++){
					if((i+j)&1)num+=((!!a[i][j])!=op);
					else num+=((!!a[i][j])!=1-op);
				}
			}
			if(num<=n*m/2){
				for(int i=1;i<=n;i++){
					for(int j=1;j<=m;j++){
						if((i+j)&1)ans[i][j]=op;
						else ans[i][j]=1-op;
					}
				}
				break;
			}
		}
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++)putchar(ans[i][j]==0?'R':(a[i][j]==1?'G':'B'));
			puts("");
		}
	}
}

bool med;
int T;
signed main(){
	// freopen(".in","r",stdin);
	// freopen(".out","w",stdout);
	
	// cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
	
	T=1;
	while(T--)work();
}