      program braille
      implicit none

      integer iargc, ichar, strlen, i, j, k, argc, pos, decade
      integer l
      parameter(l = 40)
      character argv*(l), out1*(l*6), out2*(l*6), out3*(l*6)
      character*2 line1(11), line2(11), line3(4)
      out1 = ''
      out2 = ''
      out3 = ''

c                aku   blv   cmx   dny   eoz   fp    gq    hr    is
      data line1/'* ', '* ', '**', '**', '* ', '**', '**', '* ', ' *'
c                jt w
     >         , ' *', '  '/
      data line2/'  ', '* ', '  ', ' *', ' *', '* ', '**', '**', '* '
     >         , '**', '  '/
      data line3/'  ', '* ', '**', ' *'/

      argc = iargc()
      j = 1
      do k = 1, argc
         call getarg(k, argv)
         do i = 1, strlen(argv)
            if((argv(i:i) .ge. 'a') .and.
     +         (argv(i:i) .le. 'z')) then !lowercase
               pos = mod((ichar(argv(i:i)) - ichar('a')), 10) + 1
               decade = (ichar(argv(i:i)) - ichar('a')) / 10 + 1
            else if((argv(i:i) .ge. 'A') .and.
     +              (argv(i:i) .le. 'Z')) then !uppercase
               out3(j:j+1) = line3(4)
               j = j + 3
               pos = mod((ichar(argv(i:i)) - ichar('A')), 10) + 1
               decade = (ichar(argv(i:i)) - ichar('A')) / 10 + 1
            endif

            if((argv(i:i) .ge. 'a') .and.
     +        (argv(i:i) .le. 'v')) then
               continue
            else if((argv(i:i) .ge. 'A') .and.
     +        (argv(i:i) .le. 'V')) then
               continue

            else if((argv(i:i) .ge. 'x') .and.
     +        (argv(i:i) .le. 'z')) then
               pos = pos - 1
            else if((argv(i:i) .ge. 'X') .and.
     +        (argv(i:i) .le. 'Z')) then
               pos = pos - 1

            else if((argv(i:i) .eq. 'w') .or.
     +              (argv(i:i) .eq. 'W')) then
               pos = 10
               decade = 4
            else ! unkown - leave blank
               pos = 11
               decade = 1
            endif
            out1(j:j+1) = line1(pos)
            out2(j:j+1) = line2(pos)
            out3(j:j+1) = line3(decade)
            j = j + 3
         enddo
         j = j + 3
      enddo
      write(6, '(a(l))') out1
      write(6, '(a(l))') out2
      write(6, '(a(l))') out3
      end

      integer function strlen(str)
      character str*(*)
      integer i

      do i = len(str), 1, -1
         if(str(i:i) .ne. ' ') goto 100
      enddo
  100 continue
      strlen = i
      end
