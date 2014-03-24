This is a solution using Excel which makes it pretty simple.  OK it's not traditional coding but it does the job well.

Given two dates, date1 and date2, the formulae for calculating the days, months and years are:

Days	=IF(date1>date2,DATEDIF(date2,date1,"md"),DATEDIF(date1,date2,"md"))
Months	=IF(date1>date2,DATEDIF(date2,date1,"ym"),DATEDIF(date1,date2,"ym"))
Years	=IF(date1>date2,DATEDIF(date2,date1,"y"),DATEDIF(date1,date2,"y"))

The screenshot shows some example calculations.
