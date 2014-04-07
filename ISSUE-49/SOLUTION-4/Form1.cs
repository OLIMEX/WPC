using System;
using System.Windows.Forms;

namespace WPC49_EasterDateCalculator
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        /// <summary>
        /// Handles the UI button click to calculate Easter Sunday dates.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void btnCalculate_Click(object sender, EventArgs e)
        {
            int year;
            if (int.TryParse(txtYear.Text, out year))
            {
                rtb.Text = Calculate.EasterDates(year, (int)ud.Value);
            }
            else
            {
                rtb.Text = "Invalid year";
            }
        }
    }
}
