# week61.py

a=[str(i) for i in ("1"," ","2"," ","3"," ","4"," ","5"," ","6"," ","7"," ","8"," ","9")]

counter=0
print("solutions week#61")
operands=["+","-"," "]
for i0 in operands:
	for i1 in operands:
		for i2 in operands:
			for i3 in operands:
				for i4 in operands:
					for i5 in operands:
						for i6 in operands:
							for i7 in operands:
								a[1]=i7
								a[3]=i6
								a[5]=i5
								a[7]=i4
								a[9]=i3
								a[11]=i2
								a[13]=i1
								a[15]=i0
								b="".join(a).replace(" ","")
								res=eval(b)
								if res==100:
									print b
								counter+=1
								#print b
#print counter

