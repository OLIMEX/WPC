using System;
using System.Diagnostics;
using System.Windows.Forms;

namespace WPC41_Speed_Typing_Test
{
    /// <summary>
    /// Make code which displays text, then measures how fast and correct one would enter this 
    /// test via the keyboard. You can display random text from online book or dictionary. 
    /// It’s up to you how to make the user interface, make something funny and interesting.
    /// </summary>
    public partial class Form1 : Form
    {
        private Logic logic;
        private Stopwatch stopwatch;
        private int backspaceKeyCount;

        public Form1()
        {
            InitializeComponent();
            logic = new Logic();
            stopwatch = new Stopwatch();
        }

        /// <summary>
        /// Loads the text in the selected text file.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void Form1_Load(object sender, EventArgs e)
        {
            rtbTextPassage.Text = logic.LoadText();
        }

        /// <summary>
        /// Get a short passage of words to test the user's typing.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void btnGetTest_Click(object sender, EventArgs e)
        {
            rtbTypedText.Clear();
            rtbMeasurementText.Text = logic.GetTestText(udNoOfWords.Value, rtbTextPassage.Text);
        }

        /// <summary>
        /// Restarts the typing test.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void btnClear_Click(object sender, EventArgs e)
        {
            rtbTypedText.Clear();
            lblTimeTaken.Text = string.Empty;
            lblAccuracy.Text = string.Empty;
            pbAccuracy.Value = 0;
            lblTimeForTextPassage.Text = string.Empty;
        }

        /// <summary>
        /// Starts the typing test as soon as they type the first letter into the textbox,
        /// and ends the test when the user hits the Enter key.  Updates the display with
        /// results.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void rtbTypedText_KeyDown(object sender, KeyEventArgs e)
        {
            // Check whether the user has started typing for the speed measurement test.
            // If so, start a stopwatch so we can measure the duration it takes.
            if (rtbTypedText.Text.Length == 0)
            {
                stopwatch.Reset();
                stopwatch.Start();
                backspaceKeyCount = 0;
                return;
            }

            // Has the user hit the Enter key to signify the end of the typing test?
            if (e.KeyCode == Keys.Enter)
            {
                stopwatch.Stop();

                // Display the time taken to type the short passage
                double secondsTaken = (double)(stopwatch.ElapsedMilliseconds) / 1000;
                lblTimeTaken.Text = secondsTaken.ToString("0.0");

                // Display how many words per minute this represents.
                lblWPM.Text = logic.CalculateWordsPerMinute(secondsTaken, udNoOfWords.Value).ToString();

                // Calculate and display how accurate it is.
                decimal accuracy = logic.MeasureAccuracy(
                    rtbMeasurementText.Text, 
                    rtbTypedText.Text, 
                    backspaceKeyCount);

                lblAccuracy.Text = accuracy.ToString("0.0");
                pbAccuracy.Value = (int)accuracy;

                // Update the time the passage would take to type.
                TimeSpan duration = logic.CalculateTimeToTypeTextPassage(
                    rtbTextPassage.TextLength, 
                    rtbMeasurementText.TextLength,
                    secondsTaken);

                string timeForPassage;
                if (duration.Hours == 0)
                    timeForPassage = string.Format("{0} mins {1} secs", duration.Minutes, duration.Seconds);
                else
                    timeForPassage = string.Format("{0} hrs {1} mins {2} secs", duration.Hours, duration.Minutes, duration.Seconds);
                lblTimeForTextPassage.Text = timeForPassage;
            }
            else if (e.KeyCode == Keys.Back)
            {
                // The user has hit the Backspace key to correct their text so it's a 
                // black mark each time they do so.
                backspaceKeyCount++;
            }
        }
    }
}
