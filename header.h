#ifndef header
#define header

typedef struct Color
{
	double red,green,blue;
}Color;

typedef struct Point2D
{
	double x,y;
	struct Point2D* next;
}Point2D;

typedef struct tree
{
	int number;
	struct tree *left,*right;
}Tree;

typedef struct Figure
{
	double thickness,resolution,width,height;
	Color color;
	Point2D* point;
	struct Figure* next_fig;
	int check;
	Tree* tree;
}Figure;

Figure* start_figure(double width, double height);
void set_thickness_resolution(Figure* fig,double thickness,double resolution);
void set_color(Figure* fig,Color c);
double f(double x);
void draw_fx(Figure* fig,double f(double x),double start_x, double end_x,double step_size);
void draw_ellipse(Figure* fig,Point2D * centre, Point2D * width_height);

void resize_figure(Figure* fig,Point2D *start_roi, Point2D *end_roi);

void draw_polyline(Figure *fig, Point2D *poly_line, int n);
void scale_figure(Figure* fig,double scale_x, double scale_y);
void append_figures(Figure * fig1, Figure * fig2);

void export_eps(Figure* fig, char* file_name);
void draw_polygon(Figure *fig,Point2D * poly_line);
void draw_binary_tree(Figure *fig,Tree * root);

#endif