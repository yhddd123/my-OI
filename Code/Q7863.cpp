#include<bits/stdc++.h>
#define int long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define mems(x,y) memset(x,y,sizeof(x))
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

int n,a[maxn],m;
char op[5];
bool check(){
	int num0=0,num1=0,len=0;
	for(int i=1;i<=n;i++){
		if(!a[i])++num0;
		if(a[i])++len;
		if(!a[i]){
			if(len&1)++num1;
			len=0;
		}
	}
	num1+=(len&1);
	return num1>=num0;
}
void work(){
	n=read();m=read();
	for(int i=1;i<=n;i++)a[i]=read();
	if(!(m^(n&1))){
		if((n-1)&1)printf("Alice\n"),fflush(stdout);
		else{
			printf("Bob\n");fflush(stdout);
			int x=read();cin>>op+1;
			if(op[1]=='+'){
				a[x]^=a[x+1];for(int i=x+1;i<n;i++)a[i]=a[i+1];n--;
			}
			else{
				a[x]*=a[x+1];for(int i=x+1;i<n;i++)a[i]=a[i+1];n--;
			}
		}
		while(n>2){
			printf("1 +\n");fflush(stdout);
			a[1]^=a[2];for(int i=2;i<n;i++)a[i]=a[i+1];n--;
			int x=read();cin>>op+1;
			if(op[1]=='+'){
				a[x]^=a[x+1];for(int i=x+1;i<n;i++)a[i]=a[i+1];n--;
			}
			else{
				a[x]*=a[x+1];for(int i=x+1;i<n;i++)a[i]=a[i+1];n--;
			}
		}
		// cout<<n<<" "<<a[1]<<" "<<a[2]<<"\n";
		if(n==2){
			if(!a[1]||!a[2])printf("1 *\n"),fflush(stdout);
			else printf("1 +\n"),fflush(stdout);
		}
		return ;
	}
	bool fl=check(),im=0;
	if(!fl){
		if((n-1)&1){
			printf("Bob\n"),fflush(stdout);im=1;
			int x=read();cin>>op+1;
			if(op[1]=='+'){
				a[x]^=a[x+1];for(int i=x+1;i<n;i++)a[i]=a[i+1];n--;
			}
			else{
				a[x]*=a[x+1];for(int i=x+1;i<n;i++)a[i]=a[i+1];n--;
			}
		}
		else printf("Alice\n"),fflush(stdout);
	}
	else{
		if((n-1)&1)printf("Alice\n"),fflush(stdout);
		else{
			printf("Bob\n");fflush(stdout);im=1;
			int x=read();cin>>op+1;
			if(op[1]=='+'){
				a[x]^=a[x+1];for(int i=x+1;i<n;i++)a[i]=a[i+1];n--;
			}
			else{
				a[x]*=a[x+1];for(int i=x+1;i<n;i++)a[i]=a[i+1];n--;
			}
		}
	}
	while(n>2){
		for(int i=1;i<n;i++){
			int tmp=a[i],tmp1=a[i+1];
			a[i]^=a[i+1];for(int j=i+1;j<n;j++)a[j]=a[j+1];n--;
			if(check()==fl){
				// for(int j=1;j<=n;j++)cout<<a[j]<<" ";cout<<"\n";
				printf("%lld +\n",i),fflush(stdout);
				break ;
			}
			n++;for(int j=n-1;j>=i+1;j--)a[j+1]=a[j];
			a[i]=tmp,a[i+1]=tmp1;
			a[i]*=a[i+1];for(int j=i+1;j<n;j++)a[j]=a[j+1];n--;
			if(check()==fl){
				// for(int j=1;j<=n;j++)cout<<a[j]<<" ";cout<<"\n";
				printf("%lld *\n",i),fflush(stdout);
				break ;
			}
			n++;for(int j=n-1;j>=i+1;j--)a[j+1]=a[j];
			a[i]=tmp,a[i+1]=tmp1;
		}
		int x=read();cin>>op+1;
		if(op[1]=='+'){
			a[x]^=a[x+1];for(int i=x+1;i<n;i++)a[i]=a[i+1];n--;
		}
		else{
			a[x]*=a[x+1];for(int i=x+1;i<n;i++)a[i]=a[i+1];n--;
		}
		// for(int j=1;j<=n;j++)cout<<a[j]<<" ";cout<<"\n";
	}
	if(n==2){
		if(im){
			if(!m){
				if(a[1]&&a[2])printf("1 *\n"),fflush(stdout);
				else printf("1 +\n"),fflush(stdout);
			}
			else{
				printf("1 *\n"),fflush(stdout);
			}
		}
		else{
			if(m){
				if(a[1]&&a[2])printf("1 *\n"),fflush(stdout);
				else printf("1 +\n"),fflush(stdout);
			}
			else{
				printf("1 *\n"),fflush(stdout);
			}
		}
	}
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
