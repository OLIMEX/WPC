using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace WPCWeek48
{
    public class Point
    {
        private int x;
        private int y;
        private string name;

        public Point()
        {
            x = 0;
            y = 0;
            name = "";
        }

        public int X
        {
            get { return x;}
            set { this.x = value; }
        }

        public int Y
        {
            get { return y; }
            set { this.y = value; }
        }

        public string Name
        {
            get { return name; }
            set { this.name = value; }
        }
    }
}