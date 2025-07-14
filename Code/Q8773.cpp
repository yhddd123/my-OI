#include<bits/stdc++.h>
#define int long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define mems(x,y) memset(x,y,sizeof(x))
#define pb push_back
using namespace std;
const int maxn=200010;
const int inf=1e18;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}
bool Mbe;

int n=10;
char s1[maxn],s2[maxn],s3[maxn],tmp[maxn];
vector<pair<char,int>> ans;
void mov(int x,int fl){
	if(fl==1){
		if(x)ans.pb({'o',x});
		for(int i=0;i<n;i++)tmp[(i+x)%n]=s1[i];
		for(int i=0;i<n;i++)s1[i]=tmp[i];
	}
	if(fl==2){
		if(x)ans.pb({'g',x});
		for(int i=0;i<n;i++)tmp[(i+x)%n]=s2[i];
		for(int i=0;i<n;i++)s2[i]=tmp[i];
	}
	if(fl==3){
		if(x)ans.pb({'r',x});
		for(int i=0;i<n;i++)tmp[(i+x)%n]=s3[i];
		for(int i=0;i<n;i++)s3[i]=tmp[i];
	}
	if(fl==4){
		if(x)ans.pb({'c',x});
		if(x==1){
			for(int i=0;i<3;i++){
				char op=s1[i];
				s1[i]=s2[i],s2[i]=s3[i],s3[i]=op;
			}
		}
		else{
			for(int i=0;i<3;i++){
				char op=s1[i];
				s1[i]=s3[i],s3[i]=s2[i],s2[i]=op;
			}
		}
	}
}
void work(){
	scanf("%s%s%s",s1,s2,s3);
	while(1){
		int p=-1;for(int i=0;i<n;i++)if(s1[i]!='o')p=i;
		if(p==-1)break;
		int pp=-1;for(int i=0;i<n;i++)if(s2[i]=='o')pp=i;
		if(~pp){
			mov((n-p)%n,1),mov((n+3-pp)%n,2),mov(2,4),mov(9,2),mov(1,4);
			// cout<<p<<" "<<pp<<"\n";
		// for(int i=0;i<n;i++)cout<<s1[i];puts("");
		// for(int i=0;i<n;i++)cout<<s2[i];puts("");
		// for(int i=0;i<n;i++)cout<<s3[i];puts("");
		// puts("");
			continue;
		}
		for(int i=0;i<n;i++)if(s3[i]=='o')pp=i;
		mov((n-pp)%n,3),mov((n+3-p)%n,1),mov(2,4),mov(9,1),mov(1,4);
		// for(int i=0;i<n;i++)cout<<s1[i];puts("");
		// for(int i=0;i<n;i++)cout<<s2[i];puts("");
		// for(int i=0;i<n;i++)cout<<s3[i];puts("");
		// puts("");
	}
	while(1){
		int p=-1;for(int i=0;i<n;i++)if(s2[i]!='g')p=i;
		if(p==-1)break;
		int pp=-1;for(int i=0;i<n;i++)if(s3[i]=='g')pp=i;
		mov((n-p)%n,2),mov((n+3-pp)%n,3),mov(2,4),mov(9,3),mov(1,4);
		// for(int i=0;i<n;i++)cout<<s1[i];puts("");
		// for(int i=0;i<n;i++)cout<<s2[i];puts("");
		// for(int i=0;i<n;i++)cout<<s3[i];puts("");
		// puts("");
	}
	printf("%lld\n",(int)ans.size());
	for(auto[op,x]:ans)printf("%c%lld\n",op,x);
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
