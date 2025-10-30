#include<bits/stdc++.h>
// #define int long long
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
const int maxn=85;
const int B=79;
bool mbe;

int n,m,k,c,idx;
int id[maxn][maxn];
vector<pii> e;
void work(){
	n=read();m=read();k=read();c=n-m+k-1;n-=c;
	id[1][B]=1,id[1][1]=2,id[B][1]=3;e2.pb({2,3});idx=3;
	for(int i=2;i<B;i++)id[i][B-i+1]=-1;
	for(int i=B-1;i>1;i--){
		for(int j=2;j<=B-i;j++)if(!id[i][j]){
			if(idx<n){
				id[i][j]=++n;
				int g=__gcd(i-1,B-j);
				int dx=(i-1)/g,dy=(B-j)/g;
				for(int k=i-dx,l=j+dy;k>=1;k-=dx,j+=dy)id[k][l]=-1;
			}
		}
	}
	for(int j=B-1;j>1;j--){
		for(int i=B-1;i>=B-j+1;i--)if(!id[i][j]){
			
		}
	}
	for(int i=0;i<B;i++){
		for(int j=0;j<=i;j++)if(c)printf("%d %d\n",B-j,B-(i-j)),c--;
	}
	for(int i=1;i<=l;i++){
		if(i>1)printf("%d %d\n",id[i-1][1],id[i][1]);
		for(int j=2;j<=l;j++)if(id[i][j])printf("%d %d\n",id[i][j-1],id[i][j]);
	}
	m-=n-1;
	for(int i=1;i<l;i++){
		int mx=1;
		for(int j=2;j<=l;j++)if(id[i+1][j]){
			if(m)printf("%d %d\n",id[i][1],id[i+1][j]),m--;
			mx=j;
		}
		for(int j=2;j<=l;j++)if(id[i][j]){
			if(m)printf("%d %d\n",id[i][j],id[i+1][mx]),m--;
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