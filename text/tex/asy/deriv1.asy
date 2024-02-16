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

fill(p--(bx,p.y)--tgp--cycle,0.12*cyan+white);

arrowbar axisarrow = Arrow(TeXHead);
draw((-0.2,0) -- (xmax,0), arrow=axisarrow, L=Label("$x$", position=EndPoint));
draw((xmin,ymin) -- (xmin,ymax), arrow = axisarrow, L=Label("$y$", position=EndPoint));

draw(shift(p.x,0)*((0,ymin)--(0,ymax)), dashed, L=Label("$x_0$",position=Relative(0)));
draw(shift(0,p.y)*((-0.1,0)--(xmax,0)),dashed,  L=Label("$f(x_0)$",position=Relative(1)));
draw(shift(bx,0)*((0,-0.01)--(0,ymax)), heavycyan+linewidth(0.01));

draw( fx, red+linewidth(1.2),L=Label("$y=f(x)$",position=Relative(0.9)) );
label("$P$",p,red, align=3*N+2.5*W);

draw(brace((bx,p.y),p),heavycyan,L=Label("$\Delta$",position=MidPoint,align=S));
draw(brace(tgp,(tgp.x,p.y)),heavycyan,L=Label("$\Delta\cdot\tan(\alpha)$",position=MidPoint,align=E));

draw(tg,heavyblue+linewidth(0.9));

dot(p,red+linewidth(3));
markangle((10,0),o,p,radius=24,L=Label("$\alpha$",position=MidPoint,1.5*W+0.5*S),p=blue);
markangle((10,0),p,p+d,radius=30,L=Label("$\alpha$",position=MidPoint,2*W+0.5*S),p=blue);

