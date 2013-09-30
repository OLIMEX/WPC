package com.olimex.wpc

import Week26._

object TryWeek26 {

  val square = new Quadrilateral(List(
    new Point(0, 0),
    new Point(0, 1),
    new Point(1, 1),
    new Point(1, 0)))                             //> square  : com.olimex.wpc.Week26.Quadrilateral = Quadrilateral(List(Point(0,0
                                                  //| ), Point(0,1), Point(1,1), Point(1,0)))
  val notAlignedSquare = new Quadrilateral(List(
    new Point(0, 0),
    new Point(2, 1),
    new Point(3, -1),
    new Point(1, -2)))                            //> notAlignedSquare  : com.olimex.wpc.Week26.Quadrilateral = Quadrilateral(List
                                                  //| (Point(0,0), Point(2,1), Point(3,-1), Point(1,-2)))
  val notOrderedSquare = new Quadrilateral(List(
    new Point(0, 0),
    new Point(1, 1),
    new Point(0, 1),
    new Point(1, 0)))                             //> notOrderedSquare  : com.olimex.wpc.Week26.Quadrilateral = Quadrilateral(List
                                                  //| (Point(0,0), Point(1,1), Point(0,1), Point(1,0)))
  val rectangle = new Quadrilateral(List(
    new Point(0, 0),
    new Point(0, 2),
    new Point(3, 2),
    new Point(3, 0)))                             //> rectangle  : com.olimex.wpc.Week26.Quadrilateral = Quadrilateral(List(Point(
                                                  //| 0,0), Point(0,2), Point(3,2), Point(3,0)))
  val rhombus = new Quadrilateral(List(
    new Point(0, 0),
    new Point(3, 4),
    new Point(8, 4),
    new Point(5, 0)))                             //> rhombus  : com.olimex.wpc.Week26.Quadrilateral = Quadrilateral(List(Point(0,
                                                  //| 0), Point(3,4), Point(8,4), Point(5,0)))

  val threePointsSame = new Quadrilateral(List(
    new Point(0, 0),
    new Point(0, 0),
    new Point(1, 1),
    new Point(0, 0)))                             //> threePointsSame  : com.olimex.wpc.Week26.Quadrilateral = Quadrilateral(List(
                                                  //| Point(0,0), Point(0,0), Point(1,1), Point(0,0)))

  val twoPointsSame = new Quadrilateral(List(
    new Point(0, 0),
    new Point(0, 0),
    new Point(1, 0),
    new Point(0, 1)))                             //> twoPointsSame  : com.olimex.wpc.Week26.Quadrilateral = Quadrilateral(List(Po
                                                  //| int(0,0), Point(0,0), Point(1,0), Point(0,1)))

  square.isSquare                                 //> res0: Boolean = true
  square.isOrdered                                //> res1: Boolean = true
  square.isAligned                                //> res2: Boolean = true

  notAlignedSquare.isSquare                       //> res3: Boolean = true
  notAlignedSquare.isOrdered                      //> res4: Boolean = true
  notAlignedSquare.isAligned                      //> res5: Boolean = false

  notOrderedSquare.isSquare                       //> res6: Boolean = true
  notOrderedSquare.isOrdered                      //> res7: Boolean = false
  notOrderedSquare.isAligned                      //> res8: Boolean = true

  rectangle.isSquare                              //> res9: Boolean = false

  rhombus.isSquare                                //> res10: Boolean = false

  threePointsSame.isSquare                        //> res11: Boolean = false
  twoPointsSame.isSquare                          //> res12: Boolean = false

}