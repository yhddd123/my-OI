#include<bits/stdc++.h>
#define ll long long
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
using namespace std;
inline int read(){
	int x=0,fl=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')fl=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*fl;
}
const int maxn=2010;
bool mbe;

int n,m;ll ans;
char s[maxn];
int a[maxn][maxn];
int pl[maxn][maxn],pr[maxn][maxn],pu[maxn][maxn],pd[maxn][maxn];
int sum[maxn][maxn],vl[maxn][maxn],vr[maxn][maxn];
void sovle(int l1,int r1,int l2,int r2){
	if(l1==r1||l2==r2)return ;
	if(r1-l1<r2-l2){
		int mid=(l2+r2)>>1;
		for(int i=l1;i<=r1;i++){
			for(int j=max(l2,pl[i][mid]);j<=mid;j++)sum[i][max(pu[i][j],l1)]++;
			for(int j=l1+1;j<=r1;j++)sum[i][j]+=sum[i][j-1];
		}
		for(int i=l1;i<=r1;i++){
			for(int j=i+1;j<=r1;j++)if(pl[i][mid]<=pl[j][mid])vl[i][j]=sum[j][i];
		}
		for(int i=l1;i<=r1;i++)for(int j=l1;j<=r1;j++)sum[i][j]=0;
		for(int i=l1;i<=r1;i++){
			for(int j=mid+1;j<=min(r2,pr[i][mid+1]);j++)sum[i][max(pu[i][j],l1)]++;
			for(int j=l1+1;j<=r1;j++)sum[i][j]+=sum[i][j-1];
		}
		for(int i=l1;i<=r1;i++){
			for(int j=i+1;j<=r1;j++)if(pr[i][mid+1]>=pr[j][mid+1])vr[i][j]=sum[j][i];
		}
		for(int i=l1;i<=r1;i++)for(int j=l1;j<=r1;j++)sum[i][j]=0;
		for(int i=l1;i<=r1;i++){
			for(int j=max(l2,pl[i][mid]);j<=mid;j++)sum[i][min(pd[i][j],r1)]++;
			for(int j=r1-1;j>=l1;j--)sum[i][j]+=sum[i][j+1];
		}
		for(int i=l1;i<=r1;i++){
			for(int j=i+1;j<=r1;j++)if(pl[i][mid]>=pl[j][mid])vl[i][j]=sum[i][j];
		}
		for(int i=l1;i<=r1;i++)for(int j=l1;j<=r1;j++)sum[i][j]=0;
		for(int i=l1;i<=r1;i++){
			for(int j=mid+1;j<=min(r2,pr[i][mid+1]);j++)sum[i][min(pd[i][j],r1)]++;
			for(int j=r1-1;j>=l1;j--)sum[i][j]+=sum[i][j+1];
		}
		for(int i=l1;i<=r1;i++){
			for(int j=i+1;j<=r1;j++)if(pr[i][mid+1]<=pr[j][mid+1])vr[i][j]=sum[i][j];
		}
		for(int i=l1;i<=r1;i++)for(int j=l1;j<=r1;j++)sum[i][j]=0;
		for(int i=l1;i<=r1;i++){
			for(int j=i+1;j<=r1;j++)if(a[i][mid]==a[i][mid+1]&&a[j][mid]==a[j][mid+1]){
				// cout<<i<<" "<<j<<" "<<vl[i][j]<<" "<<vr[i][j]<<"\n";
				ans+=1ll*vl[i][j]*vr[i][j];
			}
		}
		for(int i=l1;i<=r1;i++)for(int j=i+1;j<=r1;j++)vl[i][j]=vr[i][j]=0;
		// cout<<l1<<" "<<r1<<" "<<l2<<" "<<r2<<" "<<ans<<"\n";
		sovle(l1,r1,l2,mid),sovle(l1,r1,mid+1,r2);
	}
	else{
		int mid=(l1+r1)>>1;
		for(int i=l2;i<=r2;i++){
			for(int j=max(l1,pu[mid][i]);j<=mid;j++)sum[i][max(pl[j][i],l2)]++;
			for(int j=l2+1;j<=r2;j++)sum[i][j]+=sum[i][j-1];
		}
		for(int i=l2;i<=r2;i++){
			for(int j=i+1;j<=r2;j++)if(pu[mid][i]<=pu[mid][j])vl[i][j]=sum[j][i];
		}
		for(int i=l2;i<=r2;i++)for(int j=l2;j<=r2;j++)sum[i][j]=0;
		for(int i=l2;i<=r2;i++){
			for(int j=mid+1;j<=min(r1,pd[mid+1][i]);j++)sum[i][max(pl[j][i],l2)]++;
			for(int j=l2+1;j<=r2;j++)sum[i][j]+=sum[i][j-1];
		}
		for(int i=l2;i<=r2;i++){
			for(int j=i+1;j<=r2;j++)if(pd[mid+1][i]>=pd[mid+1][j])vr[i][j]=sum[j][i];
		}
		for(int i=l2;i<=r2;i++)for(int j=l2;j<=r2;j++)sum[i][j]=0;
		for(int i=l2;i<=r2;i++){
			for(int j=max(l1,pu[mid][i]);j<=mid;j++)sum[i][min(pr[j][i],r2)]++;
			for(int j=r2-1;j>=l2;j--)sum[i][j]+=sum[i][j+1];
		}
		for(int i=l2;i<=r2;i++){
			for(int j=i+1;j<=r2;j++)if(pu[mid][i]>=pu[mid][j])vl[i][j]=sum[i][j];
		}
		for(int i=l2;i<=r2;i++)for(int j=l2;j<=r2;j++)sum[i][j]=0;
		for(int i=l2;i<=r2;i++){
			for(int j=mid+1;j<=min(r1,pd[mid+1][i]);j++)sum[i][min(pr[j][i],r2)]++;
			for(int j=r2-1;j>=l2;j--)sum[i][j]+=sum[i][j+1];
		}
		for(int i=l2;i<=r2;i++){
			for(int j=i+1;j<=r2;j++)if(pd[mid+1][i]<=pd[mid+1][j])vr[i][j]=sum[i][j];
		}
		for(int i=l2;i<=r2;i++)for(int j=l2;j<=r2;j++)sum[i][j]=0;
		for(int i=l2;i<=r2;i++){
			for(int j=i+1;j<=r2;j++)if(a[mid][i]==a[mid+1][i]&&a[mid][j]==a[mid+1][j]){
				// cout<<i<<" "<<j<<" "<<vl[i][j]<<" "<<vr[i][j]<<"\n";
				ans+=1ll*vl[i][j]*vr[i][j];
			}
		}
		for(int i=l2;i<=r2;i++)for(int j=i+1;j<=r2;j++)vl[i][j]=vr[i][j]=0;
		// cout<<l1<<" "<<r1<<" "<<l2<<" "<<r2<<" "<<ans<<"\n";
		sovle(l1,mid,l2,r2),sovle(mid+1,r1,l2,r2);
	}
}
void work(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++){
		scanf("%s",s+1);
		for(int j=1;j<=m;j++)a[i][j]=s[j]-'a'+1;
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++)pl[i][j]=(a[i][j]==a[i][j-1]?pl[i][j-1]:j);
		for(int j=m;j;j--)pr[i][j]=(a[i][j]==a[i][j+1]?pr[i][j+1]:j);
	}
	for(int j=1;j<=m;j++){
		for(int i=1;i<=n;i++)pu[i][j]=(a[i][j]==a[i-1][j]?pu[i-1][j]:i);
		for(int i=n;i;i--)pd[i][j]=(a[i][j]==a[i+1][j]?pd[i+1][j]:i);
	}
	sovle(1,n,1,m);
	printf("%lld\n",ans);
}

bool med;
int T;
signed main(){
	// freopen("countcircle.in","r",stdin);
	// freopen("countcircle.out","w",stdout);
	
	// cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
	
	T=1;
	while(T--)work();
}