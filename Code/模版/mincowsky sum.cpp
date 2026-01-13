inline vector<int> operator*(const vector<int> &u,const vector<int> &v){
	if(!u.size())return v;
	if(!v.size())return u;
	int n=u.size()-1,m=v.size()-1;
	int p=0,q=0,t=0;
	while(p<=n&&u[p]==inf)p++;
	while(q<=m&&v[q]==inf)q++;
	if(p>n||q>m)return {inf};
	vector<int> res;
	res.reserve(n+m+1);
	for(int i=1;i<=p+q;i++)res.pb(inf);
	res.pb(u[p]+v[q]),p++,q++;
	while(p<=n&&q<=m){
		if(u[p]-u[p-1]<v[q]-v[q-1])res.pb(res.back()+u[p]-u[p-1]),p++;
		else res.pb(res.back()+v[q]-v[q-1]),q++;
	}
	while(p<=n)res.pb(res.back()+u[p]-u[p-1]),p++;
	while(q<=m)res.pb(res.back()+v[q]-v[q-1]),q++;
	return res;
}
vector<int> operator+(vector<int> u,vector<int> v){
	int n=u.size()-1,m=v.size()-1;
	vector<int> res(max(n,m)+1,inf);
	for(int i=0;i<=n;i++)res[i]=min(res[i],u[i]);
	for(int i=0;i<=m;i++)res[i]=min(res[i],v[i]);
	return res;
}