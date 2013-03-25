// Compute the distance between a point and a line
// Command-line usage: scala Program.scala Ax Ay Bx By Cx Cy 
// Author: Emiliano Daddario
// Scala 2.9.2 required
// This is __INTENTIONALLY__ overcomplicated and long because it's a programming exercise.
// I can write it far shorter. I'm not stupid!
import scala.collection.mutable.ArrayBuffer
import scala.annotation.tailrec
object Program {
  class Point(x: java.lang.Double, y: java.lang.Double) extends java.awt.geom.Point2D.Double(x, y) {
    override def toString = "(" + x + ", " + y + ")"
    def getDistanceFrom(point: Point) =
      math.sqrt(math.pow(this.x - point.x, 2) + math.pow(this.y - point.y, 2))
    def getDistanceFrom(line: Tuple2[Point, Point]): Double = {
      val a = line._1
      val b = line._2
      val d = a getDistanceFrom b
      val denominator = if (d != 0) d else 1
      val matrix = new Matrix(None, ArrayBuffer(
        ArrayBuffer(a.x, a.y, 1),
        ArrayBuffer(b.x, b.y, 1),
        ArrayBuffer(this.x, this.y, 1)))
      determinant(matrix)
      math.abs(matrix.determinant) / denominator
    }
  }
  implicit def matrixToArrayBuffer(matrix: Matrix): ArrayBuffer[ArrayBuffer[Double]] = matrix.array
  class Matrix(val parent: Option[Matrix], val array: ArrayBuffer[ArrayBuffer[Double]]) {
    var determinant: Double = 0d
    var j: Int = 0
  }
  @tailrec def determinant(matrix: Matrix) {
    val order = matrix.length
    if (order == 1)
      matrix.determinant = matrix(0)(0)
    if (matrix.j == order || order == 1) {
      matrix.parent match {
        case Some(parent) => {
          val sign = if (parent.j % 2 == 0) 1 else -1
          parent.determinant += sign * parent(0)(parent.j) * matrix.determinant
          parent.j += 1
          determinant(parent)
        }
        case _ => // return
      }
    } else {
      determinant(getSubMatrix(matrix))
    }
  }
  def getSubMatrix(parent: Matrix) = new Matrix(Some(parent), parent.tail.map(row => row.-(row(parent.j))))
  def main(args: Array[String]) {
    def getArg(i: Int) = java.lang.Double parseDouble args(i)
    if (args.length != 6) {
      println("Six numbers please!")
      sys.exit(1)
    }
    val ab = (new Point(getArg(0), getArg(1)), new Point(getArg(2), getArg(3)))
    val c = new Point(getArg(4), getArg(5))
    println("A = " + ab._1)
    println("B = " + ab._2)
    println("C = " + c)
    val distance = c getDistanceFrom ab
    println("Distance between C and line AB = " + distance)
  }
}