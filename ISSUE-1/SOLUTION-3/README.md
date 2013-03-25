' Input point coordinates

write "-- Point A --" & vbCrLf

Do
  write " x-> "
  intAX = getInt()
Loop While intAX = False

Do
  write " y-> "
  intAY = getInt()
Loop While intAY = False

write vbCrLf
write "-- Point B --" & vbCrLf

Do
  write " x-> "
  intBX = getInt()
Loop While intBX = False

Do
  write " y-> "
  intBY = getInt()
Loop While intBY = False

write vbCrLf
write "-- Point C --" & vbCrLf

Do
  write " x-> "
  intCX = getInt()
Loop While intCX = False

Do
  write " y-> "
  intCY = getInt()
Loop While intCY = False


' Implicit form of a line: ax + by + c
' line through two points: (ay - by)x + (bx - ax)y + ay(ax - bx) + ax(by - ay)

line_a = intAY - intBY
line_b = intBX - intAX
line_c = intAY * (intAX - intBX) + intAX * (intBY - intAY)

' distance from a point to a line: |a * cx + b * cy + c| / sqrt(a^2 + b^2)
distance = Abs(line_a * intCX + line_b * intCY + line_c) / Sqr(line_a * line_a + line_b * line_b)

write vbCrLf
write "Distance -> "
write distance


' Sub to write a string to standard output

Sub write(string)
  WScript.StdOut.Write(string)
End Sub


' Function to read an integer value from the standard input

Function getInt()

  value = WScript.StdIn.ReadLine()

  If checkInt(value) Then
    getInt = value
  Else
    write " enter an integer value!" & vbCrLf
    getInt = False
  End If

End Function


' Function to check if a string is an integer value

Function checkInt(value)

  If IsNumeric(value) Then
    If CStr(CLng(value)) = value Then
      checkInt = True
    Else
      checkInt = False
    End If
  Else
    checkInt = False
  End If

End Function
