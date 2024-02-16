//settings.outformat="png";
//settings.tex = 'lualatex';
//settings.prc=false;
settings.render=8;
//settings.maxtile=(50,50);

import graph3;
size(12cm,0);

import three;
import palette;

void showAxes(){
	draw((-2,0,0)--(2,0,0),magenta,arrow=Arrow3(),L=Label("$x$",position=EndPoint));
	draw((0,-2,0)--(0,4,0),magenta,arrow=Arrow3(),L=Label("$y$",position=EndPoint));
	draw((0,0,-0.1)--(0,0,2),magenta,arrow=Arrow3(),L=Label("$z$",position=EndPoint));
}


surface cutPlane(real f(pair xy), pair lo, pair hi, real base=0) {
  pair dr = hi-lo;
  pair g(real t){return (t,f(lo+t*dr));};
  path p1=graph(g,0,1);
  path p2=(g(0))--(0,base)--(1,base)--(g(1));

  return shift(lo.x,lo.y,base)*rotate(degrees(dr),Z)*
    xscale3(length(dr))*
    rotate(90,X)*surface(buildcycle(p1,p2));
}


path3 onSurf(real f(pair xy), pair lo, pair hi) {
  pair dr = hi-lo;
  triple g(real t){pair p=lo+t*dr;return (p.x,p.y,f(p));};
  return graph(g,0,1);
}

currentlight=light(new pen[]{0.9*rgb(0.9,0.9,1),0.9*rgb(0.9,0.9,1)},
                   new triple[]{(0.5,-1,1),(0,1,1)});
  
/*
currentprojection=
  orthographic(camera=(8,-7,1.4),
               up=(0,0,1),
               target=(0,0,0),
               zoom=0.8);
               */

//real f(pair xy) {return 3-0.5*(xy.x^2+xy.y^2);}
real f(pair z) {return 0.5+1.2*exp(-z.x^2-z.y^2);}
real dfx(pair z) {return -2.4*z.x*exp(-z.x^2-z.y^2);}

real xmin = -1.5; real xmax = 1.5;
real ymin = -1.5;  real ymax = 1.5;
pair p = (-0.2,-0.4);

triple proj(triple p) { return (p.x,p.y,0);}
triple ptf(real x, real y) {return (x,y,f((x,y)));}

material baseMat(pen p =cyan, real op=1) {
	return material(p+opacity(op),shininess=0.2);
}


surface s = surface(f, (xmin,p.y+1e-4), (xmax,ymax), 18,15,Spline);
surface s2 = surface(f, (xmin,ymin), (xmax,p.y-0.2), 18,15,Spline);


// bounding box
for (real x: new real[]{xmin,xmax}) for(real y:new real[]{ymin,ymax})
draw(proj(ptf(x,y))--ptf(x,y),linewidth(0.2));
draw((xmin,ymin,0)--(xmax,ymin,0)--(xmax,ymax,0)--(xmin,ymax,0) -- cycle,gray(0.4));


real mrg=0.3;
real[][] trn=shift(xmin-mrg,p.y+1e-4,-mrg)*zscale3(2.5)*xscale3(2*mrg+xmax-xmin)*rotate(90,X);
draw(trn*surface((0,0)--(0,1)--(1,1)--(1,0)--cycle),baseMat(green,0.2));
label("$y=p_y$",trn*(1,1,0), align=N, deepgreen);


draw(s, surfacepen=baseMat(cyan), meshpen=gray(0.2)+linewidth(0.1));
draw(s2, surfacepen=baseMat(yellow,0.5), meshpen=gray(0.2)+linewidth(0.1));



draw(cutPlane(f,(xmin,p.y),(xmax,p.y)),baseMat(orange));
//draw(cutPlane(f,(xmax,p.y),(xmax,ymax)),baseMat(cyan,op));
//draw(cutPlane(f,(xmin,ymin),(xmin,p.y)),baseMat(orange,op));
//draw(cutPlane(f,(xmax,ymin),(xmax,p.y)),baseMat(orange,op));
//draw(cutPlane(f,(xmin,ymin),(xmax,ymin)),baseMat(orange,op));

draw(onSurf(f,(xmin,p.y+1e-2),(xmax,p.y+1e-2)),red+linewidth(2));
label("$f_{y=p_y}(x)$",(1.65,-1,1),red);

triple dr = (1,0,dfx(p)),pp=(p.x,p.y,f(p));
draw(pp-1.5*dr--pp+1.5*dr,blue+linewidth(1));

draw((p.x,p.y,0)--(p.x,p.y,f(p)),dashed+linewidth(0.8));
label("$[p_x,p_y,f(p_x,p_y)]$",position=pp+(-0.18,0,0.18),align=NW);
draw((p.x,p.y,0)--(p.x,p.y,0.5+f(p)),gray(0.5)+linewidth(0.4));
draw((xmin,p.y,f(p))--(xmax,p.y,f(p)),gray(0.5)+linewidth(0.4));


dot((p.x,p.y,0));
dot((p.x,p.y,f(p)));

path3 anglearc(real radius, triple A, triple B, triple C)  {
	triple center = B;	
	triple start = B + radius * unit(A-B);
	return arc(center, start, C,cross(A-B, C-B),CCW);
}

draw(anglearc(0.5, pp+dr, pp, pp+X), L=Label("$\alpha$"), blue);

showAxes();


currentprojection=
  orthographic(camera=(4.090496686908698,-9.817669806607999,1.3569045711465992),
               up=(-0.001225734,0.001083773,0.01153654),
               target=(-1.776357e-15,1.776357e-15,-8.881784e-16),
               zoom=0.972405);

