(*
 * Olimex WPC #27
 *
 * Calculate an Angry Bird trajectory.
 *
 * Inputs:
 *   Mass in kg
 *   Initial force in N
 *   Time interval in s during which initial force was applied
 *   Elevation of starting position in m
 *   Initial angle in rad
 *   Gravitational acceleration in m/s^2
 *   Frontal surface area of object in m^2
 *   Drag coefficient (dimensionless constant)
 *   Air density in kg/m^3
 *
 * Outputs:
 *   An OpenGL rendered trajectory with and without air resistance
 *
 * Environment:
 *   Linux Mint 15
 *   Lazarus 0.9.30.4-4 (optional)
 *   Free Pascal 2.6.0
 *   FreeGLUT 3.0
 *
 * Compilation:
 *   fpc main.pas
 *   (Ignore the warning from ld)
 *
 *)

program main;

{$mode objfpc}{$H+}

uses SysUtils, Physics, Animation;

var params: Parameters;
    trajectory: Path;

begin

  with params do
    begin
      mass :=  0.5;
      impulse_force := 20;
      impulse_time := 0.5;
      surface_area := 0.03;
      drag_coefficient := 0.75;
      air_density := 1.2;
      launch_angle := pi/4;
      gravity := 9.81;
      initial_elevation := 1.0;
    end;

  InitPhysics(params);
  CalcTrajectory(params, trajectory);
  DrawScene(params, trajectory);

end.

