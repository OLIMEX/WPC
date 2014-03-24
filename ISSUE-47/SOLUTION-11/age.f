      program age_diff
      implicit none

      integer d1(3), d2(3), d3(3)
      integer argc, iargc, ydiff, mdiff, ddiff, diff, i
      character*20 arg, date1, date2
      logical check_validity
      integer date2days, days_in_month

      argc = iargc()
      if(argc .ne. 2) then
         call getarg(0, arg)
         write(6, *), 'usage: ' // arg // 'date1 date2'
         write(6, *), 'dates are expected as yyyymmdd'
         goto 100
      endif

      call getarg(1, date1)
      read(date1, '(i4i2i2)', err = 100) d1(1), d1(2), d1(3)
      call getarg(2, date2)
      read(date2, '(i4i2i2)', err = 100) d2(1), d2(2), d2(3)
      if((check_validity(d1(1), d1(2), d1(3)) .eqv. .false.) .or.
     +   (check_validity(d2(1), d2(2), d2(3)) .eqv. .false.)) then
         goto 100
      endif

      diff = date2days(d1(1), d1(2), d1(3)) -
     +       date2days(d2(1), d2(2), d2(3))
      if(diff .eq. 0) then
         write(6, *) 'the dates are the same'
         goto 100
      else if(diff .lt. 0) then
         do i = 1, 3
            d3(i) = d1(i)
            d1(i) = d2(i)
            d2(i) = d3(i)
         enddo
      endif
      ydiff = d1(1) - d2(1)
      if(d1(2) .ge. d2(2)) then
         mdiff = d1(2) - d2(2)
      else
         ydiff = ydiff - 1
         mdiff = 12 + d1(2) - d2(2)
      endif
      if(d1(3) .ge. d2(3)) then
         ddiff = d1(3) - d2(3)
      else
         mdiff = mdiff - 1
         if(mdiff .lt. 0) then
            mdiff = 11
            ydiff = ydiff - 1
         endif
         if(d1(2) .eq. 1) d1(2) = 12
         ddiff = days_in_month(d1(2) - 1, d2(1)) +
     +           d1(3) - d2(3)
      endif
      write(6, '(i4, "/", i2, "/", i2,
     +      " is older than ", i4, "/", i2, "/", i2, " by")'),
     +      d2(1), d2(2), d2(3), d1(1), d1(2), d1(3)
      write(6, '(i4, " years, ", i2, " months, and ", i2, " days")'),
     +      ydiff, mdiff, ddiff
  100 continue
      end program


      integer function days_in_year(y)
      implicit none
      integer y

      if((mod(y, 4) .eq. 0) .and. (mod(y, 100) .ne. 0)) then
         days_in_year = 366
      else
         days_in_year = 365
      endif
      return
      end function

      integer function days_in_month(m, y)
      implicit none
      integer m, y, days_in_year

      select case(m)
      case(1)
         days_in_month = 31
      case(2)
         if(days_in_year(y) .eq. 365) then
            days_in_month = 28
         else
            days_in_month = 29
         endif
      case(3)
         days_in_month = 31
      case(4)
         days_in_month = 30
      case(5)
         days_in_month = 31
      case(6)
         days_in_month = 30
      case(7)
         days_in_month = 31
      case(8)
         days_in_month = 31
      case(9)
         days_in_month = 30
      case(10)
         days_in_month = 31
      case(11)
         days_in_month = 30
      case(12)
         days_in_month = 31
      end select
      return
      end function


      integer function date2days(y, m, d)
      implicit none
      integer y, m, d, i, days_in_year, days_in_month

      date2days = d
      do i = 0, y - 1, 1
         date2days = date2days + days_in_year(i)
      enddo
      do i = 0, m - 1, 1
         date2days = date2days + days_in_month(i, y)
      enddo
      end function

      logical function check_validity(y, m, d)
      implicit none
      integer y, m, d, days_in_month
      if((m .lt. 1) .or. (m .gt. 12)) then
         write(6, *) 'invalid month ', m
         check_validity = .false.
         return
      endif
      if((d .lt. 1) .or. (d .gt. days_in_month(m, y))) then
         write(6, *) 'invalid day ', d
         check_validity = .false.
         return
      endif
      check_validity = .true.
      return
      end function
