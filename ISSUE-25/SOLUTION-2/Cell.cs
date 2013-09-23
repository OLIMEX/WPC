
namespace WPC25_EqualTravelPaths
{
    public class Cell
    {
        public Point CurrentCell { get; set; }
        public Point PreviousCell { get; set; }
        public int MoveCount { get; set; }

        public Cell() { }
        public Cell(Cell donor)
        {
            this.CurrentCell = new Point(donor.CurrentCell.X, donor.CurrentCell.Y);
            this.PreviousCell = new Point(donor.PreviousCell.X, donor.PreviousCell.Y);
            this.MoveCount = donor.MoveCount;
        }
    }
}
