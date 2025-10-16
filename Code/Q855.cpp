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
const int maxn=25010;
const int inf=1e9;
bool mbe;

int n;
char op;
char s[maxn],t[maxn];
int num[maxn];
void work(){
	cin>>n>>op>>s+1>>t+1;
	for(int i=1;i<=n;i++)num[i]=num[i-1]+(s[i]==op);
	bool fl=0;
	for(int i=n;i;i--){
		if(s[i]!='z'){
			if(i==n){
				if(num[i]){
					s[i]++;
					fl=1;break;
				}
				if(s[i]-'a'<op-'a'){s[i]=op;fl=1;break;}
			}
			if(i<n){
				s[i]++;for(int j=i+1;j<n;j++)s[j]='a';
				if(!num[i-1])s[n]=op;
				else s[n]='a';
				fl=1;break;
			}
		}
	}
	// for(int i=1;i<=n;i++)cout<<s[i];cout<<"\n";
	if(!fl){puts("NO");return ;}
	for(int i=1;i<=n;i++){
		if(s[i]-'a'>t[i]-'a'){puts("NO");return ;}
		if(s[i]-'a'<t[i]-'a')break;
		if(i==n){puts("NO");return ;}
	}
	for(int i=1;i<=n;i++)cout<<s[i];cout<<"\n";
}

bool med;
int T;
signed main(){
	// freopen(".in","r",stdin);
	// freopen(".out","w",stdout);
	
	// cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
	
	T=read();
	while(T--)work();
}