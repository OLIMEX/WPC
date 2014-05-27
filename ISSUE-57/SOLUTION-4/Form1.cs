using System;
using System.IO;
using System.Net;
using System.Windows.Forms;

namespace WPC57_TextToHtmlRatioCalculator
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        /// <summary>
        /// Browse to a web page to get some HTML and show it in a text box.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void btnGo_Click(object sender, EventArgs e)
        {
            WebClient request = new WebClient();

            Stream response = request.OpenRead(txtUrl.Text);
            StreamReader sr = new StreamReader(response);
            string responseHtml = sr.ReadToEnd();

            rtb.Text = responseHtml;
        }

        /// <summary>
        /// Analyze the html in the text box.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void btnAnalyze_Click(object sender, EventArgs e)
        {
            if (rtb.Text.Trim().Length == 0)
            {
                return;
            }

            HtmlAnalyzer analyzer = new HtmlAnalyzer(rtb.Text);

            txtTextToHtmlRatio.Text = string.Format("{0:0.000}%", analyzer.TextToHtmlRatio);
            txtTextToTotalPercentage.Text = string.Format("{0:0.000}%", analyzer.TextToTotalPercentage);
            txtHtmlToTotalPercentage.Text = string.Format("{0:0.000}%", analyzer.HtmlToTotalPercentage);
            txtTotalChars.Text = analyzer.TotalChars.ToString();

            rtbText.Text = analyzer.Text;
        }
    }
}
