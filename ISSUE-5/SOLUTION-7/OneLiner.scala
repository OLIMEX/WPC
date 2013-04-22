import scalaz._; import Scalaz._; import effects._; import scala.math._

object M extends App{((l:Int,t:Int,N:Int)=>println(((N times((a:(Int,Int,Double))=>if(random*t/2d<=l/2d*sin(random*Pi/2d))(a._1+1,a._2+1,(a._1+1)/(a._2+1).toDouble)else(a._1+1,a._2,(a._1+1)/a._2.toDouble)).endo) apply (0,0,0d))._3*2d*l/t))apply(5,6,3408)}

// This is a "true" one-liner Scala program because it doesn't contain semicolons (apart from import statements).
// Monte Carlo simulation of Buffon's needle experiment with Lazzarini's input numbers (5, 6, 3408) to evaluate pi
// Author: Emiliano Daddario, 2013
// Instructions for Linux:
// Download Scalaz from http://repo1.maven.org/maven2/org/scalaz/scalaz-core_2.9.2/6.0.4/scalaz-core_2.9.2-6.0.4.jar
// Compile using scalac -classpath /path/to/scalaz-core_2.9.2-6.0.4.jar /path/to/OneLiner.scala
// Run using scala -classpath /path/to/scalaz-core_2.9.2-6.0.4.jar /path/to/OneLiner
// Here is a similar version, slightly expanded (but not that much :)
// Neither does this contain semicolons.
/*
object Main extends App {
  (
    (l: Int, t: Int, N: Int) =>
      println(
        ( (_: (Int, Int) ) match { case // boilerplate
          (n, h) => 2d * l * n / t / h
        } ) apply(
          ( N times (
            (_: (Int, Int) ) match { case // boilerplate
              (n, h) => if ( random * t / 2d <= l / 2d * sin( random * Pi / 2d ) ) (n + 1, h + 1) else (n + 1, h)
          } ).endo ) apply( Tuple2(0, 0) )
        )
      )
  ) apply(5, 6, 3408)
}
*/
