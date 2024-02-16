settings.outformat="pdf";
settings.tex = 'lualatex';
import graph;
import markers;
size(7cm,0);

defaultpen(fontsize(10pt));

real f(real x) { return x^3 + 0.2; }

real xmin = 0.1;
real xmax = 1;
real ymin = -0.1;
real ymax = f(xmax);

path fx =  graph(f,xmin-0.02,xmax);
real x0 = 0.43;
real t = times(fx,x0)[0];
pair p = point(fx,t);
pair d = unit(dir(fx,t));
path tg = shift(p)*scale(0.7)*(-d--d);
pair o = point(tg,intersect(tg,((-10,0)--(10,0)))[0]);
real bx = 0.85;
pair tgp = point(tg,times(tg,bx)[0]);
pair fp = point(fx,times(fx,bx)[0]);

path thru(pair a, pair b) {
  pair d = unit(b-a);
  real y = min(tg).y, x=max(tg).x;
  path line = (a-10*d)--(a+10*d);
  pair l = point(line,times(line,(0,y))[0]), r= point(line,times(line,x)[0]);
  return l--r;
}

int n=7;
pair[] pts; 
pen[] ptsclr;
pen cp=heavygreen;

for(int i=1;i<n;++i) {
  real t = log10(1+10*i/n);
  pts.push(point(fx,intersections(fx,thru(p,(1-t)*fp+t*tgp))[1][0]));
  t=i/n;
  ptsclr.push((1-t)*cp+t*heavyblue);
}

fill(p--(bx,p.y)--fp--cycle,0.12*cyan+white);

arrowbar axisarrow = Arrow(TeXHead);
draw((-0.2,0) -- (xmax,0), arrow=axisarrow, L=Label("$x$", position=EndPoint));
draw((xmin,ymin) -- (xmin,ymax), arrow = axisarrow, L=Label("$y$", position=EndPoint));

draw(shift(p.x,0)*((0,ymin)--(0,ymax)), dashed, L=Label("$x_0$",position=Relative(0)));
draw(shift(0,p.y)*((-0.1,0)--(xmax,0)),dashed,  L=Label("$f(x_0)$",position=Relative(1)));
draw(shift(0,fp.y)*((-0.1,0)--(xmax,0)),heavycyan+dashed,  L=Label("$f(x_0+\Delta)$",position=Relative(1),S+0.1*E));
draw(shift(bx,0)*((0,ymin)--(0,ymax)), heavycyan+linewidth(0.01),  L=Label("$x_0$+\Delta",position=Relative(0)));

for(pair pt:pts) {
  draw(shift(pt.x,0)*((0,-0.01)--(0,ymax)), 0.6*white+0.4*heavycyan+linewidth(0.01));
}

draw(thru(p,fp), cp+linewidth(0.9));

draw(brace((bx,0),(p.x,0)),heavycyan,L=Label("$\Delta$",position=MidPoint,align=S));


draw( fx, red+linewidth(1.2),L=Label("$y=f(x)$",position=Relative(0.9),W) );
label("$P$",p,red, align=3*N+2.5*W);

for(int i=0;i<pts.length;++i) {
  draw(thru(p,pts[i]),0.2*white+ptsclr[i]+linewidth(0.7-(i+1)*(0.7-0.1)/n));
}

draw(tg,heavyblue+linewidth(0.3));
dot(p,red+linewidth(3));
dot(fp,cp+linewidth(3));

for(int i=0;i<pts.length;++i) {
  dot(pts[i],ptsclr[i]+linewidth(2));
}

