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
const int maxn=1510;
const int inf=1e9;
bool mbe;

int n;
int a[maxn][maxn];
void sovle(int n){
	if(n==2){
		a[1][1]=a[2][2]=a[3][3]=1;
		a[1][7]=a[2][6]=a[3][5]=1;
		a[5][3]=a[6][2]=a[7][1]=1;
		a[5][5]=a[6][6]=a[7][7]=1;
		a[1][4]=a[4][1]=a[7][4]=a[4][7]=1;
		return ;
	}
	for(int i=1;i<=n;i++)a[3*(i-1)+1][3*n+1]=a[3*(i-1)+2][3*n]=a[3*(i-1)+3][3*n-1]=1;
	a[3*n+1][3*n+1]=1;
	if(n==3){
		a[10][1]=a[9][2]=a[8][3]=1;
		a[10][4]=1;
		a[8][5]=a[9][6]=1;
	}
	else{
		a[3*n+1][1]=a[3*n][2]=a[3*n-1][3]=1;
		a[3*n+1][4]=a[3*n][5]=a[3*n-1][6]=1;
		a[3*n][7]=a[3*n-1][8]=1;
		for(int i=1;i<=n-4;i++){
			a[3*n+1][3*(i+2)]=a[3*n][3*(i+2)+1]=a[3*n-1][3*(i+2)+2]=1;
		}
		a[3*n+1][3*n-3]=1;
	}
	sovle(n-1);
}
void work(){
	n=read();
	if(n==1){puts("No");return ;}
	puts("Yes");
	sovle(n);
	for(int i=1;i<=3*n+1;i++){
		for(int j=1;j<=3*n+1;j++)printf("%c",a[i][j]?'#':'.');puts("");
	}
}

bool med;
signed main(){
	// freopen(".in","r",stdin);
	// freopen(".out","w",stdout);
	
	cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
	
	int T=1;
	while(T--)work();
}