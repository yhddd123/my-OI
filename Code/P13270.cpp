#include<bits/stdc++.h>
#define int long long
#define db double
#define mod 1000000007
using namespace std;
const int maxn=20000010;
const int inf=1e18;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}

int n;
char s[maxn];

int T;
signed main(){
	//	freopen(".in","r",stdin);
	//	freopen(".out","w",stdout);
	
	n=read();scanf("%s",s+1);
	for(int i=1;i<=n;i++)s[i+n]=s[i];
	int s1=1,s2=2,l=0;
	while(s1<=n&&s2<=n&&l<n){
        // cout<<s1<<" "<<s2<<" "<<l<<"\n";
		if(s[s1+l]==s[s2+l])l++;
		else{
			if(s[s1+l]>s[s2+l])s1+=l+1;
			else s2+=l+1;
			if(s1==s2)s2++;
			l=0;
		}
	}
	int pos=min(s1,s2);
    // cout<<s1<<" "<<s2<<"\n";
	for(int i=pos;i<=pos+n-1;i++)printf("%c",s[i]);
}