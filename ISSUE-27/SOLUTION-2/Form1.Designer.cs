namespace WPC27___AngryBirds
{
    partial class Form1
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            System.Windows.Forms.DataVisualization.Charting.ChartArea chartArea1 = new System.Windows.Forms.DataVisualization.Charting.ChartArea();
            System.Windows.Forms.DataVisualization.Charting.Series series1 = new System.Windows.Forms.DataVisualization.Charting.Series();
            this.chart1 = new System.Windows.Forms.DataVisualization.Charting.Chart();
            this.label2 = new System.Windows.Forms.Label();
            this.lblPoints = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.udAngle = new System.Windows.Forms.NumericUpDown();
            this.label3 = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.udMass = new System.Windows.Forms.NumericUpDown();
            this.udDrag = new System.Windows.Forms.NumericUpDown();
            this.label6 = new System.Windows.Forms.Label();
            this.udMaxPoints = new System.Windows.Forms.NumericUpDown();
            this.label7 = new System.Windows.Forms.Label();
            this.udForce = new System.Windows.Forms.NumericUpDown();
            this.label8 = new System.Windows.Forms.Label();
            this.udInitialForceDuration = new System.Windows.Forms.NumericUpDown();
            ((System.ComponentModel.ISupportInitialize)(this.chart1)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.udAngle)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.udMass)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.udDrag)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.udMaxPoints)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.udForce)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.udInitialForceDuration)).BeginInit();
            this.SuspendLayout();
            // 
            // chart1
            // 
            this.chart1.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            chartArea1.Name = "ChartArea1";
            this.chart1.ChartAreas.Add(chartArea1);
            this.chart1.Location = new System.Drawing.Point(210, 7);
            this.chart1.Name = "chart1";
            series1.ChartArea = "ChartArea1";
            series1.ChartType = System.Windows.Forms.DataVisualization.Charting.SeriesChartType.Line;
            series1.IsVisibleInLegend = false;
            series1.Name = "Series1";
            series1.SmartLabelStyle.Enabled = false;
            this.chart1.Series.Add(series1);
            this.chart1.Size = new System.Drawing.Size(485, 334);
            this.chart1.TabIndex = 0;
            this.chart1.Text = "chart1";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(9, 9);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(134, 13);
            this.label2.TabIndex = 6;
            this.label2.Text = "Angle at launch (degrees) :";
            // 
            // lblPoints
            // 
            this.lblPoints.AutoSize = true;
            this.lblPoints.Location = new System.Drawing.Point(146, 173);
            this.lblPoints.Name = "lblPoints";
            this.lblPoints.Size = new System.Drawing.Size(13, 13);
            this.lblPoints.TabIndex = 7;
            this.lblPoints.Text = "0";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(9, 173);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(129, 13);
            this.label4.TabIndex = 8;
            this.label4.Text = "No of points in the graph :";
            // 
            // udAngle
            // 
            this.udAngle.Location = new System.Drawing.Point(149, 7);
            this.udAngle.Maximum = new decimal(new int[] {
            90,
            0,
            0,
            0});
            this.udAngle.Name = "udAngle";
            this.udAngle.Size = new System.Drawing.Size(47, 20);
            this.udAngle.TabIndex = 9;
            this.udAngle.Value = new decimal(new int[] {
            45,
            0,
            0,
            0});
            this.udAngle.ValueChanged += new System.EventHandler(this.ValueChanged);
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(9, 87);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(32, 13);
            this.label3.TabIndex = 11;
            this.label3.Text = "Mass";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(9, 113);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(30, 13);
            this.label5.TabIndex = 13;
            this.label5.Text = "Drag";
            // 
            // udMass
            // 
            this.udMass.DecimalPlaces = 3;
            this.udMass.Increment = new decimal(new int[] {
            2,
            0,
            0,
            131072});
            this.udMass.Location = new System.Drawing.Point(149, 85);
            this.udMass.Maximum = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.udMass.Name = "udMass";
            this.udMass.Size = new System.Drawing.Size(47, 20);
            this.udMass.TabIndex = 14;
            this.udMass.Value = new decimal(new int[] {
            1,
            0,
            0,
            65536});
            this.udMass.ValueChanged += new System.EventHandler(this.ValueChanged);
            // 
            // udDrag
            // 
            this.udDrag.DecimalPlaces = 5;
            this.udDrag.Increment = new decimal(new int[] {
            1,
            0,
            0,
            262144});
            this.udDrag.Location = new System.Drawing.Point(125, 111);
            this.udDrag.Maximum = new decimal(new int[] {
            1,
            0,
            0,
            131072});
            this.udDrag.Name = "udDrag";
            this.udDrag.Size = new System.Drawing.Size(71, 20);
            this.udDrag.TabIndex = 15;
            this.udDrag.Value = new decimal(new int[] {
            13,
            0,
            0,
            262144});
            this.udDrag.ValueChanged += new System.EventHandler(this.ValueChanged);
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(9, 139);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(114, 13);
            this.label6.TabIndex = 16;
            this.label6.Text = "Max number of points :";
            // 
            // udMaxPoints
            // 
            this.udMaxPoints.Increment = new decimal(new int[] {
            10,
            0,
            0,
            0});
            this.udMaxPoints.Location = new System.Drawing.Point(149, 137);
            this.udMaxPoints.Maximum = new decimal(new int[] {
            1000,
            0,
            0,
            0});
            this.udMaxPoints.Name = "udMaxPoints";
            this.udMaxPoints.Size = new System.Drawing.Size(47, 20);
            this.udMaxPoints.TabIndex = 17;
            this.udMaxPoints.Value = new decimal(new int[] {
            500,
            0,
            0,
            0});
            this.udMaxPoints.ValueChanged += new System.EventHandler(this.ValueChanged);
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(9, 35);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(64, 13);
            this.label7.TabIndex = 18;
            this.label7.Text = "Initial force :";
            // 
            // udForce
            // 
            this.udForce.Location = new System.Drawing.Point(149, 33);
            this.udForce.Maximum = new decimal(new int[] {
            250,
            0,
            0,
            0});
            this.udForce.Name = "udForce";
            this.udForce.Size = new System.Drawing.Size(47, 20);
            this.udForce.TabIndex = 19;
            this.udForce.Value = new decimal(new int[] {
            10,
            0,
            0,
            0});
            this.udForce.ValueChanged += new System.EventHandler(this.ValueChanged);
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Location = new System.Drawing.Point(9, 61);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(118, 13);
            this.label8.TabIndex = 20;
            this.label8.Text = "Duration of initial force :";
            // 
            // udInitialForceDuration
            // 
            this.udInitialForceDuration.DecimalPlaces = 1;
            this.udInitialForceDuration.Increment = new decimal(new int[] {
            1,
            0,
            0,
            65536});
            this.udInitialForceDuration.Location = new System.Drawing.Point(149, 59);
            this.udInitialForceDuration.Maximum = new decimal(new int[] {
            5,
            0,
            0,
            0});
            this.udInitialForceDuration.Name = "udInitialForceDuration";
            this.udInitialForceDuration.Size = new System.Drawing.Size(47, 20);
            this.udInitialForceDuration.TabIndex = 21;
            this.udInitialForceDuration.Value = new decimal(new int[] {
            5,
            0,
            0,
            65536});
            this.udInitialForceDuration.ValueChanged += new System.EventHandler(this.ValueChanged);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(707, 353);
            this.Controls.Add(this.udInitialForceDuration);
            this.Controls.Add(this.label8);
            this.Controls.Add(this.udForce);
            this.Controls.Add(this.label7);
            this.Controls.Add(this.udMaxPoints);
            this.Controls.Add(this.label6);
            this.Controls.Add(this.udDrag);
            this.Controls.Add(this.udMass);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.udAngle);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.lblPoints);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.chart1);
            this.Name = "Form1";
            this.Text = "WPC27 - Angry Birds";
            ((System.ComponentModel.ISupportInitialize)(this.chart1)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.udAngle)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.udMass)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.udDrag)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.udMaxPoints)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.udForce)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.udInitialForceDuration)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.DataVisualization.Charting.Chart chart1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label lblPoints;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.NumericUpDown udAngle;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.NumericUpDown udMass;
        private System.Windows.Forms.NumericUpDown udDrag;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.NumericUpDown udMaxPoints;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.NumericUpDown udForce;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.NumericUpDown udInitialForceDuration;
    }
}

