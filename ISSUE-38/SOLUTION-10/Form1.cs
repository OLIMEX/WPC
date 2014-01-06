using System;
using System.Drawing;
using System.IO;
using System.Reflection;
using System.Windows.Forms;

namespace WPC38_CentreOfMass
{
    public partial class Form1 : Form
    {
        string imageName;
        Bitmap image;
        Point centre;
        Bitmap dot;

        /// <summary>
        /// The images are sized 100 x 100 pixels but are zoomed to twice this size for clarity.
        /// </summary>
        const int ZoomLevel = 2;

        /// <summary>
        /// Initialise the form and sets up any globals.
        /// </summary>
        public Form1()
        {
            InitializeComponent();
            dot = GetBitmap("dot");
        }

        /// <summary>
        /// Event handler for all the form's radio buttons.  The image associated with the 
        /// selected radio button is read and displayed in the form.
        /// </summary>
        /// <param name="sender">The radio button that is changing state.</param>
        /// <param name="e">Ignored</param>
        private void rb_CheckedChanged(object sender, EventArgs e)
        {
            RadioButton rb = sender as RadioButton;
            if (rb.Checked)
            {
                imageName = rb.Name;
                SetCentre(0, 0);
                DisplayImage(imageName);
            }
        }

        /// <summary>
        /// The event handler for the Calculate button
        /// </summary>
        /// <param name="sender">ignored</param>
        /// <param name="e">ignored</param>
        private void btnCalculate_Click(object sender, EventArgs e)
        {
            // Calculate the centre of mass point for the lamina.
            centre = CentreOfMass(image);

            // Update the form withthe result.
            lblCoordinates.Text = string.Format("({0}, {1})", centre.X, centre.Y);
            pn1.Invalidate();
        }

        /// <summary>
        /// The crux of the challenge.  Pretty simple actually.
        /// </summary>
        /// <param name="image">The image containing the lamina.</param>
        /// <returns>The coordinates of the point that represents the centre of mass/gravity.</returns>
        public Point CentreOfMass(Bitmap image)
        {
            int xCentre = 0;
            int yCentre = 0;
            int pixelCount = 0;

            for (int y = 0; y < image.Height; y++)
            {
                for (int x = 0; x < image.Width; x++)
                {
                    // If the pixel is coloured greenish, it's part of the lamina surface.
                    if (image.GetPixel(x, y).G > 140)
                    {
                        xCentre += x;
                        yCentre += y;
                        pixelCount++;
                    }
                }
            }
            return new Point(xCentre / pixelCount, yCentre / pixelCount);
        }

        /// <summary>
        /// Read a bitmap from the project's embedded resources.
        /// </summary>
        /// <param name="name"></param>
        /// <returns></returns>
        public Bitmap GetBitmap(string imageName)
        {
            // Resolve the image name into the full resource path for the image we want.
            string bitmapName = string.Format("WPC38_CentreOfMass.images.{0}.bmp", imageName);

            // Get the bitmap from the embedded resources and hand it over.
            Assembly assembly = Assembly.GetExecutingAssembly();
            Stream stream = assembly.GetManifestResourceStream(bitmapName);
            Bitmap bitmap = Bitmap.FromStream(stream) as Bitmap;
            return bitmap;
        }

        /// <summary>
        /// Displays the bitmap image on the form and clears centre of mass for any previous
        /// image.
        /// </summary>
        /// <param name="imageName">The name of the image to display on the form, e.g. rb1</param>
        private void DisplayImage(string imageName)
        {
            // Read the image from the resources
            image = GetBitmap(imageName);

            // Display the image.
            pn1.Invalidate();

            // Clear the text that says where the centre of mass is located.
            lblCoordinates.Text = "";
        }

        /// <summary>
        /// Sets the position of the centre point.
        /// </summary>
        /// <param name="x">The x co-ordinate</param>
        /// <param name="y">The y co-ordinate</param>
        private void SetCentre(int x, int y)
        {
            centre.X = x;
            centre.Y = y;
        }

        /// <summary>
        /// Repaint the panel to show the image.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void pn1_Paint(object sender, PaintEventArgs e)
        {
            Graphics g = e.Graphics;
            
            // Draw the image.
            if (image != null)
                g.DrawImage(image, 0, 0, 200, 200);

            // Draw the centre of mass of the image, if necessary.
            if (!centre.IsEmpty)
                g.DrawImage(dot, ZoomLevel * centre.X, ZoomLevel * centre.Y);
        }
    }
}
