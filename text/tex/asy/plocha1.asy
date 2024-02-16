settings.outformat="pdf";
settings.tex = 'lualatex';
settings.prc=false;
settings.render=0;
//settings.maxtile=(50,50);

import graph3;
size(12cm,0);

import three;
import palette;

currentprojection=orthographic(15, -9, 5.5);
currentlight=(-1,5,10);

real xmin = -1.5; real xmax = 2.3;
real ymin = -1.3;  real ymax = 2.5;

real d(real x, real y) {
  return sqrt(x^2+y^2);
}

real f(pair xy) {
  real x = xy.x; real y = xy.y;
  //real z = -3*x*y*exp(-x^2 - y^2);
  real z = 3.4+cos(d(x+0.9,y-1.2))+0.6*sin(d(x-0.1,y-0.2))^3+cos(d(x+2,y+2));
  //xy = rotate(17)*xy;
  return z;
}

real pow(real a, real b) {return a^b;}

real dFdx(pair xy) {
  real x = xy.x; real y = xy.y;
return -(x + 2)*sin(sqrt(pow(x + 2, 2) + pow(y + 2, 2)))/sqrt(pow(x + 2, 2) +
pow(y + 2, 2)) + 0.89999999999999991*(2*x -
0.20000000000000001)*pow(sin(sqrt(pow(x - 0.10000000000000001, 2) + pow(y -
0.20000000000000001, 2))), 2)*cos(sqrt(pow(x - 0.10000000000000001, 2) + pow(y
- 0.20000000000000001, 2)))/sqrt(pow(x - 0.10000000000000001, 2) + pow(y -
0.20000000000000001, 2)) - 0.41666666666666669*(2*x +
1.8)*sin(1.2*sqrt(0.69444444444444442*pow(x + 0.90000000000000002, 2) +
pow(0.83333333333333337*y - 1, 2)))/sqrt(0.69444444444444442*pow(x +
0.90000000000000002, 2) + pow(0.83333333333333337*y - 1, 2)); 
}

real dFdy(pair xy) {
  real x = xy.x; real y = xy.y;
return   -(y + 2)*sin(sqrt(pow(x + 2, 2) + pow(y + 2, 2)))/sqrt(pow(x + 2, 2) + pow(y + 2, 2)) - 0.41666666666666669*(2*y - 2.3999999999999999)*sin(1.2*sqrt(0.69444444444444442*pow(x + 0.90000000000000002, 2) + pow(0.83333333333333337*y - 1, 2)))/sqrt(0.69444444444444442*pow(x + 0.90000000000000002, 2) + pow(0.83333333333333337*y - 1, 2)) + 0.89999999999999991*(2*y - 0.40000000000000002)*pow(sin(sqrt(pow(x - 0.10000000000000001, 2) + pow(y - 0.20000000000000001, 2))), 2)*cos(sqrt(pow(x - 0.10000000000000001, 2) + pow(y - 0.20000000000000001, 2)))/sqrt(pow(x - 0.10000000000000001, 2) + pow(y - 0.20000000000000001, 2));
}

triple proj(triple p) { return (p.x,p.y,0);}
triple ptf(real x, real y) {return (x,y,f((x,y)));}

pen hpen = gray+dashed+linewidth(0.2);

surface s = surface(f, (xmin,ymin), (xmax,ymax), 20,20,Spline);

for (real x: new real[]{xmin,xmax}) for(real y:new real[]{ymin,ymax}) 
draw((x,y,0)--(x,y,f((x,y))),linewidth(0.2));

draw(s, surfacepen=material(diffusepen=0.2*heavycyan+white,specularpen=white,shininess=0.2),  meshpen=0.3*heavycyan+gray(0.2)+linewidth(0.1));

draw((xmax,ymin,0)--(xmax,ymin,f((xmax,ymin))),linewidth(0.2));
draw( (xmin,ymin,0) -- (xmin,ymax,0) -- (xmax,ymax,0) -- (xmax,ymin,0) -- cycle, linewidth(0.2));
draw(s.uequals(20-1e-9),linewidth(0.4));
draw(s.vequals(0),linewidth(0.4));

//triple p=point(s.uequals(10),intersect(s.uequals(10),s.vequals(14))[0]);
triple oo=(xmin,ymin,0);
real px=-0.1, py=1.9;
triple p = (px,py,f((px,py)));
draw(proj(p)--p,hpen);

pen dotPen = orange+linewidth(2.5);
pen dotPen2 = linewidth(2.1);

dot(p,dotPen);
dot(proj(p),dotPen2);

for (int i=0; i<6; ++i) {
  triple grad = 0.9*(-dFdx((p.x,p.y)),-dFdy((p.x,p.y)),0);
  grad=0.5/d(grad.x,grad.y)*grad;
  triple q=proj(p)+grad+Z*f((grad.x+p.x,grad.y+p.y));
  if (i==3) {
    real r=d(grad.x,grad.y);
    pen cc=mediumgray;
    draw(circle(proj(p),r,Z),cc+linewidth(0.1));
    for (real a : new real[]{-25,69,127,165,212}) {
      triple k = rotate(angle=a,u=p,v=p+Z)*(proj(p)+r*X);
      triple k2 = k+(0,0,f((k.x,k.y)));
      draw(proj(p)--k, cc+linewidth(0.1), arrow=Arrow3(HookHead2, emissive(lightblue), size=3));      
      //draw(p--k2, cc+linewidth(0.1), arrow=Arrow3(HookHead2, emissive(lightblue), size=3));      
      //draw(k--k2, cc+dashed+linewidth(0.1));
      //dot(k2,cc+linewidth(1.8));
    }
    draw(proj(p)--p,hpen+red);
    draw(proj(q)--q,hpen+red);
    draw(proj(p)--proj(q),linewidth(1.2)+heavygreen,arrow=Arrow3(HookHead2, emissive(heavygreen), size=5), 
    L=Label("$\vec g$",position=MidPoint));
    label("$[x,y]$",proj(p),3*E+1*S);
    triple vc=( 0,1,1);
    draw((p+0.1*vc)--(p+vc),red+dotted+linewidth(0.1));
    label("$h(x,y)$",p+vc,red,align=E+N);
    draw(p--q,red+linewidth(1.4),arrow=Arrow3(HookHead2, emissive(red), size=5));
    dot(p,red+linewidth(4));
    dot(proj(p),linewidth(3));

  } else {
    draw(proj(q)--q,hpen);
    draw(p--q,orange+linewidth(1.4));
    draw(proj(p)--proj(q));
  }
  dot(q,dotPen);
  dot(proj(q),dotPen2);
  p=q;
}


//draw(O--X,green);draw(O--Y,blue); draw(O--Z,red);


//for (triple x: new triple[]{p,q}) draw(proj(x)--x,hpen);



pen xclr=heavygreen, yclr=heavyblue;
draw( oo -- oo+X, xclr, arrow=Arrow3(DefaultHead2, emissive(xclr)), L=Label("$x$", position=EndPoint, align=1.2*(W+S)));
draw( oo -- oo+Y, yclr, arrow=Arrow3(DefaultHead2, emissive(yclr)), L=Label("$y$", position=EndPoint, align=1.2*(W+N)));

