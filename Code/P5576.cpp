#include<bits/stdc++.h>
#define pii pair<int,int>
#define mems(x,y) memset(x,y,sizeof x)
using namespace std;
const int maxn=1000010; 
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}
bool Mbe;

int n,m;
string s[maxn];
int siz[maxn];
int len[maxn],lnk[maxn];
int p,cur;
int rt[maxn];
int a[maxn][2];
void insert(int c,int id){
	int nd=++cur;
	len[nd]=len[p]+1;
	while(p&&!a[p][c])a[p][c]=nd,p=lnk[p];
	if(!p){lnk[p=nd]=rt[id];return ;}
	int q=a[p][c];
	if(len[p]+1==len[q])lnk[nd]=q;
	else{
		int cl=++cur;
		len[cl]=len[p]+1;lnk[cl]=lnk[q];
		a[cl][0]=a[q][0],a[cl][1]=a[q][1];
		lnk[nd]=lnk[q]=cl;
		while(p&&a[p][c]==q)a[p][c]=cl,p=lnk[p];
	}
	p=nd;
}
void go(int &p,int c,int &l){
	while(1){
		if(a[p][c]){
			p=a[p][c],l++;
			break;
		}
		if(!l)break;
		l--;
		if(l==len[lnk[p]])p=lnk[p];
	}
}
struct ask{
	int l,r;
}qq[maxn];
int id[maxn],ans[maxn],tmp[maxn];
int _sl[maxn],*sl[maxn],*sum;
void sovle(int l,int r,int ql,int qr,int lim){
	if(ql>qr)return ;
	int tot=0;
	while(1){
		for(int i=l;i<=r;i++)if(siz[i]<=lim)tmp[++tot]=i;
		if(tot)break;
		lim<<=1;
	}
	int mid=tmp[1+tot>>1],qmid=ql-1;
	sum=_sl;
	for(int i=l;i<=r;i++){
		sl[i]=sum;
		sum+=siz[mid]+1;
	}
	for(int j=0;j<siz[mid];j++)sl[mid][j]=j+1;
//	cout<<l<<" "<<r<<" "<<mid<<" a\n";
	for(int i=mid+1;i<=r;i++){
		int p=rt[i],d=0;
		for(int j=0;j<siz[mid];j++){
			int c=s[mid][j]-'0';
			go(p,c,d);
			sl[i][j]=min(sl[i-1][j],d);
//			cout<<i<<" "<<j<<" "<<d<<"\n";
		}
	}
	for(int i=mid-1;i>=l;i--){
		int p=rt[i],d=0;
		for(int j=0;j<siz[mid];j++){
			int c=s[mid][j]-'0';
			go(p,c,d);
			sl[i][j]=min(sl[i+1][j],d);
		}
	}
	int tr=0;
	for(int i=ql;i<=qr;i++){
		int u=id[i];
		if(qq[u].r<mid)id[++qmid]=u;
		else if(qq[u].l>mid)tmp[++tr]=u;
		else{
			for(int j=0;j<siz[mid];j++)ans[u]=max(ans[u],min(sl[qq[u].l][j],sl[qq[u].r][j]));
		}
	}
	for(int i=1;i<=tr;i++)id[qmid+i]=tmp[i];
	qr=qmid+tr;
	sovle(l,mid-1,ql,qmid,lim);sovle(mid+1,r,qmid+1,qr,lim);
}
void work(){
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		cin>>s[i];siz[i]=s[i].size();
		rt[i]=p=++cur;
		for(auto j:s[i])insert(j-'0',i);
	}
	for(int i=1;i<=m;i++){
		cin>>qq[i].l>>qq[i].r;
		id[i]=i;
	}
	sovle(1,n,1,m,10);
	for(int i=1;i<=m;i++)cout<<ans[i]<<"\n";
}

// \
444

bool Med;
int T;
signed main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	
//	cerr<<(&Mbe-&Med)/1048576.0<<" MB\n";
	
	T=1;
	while(T--)work();
}
