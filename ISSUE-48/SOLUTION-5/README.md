This C# solution works the answer out by doing this:

1.  Translate all the points A, B and C to place point A at the origin of the plane.
2.  Rotate the points around point A (at the origin) such that point B is now on the x-axis.
3.  If the Y co-ordinate of all three points are 0, they're all on the same line.
4.  If the Y co-ordinate of point C is below the x-axis, the path A->B->C goes in a clockwise direction, otherwise it goes in an anti-clockwise direction.

Sample tests in the screenshot.

Nigel