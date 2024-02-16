//settings.outformat="png";
//settings.tex = 'lualatex';
//settings.prc=false;
settings.render=8;
//settings.maxtile=(50,50);

import graph3;
size(11cm,0);

import three;
import palette;
pair p = (-0.2,-0.2);

real grbt = 0.7;
void showAxes(){
	draw((-1.1,p.y,0)--(1.5,p.y,0),gray(grbt),arrow=Arrow3(),L=Label("$x$",position=EndPoint));
	draw((p.x,-1.1,0)--(p.x,2,0),gray(grbt),arrow=Arrow3(),L=Label("$y$",position=EndPoint));
	//draw((0,0,-0.1)--(0,0,2),magenta,arrow=Arrow3(),L=Label("$z$",position=EndPoint));
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
real f(pair z) {return 0.55+1.1*exp(-z.x^2-z.y^2);}
real dfx(pair z) {return -2.2*z.x*exp(-z.x^2-z.y^2);}
real dfy(pair z) {return -2.2*z.y*exp(-z.x^2-z.y^2);}

real xmin = -1; real xmax = 1;
real ymin = -1;  real ymax = 1;

triple proj(triple p) { return (p.x,p.y,0);}
triple ptf(real x, real y) {return (x,y,f((x,y)));}

material baseMat(pen p =cyan, real op=1) {
	return material(p+opacity(op),shininess=0.2);
}


surface s = surface(f, (xmin,ymin), (xmax,ymax), 18,15,Spline);


// bounding box
/*
for (real x: new real[]{xmin,xmax}) for(real y:new real[]{ymin,ymax})
draw(proj(ptf(x,y))--ptf(x,y),gray(0.2)+linewidth(0.2));
draw((xmin,ymin,0)--(xmax,ymin,0)--(xmax,ymax,0)--(xmin,ymax,0) -- cycle,gray(0.2)+linewidth(0.2));
*/

/*
real mrg=0.3;
real[][] trn=shift(xmin-mrg,p.y+1e-4,-mrg)*zscale3(2.5)*xscale3(2*mrg+xmax-xmin)*rotate(90,X);
draw(trn*surface((0,0)--(0,1)--(1,1)--(1,0)--cycle),baseMat(cyan,0.2));
label("$y=p_x$",trn*(1,1,0), align=N, heavycyan);
*/

draw(s, surfacepen=baseMat(cyan), meshpen=gray(0.2)+linewidth(0.1));



//draw(cutPlane(f,(xmin,p.y),(xmax,p.y)),baseMat(cyan));
//draw(cutPlane(f,(xmax,p.y),(xmax,ymax)),baseMat(cyan,op));
//draw(cutPlane(f,(xmin,ymin),(xmin,p.y)),baseMat(orange,op));
//draw(cutPlane(f,(xmax,ymin),(xmax,p.y)),baseMat(orange,op));
//draw(cutPlane(f,(xmin,ymin),(xmax,ymin)),baseMat(orange,op));

draw(onSurf(f,(xmin,p.y),(xmax,p.y)),red+linewidth(1.5));
draw(onSurf(f,(p.x,ymin),(p.x,ymax)),red+linewidth(1.5));
//label("$f_{y=p_y}(x)$",(1.65,-1,1),red);


triple drx = (1,0,dfx(p)),dry=(0,1,dfy(p)),pp=(p.x,p.y,f(p));
real ypc = 0.87;
draw(pp-ypc*drx--pp+1*drx,blue+linewidth(0.3), arrow=Arrow3(HookHead2,5), L=Label("$\vec{u}$", position=EndPoint));
draw(pp-ypc*dry--pp+1*dry,blue+linewidth(0.3), arrow=Arrow3(HookHead2,5), L=Label("$\vec{v}$", position=EndPoint));

draw(shift(pp)*surface( -ypc*drx-ypc*dry -- drx-ypc*dry -- drx+dry -- -ypc*drx+dry -- cycle ),
     yellow+opacity(0.2));

draw((p.x,p.y,0)--(p.x,p.y,f(p)),linewidth(0.4));

triple offs(pair z) {
  return z.x*drx + z.y*dry;
}

real r=0.9,alpha=42*pi/180;
real sa = r*sin(alpha), ca=r*cos(alpha);


//draw((p.x+d,p.y,0)--pp+offs((d,0)));

draw(circle(proj(pp),r,Z),gray(grbt));

pen clr=deepgreen;
real lw=0.7;
draw(proj(pp)--proj(pp)+(ca,sa,0),arrow=Arrow3(HookHead2,5), clr+linewidth(lw), L=Label("$\Delta$",position=MidPoint, align=N));
draw(proj(pp)+(ca,sa,0)--pp+offs((ca,sa)),clr+linewidth(0.1));
draw(pp--pp+offs((ca,sa)),clr+linewidth(lw),arrow=Arrow3(HookHead2,5));

//draw(proj(pp)+(ca,sa,0)--proj(pp)+(ca,0,0),gray+linewidth(0.1));

clr=orange;
draw(proj(pp)--proj(pp)+(ca,0,0),arrow=Arrow3(HookHead2,5), clr+linewidth(lw));
draw(proj(pp)+(ca,0,0)--pp+offs((ca,0)),clr+linewidth(0.1));
draw(pp--pp+offs((ca,0)),clr+linewidth(lw),arrow=Arrow3(HookHead2,5));

draw(proj(pp)+(ca,0,0)--proj(pp)+(ca,sa,0),arrow=Arrow3(HookHead2,5), clr+linewidth(lw));
draw(pp+offs((ca,0))--pp+offs((ca,sa)),clr+linewidth(lw),arrow=Arrow3(HookHead2,5));


/*
label("$[p_x,p_y,f(p_x,p_y)]$",position=pp+(-0.18,0,0.18),align=NW);
draw((p.x,p.y,0)--(p.x,p.y,0.5+f(p)),gray(0.5)+linewidth(0.4));
draw((xmin,p.y,f(p))--(xmax,p.y,f(p)),gray(0.5)+linewidth(0.4));
*/

dot((p.x,p.y,0));
dot((p.x,p.y,f(p)));

label("$p$",(p.x,p.y,0),align=NW);
path3 anglearc(real radius, triple A, triple B, triple C)  {
	triple center = B;	
	triple start = B + radius * unit(A-B);
	return arc(center, start, C,cross(A-B, C-B),CCW);
}

draw(shift(proj(pp))*(O--1.4*(ca,sa,0)),blue+linewidth(0.5));
draw(anglearc(r, proj(pp)+(10,0,0), proj(pp), proj(pp)+10*(ca,sa,0)), blue+linewidth(1));
label("$\alpha$",0.5*r*(cos(alpha/2),sin(alpha/2),0)+(0.28,0,0),blue+linewidth(0.5));

showAxes();
currentprojection=
  orthographic(camera=(4.09049773756575,-9.8176714345605,1.3569047696557501),
               up=(-0.001225193,0.001083294,0.01153145),
               target=(0,-1.776357e-15,2.220446e-16),
               zoom=0.972405);
currentprojection=
  orthographic(camera=(4.090498886640001,-9.817672929480002,1.3569056172000005),
               up=(-0.0008452093,0.0007473194,0.007955063),
               target=(0,-1.776357e-15,2.220446e-16),
               zoom=0.972405);

currentprojection=
  orthographic(camera=(4.09049858260215,-9.817673170060353,1.35690586269375),
               up=(-0.0009329496,0.0008248981,0.008780868),
               target=(-8.881784e-16,-1.776357e-15,0),
               zoom=0.972405);
