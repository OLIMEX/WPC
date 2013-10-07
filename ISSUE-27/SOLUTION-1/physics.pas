unit Physics;

{$mode objfpc}{$H+}

interface

uses SysUtils;

// The approximate amount of points we want to calculate
const num_points_target = 400;

// The parameters required by the model
type Parameters = record
  mass: double;               // Mass in kg
  impulse_force: double;      // Initial force in N
  impulse_time: double;       // Time interval in s during which initial force was applied
  initial_elevation: double;  // Elevation of starting position in m
  launch_angle: double;       // Initial angle in rad
  gravity: double;            // Gravitational acceleration in m/s^2
  surface_area: double;       // Frontal surface area of object in m^2
  drag_coefficient: double;   // Drag coefficient (dimensionless constant)
  air_density: double;        // Air density in kg/m^3;
  initial_velocity: double;   // Initial velocity in m/s

  drag_constant: double;      // Calculated drag constant
  time_interval: double;      // Time interval between calculations
  xmax: double;               // Max x coordinate observed during calculations
  ymax: double;               // Max y coordinate observed during calculations
end;

type Point = record
   // Position with air resistance
   x: double;
   y: double;
   // Position without air resistance
   nax: double;
   nay: double;
end;

// An array containing the calculated trajectory
type Path = array of Point;

procedure InitPhysics(var p: Parameters);
procedure CalcTrajectory(var p: Parameters; var t: Path);

implementation

procedure InitPhysics(var p: Parameters);
var estimated_flight_time: double;
begin
  p.initial_velocity :=  p.impulse_force * p.impulse_time / p.mass;
  p.drag_constant :=  p.surface_area * p.drag_coefficient * p.air_density / 2;
  estimated_flight_time := (   (p.initial_velocity * sin(p.launch_angle))
                      + sqrt(   sqr(p.initial_velocity * sin(p.launch_angle))
                              + (2 * p.gravity * p.initial_elevation)
                            )
                    ) / p.gravity;
  p.time_interval := estimated_flight_time / num_points_target;
  p.xmax := 0;
  p.ymax := p.initial_elevation;
end;

procedure CalcTrajectory(var p: Parameters; var t: Path);
var x,y: double;
    v, vx, vy: double;
    ax, ay: double;
    cur_point: integer;
    drag_factor: double;
    nax,nay: double;
    navx, navy: double;
begin
  // Initial position
  x := 0;
  y := p.initial_elevation;
  nax := x;
  nay := y;

  // Initial velocity
  v := p.initial_velocity;
  vx := v * cos(p.launch_angle);
  vy := v * sin(p.launch_angle);
  navx := vx;
  navy := vy;

  drag_factor := p.drag_constant / p.mass;

  // Initialize array of points
  cur_point := 0;
  SetLength(t, 100);

  t[cur_point].x := x;
  t[cur_point].y := y;
  t[cur_point].nax := nax;
  t[cur_point].nay := nay;

  // Stop when both objects are on the ground
  while ((y > 0) or (nay > 0)) do
    begin
      // Expand array if required
      if cur_point >= High(t) then SetLength(t, Length(t) + 100);

      // Determine acceleration
      v := sqrt(sqr(vx) + sqr(vy));
      ax := - v * vx  * drag_factor;
      ay := - p.gravity - v * vy * drag_factor;

      // Determine new velocity
      vx := vx + ax * p.time_interval;
      vy := vy + ay * p.time_interval;
      navy := navy - p.gravity * p.time_interval;

      // Determine new position
      x := x + vx * p.time_interval + 0.5 * ax * sqr(p.time_interval);
      y := y + vy * p.time_interval + 0.5 * ay * sqr(p.time_interval);
      if (y <= 0) then
        begin
          y := 0;
          vx := 0;
          vy := 0;
        end;
      nax := nax + navx * p.time_interval;
      nay := nay + navy * p.time_interval - 0.5 * p.gravity * sqr(p.time_interval);
      if (nay < 0) then
        begin
          nay := 0;
          navx := 0;
          navy := 0;
        end;

      // Store new position
      inc(cur_point);
      t[cur_point].x := x;
      t[cur_point].y := y;
      t[cur_point].nax := nax;
      t[cur_point].nay := nay;

      // Store max x and y seen so far
      if (p.xmax < x) then p.xmax := x;
      if (p.ymax < y) then p.ymax := y;
      if (p.xmax < nax) then p.xmax := nax;
      if (p.ymax < nay) then p.ymax := nay;
    end;

  // Trim array of points
  SetLength(t, cur_point + 1);
end;

end.

