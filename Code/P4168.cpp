#include<bits/stdc++.h>
#define int long long
#define mod 1000000007
using namespace std;
const int maxn=40010;
const int maxm=210;
const int inf=1e9;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}

int n,m,a[maxn],s,num,ans;
int b[maxn],len;
int sum[maxm][maxn],f[maxm][maxn];
int t[maxn];

int T;
signed main(){
//		freopen("P4168_1.in","r",stdin);
	//	freopen(".out","w",stdout);
	
	n=read();m=read();s=sqrt(n);num=(n+s-1)/s;
	for(int i=1;i<=n;i++)a[i]=read(),b[i]=a[i];
	sort(b+1,b+n+1);len=unique(b+1,b+n+1)-b-1;
	for(int i=1;i<=n;i++)a[i]=lower_bound(b+1,b+len+1,a[i])-b;
	for(int i=1;i<=num;i++){
		for(int j=s*(i-1)+1;j<=min(n,s*i);j++)sum[i][a[j]]++;
		for(int j=1;j<=len;j++)sum[i][j]+=sum[i-1][j];
	}
	for(int i=1;i<=num;i++){
		for(int j=i;j<=num;j++){
			int res=f[i][j-1];
			for(int k=s*(j-1)+1;k<=min(n,s*j);k++){
				if(sum[j][a[k]]-sum[i-1][a[k]]>sum[j][res]-sum[i-1][res])res=a[k];
				if(sum[j][a[k]]-sum[i-1][a[k]]==sum[j][res]-sum[i-1][res]&&res>a[k])res=a[k];
			}
			f[i][j]=res;
		}
	}
	while(m--){
		int u=(read()+ans-1)%n+1,v=(read()+ans-1)%n+1;
		if(u>v)swap(u,v);ans=0;
		int l=(u-1)/s+1,r=(v-1)/s+1;
		if(r-l<=1){
			for(int i=u;i<=v;i++)t[a[i]]++;
			for(int i=u;i<=v;i++){
				if(t[a[i]]>t[ans])ans=a[i];
				if(t[a[i]]==t[ans]&&ans>a[i])ans=a[i];
			}
			for(int i=u;i<=v;i++)t[a[i]]--;
		}
		else{
			for(int i=u;i<=min(n,s*l);i++)t[a[i]]++;
			for(int i=s*(r-1)+1;i<=v;i++)t[a[i]]++;
			ans=f[l+1][r-1];
			for(int i=u;i<=min(n,s*l);i++){
				if(t[a[i]]+sum[r-1][a[i]]-sum[l][a[i]]>t[ans]+sum[r-1][ans]-sum[l][ans])ans=a[i];
				if(t[a[i]]+sum[r-1][a[i]]-sum[l][a[i]]==t[ans]+sum[r-1][ans]-sum[l][ans]&&ans>a[i])ans=a[i];
			}
			for(int i=s*(r-1)+1;i<=v;i++){
				if(t[a[i]]+sum[r-1][a[i]]-sum[l][a[i]]>t[ans]+sum[r-1][ans]-sum[l][ans])ans=a[i];
				if(t[a[i]]+sum[r-1][a[i]]-sum[l][a[i]]==t[ans]+sum[r-1][ans]-sum[l][ans]&&ans>a[i])ans=a[i];
			}
			for(int i=u;i<=min(n,s*l);i++)t[a[i]]--;
			for(int i=s*(r-1)+1;i<=v;i++)t[a[i]]--;
		}
		ans=b[ans];
		printf("%lld\n",ans);
	}
	
}
