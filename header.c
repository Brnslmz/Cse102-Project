#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "header.h"

Point2D* new_point();
double calculate_ellipse_y(double x,Point2D* width_height,int neg);
void draw_tree_left(Figure *fig,Tree* root,Point2D* start_p);
void draw_tree_right(Figure *fig,Tree* root,Point2D* start_p);
void draw_left(Figure *fig,Point2D* start_p);
void draw_right(Figure *fig,Point2D* start_p);

Figure* start_figure(double width, double height)
{
	Figure *temp;
	temp = (Figure*)malloc(sizeof(Figure));
	temp->width=width;
	temp->height=height;
	temp->check=0;
	temp->point=NULL;
	temp->next_fig=NULL;
	return temp;
}
void set_color(Figure* fig, Color c)
{
	fig->color.red=c.red;
	fig->color.green=c.green;
	fig->color.blue=c.blue;
}
void set_thickness_resolution(Figure* fig,double thickness,double resolution)
{
	fig->thickness=thickness;
	fig->resolution=resolution;
}
double f(double x)
{
	return sin(x);
}
void draw_fx(Figure* fig,double f(double x),double start_x, double end_x,double step_size)
{
	Point2D *temp_point;
	fig->point = (Point2D*)malloc(sizeof(Point2D));
	temp_point=fig->point;
	for (double i = start_x; i <=end_x; i+=1/step_size)
	{
		temp_point->x=i;
		temp_point->y=f(i);
		temp_point->next=(Point2D*)malloc(sizeof(Point2D));
		temp_point=temp_point->next;
	}
	temp_point->next=NULL;
 	temp_point=fig->point;
}
void draw_circle(Figure* fig,Point2D* center,double r)
{	
	Point2D *radius=new_point();
	radius->x = radius->y = r/2;
	draw_ellipse(fig,center,radius);
}
void draw_ellipse(Figure* fig,Point2D* center,Point2D* width_height)
{
	Point2D *temp_point;
	fig->point =new_point();
	temp_point=fig->point;
	while(temp_point->next!=NULL)
		temp_point=temp_point->next;
	for (double i = -width_height->x; i <= width_height->x; i+=1/fig->resolution)
	{
		temp_point->x=i+center->x;
		temp_point->y=calculate_ellipse_y(i,width_height,0)+center->y;
		temp_point->next=(Point2D*)malloc(sizeof(Point2D));
		temp_point=temp_point->next;
	}
	for (double i = width_height->x; i>= -width_height->x; i-=1/fig->resolution)
	{
		temp_point->x=i+center->x;
		temp_point->y=calculate_ellipse_y(i,width_height,1)+center->y;
		temp_point->next=(Point2D*)malloc(sizeof(Point2D));
		temp_point=temp_point->next;
	}
	for (double i = -width_height->x; i <= (-width_height->x)+1; i+=1/fig->resolution)
	{
		temp_point->x=i+center->x;
		temp_point->y=calculate_ellipse_y(i,width_height,0)+center->y;
		temp_point->next=(Point2D*)malloc(sizeof(Point2D));
		temp_point=temp_point->next;
	}
	temp_point->next=NULL;
 	temp_point=fig->point;
}
double calculate_ellipse_y(double x,Point2D* width_height,int neg)
{	
	double a,b;
	a=(x/width_height->x);
	a=a*a;
	b=1-a;
	b=sqrt(b);
	b=(b*width_height->y);
	if(neg!=0)
		return -b;
	return b;
}
Point2D* new_point()
{
	Point2D *point;
	point = (Point2D*)malloc(sizeof(Point2D));
	point->next = NULL;
	return point;
}
void resize_figure(Figure *fig, Point2D* start_roi, Point2D* end_roi)
{
	fig->width = end_roi->x - start_roi->x;
	fig->height = end_roi->y - start_roi->y;
}
void draw_polyline(Figure *fig, Point2D *poly_line, int n)
{
	Point2D *temp;
	fig->point = new_point();
	temp = fig->point;
	for (int i = 0; i <= n+1; i++)
	{
		temp->x = poly_line[i%n].x;//by %n , it closes the polygon
		temp->y = poly_line[i%n].y;
		temp->next = new_point();
		temp=temp->next;
	}
}
void draw_polygon(Figure *fig,Point2D * poly_line)
{
	Point2D *temp,*temp_line;
	fig->point = new_point();
	temp = fig->point;
	temp_line=poly_line;
	while(temp_line !=NULL)
	{
		temp->x =temp_line->x;
		temp->y =temp_line->y;
		temp->next = new_point();
		temp=temp->next;
		temp_line=temp_line->next;
	}
	temp_line=poly_line;
	temp->x =temp_line->x;
	temp->y =temp_line->y;
	temp->next = new_point();
	temp=temp->next;
	temp_line=temp_line->next;
	temp->x =temp_line->x;
	temp->y =temp_line->y;
	temp->next = new_point();
	temp=temp->next;
	temp->next =NULL;
}
void draw_binary_tree(Figure *fig,Tree* root)
{
	Point2D *start_p=new_point();
	start_p->x=0;
	start_p->y=(fig->height/2)-6;
	draw_circle(fig,start_p,10);
	fig->tree=root;
	fig->check=1;
	if (root==NULL)
	{
		printf("Root Null\n");
	}
	if (root->left != NULL)
	{
		start_p->x=-5;
		start_p->y=(fig->height/2)-6;
		draw_tree_left(fig,root->left,start_p);
	}
	if (root->right != NULL)
	{
		start_p->x=5;
		start_p->y=(fig->height/2)-6;
		draw_tree_right(fig,root->right,start_p);
	}
}
void draw_left(Figure *fig,Point2D* start_p)
{
	double temp_x=start_p->x,temp_y=start_p->y;
	Point2D *temp_point;
	fig->point =new_point();
	temp_point=fig->point;

	temp_point->x=temp_x;
	temp_point->y=temp_y;
	temp_point->next=(Point2D*)malloc(sizeof(Point2D));
	temp_point=temp_point->next;
	temp_point->x= -10+temp_x;
	temp_point->y= -10+temp_y;
	temp_point->next=(Point2D*)malloc(sizeof(Point2D));
	temp_point=temp_point->next;
	temp_point->x= -10+temp_x;
	temp_point->y= -10+temp_y;
	temp_point->next=NULL;
 	temp_point=fig->point;

}
void draw_right(Figure *fig,Point2D* start_p)
{
	double temp_x=start_p->x,temp_y=start_p->y;
	Point2D *temp_point;
	fig->point =new_point();
	temp_point=fig->point;

	temp_point->x=temp_x;
	temp_point->y=temp_y;
	temp_point->next=(Point2D*)malloc(sizeof(Point2D));
	temp_point=temp_point->next;
	temp_point->x= 10+temp_x;
	temp_point->y= -10+temp_y;
	temp_point->next=(Point2D*)malloc(sizeof(Point2D));
	temp_point=temp_point->next;
	temp_point->x= 10+temp_x;
	temp_point->y= -10+temp_y;
	temp_point->next=NULL;
 	temp_point=fig->point;

}
void draw_tree_left(Figure *fig,Tree* root,Point2D* start_p)
{
	double temp_x=start_p->x,temp_y=start_p->y;
	Figure *next_fig,*next_fig2;
	next_fig=start_figure(fig->width,fig->height);
	set_color(next_fig,fig->color);
	set_thickness_resolution(next_fig,fig->thickness,fig->resolution);
	draw_left(next_fig,start_p);
	append_figures(fig,next_fig);

	next_fig2=start_figure(fig->width,fig->height);
	set_color(next_fig2,fig->color);
	set_thickness_resolution(next_fig2,fig->thickness,fig->resolution);

	next_fig2->tree=root;
	next_fig2->check=1;
 	Point2D *temp_center=new_point();
 	temp_center->x=temp_x-10;
	temp_center->y=temp_y-15;

	draw_circle(next_fig2,temp_center,10);
	append_figures(fig,next_fig2);
	if (root->left != NULL)
	{
		start_p->x=temp_x-15;
		start_p->y=temp_y-15;
		draw_tree_left(fig,root->left,start_p);
	}
	if (root->right != NULL)
	{
		start_p->x=temp_x-5;
		start_p->y=temp_y-15;
		draw_tree_right(fig,root->right,start_p);
	}
	
}
void draw_tree_right(Figure *fig,Tree* root,Point2D* start_p)
{
	double temp_x=start_p->x,temp_y=start_p->y;
	Figure *next_fig,*next_fig2;
	next_fig=start_figure(fig->width,fig->height);
	set_color(next_fig,fig->color);
	set_thickness_resolution(next_fig,fig->thickness,fig->resolution);
	draw_right(next_fig,start_p);
	append_figures(fig,next_fig);

	next_fig2=start_figure(fig->width,fig->height);
	set_color(next_fig2,fig->color);
	set_thickness_resolution(next_fig2,fig->thickness,fig->resolution);

	next_fig2->tree=root;
	next_fig2->check=1;
 	Point2D *temp_center=new_point();
 	temp_center->x=temp_x+10;
	temp_center->y=temp_y-15;

	draw_circle(next_fig2,temp_center,10);
	append_figures(fig,next_fig2);
	if (root->left != NULL)
	{
		start_p->x=temp_x+5;
		start_p->y=temp_y-15;
		draw_tree_left(fig,root->left,start_p);
	}
	if (root->right != NULL)
	{
		start_p->x=temp_x+15;
		start_p->y=temp_y-15;
		draw_tree_right(fig,root->right,start_p);
	}
}
void scale_figure(Figure *fig, double scale_x, double scale_y)
{
	Figure *temp_fig = fig;
	Point2D *temp_point;
	while(temp_fig != NULL)
	{
		temp_point = temp_fig->point;
		while(temp_point != NULL)
		{
			temp_point->x *= scale_x;
			temp_point->y *= scale_y;
			temp_point = temp_point->next;
		}
		temp_fig = temp_fig->next_fig;
	}
}
void append_figures(Figure *fig1, Figure *fig2)
{
	Figure *temp = fig1;
	while(temp->next_fig != NULL)
		temp = temp->next_fig;
	temp->next_fig =fig2;
}
void export_eps(Figure* fig, char* file_name)
{	
	Figure *temp_fig;
	temp_fig =fig;
	Point2D *temp_point;

	FILE *in=fopen(file_name,"w+");
	fprintf(in,"%%!PS\n");
	fprintf(in,"%%%%BoundingBox:%f %f %f %f\n",-(fig->width)/2,-fig->height/2,fig->width/2,fig->height/2);
	while(temp_fig!=NULL)
	{
		fprintf(in,"newpath\n");
		fprintf(in," %f %f %f setrgbcolor\n",temp_fig->color.red,temp_fig->color.green,temp_fig->color.blue );
		fprintf(in,"%f setlinewidth\n",temp_fig->thickness );
		if(temp_fig->point!=NULL)
		{
			temp_point=temp_fig->point;
			if (temp_fig->check==1)
			{
				fprintf(in,"%f %f moveto\n",(temp_point->x)+1.5,(temp_point->y)-1.5);
				fprintf(in,"/Times-Roman findfont 5 scalefont setfont");
				fprintf(in,"(%d) show\n",temp_fig->tree->number);
			}
			fprintf(in,"%f %f moveto\n",temp_point->x,temp_point->y);
			while(temp_point->next!=NULL)
			{
				fprintf(in,"%f %f lineto\n",temp_point->x,temp_point->y);
				temp_point=temp_point->next;
			}	
 			fprintf(in,"stroke\n");
		}
		temp_fig=temp_fig->next_fig;
	 	fprintf(in,"closepath\n");
	 	fprintf(in,"stroke\n");
	}
 	fprintf(in,"showpage\n");

}