
namespace WPC35_Maze
{
    public class Square
    {
        public Point CurrentSquare { get; set; }
        public Point PreviousSquare { get; set; }
        public int SquareCounter { get; set; }

        public Square(int x, int y)
        {
            CurrentSquare = new Point(x, y);
        }

        public Square(Square donor)
        {
            this.CurrentSquare = new Point(donor.CurrentSquare.X, donor.CurrentSquare.Y);
            this.PreviousSquare = new Point(donor.PreviousSquare.X, donor.PreviousSquare.Y);
            this.SquareCounter = donor.SquareCounter;
        }
    }
}
