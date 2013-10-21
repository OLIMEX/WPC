using System;
using System.Collections.Generic;
using System.Collections.Specialized;
using System.IO;
using System.Net;
using System.Text.RegularExpressions;
using System.Threading;
using System.Web.Script.Serialization;

namespace JSONTest
{
    /// <summary>
    /// This program can only be run after you've signed into Github using a browser.
    /// The process is:
    /// 
    /// 1.  Use Firefox to sign into Github.com
    /// 2.  Use Firebug to obtain the values of the _gh_sess and user_session cookies.
    /// 3.  Update the username constant with your Github username
    /// 4.  Update the _gh_sess and user_session constants below with the cookie values.
    /// 5.  Run the program.  No password is required because you're already logged in.
    /// 
    /// The aim is to obtain email addresses, which this does, not to show how to automate
    /// the login process.
    /// 
    /// The program sends requests to api.github.com to get a list of users and then iterate
    /// through the details of each user to find any that have an email address.
    /// </summary>
    public class Program
    {
        /// <summary>
        /// Your Github username
        /// </summary>
        const string username = "put your username here";

        /// <summary>
        /// Add the _gh_sess cookie value here
        /// </summary>
        const string _gh_sess = "BAh7CDoP...";
        
        /// <summary>
        /// Add the user_session cookie value here
        /// </summary>
        const string user_session = "ZmJ7b3Pwk...";

        /// <summary>
        /// Everything starts somewhere.
        /// </summary>
        /// <param name="args"></param>
        static void Main(string[] args)
        {
            // Create the logged in cookies that will allow us to use the api.
            Cookie cookie1 = new Cookie("_gh_sess", _gh_sess, "/");
            Cookie cookie2 = new Cookie("dotcom_user", username, "/");
            Cookie cookie3 = new Cookie("logged_in", "yes", "/");
            Cookie cookie4 = new Cookie("spy_user", username, "/");
            Cookie cookie5 = new Cookie("tz", "Europe%2FLondon", "/");
            Cookie cookie6 = new Cookie("user_session", user_session, "/");

            string cookies = string.Format("{0}; {1}; {2}; {3}; {4}; {5}; ",
                cookie1.ToString(),
                cookie2.ToString(),
                cookie3.ToString(),
                cookie4.ToString(),
                cookie5.ToString(),
                cookie6.ToString());

            // ************************************************************************************
            // Browse to the home page after we've logged in just to confirm we're logged in.
            // ************************************************************************************
            WebClient request = new WebClient();
            NameValueCollection headers = CreateHeaders(cookies);
            request.Headers.Add(headers);

            Stream response = request.OpenRead("https://github.com/");
            StreamReader sr = new StreamReader(response);
            string responseHtml = sr.ReadToEnd();

            // Check whether we're logged in by seeing if our username appears in the response html.
            Regex regex = new Regex(username);
            MatchCollection matches = regex.Matches(responseHtml);
            if (matches.Count == 0)
            {
                Console.WriteLine("Not logged in.  Change cookies");
                Console.Read();
                return;
            }

            // OK we're logged in.
            Thread.Sleep(1000);     // be kind to Github.

            // Initiate logging to a text file.
            StreamWriter sw = new StreamWriter(Path.Combine(AppDomain.CurrentDomain.BaseDirectory, "github email addresses.txt"));

            // ************************************************************************************
            // Get a list of users in JSON format and parse into a list of objects.
            // The response is limited to just 100 users.
            // ************************************************************************************
            response = request.OpenRead("https://api.github.com/users");
            sr = new StreamReader(response);
            responseHtml = sr.ReadToEnd();

            JavaScriptSerializer jss = new JavaScriptSerializer();
            List<GitHubUserSummary> usersList = jss.Deserialize<List<GitHubUserSummary>>(responseHtml);

            Console.WriteLine("Number of users : {0}", usersList.Count);
            Thread.Sleep(90000);     // One request every 1.5 mins to keep inside the Github rate limit

            // ************************************************************************************
            // Cycle through the list of users and details of each
            // ************************************************************************************
            foreach (GitHubUserSummary summary in usersList)
            {
                // The summary url property holds the url to get the details of one user.
                // If we request it, it might contain their email address.
                try
                {
                    response = request.OpenRead(summary.url);
                    sr = new StreamReader(response);
                    responseHtml = sr.ReadToEnd();

                    GitHubUserDetail detail = jss.Deserialize<GitHubUserDetail>(responseHtml);

                    // Check the email property for a valid email address
                    if (detail.email != null)
                    {
                        string output = string.Format("{0}    Email : {1}", detail.name.PadRight(20, ' '), detail.email);
                        Console.WriteLine(output);
                        sw.WriteLine(output);
                    }
                }
                catch (WebException wex)
                {
                    // Don't bother logging.
                    // The user's details are private or we couldn't deserialize the JSON data.
                }

                Thread.Sleep(90000);     // One request every 1.5 mins to keep inside the Github rate limit
                sw.Flush();
            }

            // Close the log file
            sw.Close();

            // Leave the console open so we can see the email addresses.
            Console.WriteLine("Finished");
            Console.Read();
        }

        /// <summary>
        /// Create some standard static HTTP headers with optional cookies.
        /// </summary>
        /// <param name="cookies">The string of cookies to add to the header.  Optional</param>
        /// <returns>The collection of name=value pairs for an http request</returns>
        private static NameValueCollection CreateHeaders(string cookies)
        {
            NameValueCollection headers = new NameValueCollection();
            headers.Add("User-Agent", "Mozilla/5.0 (Windows NT 6.1; WOW64; rv:24.0) Gecko/20100101 Firefox/24.0");
            headers.Add("Accept-Language", "en-gb,en");
            headers.Add("Accept-Charset", "ISO-8859-1,utf-8");
            headers.Add("Cache-Control", "max-age=0");
            if (!string.IsNullOrEmpty(cookies))
            {
                headers.Add("Cookie", cookies);
            }

            return headers;
        }

        /// <summary>
        /// Deserialize a string of JSON data into an object.
        /// </summary>
        /// <typeparam name="T">The type of object to serialize the JSON data into</typeparam>
        /// <param name="JsonData">The string of JSON data</param>
        /// <returns>An object of the specified type populated with data</returns>
        public static T JsonToObject<T>(string JsonData)
        {
            JavaScriptSerializer jss = new JavaScriptSerializer();
            T rf = (T)jss.Deserialize(JsonData, typeof(T));
            return rf;
        }
    }
}
