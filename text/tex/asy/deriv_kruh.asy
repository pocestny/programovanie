settings.outformat="pdf";
settings.tex = 'lualatex';
import graph;
import markers;
size(11cm,0);

defaultpen(fontsize(10pt));

real f(real x) {return sqrt(1-x^2);}
real x = -0.5;
pair p = (x,f(x));
path tg = shift(p)*rotate(90)*scale(1.4)*(-p--p);
real xmin = -1.7;
real xmax = 1.1;
real ymin = -0.1;
real ymax = 1.5;
path fx = graph(new pair (real t) {return (sin(t),cos(t));},-pi/2,pi/2);
pair q = intersectionpoint(fx,(0,0)--max(tg)-p);
pair qq = extension((1,0),(1,1),(0,0),max(tg)-p);


for(pair dp : new pair[]{(0,0),-p}){
markangle(p+(1,0)+dp,p+dp,max(tg)+dp,p=orange+linewidth(0.3),L=Label("$\alpha$"),
filltype=FillDraw(drawpen=orange+linewidth(0.3),fillpen=0.2*yellow+0.8*white));
}

draw((0,0)--qq,heavygreen,arrow=Arrow(SimpleHead),L=Label("$\vec v$",position=MidPoint));
draw(qq--(qq.x,0)^^p+(1,0)--intersectionpoint(shift(1,0)*(p--p+(0,10)),tg),orange+dotted);

//draw((0,0)--q,orange,arrow=Arrow(SimpleHead));


arrowbar axisarrow = Arrow(TeXHead);
draw((xmin,0) -- (xmax,0), arrow=axisarrow, L=Label("$x$", position=EndPoint));
draw((0,ymin) -- (0,ymax), arrow = axisarrow, L=Label("$y$", position=EndPoint));

draw((0,0)--1.8*p,gray+dashed+linewidth(0.1));
draw(p--(p.x,-0.1),deepcyan+dashed+linewidth(0.1),L=Label("$x_0$",position=EndPoint));
draw(p-(1,0)--p+(1.1,0),orange+linewidth(0.3));
draw(fx,red+linewidth(0.9), L=Label("$h(x)$",position=Relative(0.75),N+E));
draw(tg,deepcyan+linewidth(0.9));
dot((0,0),linewidth(2));
dot(p,linewidth(2));
draw((0,0)--p,L=Label("$P$",position=EndPoint),arrow=Arrow(SimpleHead));
label("$0$",(0,0),SE);

draw(brace((1,0),(0,0)),heavygreen,L=Label("$1$",position=Relative(0.5),S));
draw(brace(qq,(1,0)),heavygreen,L=Label("$h'(x_0)$",position=Relative(0.5),E));
draw(brace(p+qq,p+(1,0)),orange,L=Label("$h'(x_0)$",position=Relative(0.5),E));

markangle(qq,(0,0),p,radius=10,p=magenta);
dot((0.01,0.05),magenta+linewidth(1.5));
