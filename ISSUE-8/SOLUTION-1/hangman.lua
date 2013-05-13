#!/usr/bin/lua

--[[
-- OLIMEX WEEKEND PROGRAMMING CHALLENGE ISSUE #8
-- author: Hanspeter Portner
-- language: Lua
-- note 1: dictionary of possible words is expected to be in one file called 'all.words'
-- note 2: you can enable cheating and get the current word. This is only fair, as the program cheats too...
--]]

-- cheating = true -- uncomment to activate cheating

image = {
	"\n\n\n\n\n",
	"\n\n\n|\n|\n",
	"\n|    \n|\n|\n|\n",
	"______\n|    \n|\n|\n|\n",
	"______\n|    |\n|\n|\n|\n",
	"______\n|    |\n|    0\n|\n|\n",
	"______\n|    |\n|    0\n|    | \n| \n",
	"______\n|    |\n|    0\n|   /|\n|\n",
	"______\n|    |\n|    0\n|   /|\\\n|\n",
	"______\n|    |\n|    0\n|   /|\\\n|   /\n",
	"______\n|    |\n|    0\n|   /|\\\n|   / \\\n",
}

math.randomseed(os.time())

dict = {}
state = 1
guesses = {}

while #dict == 0 do -- let user choose word length and load the dictionary
	io.stdout:write("choose word length: ")
	local len = tonumber(io.stdin:read("*l"))
	f = io.input("all.words")
	for l in f:lines() do if #l == len then table.insert(dict, l) end end
	f:close()
end

check = function(char) -- checks a given char to stored guesses
	for _, v in ipairs(guesses) do if char == v then return v end end
	return '_'
end

reduce = function(char) -- this function reduces the dictionary of remaining words
	local sub = {}
	for _, v in ipairs(dict) do if not string.find(v, char) then table.insert(sub, v) end end
	dict = sub
	if #dict > 0 then word = dict[math.random(#dict)] end
end

word = dict[math.random(#dict)] -- choose random word
old = string.gsub(word, "(%a)", check) -- mask unkonwn chars

while true do
	io.stdout:write("\n"..image[state]) -- print hangman
	if state == #image then io.stdout:write("you loose, the word was: "..word.."\n"); break end -- you have lost
	if not string.find(old, '_') then io.stdout:write("you win\n"); break end -- you win
	if cheating then io.stdout:write("\n"..old.."("..word..")".." : ")
	else io.stdout:write("\n"..old.." : ") end -- print current masked word
	local guess = string.sub(io.stdin:read("*l"), 1, 1) -- read next guess
	if check(guess) ~= guess then -- check if guess already used
		table.insert(guesses, guess)
		reduce(guess) -- reduce table of possible solutions  and choose new random word (if possible)
		local new = string.gsub(word, "(%a)", check) -- mask unknown chars
		if old == new then state = state + 1 end -- one step nearer to hanging
		old = new
	else io.stdout:write(guess.." already used\n") end
end
