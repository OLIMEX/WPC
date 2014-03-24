namespace DateDiff
{
	partial class MainForm
	{
		private System.ComponentModel.IContainer components = null;
		
		protected override void Dispose(bool disposing)
		{
			if (disposing) {
				if (components != null) {
					components.Dispose();
				}
			}
			base.Dispose(disposing);
		}
		
		private void InitializeComponent()
		{
			this.label1 = new System.Windows.Forms.Label();
			this.label2 = new System.Windows.Forms.Label();
			this.dateTimePicker1 = new System.Windows.Forms.DateTimePicker();
			this.dateTimePicker2 = new System.Windows.Forms.DateTimePicker();
			this.label3 = new System.Windows.Forms.Label();
			this.resultLabel = new System.Windows.Forms.Label();
			this.SuspendLayout();

			this.label1.Location = new System.Drawing.Point(49, 16);
			this.label1.Name = "label1";
			this.label1.Size = new System.Drawing.Size(100, 23);
			this.label1.TabIndex = 0;
			this.label1.Text = "Date 1:";

			this.label2.Location = new System.Drawing.Point(49, 46);
			this.label2.Name = "label2";
			this.label2.Size = new System.Drawing.Size(100, 23);
			this.label2.TabIndex = 1;
			this.label2.Text = "Date 2:";

			this.dateTimePicker1.Format = System.Windows.Forms.DateTimePickerFormat.Short;
			this.dateTimePicker1.Location = new System.Drawing.Point(105, 12);
			this.dateTimePicker1.Name = "dateTimePicker1";
			this.dateTimePicker1.Size = new System.Drawing.Size(110, 20);
			this.dateTimePicker1.TabIndex = 2;
			this.dateTimePicker1.ValueChanged += new System.EventHandler(this.DateTimePickerValueChanged);

			this.dateTimePicker2.Format = System.Windows.Forms.DateTimePickerFormat.Short;
			this.dateTimePicker2.Location = new System.Drawing.Point(105, 42);
			this.dateTimePicker2.Name = "dateTimePicker2";
			this.dateTimePicker2.Size = new System.Drawing.Size(110, 20);
			this.dateTimePicker2.TabIndex = 3;
			this.dateTimePicker2.ValueChanged += new System.EventHandler(this.DateTimePickerValueChanged);

			this.label3.Location = new System.Drawing.Point(19, 85);
			this.label3.Name = "label3";
			this.label3.Size = new System.Drawing.Size(63, 23);
			this.label3.TabIndex = 4;
			this.label3.Text = "Difference:";

			this.resultLabel.Location = new System.Drawing.Point(85, 85);
			this.resultLabel.Name = "resultLabel";
			this.resultLabel.Size = new System.Drawing.Size(225, 23);
			this.resultLabel.TabIndex = 0;
			this.resultLabel.Text = "---";

			this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size(320, 120);
			this.Controls.Add(this.resultLabel);
			this.Controls.Add(this.label3);
			this.Controls.Add(this.dateTimePicker2);
			this.Controls.Add(this.dateTimePicker1);
			this.Controls.Add(this.label2);
			this.Controls.Add(this.label1);
			this.Name = "MainForm";
			this.Text = "DateDiff";
			this.ResumeLayout(false);
		}
		private System.Windows.Forms.Label resultLabel;
		private System.Windows.Forms.Label label3;
		private System.Windows.Forms.DateTimePicker dateTimePicker2;
		private System.Windows.Forms.DateTimePicker dateTimePicker1;
		private System.Windows.Forms.Label label2;
		private System.Windows.Forms.Label label1;
		
		
		void DateTimePickerValueChanged(object sender, System.EventArgs e)
		{
			UpdateDisplay();
		}
	}
}
