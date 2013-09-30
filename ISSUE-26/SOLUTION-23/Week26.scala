package com.olimex.wpc

object Week26 {

  /*
   * Four points represent a square if the 6 segments you can draw between each pair of them are:
   * - 4 equal edges
   * - 2 equal diagonals
   * 
   *  P4      P3
   *   o------o      edge1: P1-P2
   *   |\    /|      edge2: P2-P3
   *   | \  / |      edge3: P3-P4
   *   |  \/  |      edge4: P4-P1
   *   |  /\  |      diagonal1: P1-P3
   *   | /  \ |      diagonal2: P2-P4
   *   |/    \|
   *   o------o
   *  P1      P2
   * 
   * If they are ordered (P1, P2, P3, P4) and you consider the segments P1-P2, P2-P3, P3-P4,
   * P4-P1, P1-P3, P2-P4, you'll find the 4 edges, than the 2 diagonals.
   * If they are unordered (ie P1, P3, P4, P2) you'll find at least a diagonal before the last edge.
   * 
   * If you scan the lengths of the 6 segments, in a square you'll find only 2 different values:
   * the smaller one is the edge, the bigger is the diagonal.
   * 
   * If you find at least 3 different values, it is not a square.
   * If you have at least 3 equal points, there are two values, but the smaller is 0.
   *
   * To test if a square is aligned to the x and y-axis, you must test if an edge is aligned.
   * If it has unordered points, the first segment could be a diagonal, so you must test if 
   * at least one of the first two segments is aligned.
   * 
   * The solution is calculated lazily: only the needed values are calculated (i.e.: 
   * if the first three segments have all different lengths, there's no need to calculate
   * the others, since surely it is not a square).
   * 
   * For the lengths of the 6 segments I'm using the squared values, not to calculate a
   * square root; this has some advantages:
   * - it does not waste time in useless calculations (only sums and multiplications)
   * - you can use integer values
   * - you can easily compare an edge and a diagonal, since the latter is twofold the former
   *   in a square (and you are still using integer arithmetic)
   */

  type Coord = Int // integer coordinates, but they could be double

  case class Point(x: Coord, y: Coord) {
    def squaredDistance(p: Point): Coord = square(p.x - x) + square(p.y - y)
      
    def square(a: Coord) = a * a
  }

  abstract class SquareOrNotSquare

  case object NotSquare extends SquareOrNotSquare

  case class Square(aligned: Boolean, ordered: Boolean) extends SquareOrNotSquare

  case class Quadrilateral(p: Seq[Point]) {
    require(p.length == 4) // must be a quadrilateral

    // a Stream, so that it calculates only the needed values
    lazy val segmentsLength: Stream[Coord] = Stream(p(0).squaredDistance(p(1)),
      p(1).squaredDistance(p(2)),
      p(2).squaredDistance(p(3)),
      p(3).squaredDistance(p(0)),
      p(0).squaredDistance(p(2)),
      p(1).squaredDistance(p(3)))

    def sameXorSameY(p1: Point, p2: Point): Boolean = (p1.x == p2.x) || (p1.y == p2.y)

    lazy val isSquare: Boolean = whatAmI match {
      case Square(aligned, ordered) => true
      case NotSquare => false
    }

    lazy val isOrdered: Boolean = whatAmI match {
      case Square(aligned, ordered) => ordered
      case NotSquare => false
    }

    // it uses recursion not to have vars
    // but a non recursive version with vars would be probably faster
    lazy val whatAmI: SquareOrNotSquare = {

      def solve(lengths: Stream[Coord], edge: Coord, diag: Coord, edgesBeforeFirstDiag: Int): SquareOrNotSquare = {
        if (lengths.isEmpty) { // all 6 edges evaluated
          if (edge > 0)
            new Square(isAligned, edgesBeforeFirstDiag == 4)
          else // if the edge is 0, there are at least three points which are the same point
            NotSquare
        } else {
          if (edge == diag) { // no diagonal found yet
            if (lengths.head == edge) // another edge found
              solve(lengths.tail, edge, diag, edgesBeforeFirstDiag + 1)
            else if (lengths.head < edge) { // the first edge was a diagonal instead
              solve(lengths.tail, lengths.head, edge, 0)
            } else // first diagonal found
              solve(lengths.tail, edge, lengths.head, edgesBeforeFirstDiag)
          } else if (lengths.head != edge && lengths.head != diag)
            NotSquare
          else
            solve(lengths.tail, edge, diag, edgesBeforeFirstDiag)
        }
      }

      solve(segmentsLength.tail, segmentsLength.head, segmentsLength.head, 1)
    }

    // if it's a square, one of the first two segments is an edge
    lazy val isAligned = sameXorSameY(p(0), p(1)) || sameXorSameY(p(1), p(2))

  }

}

