if arg[1] == nil then
	print("Specify stair len.");
	os.exit();
end;
len = tonumber(arg[1]);
stairWays = setmetatable({},{
	__index = function(self, index)
		if index < 3 then
			return 1;
		else
			return self[index - 1] + self[index - 2];
		end;
	end;
});
print("Ways num: ",stairWays[len]);
