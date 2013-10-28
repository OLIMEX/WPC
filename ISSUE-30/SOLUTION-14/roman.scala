package number

object roman {
  val pairs = List((1000, "M"), (900, "CM"), (500, "D"), (400, "CD"), (100, "C"), (90, "XC"), (50, "L"), (40, "XL"), (10, "X"), (9, "IX"), (5, "V"), (4, "IV"), (1, "I"))

  def convert(num: Int, pos: List[(Int, String)] = pairs): String = {
    if (num == 0) ""
    else if (num >= pos.head._1) pos.head._2 + convert(num - pos.head._1, pos)
    else convert(num, pos.tail)
  }
}