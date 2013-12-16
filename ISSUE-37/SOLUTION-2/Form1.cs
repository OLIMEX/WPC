using System;
using System.Drawing;
using System.IO;
using System.Reflection;
using System.Windows.Forms;
using System.Windows.Input;

namespace WPC37_Snake
{
    internal enum Direction
    {
        LEFT, RIGHT, UP, DOWN, STILL
    }

    internal enum CollisionObject
    {
        NONE, WALL, SNAKE, TARGET
    }

    /// <summary>
    /// All done in a Windows form with a panel.
    /// </summary>
    public partial class Form1 : Form
    {
        private Bitmap _headPNG;
        private Bitmap _bodyPNG;
        private Bitmap _targetPNG;
        private Bitmap _gameOverPNG;
        private int _x, _y;
        private int _xStep, _yStep;
        private Timer _keyCaptureTimer;
        private Timer _displayUpdateTimer;
        private Point[] _snake;
        private bool _gameOver;
        private Direction _direction;
        private Point _targetLocation;
        private int _snakeLength;
        private int _xMax;
        private int _yMax;

        /// <summary>
        /// The size of the square that holds one target or snake element in pixels.
        /// This is the quantized step that the snake moves around the play area in pixels.
        /// </summary>
        private const int PIXELSIZE = 12;

        private Color gameOverBackground = Color.RoyalBlue;

        public Form1()
        {
            InitializeComponent();
        }

        /// <summary>
        /// One-time only setup for the game.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void Form1_Load(object sender, EventArgs e)
        {
            // Resize the form so that the panel contains an integral number of snake elements.
            this.Width = PIXELSIZE * ((int)(this.Width / PIXELSIZE) + 1) + 4;
            this.Height = PIXELSIZE * ((int)(this.Height / PIXELSIZE) + 1);

            // Define how large the play area is in snake element blocks
            _xMax = this.pn1.Width / PIXELSIZE;
            _yMax = this.pn1.Height / PIXELSIZE;

            // Load the images we need to run the game.
            _headPNG = GetBitmap("head.png");
            _bodyPNG = GetBitmap("body.png");
            _targetPNG = GetBitmap("target.png");
            _gameOverPNG = GetBitmap("gameover.png");

            // Setup a timer to capture key presses on the keyboard.
            SetupKeyCaptureTimer();

            // Setup a timer to update the display.
            SetupDisplayUpdateTimer();

            // Start up a new game.
            InitializeNewGame();
        }

        /// <summary>
        /// Initialises a new game.
        /// </summary>
        private void InitializeNewGame()
        {
            _gameOver = false;
            _direction = Direction.STILL;

            _xStep = 0;
            _yStep = 0;

            _snake = CreateInitialSnake();
            _targetLocation = GetRandomTarget(_snake);

            // Set the background for the play area.
            this.pn1.BackColor = Color.Black;
            
            // Show how long the snake is at the bottom of the form.
            UpdateGameStatus(_snakeLength);

            // Tell the form panel to update itself i.e. draw the target and snake.
            pn1.Invalidate();
        }

        /// <summary>
        /// Setup the timer that will control how often we scan for a keypress.
        /// </summary>
        private void SetupKeyCaptureTimer()
        {
            _keyCaptureTimer = new Timer();
            _keyCaptureTimer.Interval = 10;
            _keyCaptureTimer.Tick += KeyCaptureTimerEvent;
            _keyCaptureTimer.Start();
        }

        /// <summary>
        /// Setup the timer that will control how often we update the display.
        /// The interval specified here determines the speed of the game.
        /// </summary>
        private void SetupDisplayUpdateTimer()
        {
            _displayUpdateTimer = new Timer();
            _displayUpdateTimer.Interval = 200;     // Adjust to make faster or slower
            _displayUpdateTimer.Tick += DisplayUpdateTimerEvent;
            _displayUpdateTimer.Start();
        }

        /// <summary>
        /// Relocate the target.  This is done at the beginning of the game and after hitting
        /// the target.
        /// </summary>
        /// <param name="snake">The set of points the snake is occupying.  This is so we
        /// can avoid placing the target on one of these elements.</param>
        /// <returns></returns>
        private Point GetRandomTarget(Point[] snake)
        {
            Point target;

            // Loop until we find a suitable position for the target within the play area
            // which isn't already occupied by the snake.
            while (true)
            {
                Random r = new Random();
                int x = r.Next(_xMax);
                int y = r.Next(_yMax);
                target = new Point(x, y);

                // Check whether the target location is already occupied by the snake.
                bool suitableTargetLocation = true;
                for (int i = 0; i < _snake.Length; i++)
                {
                    if (target == _snake[i])
                    {
                        suitableTargetLocation = false;
                        break;
                    }
                }

                // If the target location is suitable, we're done.
                if (suitableTargetLocation) break;
            }

            return target;
        }

