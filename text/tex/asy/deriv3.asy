settings.outformat="pdf";
settings.tex = 'lualatex';
import graph;
import markers;
size(6cm,0);

defaultpen(fontsize(10pt));

real f(real x) { return 8x^3-3*x^4+18*x^2; }
real df(real x) {return 24x^2-12x^3+36x;}
real[] rt = {-1,3,0};


real xmin = -2.5;
real xmax = 4.5;
real ymin = -3;
real ymax = 5;

picture pic;
scale(pic,Linear,Linear(0.03));
path fx =  graph(pic,f,xmin,xmax);
path dfx =  graph(pic,df,xmin,xmax);

arrowbar axisarrow = Arrow(TeXHead);
draw(pic,(xmin,0) -- (xmax,0), arrow=axisarrow, L=Label("$x$", position=EndPoint));
//draw(pic, (0,ymin) -- (0,ymax), arrow = axisarrow, L=Label("$y$", position=EndPoint));
for(real x:rt) {
  draw(pic,(x,ymin)--(x,ymax),dashed+linewidth(0.1),L=Label("$"+string(x)+"$",position=EndPoint));
  dot(pic,Scale(pic,(x,0)), deepcyan+linewidth(3));
  dot(pic,Scale(pic,(x,f(x))),orange+linewidth(3));
  draw(pic,Scale(pic,(x,f(x))-(0.9,0))--Scale(pic,(x,f(x))+(0.9,0)),red+dashed+linewidth(0.2));
}


draw( pic, fx, orange+linewidth(1),L=Label("$y=f(x)$",position=Relative(0.1),W) );
draw( pic, dfx, deepcyan+linewidth(1),L=Label("$y=f'(x)$",position=Relative(0.15),W) );
clip( pic , box((xmin-3,ymin),(xmax+0.5,ymax+0.5)));
dot(pic,Scale(pic,(0,0)), deepcyan+linewidth(3));
add(pic);

