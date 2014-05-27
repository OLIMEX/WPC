using System.Text;

/// <summary>
/// Some people think text to HTML tags ratio on web page is important parameter 
/// for Google indexing and good sites should have about 20-30% ratio of pure 
/// text vs HTML tags.
/// 
/// Problem:
/// Make code which calculates Text/HTML ratio on given html page.
/// </summary>
namespace WPC57_TextToHtmlRatioCalculator
{
    public enum State
    {
        Html,
        Text,
        Script,
        Css,
        Option,
        Cdata
    }

    public class HtmlAnalyzer
    {
        private State state;
        private int totalCharacterCount;
        private int textCharacterCount;
        private int htmlCharacterCount;
        private StringBuilder text;

        /// <summary>
        /// Constructs an instance and parses the supplied HTML page.
        /// </summary>
        /// <param name="html">The html to analyze.</param>
        public HtmlAnalyzer(string html)
        {
            // Initial analyzer state
            state = State.Html;

            totalCharacterCount = html.Length;

            // Stores the normal text extracted from the html page.
            // We can then display the extracted text as a visual confirmation
            // of whether we did a good job or not.
            text = new StringBuilder();

            // Scan the html.
            int charIndex = 0;
            while (charIndex < html.Length)
            {
                // Look for an html tag
                if (html[charIndex] == '<')
                {
                    string nextChars = html.Substring(charIndex).ToLower();
                    if (nextChars.StartsWith("<script ") ||
                        nextChars.StartsWith("<script>"))
                    {
                        state = State.Script;
                    }

                    else if (nextChars.StartsWith("<style ") ||
                        nextChars.StartsWith("<style>"))
                    {
                        state = State.Css;
                    }

                    else if (nextChars.StartsWith("<option") && state != State.Script)
                    {
                        state = State.Option;
                    }

                    else if (nextChars.StartsWith("<![cdata[") && state != State.Script)
                    {
                        state = State.Cdata;
                    }
                    else if (nextChars.StartsWith("</script>"))
                    {
                        state = State.Html;
                    }
                    else if (state != State.Script)
                    {
                        state = State.Html;
                    }
                }

                // Depending on the current state, bump the appropriate text or html
                // character counter.
                if (state == State.Html || 
                    state == State.Script || 
                    state == State.Css || 
                    state == State.Option ||
                    state == State.Cdata)
                {
                    htmlCharacterCount++;
                }
                else if (state == State.Text)
                {
                    textCharacterCount++;
                    text.Append(html[charIndex]);
                }

                // End of html tag
                if (html[charIndex] == '>')
                {
                    // If we've been traversing a script tag, treat the whole tag contents
                    // as html. It's certainly not text!
                    if (
                        state == State.Script ||
                        state == State.Css ||
                        state == State.Option ||
                        state == State.Cdata)
                    {
                        // Keep counting characters as Html
                    }
                    else
                    {
                        // Assume the text that follows a > character will be text
                        // unless we find out on the next scan that it isn't.
                        state = State.Text;
                    }
                }

                charIndex++;
            }
        }

        public double TextToHtmlRatio
        {
            get { return 100 * (double)textCharacterCount / (double)htmlCharacterCount; }
        }

        public double TextToTotalPercentage
        {
            get { return 100 * (double)textCharacterCount / (double)totalCharacterCount; }
        }

        public double HtmlToTotalPercentage
        {
            get { return 100 * (double)htmlCharacterCount / (double)totalCharacterCount; }
        }

        public string Text
        {
            get { return text.ToString(); }
        }

        public int TotalChars
        {
            get { return totalCharacterCount; }
        }
    }
}
