#!/bin/bash
#
# 2014-06-27 by kantal59 
# License: LGPL
# OLIMEX WPC#59: Big – Little Endians
# 			Make code which detects on what machine is ran – with Big or Little Endian. 
# 			Can you do it in other language than C?

# 	 		The lscpu command is part of the util-linux package.
lscpu|grep -i endian
