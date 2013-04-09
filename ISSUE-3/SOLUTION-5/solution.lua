#!/usr/bin/lua

--[[
-- OLIMEX WEEKEND PROGRAMMING CHALLENGE ISSUE #3
-- author: Hanspeter <ventosus> Portner
-- language: Lua, compatible with Lua5.1, Lua5.2 and LuaJIT2.0.1
--]]

-- read input from stdin and store it in table words
local words = {} -- table of strings to match

for l in io.lines()  do
     if l ~= '<end>' then
         words[#words+1] = l -- fill table
     end
end

-- iterator to get next substring of string
local function next_substring(str, cache)
     return coroutine.wrap(function()
         local win, pos

         for win = 1, #str do -- substring window length
             for pos = 1, #str-win+1 do -- substring position
                 local sub = string.sub(str, pos, pos+win-1) -- substring with given window and position
                 if not cache[sub] then -- only consider non-cached substrings
                     coroutine.yield(sub) -- return substring
                 end
             end
         end
     end)
end

-- main loop
local cache = {} -- table of already checked substrings, which turned 
out to be non-unique
--setmetatable(cache, {.mode='k'}) -- if short on memory, make this a 
table with weak keys, so it can be gargabe collected

for i, v in ipairs(words) do -- loop over strings in input
     for sub in next_substring(v, cache) do -- loop over substrings
         local match = nil -- initialize flag to mark a match

         for j, w in ipairs(words) do -- loop over paired string in input
             if i ~= j then -- skip self
                 match = string.find(w, sub) -- look for substring in paired string
                 if match then
                     cache[sub] = true -- cache this substring
                     break -- exit inner loop when match was found
                 end
             end
         end

         if not match then print(v .. ' -> ' .. sub) break end -- there was no match -> print result
     end
end