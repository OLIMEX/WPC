problem='123456789';
results={};
%We can either add '+', '-', or '' (nothing) between
%two numbers. Therefore, there is 3^8 possible cases.
for i=0:3^8-1
    n=dec2base(i,3,8); % produce the basis 3 numbers with 8 digits
%     disp(n)
    tempstr='';
    for j=1:8
        switch n(j)
            case {'0'}
                str='';
            case {'1'}
                str='+';
            case {'2'}
                str='-';
        end
        tempstr=[tempstr,problem(j),str];
    end
    tempstr=[tempstr,'9'];
%     disp(tempstr)
    if eval(tempstr)==100 %Check the condtion
        results{end+1,1}=tempstr;
    end
end
disp(results) % display the results