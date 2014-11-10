<?php

/***********************************************************************
* As the number of missing consecutive pages is an even number (9808), *
* there should be an even number of odd pages. This starts with 3 and  *
* increments by 4 every time (3, 7, 11, 15, ....).                     *
* As in principle more than one solution is possible, we have to check *
* up to 9808/3=3269.                                                   *
* We have a fitting solution if 9808/no is an integer value.           *
* 9808/no is the middle one of the missing pages.                      *
* First one = Middle one - (no-1)/2.                                   *
* However it is possible that we also have an even number of even      *
* numbers. In this case our loop starts at 4 and increments also by 4. *
* Unfortunately we don't have a middle page now. That is why we have   *
* to add 0.5 in the formulas now.                                      *
***********************************************************************/

echo "<HTML><HEAD><TITLE>Missing pages</TITLE></HEAD>";
echo "<BODY><H1>Missing pages of book</H1>";

for($no=3;$no<3270;$no+=4)
{
    if((9808/$no)==floor(9808/$no))
    {
        $first = (9808/$no) - (($no-1)/2);
        echo "No of missing pages: ".$no."<BR><BR>";
        echo "The missing pages: ";
        for($x=0;$x<$no;$x++)
        {
            echo ($first+$x).", ";
        };
        echo "<HR>";
    };
};
for($no=4;$no<3270;$no+=4)
{
    if((9808/$no)==(floor(9808/$no) + 0.5))
    {
        $first = (9808/$no) + 0.5 - ($no/2);
        echo "No of missing pages: ".$no."<BR><BR>";
        echo "The missing pages: ";
        for($x=0;$x<$no;$x++)
        {
            echo ($first+$x).", ";
        };
        echo "<HR>";
    };
};
echo "</BODY></HTML>";
?> 
