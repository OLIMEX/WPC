#
# Olimex WPC #39
#
# Calculate a CRC-16 checksum
#
# Note: Assuming LSB first for serial communication
# 

# A table to hold a precalculated value for every byte
table = Uint16[0 for i = 1:256]

# The polynomal to be used
polynomal = uint16(0xa001)

#
# Fill the table with precalculated values
#
function table_init()
	for index::Uint8 = 0:255
        temp = uint16(0)
        word = uint16(index)
		for j = 1:8
			if ((temp $ word) & 0x001) == 1
				temp = (temp >> 1) $ polynomal
			else
				temp = temp >> 1 
			end
			word = word >> 1
		end
		table[index + 1] = temp
	end
end

#
# Update the CRC value with the next byte
#
function update_crc(next_byte, crc_16)
    word = uint16(next_byte)
    temp = uint8(crc_16 $ word)
    return (crc_16 >>> 8) $ table[temp + 1]
end

#
# Test the CRC routine for a number of test values
#

testvalues = [(b"ABCDEFG", 0x9E6C),
		      (b"0123456789", 0x443D),
		      (b"Olimex!", 0x0A05)]

function test()
    table_init()
	println()
	for (input, expected) in testvalues
		crc_16::Uint16 = 0
		for byte in input
			crc_16 = update_crc(byte, crc_16)
    	end
		@assert crc_16 == expected
    	println("Input: \"", ascii(input), "\"\t CRC = ", crc_16)
	end
	println()
end

test()

