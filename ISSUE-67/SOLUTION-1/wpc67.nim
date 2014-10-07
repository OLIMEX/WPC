for i in countup(1,9807):
  var sum = 0
  var j = i
  while sum < 9808:
    sum = sum + j
    if sum == 9808:
      echo("Missing pages: ", $i, " until ", $j)
    j = j + 1