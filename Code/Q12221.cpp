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
const int maxn=300010;
const int maxk=15;
const int inf=1e9;
bool mbe;

int to[maxk][2],len[maxk];
int n,k,l;
char s[maxn];
struct mat{
	int e[maxk][maxk];
	mat(){memset(e,0,sizeof(e));}
}bas;
mat operator*(mat &u,mat &v){
	mat res;
	for(int i=1;i<=l;i++){
		for(int k=1;k<=l;k++){
			for(int j=1;j<=l;j++)(res.e[i][j]+=u.e[i][k]*v.e[k][j])%=mod;
		}
	}
	return res;
}
mat one(){
	mat res;
	for(int i=1;i<=l;i++)res.e[i][i]=1;
	return res;
}
mat qpow(mat a,int b){
	mat ans=one();
	while(b){
		if(b&1)ans=ans*a;
		a=a*a;
		b>>=1;
	}
	return ans;
}
void work(){
	l=12;
	n=read();scanf("%s",s+1);k=read();
	to[1][0]=2,to[1][1]=3;
	to[2][0]=1,to[2][1]=4;
	to[3][0]=5,to[3][1]=6;
	to[4][0]=7,to[4][1]=8;
	to[5][0]=3,to[5][1]=9;
	to[6][0]=10,to[6][1]=1;
	to[7][0]=4,to[7][1]=10;
	to[8][0]=9,to[8][1]=2;
	to[9][0]=8,to[9][1]=11;
	to[10][0]=6,to[10][1]=12;
	to[11][0]=12,to[11][1]=5;
	to[12][0]=11,to[12][1]=7;
	int p=1;for(int i=1;i<=n;i++)p=to[p][s[i]-'a'];
	for(int i=1;i<=l;i++)bas.e[to[i][0]][i]=bas.e[to[i][1]][i]=1;
	bas=qpow(bas,k);
	// cout<<p<<" "<<len[p]<<"\n";
	printf("%lld\n",bas.e[p][1]);
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