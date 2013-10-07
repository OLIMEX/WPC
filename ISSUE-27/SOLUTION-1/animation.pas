unit Animation;

{$mode objfpc}{$H+}

interface

uses SysUtils, gl, glu, glut, Physics;

procedure DrawScene(params: Parameters; trajectory: Path);

implementation

var GLtrajectory: Path;
    GLparams: Parameters;
    animate: boolean = false;
    elapsed: integer = 0;

// Draw instructions in the viewport
procedure DrawGLText;
var
  i: integer;
  text: string;
  viewport: array[0..3] of integer;
begin
  glMatrixMode(GL_PROJECTION);
      glPushMatrix;
      glLoadIdentity;
      glGetIntegerv(GL_VIEWPORT, @viewport);
      gluOrtho2D(0, viewport[2]-viewport[0],
                 0, viewport[3]-viewport[1]);
      glMatrixMode(GL_MODELVIEW);
      glPushMatrix;
      glLoadIdentity;
      glDisable(GL_DEPTH_TEST);

      glColor3f(0,0,0);
      glRasterPos2f(10, 40);
      text := 'Press ''g'' to start animation';
      for i := 1 to length(text) do
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, integer(text[i]));

      glRasterPos2f(10, 20);
      text := 'Press ''Esc'' to exit the program';
      for i := 1 to length(text) do
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, integer(text[i]));

      glMatrixMode(GL_PROJECTION);
      glPopMatrix;
      glMatrixMode(GL_MODELVIEW);
      glPopMatrix;
      glEnable(GL_DEPTH_TEST);
end;

// Draw the OpenGL scene
procedure DrawGLScene; cdecl;
var time: integer;
    i: integer;
begin

  glClear(GL_COLOR_BUFFER_BIT or GL_DEPTH_BUFFER_BIT);

  if (not animate) then
    begin
      // Draw the initial position and some instructions
      // if the animation has not been started yet
      time := 0;
      DrawGLText;
    end
  else
    begin
      // Record time at start of animation in elapsed
      if (elapsed = 0) then elapsed := glutGet(GLUT_ELAPSED_TIME);
      time := trunc((glutGet(GLUT_ELAPSED_TIME) - elapsed) / 10);
      if (time > High(GLTrajectory)) then time := High(GLTrajectory);
    end;

  // The trajectory with air resistance
  glColor3f(0, 1, 0);
  glBegin(GL_LINES);
    for i:= 1 to time do
      begin
        glVertex3f(GLtrajectory[i-1].x,GLtrajectory[i-1].y,0);
        glVertex3f(GLtrajectory[i].x,GLtrajectory[i].y,0);
      end;
  glEnd;

  // The trajectory without air resistance
  glColor3f(0, 0, 1);
  glBegin(GL_LINES);
    for i:= 1 to time do
      begin
        glVertex3f(GLtrajectory[i-1].nax,GLtrajectory[i-1].nay,0);
        glVertex3f(GLtrajectory[i].nax,GLtrajectory[i].nay,0);
      end;
  glEnd;

  // Lines indicating the start position and the trajectory along the X axis
  glColor3f(0,0,0);
  glBegin(GL_LINES);
    glVertex3f(0,0,0);
    glVertex3f(GLparams.xmax,0,0);
    glVertex3f(0,0,0);
    glVertex3f(0,GLparams.initial_elevation,0);
  glEnd;

  // A sphere with air resistance
  glPushMatrix;
    glColor3f(1, 0.5, 0.5);
    glTranslatef( GLTrajectory[time].x, GLTrajectory[time].y, 0);
    glutSolidSphere(0.5, 20, 20);
  glPopMatrix;

 // A sphere without air resistance
  glPushMatrix;
    glColor3f(0.0, 1.0, 1.0);
    glTranslatef( GLTrajectory[time].nax, GLTrajectory[time].nay, 0);
    glutSolidSphere(0.5, 20, 20);
  glPopMatrix;

  glutSwapBuffers;
end;

procedure ReSizeGLScene(width, height: integer); cdecl;
begin
  if height = 0 then height := 1;

  glViewport(0, 0, width, height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity;
  gluPerspective(45, width / height, 0.1, 1000);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity;

  gluLookAt(GLparams.xmax / 2, GLparams.ymax, GLparams.xmax,
            GLparams.xmax / 2, GLparams.ymax, 0,
            0, 1, 0);
end;

procedure HandleGLKeyboard(Key: Byte; X, Y: Longint); cdecl;
begin
  if Key = 27 then
    Halt(0)
  else if Key = 103 then
    animate := true;
end;


procedure InitGlut;
var
  cmd: array of PChar;
  count: integer;
begin
  count := 1;
  SetLength(cmd, count);
  cmd[0] := PChar(ParamStr(0));
  glutInit(@count, @cmd);
end;

procedure InitDisplay;
begin
  glutInitDisplayMode(GLUT_DOUBLE or GLUT_RGB or GLUT_DEPTH);
  glutInitWindowSize(640, 480);
  glutCreateWindow('Trajectory');
end;

procedure InitGL;
const diffuse : array[0..3] of GLfloat = (0.8,0.8,0.8,1);
      ambient : array[0..3] of GLfloat = (0.2,0.2,0.2,1);
      specular: array[0..3] of GLfloat = (0.5,0.5,0.5,1);
      position: array[0..3] of GLfloat = (50,50,-50,1);
begin
  glClearColor(0.9, 0.9, 0.9, 0);

  glEnable(GL_LIGHTING);
  glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
  glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
  glLightfv(GL_LIGHT0, GL_POSITION, position);
  glEnable(GL_LIGHT0);

  glShadeModel(GL_SMOOTH);
  glEnable(GL_COLOR_MATERIAL);
  glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
end;

procedure DrawScene(params: Parameters; trajectory: Path);
begin
  GLtrajectory := trajectory;
  GLparams := params;

  InitGlut;
  InitDisplay;
  InitGL;

  glutDisplayFunc(@DrawGLScene);
  glutReshapeFunc(@ReSizeGLScene);
  glutKeyboardFunc(@HandleGLKeyboard);
  glutIdleFunc(@DrawGLScene);

  glutMainLoop;
end;

end.

