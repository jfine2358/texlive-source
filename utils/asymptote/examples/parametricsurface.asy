import graph3;

size(200,0);
currentprojection=orthographic(4,0,2);

real R=2;
real a=1.9;

triple f(pair t) {
  return ((R+a*cos(t.y))*cos(t.x),(R+a*cos(t.y))*sin(t.x),a*sin(t.y));
}

pen p=rgb(0.2,0.5,0.7);

// surface only
draw(surface(f,(0,0),(2pi,2pi),8,8,Spline),lightgray);

// mesh only
//draw(surface(f,(0,0),(2pi,2pi),8,8,Spline),nullpen,meshpen=p);

// surface & mesh
//draw(surface(f,(0,0),(2pi,2pi),8,8,Spline),lightgray,meshpen=p);
