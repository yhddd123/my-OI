#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn=210;
const int inf=1e18;
inline int read(){
	int x=0,fl=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')fl=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+(ch-'0');ch=getchar();}
	return x*fl;
}

int m,n,num;
int a[maxn][maxn],s[maxn][maxn];
string c[maxn][maxn];
int len[maxn],lim[maxn],t[maxn];
map<string,int> mp,nam[maxn];
string rnk[maxn];
int p[maxn],b[maxn];
string ss,tt,res;

signed main(){
//	freopen("struct.in","r",stdin);
//	freopen("struct.out","w",stdout);
	m=read();
	mp["byte"]=++n;mp["short"]=++n;mp["int"]=++n;mp["long"]=++n;
	len[1]=lim[1]=1;len[2]=lim[2]=2;len[3]=lim[3]=4;len[4]=lim[4]=8;
	while(m--){
		int opt=read();
		if(opt==1){
			cin>>ss;mp[ss]=++n;
			t[n]=read();
			for(int i=1;i<=t[n];i++){
				cin>>ss>>tt;a[n][i]=mp[ss];
				nam[n][tt]=i;c[n][i]=tt;
				lim[n]=max(lim[n],lim[a[n][i]]);
			}
			for(int i=2;i<=t[n];i++){
				s[n][i]=(s[n][i-1]+len[a[n][i-1]]+lim[a[n][i]]-1)/lim[a[n][i]]*lim[a[n][i]];
			}
			len[n]=(s[n][t[n]]+len[a[n][t[n]]]+lim[n]-1)/lim[n]*lim[n];
			s[n][t[n]+1]=len[n];
			printf("%lld %lld\n",len[n],lim[n]);
		}
		if(opt==2){
			cin>>ss>>tt;mp[tt]=++num;
			b[num]=mp[ss];rnk[num]=tt;
			p[num]=(p[num-1]+len[b[num-1]]+lim[b[num]]-1)/lim[b[num]]*lim[b[num]];
			printf("%lld\n",p[num]);
		}
		if(opt==3){
			cin>>ss;
			int len=ss.size(),lst=0;
			int fl=0;int ans=0;
			for(int i=0;i<len;i++){
				if(ss[i]=='.'){
					tt=ss.substr(lst,i-lst);
					if(!fl){
						ans=p[mp[tt]];
						lst=i+1;fl=b[mp[tt]];
					}
					else{
						ans+=s[fl][nam[fl][tt]];
						lst=i+1;fl=a[fl][nam[fl][tt]];
					}
					// cout<<tt<<" "<<ans<<"\n";
				}
			}
			if(lst!=len){
				tt=ss.substr(lst,len-lst);
				// cout<<tt<<" ";
				if(!fl){
					ans=p[mp[tt]];
				}
				else{
					ans+=s[fl][nam[fl][tt]];
				}
			}
			printf("%lld\n",ans);
		}
		if(opt==4){
			int x=read();res="";
			p[num+1]=inf;
			int pos=upper_bound(p+1,p+num+2,x)-p-1;
			x-=p[pos];int u=b[pos];
			res+=rnk[pos];
			// cerr<<res<<" "<<pos<<"\n";
			while(1){
				if(!t[u]){
					if(len[u]<=x)res="ERR";
					break;
				}
				int pos=upper_bound(s[u]+1,s[u]+1+t[u]+1,x)-s[u]-1;
				x-=s[u][pos];res+='.';res+=c[u][pos];
				u=a[u][pos];
			}
			cout<<res<<"\n";
		}
	}
}
