# sys.set_int_max_str_digits(4010);
T=int(input())
for t in range(T):
	n=int(input())
	x=n
	l=0
	while(x):
		x=x//10
		l=l+1
	v=0
	for i in range(l):
		v=v*10+1
	fl=0
	for i in range(1,10):
		a=v*i;
		if(a>=n):
			continue
		b=n-a
		x=b
		val=x%10
		ck=1
		while(x):
			if(x%10!=val):
				ck=0
				break
			x=x//10
		if(ck):
			print(a,b)
			fl=1
			break
	if(fl):
		continue
	v=0
	for i in range(l-1):
		v=v*10+1;
	fl=0
	for i in range(1,10):
		a=v*i;
		if(a>=n):
			continue
		b=n-a
		# print(a,b)
		ck=1
		x=b
		val=x%10
		while(x):
			if(x%10!=val):
				ck=0
				break
			x=x//10
		if(ck):
			print(a,b)
			fl=1
			break