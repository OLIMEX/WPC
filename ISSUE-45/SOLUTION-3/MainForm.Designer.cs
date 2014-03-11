namespace median
{
	partial class MainForm
	{
		/// <summary>
		/// Designer variable used to keep track of non-visual components.
		/// </summary>
		private System.ComponentModel.IContainer components = null;
		
		/// <summary>
		/// Disposes resources used by the form.
		/// </summary>
		/// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
		protected override void Dispose(bool disposing)
		{
			if (disposing) {
				if (components != null) {
					components.Dispose();
				}
			}
			base.Dispose(disposing);
		}
		
		/// <summary>
		/// This method is required for Windows Forms designer support.
		/// Do not change the method contents inside the source code editor. The Forms designer might
		/// not be able to load this method if it was changed manually.
		/// </summary>
		private void InitializeComponent()
		{
			System.Windows.Forms.DataVisualization.Charting.ChartArea chartArea1 = new System.Windows.Forms.DataVisualization.Charting.ChartArea();
			System.Windows.Forms.DataVisualization.Charting.Series series1 = new System.Windows.Forms.DataVisualization.Charting.Series();
			System.Windows.Forms.DataVisualization.Charting.DataPoint dataPoint1 = new System.Windows.Forms.DataVisualization.Charting.DataPoint(1D, 1D);
			System.Windows.Forms.DataVisualization.Charting.DataPoint dataPoint2 = new System.Windows.Forms.DataVisualization.Charting.DataPoint(2D, 2D);
			System.Windows.Forms.DataVisualization.Charting.Series series2 = new System.Windows.Forms.DataVisualization.Charting.Series();
			this.MedianChart = new System.Windows.Forms.DataVisualization.Charting.Chart();
			this.windowUpDown = new System.Windows.Forms.NumericUpDown();
			this.label1 = new System.Windows.Forms.Label();
			this.windowTrackBar = new System.Windows.Forms.TrackBar();
			((System.ComponentModel.ISupportInitialize)(this.MedianChart)).BeginInit();
			((System.ComponentModel.ISupportInitialize)(this.windowUpDown)).BeginInit();
			((System.ComponentModel.ISupportInitialize)(this.windowTrackBar)).BeginInit();
			this.SuspendLayout();
			// 
			// MedianChart
			// 
			chartArea1.AxisX.Interval = 100D;
			chartArea1.AxisX.IntervalType = System.Windows.Forms.DataVisualization.Charting.DateTimeIntervalType.Number;
			chartArea1.AxisX.Minimum = 0D;
			chartArea1.Name = "MedianChartArea";
			this.MedianChart.ChartAreas.Add(chartArea1);
			this.MedianChart.Location = new System.Drawing.Point(13, 13);
			this.MedianChart.Name = "MedianChart";
			series1.ChartArea = "MedianChartArea";
			series1.ChartType = System.Windows.Forms.DataVisualization.Charting.SeriesChartType.Line;
			series1.Legend = "Legend1";
			series1.Name = "OriginalSeries";
			series1.Points.Add(dataPoint1);
			series1.Points.Add(dataPoint2);
			series2.ChartArea = "MedianChartArea";
			series2.ChartType = System.Windows.Forms.DataVisualization.Charting.SeriesChartType.Line;
			series2.Color = System.Drawing.Color.Red;
			series2.Name = "FilteredSeries";
			this.MedianChart.Series.Add(series1);
			this.MedianChart.Series.Add(series2);
			this.MedianChart.Size = new System.Drawing.Size(871, 627);
			this.MedianChart.TabIndex = 0;
			this.MedianChart.Text = "Median chart";
			// 
			// windowUpDown
			// 
			this.windowUpDown.Location = new System.Drawing.Point(115, 647);
			this.windowUpDown.Minimum = new decimal(new int[] {
									3,
									0,
									0,
									0});
			this.windowUpDown.Name = "windowUpDown";
			this.windowUpDown.Size = new System.Drawing.Size(82, 20);
			this.windowUpDown.TabIndex = 1;
			this.windowUpDown.Value = new decimal(new int[] {
									3,
									0,
									0,
									0});
			this.windowUpDown.ValueChanged += new System.EventHandler(this.WindowUpDownValueChanged);
			// 
			// label1
			// 
			this.label1.Location = new System.Drawing.Point(13, 647);
			this.label1.Name = "label1";
			this.label1.Size = new System.Drawing.Size(96, 20);
			this.label1.TabIndex = 2;
			this.label1.Text = "Median window";
			this.label1.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
			// 
			// windowTrackBar
			// 
			this.windowTrackBar.LargeChange = 10;
			this.windowTrackBar.Location = new System.Drawing.Point(227, 644);
			this.windowTrackBar.Maximum = 100;
			this.windowTrackBar.Minimum = 3;
			this.windowTrackBar.Name = "windowTrackBar";
			this.windowTrackBar.Size = new System.Drawing.Size(157, 42);
			this.windowTrackBar.TabIndex = 4;
			this.windowTrackBar.TickFrequency = 5;
			this.windowTrackBar.Value = 3;
			this.windowTrackBar.Scroll += new System.EventHandler(this.WindowTrackBarScroll);
			// 
			// MainForm
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size(896, 679);
			this.Controls.Add(this.windowTrackBar);
			this.Controls.Add(this.label1);
			this.Controls.Add(this.windowUpDown);
			this.Controls.Add(this.MedianChart);
			this.Name = "MainForm";
			this.Text = "median";
			this.Load += new System.EventHandler(this.MainFormLoad);
			((System.ComponentModel.ISupportInitialize)(this.MedianChart)).EndInit();
			((System.ComponentModel.ISupportInitialize)(this.windowUpDown)).EndInit();
			((System.ComponentModel.ISupportInitialize)(this.windowTrackBar)).EndInit();
			this.ResumeLayout(false);
			this.PerformLayout();
		}
		private System.Windows.Forms.TrackBar windowTrackBar;
		private System.Windows.Forms.Label label1;
		private System.Windows.Forms.NumericUpDown windowUpDown;
		private System.Windows.Forms.DataVisualization.Charting.Chart MedianChart;
	}
}
