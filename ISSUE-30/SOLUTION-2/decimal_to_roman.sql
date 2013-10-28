--
-- Convert a decimal number to roman numerals 
-- as a Microsoft Transact-SQL user defined function
-- 
create function decimal_to_roman (@decimal_input integer)
returns varchar(max)
as
begin

if @decimal_input <= 0
  begin
    return 'Error: input must be greater than 0'
  end

declare @lookup table
(
  decimal_value int,
  string_value varchar(2)
)

insert into @lookup values (1,'I')
insert into @lookup values (4,'IV')
insert into @lookup values (5,'V')
insert into @lookup values (9,'IX')
insert into @lookup values (10,'X')
insert into @lookup values (40,'XL')
insert into @lookup values (50,'L')
insert into @lookup values (90,'XC')
insert into @lookup values (100,'C')
insert into @lookup values (400,'CD')
insert into @lookup values (500,'D')
insert into @lookup values (900,'CM')
insert into @lookup values (1000,'M')

declare @lookup_decimal integer
declare @lookup_roman varchar(2)
declare @roman_output varchar(max)

set @roman_output = ''

while @decimal_input > 0
  begin
        select top 1
               @lookup_roman = l.string_value,
               @lookup_decimal = l.decimal_value
          from @lookup l
         where l.decimal_value <= @decimal_input
         order by l.decimal_value desc

        set @decimal_input = @decimal_input - @lookup_decimal
        set @roman_output = @roman_output + @lookup_roman
 end

return @roman_output

end
