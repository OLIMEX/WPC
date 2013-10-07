using System;
using System.Windows.Forms;
using System.Windows.Forms.DataVisualization.Charting;

namespace WPC27___AngryBirds
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
            SetupGraph();
        }

        /// <summary>
        /// Using the input parameters, calculate the x,y coordinates for points along the trajectory
        /// and plot them on the graph
        /// </summary>
        private void CalculateAndDrawGraph()
        {
            // Calculate the Y positions
            double x = 0;
            double y = 0;

            // Read the input parameters from the UI form
            double angle = (double)(udAngle.Value) * Math.PI / 180;
            double initialForce = (double)udForce.Value;
            double initialForceDuration = (double)udInitialForceDuration.Value;
            double mass = (double)udMass.Value;
            double drag = (double)udDrag.Value;
            int maxPoints = (int)udMaxPoints.Value;

            // Initial velocity is calculated using from initial force and duration using Newton's law
            double velocity = (initialForce / mass) * initialForceDuration;
            double vx = velocity * Math.Cos(angle);     // velocity component in the horizontal direction
            double vy = velocity * Math.Sin(angle);     // velocity component in the vertical direction

            // Acceleration components
            double ax = 0;
            double ay = 0;

            // Gravity
            double g = 9.81;

            // Keeps track of time
            double t = 0;
            double tDelta = 0.05;        // Time interval (s) for calculating point positions

            // Failsafe to ensure we exit the iterative calculation loop
            int noOfPoints = 0;

            // Remove previous points from the graph
            chart1.Series[0].Points.Clear();

            do
            {
                // Plot the current point
                DataPoint pt = new DataPoint(x, y);
                chart1.Series[0].Points.Add(pt);

                // Calculate the acceleration components
                ax = -(drag / mass) * velocity * vx;
                ay = -g - (drag / mass) * velocity * vy;

                // Calculate the new velocity components
                vx = vx + ax * tDelta;
                vy = vy + ay * tDelta;

                // Calculate the new trajectory position
                x = x + (vx * tDelta) + (ax * tDelta * tDelta) / 2;
                y = y + (vy * tDelta) + (ay * tDelta * tDelta) / 2;

                // Increment the time
                t = t + tDelta;

                // Limit to a maximum number of points
                noOfPoints++;
            }
            while (noOfPoints < maxPoints && y >= 0);

            // Tell the user how many iterations we took.
            lblPoints.Text = noOfPoints.ToString();
        }

        /// <summary>
        /// Setup the static parts of the graph
        /// </summary>
        private void SetupGraph()
        {
            // Main chart
            chart1.Enabled = false;
            chart1.Titles.Add("WPC27 - Angry Birds");
            chart1.Legends.Clear();
            chart1.Series.Add("Projectile");

            ChartArea ca = chart1.ChartAreas[0];

            // X axis
            ca.AxisX.Minimum = 0;
            ca.AxisX.Maximum = 150;
            ca.AxisX.MajorTickMark.Enabled = false;
            ca.AxisX.Title = "Distance (m)";

            // Y axis
            ca.AxisY.Minimum = 0;
            ca.AxisY.Maximum = 50;
            ca.AxisY.MajorTickMark.Enabled = false;
            ca.AxisY.Title = "Height (m)";
        }

        /// <summary>
        /// When an input parametr is changed, recalculate and draw the graph.
        /// </summary>
        /// <param name="sender">Ignored</param>
        /// <param name="e">Ignored</param>
        private void ValueChanged(object sender, EventArgs e)
        {
            CalculateAndDrawGraph();
        }
    }
}
