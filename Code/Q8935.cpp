#include<bits/stdc++.h>
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define mems(x,y) memset(x,y,sizeof(x))
using namespace std;
const int maxn=1010;
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
char s[maxn][maxn];
int vis[maxn];
void out(){
	puts("NO");
	exit(0);
}
bool check(){
	for(int i=1;i<=m;i++)if(s[0][i]!='.'){
		bool fl=0;
		for(int j=1;j<=n;j++)if(s[j][i]!='.'){
			if(s[j][i]==s[0][i]){fl=1;break;}
			else return 0;
		}
		if(!fl)return 0;
	}
	for(int i=1;i<=m;i++)if(s[n+1][i]!='.'){
		bool fl=0;
		for(int j=n;j;j--)if(s[j][i]!='.'){
			if(s[j][i]==s[n+1][i]){fl=1;break;}
			else return 0;
		}
		if(!fl)return 0;
	}
	for(int i=1;i<=n;i++)if(s[i][0]!='.'){
		bool fl=0;
		for(int j=1;j<=m;j++)if(s[i][j]!='.'){
			if(s[i][j]==s[i][0]){fl=1;break;}
			else return 0;
		}
		if(!fl)return 0;
	}
	for(int i=1;i<=n;i++)if(s[i][m+1]!='.'){
		bool fl=0;
		for(int j=m;j;j--)if(s[i][j]!='.'){
			if(s[i][j]==s[i][m+1]){fl=1;break;}
			else return 0;
		}
		if(!fl)return 0;
	}
	return 1;
}
void work(){
	n=read();m=read();
	for(int i=0;i<=n+1;i++){
		scanf("%s",s[i]);
	}
	for(int i=1;i<=m;i++)if(s[0][i]!='.'){
		int p=0;
		for(int j=1;j<=n;j++)if(s[j][i]=='.'){s[j][i]=s[0][i];p=j;break;}
		if(!p)out();
	}
	for(int i=1;i<=n;i++)if(s[i][m+1]!='.'){
		int p=0;
		for(int j=m;j;j--)if(s[i][j]!='x'){
			if(s[i][j]=='.'||s[i][j]==s[i][m+1]){s[i][j]=s[i][m+1];p=j;break;}
			else{
				int pp=0;
				for(int k=i+1;k<=n;k++)if(s[k][j]!='x'){
					if(s[k][j]=='.'||s[k][j]==s[i][j]){
						s[k][j]=s[i][j],s[i][j]='.';pp=k;
						break;
					}
					else out();
				}
				if(!pp)out();
			}
		}
		if(!p)out();
	}
	for(int i=m;i;i--)if(s[n+1][i]!='.'){
		int p=0;
		for(int j=n;j;j--)if(s[j][i]!='x'){
			if(s[j][i]=='.'||s[j][i]==s[n+1][i]){s[j][i]=s[n+1][i];p=j;break;}
			else{
				int pp=0;
				for(int k=i-1;k;k--)if(s[j][k]!='x'){
					if(s[j][k]=='.'||s[j][k]==s[j][i]){
						s[j][k]=s[j][i],s[j][i]='.';pp=k;
						break;
					}
					else out();
				}
				if(!pp)out();
			}
		}
		if(!p)out();
	}
	int pos=0;for(int i=1;i<=n;i++)if(s[0][1]=='.'||s[i][0]=='.'||s[0][1]==s[i][0]){pos=i;break;}
	if(!pos)out();
	for(int i=n;i>pos;i--)if(s[i][0]!='.'){
		int p=0;
		for(int j=1;j<=m;j++)if(s[i][j]!='x'){
			if(s[i][j]=='.'||s[i][j]==s[i][0]){s[i][j]=s[i][0];p=j;break;}
			else{
				int pp=0;
				for(int k=i-1;k;k--)if(s[k][j]!='x'){
					if(s[k][j]=='.'||s[k][j]==s[i][j]){
						s[k][j]=s[i][j],s[i][j]='.';pp=k;
						break;
					}
					else out();
				}
				if(!pp)out();
			}
		}
		if(!p)out();
	}
	for(int i=1;i<=pos;i++)if(s[i][0]!='.'){
		int p=0;
		for(int j=1;j<=m;j++)if(s[i][j]!='x'){
			if(s[i][j]=='.'||s[i][j]==s[i][0]){s[i][j]=s[i][0];p=j;break;}
			else{
				int pp=0;
				for(int k=i+1;k<=n;k++)if(s[k][j]!='x'){
					if(s[k][j]=='.'||s[k][j]==s[i][j]){
						s[k][j]=s[i][j],s[i][j]='.';pp=k;
						break;
					}
					else out();
				}
				if(!pp)out();
			}
		}
		if(!p)out();
	}
	// for(int i=1;i<=n;i++){
		// for(int j=1;j<=m;j++)cout<<s[i][j];cout<<"\n";
	// }
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(s[i][j]=='x')s[i][j]='.';
		}
	}
	if(!check())out();
	puts("YES");
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++)printf("%c",s[i][j]);
		puts("");
	}
}

// \
444

bool Med;
int T;
signed main(){
	// freopen("easy.in","r",stdin);
	 // freopen("easy.out","w",stdout);
	
//	ios::sync_with_stdio(0);
//	cin.tie(0);cout.tie(0);
	
//	cerr<<(&Mbe-&Med)/1048576.0<<" MB\n";
	
	T=1;
	while(T--)work();
}