        /// <summary>
        /// Move the snake and check for collisions.  This is called by the display update timer
        /// </summary>
        /// <param name="sender">ignored</param>
        /// <param name="e">ignored</param>
        void DisplayUpdateTimerEvent(object sender, EventArgs e)
        {
            if (!_gameOver)
            {
                // Move the snake
                _x += _xStep;
                _y += _yStep;

                // Update the variable that tells us which direction the snake is travelling.
                if (_xStep > 0)
                    _direction = Direction.RIGHT;
                else if (_xStep < 0)
                    _direction = Direction.LEFT;
                else if (_yStep > 0)
                    _direction = Direction.DOWN;
                else if (_yStep < 0)
                    _direction = Direction.UP;

                // Check for collisions
                CollisionObject objectHit = DetectObjectHit();

                // If we hit the target, increase the snake length and find a new position for 
                // the next target.
                if (objectHit == CollisionObject.TARGET)
                {
                    _snake = IncreaseSnakeLength(_targetLocation);

                    // update the status bar.
                    UpdateGameStatus(_snakeLength);

                    // Move the target to a new location.
                    _targetLocation = GetRandomTarget(_snake);
                    pn1.Invalidate();
                    return;
                }

                // Is it all over for this game?
                if (objectHit == CollisionObject.WALL || objectHit == CollisionObject.SNAKE)
                {
                    _gameOver = true;
                    _displayUpdateTimer.Enabled = false;
                    this.pn1.BackColor = gameOverBackground;
                    UpdateGameStatus(_snakeLength);
                    return;
                }

                // If it's moving, update the snake's position and update the display.
                if (_direction != Direction.STILL)
                {
                    UpdateSnakePosition(_x, _y);
                    // Update the form's panel.
                    pn1.Invalidate();
                }
            }
        }

        /// <summary>
        /// Check whether we've hit anything.
        /// </summary>
        /// <returns>The type of object we've hit, or NONE</returns>
        private CollisionObject DetectObjectHit()
        {
            // Have we collided with the edge of the play area?
            if (_x < 0 || _y < 0 || _x >= _xMax || _y >= _yMax)
            {
                return CollisionObject.WALL;
            }

            // Have we collided with the target?
            if (_direction == Direction.LEFT)
            {
                if (_snake[0].X - 1 == _targetLocation.X && _snake[0].Y == _targetLocation.Y)
                    return CollisionObject.TARGET;
            }
            else if (_direction == Direction.RIGHT)
            {
                if (_snake[0].X + 1 == _targetLocation.X && _snake[0].Y == _targetLocation.Y)
                    return CollisionObject.TARGET;
            }
            else if (_direction == Direction.UP)
            {
                if (_snake[0].X == _targetLocation.X && _snake[0].Y - 1 == _targetLocation.Y)
                    return CollisionObject.TARGET;
            }
            else if (_direction == Direction.DOWN)
            {
                if (_snake[0].X == _targetLocation.X && _snake[0].Y + 1 == _targetLocation.Y)
                    return CollisionObject.TARGET;
            }

            // Have we collided with the snake itself?
            Point current = new Point(_x, _y);
            for (int i = 4; i < _snake.Length - 1; i++)
            {
                if (_snake[i] == current)
                {
                    return CollisionObject.SNAKE;
                }
            }

            return CollisionObject.NONE;
        }

        /// <summary>
        /// React to the user's command and apply some basic validation.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        void KeyCaptureTimerEvent(object sender, EventArgs e)
        {
            if (Keyboard.IsKeyDown(Key.Down))
            {
                // If we're moving up, we can't suddenly go down.
                if (_direction != Direction.UP)
                {
                    _xStep = 0;
                    _yStep = 1;
                }
            }
            else if (Keyboard.IsKeyDown(Key.Up))
            {
                // If we're moving down, we can't suddenly go up.
                if (_direction != Direction.DOWN)
                {
                    _xStep = 0;
                    _yStep = -1;
                }
            }
            else if (Keyboard.IsKeyDown(Key.Right))
            {
                // If we're moving left, we can't suddenly move right.
                if (_direction != Direction.LEFT)
                {
                    _xStep = 1;
                    _yStep = 0;
                }
            }
            else if (Keyboard.IsKeyDown(Key.Left))
            {
                // If we're moving right, we can't suddenly move left.
                if (_direction != Direction.RIGHT)
                {
                    _xStep = -1;
                    _yStep = 0;
                }
            }
            else if (Keyboard.IsKeyDown(Key.Space))
            {
                InitializeNewGame();
                _displayUpdateTimer.Enabled = true;
            }
        }

