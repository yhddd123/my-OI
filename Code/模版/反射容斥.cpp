int calc(int n,int m,int l,int r){
	// cout<<n<<" "<<m<<" "<<l<<" "<<r<<endl;
	if(l>=0||r<=0)return 0;
	if(n+l>=m||n+r<=m)return 0;
	if(l==r)return 0;
	int res=0;
	for(int k=-(m+r-l-1)/(r-l);k<=n/(r-l);k++)(res+=C(n+m,n-k*(r-l)))%=mod;
	for(int k=-(m-r+r-l-1)/(r-l);k<=(n+r)/(r-l);k++)(res+=mod-C(n+m,n-k*(r-l)+r))%=mod;
	return res%mod;
}