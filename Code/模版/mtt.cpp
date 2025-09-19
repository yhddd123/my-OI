namespace mtt{
int _mod=mod;
struct cp{
	db a,b;
	cp(db u=0,db v=0){a=u,b=v;}
	cp operator+(const cp&tmp)const{return {a+tmp.a,b+tmp.b};}
	cp operator-(const cp&tmp)const{return {a-tmp.a,b-tmp.b};}
	cp operator*(const cp&tmp)const{return {a*tmp.a-b*tmp.b,a*tmp.b+b*tmp.a};}
};
const db pi=acos(-1);
int to[maxn<<3];
void fft(vector<cp> &a,int flag){
	int n=a.size();
	for(int i=0;i<n;i++)if(i<to[i])swap(a[i],a[to[i]]);
	for(int l=2;l<=n;l<<=1){
		cp bas=cp(cos(2*pi/l),flag*sin(2*pi/l));
		int k=l>>1;
		for(int i=0;i<n;i+=l){
			cp mul=cp(1,0);
			for(int j=i;j<i+k;j++){
				cp val=mul*a[j+k];
				a[j+k]=a[j]-val,a[j]=a[j]+val;
				mul=mul*bas;
			}
		}
	}
	if(flag==-1){
		for(int i=0;i<n;i++)a[i].a/=n,a[i].b/=n;
	}
}
const int B=(1<<15)-1;
int calc(db x){return (long long)(x+0.5)%_mod;}
vector<int> mul(vector<int> a,vector<int> b){
	int n=a.size()-1,m=b.size()-1,k=1;
	while(k<n+m+1)k<<=1;
	for(int i=0;i<k;i++)to[i]=(to[i>>1]>>1)|((i&1)?(k>>1):0);
	vector<cp> f(k),g(k),h(k);
	for(int i=0;i<=n;i++)f[i]=cp(a[i]&B,0),g[i]=cp(a[i]>>15,0);
	for(int i=0;i<=m;i++)h[i]=cp(b[i]&B,b[i]>>15);
	fft(f,1),fft(g,1),fft(h,1);
	for(int i=0;i<k;i++)f[i]=f[i]*h[i],g[i]=g[i]*h[i];
	fft(f,-1),fft(g,-1);
	vector<int> ans(n+m+1);
	for(int i=0;i<=n+m;i++)ans[i]=(1ll*calc(f[i].a)+(1ll*(calc(f[i].b)+calc(g[i].a))<<15ll)%_mod+(1ll*calc(g[i].b)<<30ll)%_mod)%_mod;
	return ans;
}
}