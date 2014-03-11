using System;
using System.Collections.Generic;
using System.Drawing;
using System.Windows.Forms;
using System.Windows.Forms.DataVisualization.Charting;

namespace median
{
	public partial class MainForm : Form
	{		
		public MainForm()
		{
			InitializeComponent();			
		}
		
		/// <summary>
		/// Load and display the original measurements
		/// </summary>
		void MainFormLoad(object sender, EventArgs e)
		{
			Series original = MedianChart.Series["OriginalSeries"];
			original.Points.Clear();
		
			for (int x=0; x < DataClass.OriginalValues.Count; x++)
			{
				original.Points.Add(new DataPoint(x, DataClass.OriginalValues[x]));
			}
			
			UpdateMedian((int)windowUpDown.Value);
		}
		
		/// <summary>
		/// Calculate and display the filtered measurements
		/// </summary>		
		private void UpdateMedian(int windowSize)
		{
			DataClass.Filter(windowSize);
			
			Series filtered = MedianChart.Series["FilteredSeries"];
			filtered.Points.Clear();
			
			for (int x=0; x < DataClass.FilteredValues.Count; x++)
			{
				filtered.Points.Add(new DataPoint(x, DataClass.FilteredValues[x]));
			}					
		}
				
		void WindowUpDownValueChanged(object sender, EventArgs e)
		{
			windowTrackBar.Value = (int)windowUpDown.Value;
			UpdateMedian((int)windowUpDown.Value);
		}
		
		void WindowTrackBarScroll(object sender, EventArgs e)
		{
			windowUpDown.Value = windowTrackBar.Value;
			UpdateMedian(windowTrackBar.Value);
		}
	}
}