        /// <summary>
        /// Updates the set of points occupied by the snake.
        /// </summary>
        /// <param name="x">The new x co-ordinate of the snake's head</param>
        /// <param name="y">The new y co-ordinate of the snake's head</param>
        private void UpdateSnakePosition(int x, int y)
        {
            // Move the head and body parts one position down the snake
            for (int i = _snake.Length - 2; i >= 0; i--)
            {
                _snake[i + 1] = _snake[i];
            }
            _snake[0] = new Point(x, y);
        }

        /// <summary>
        /// Increase the snake's length.  This is done when we hit the target.
        /// </summary>
        /// <param name="newHead">The position of the target which will become the snake's head.
        /// </param>
        /// <returns>The set of points that make up the new snake.</returns>
        private Point[] IncreaseSnakeLength(Point newHead)
        {
            Point[] newSnake = new Point[++_snakeLength];
            newSnake[0] = newHead;

            for (int i = 1; i < _snakeLength; i++)
            {
                newSnake[i] = _snake[i - 1];
            }
            return newSnake;
        }

        /// <summary>
        /// Create the initial snake at the start of the game.
        /// </summary>
        /// <returns></returns>
        private Point[] CreateInitialSnake()
        {
            // The initial snake will be 4 squares long.
            _snakeLength = 4;

            // Put the snake around the middle of the play area.
            int x = (int)(_xMax / 2);
            int y = (int)(_yMax / 2);
            _x = x;
            _y = y;

            // Populate the snake array with the location of each snake element.
            Point[] initialSnake = new Point[_snakeLength];
            for (int i = 0; i < _snakeLength; i++)
            {
                // The snake will be pointing right but we could be smarter and position it 
                // in any direction if we wanted to be more adventurous!
                initialSnake[i] = new Point(x--, y);
            }
            return initialSnake;
        }

        /// <summary>
        /// Read a bitmap from the game's resources.
        /// </summary>
        /// <param name="name"></param>
        /// <returns></returns>
        private Bitmap GetBitmap(string name)
        {
            // Resolve the manifest path for the bitmap
            string bitmapName = string.Format("WPC37_Snake.images.{0}", name);

            // Get the bitmap from the manifest
            Assembly assembly = Assembly.GetExecutingAssembly();
            Stream stream = assembly.GetManifestResourceStream(bitmapName);
            Bitmap bitmap = Bitmap.FromStream(stream) as Bitmap;
            return bitmap;
        }

        /// <summary>
        /// Repaint the panel showing the target and the snake.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void pn1_Paint(object sender, PaintEventArgs e)
        {
            Point p;
            for (int i = 0; i < _snakeLength; i++)
            {
                p = new Point(_snake[i].X * PIXELSIZE, _snake[i].Y * PIXELSIZE);
                if (i == 0)
                {
                    e.Graphics.DrawImage(_headPNG, p);
                }
                else
                {
                    e.Graphics.DrawImage(_bodyPNG, p);
                }
            }

            // Draw the target
            p = new Point(_targetLocation.X * PIXELSIZE, _targetLocation.Y * PIXELSIZE);
            e.Graphics.DrawImage(_targetPNG, p);

            // At the end of the game, display the GAME OVER image.
            if (_gameOver)
            {
                p = new Point((_xMax * PIXELSIZE - _gameOverPNG.Width) / 2, (_yMax * PIXELSIZE - _gameOverPNG.Height) / 2);
                e.Graphics.Clear(gameOverBackground);
                e.Graphics.DrawImage(_gameOverPNG, p);
            }
        }

        /// <summary>
        /// Update the status text at the bottom of the form which shows how long the snake is.
        /// </summary>
        /// <param name="length"></param>
        private void UpdateGameStatus(int length)
        {
            if (_gameOver)
            {
                lblStatus.Text = "Snake length : " + _snakeLength + ".  Press spacebar to play.";
            }
            else
            {
                lblStatus.Text = "Snake length : " + _snakeLength;
            }
        }
    }
}
