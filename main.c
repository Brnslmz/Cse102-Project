#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "header.h"

int main()
{
	Color c1={0,0,0};
	Figure *fig1;
	fig1=start_figure(100,100);
	set_color(fig1,c1);
	set_thickness_resolution(fig1,1,100);
	draw_fx(fig1,cos,-50,50,fig1->resolution);
	export_eps(fig1,"draw_fx.eps");


	Color c2={1,0,0};
	Figure *fig2;
	fig2=start_figure(100,100);
	set_color(fig2,c2);
	set_thickness_resolution(fig2,0.1,100);
	Point2D arr[6]={{0,0},{-5,5},{0,10},{10,10},{15,5},{10,0}};
	draw_polyline(fig2,arr,6);
	export_eps(fig2,"draw_polyline.eps");

	Point2D *linked=(Point2D*)malloc(sizeof(Point2D*));
	Point2D *temp_point;
	temp_point=linked;
	temp_point->x=0;
	temp_point->y=0;
	temp_point->next=(Point2D*)malloc(sizeof(Point2D));
	temp_point=temp_point->next;
	temp_point->x=10;
	temp_point->y=24;
	temp_point->next=(Point2D*)malloc(sizeof(Point2D));
	temp_point=temp_point->next;
	temp_point->x=20;
	temp_point->y=0;
	temp_point->next=(Point2D*)malloc(sizeof(Point2D));
	temp_point=temp_point->next;
	temp_point->next=NULL;
	temp_point=linked;

	Color c3={1,1,0};
	Figure *fig3;
	fig3=start_figure(100,100);
	set_color(fig3,c3);
	set_thickness_resolution(fig3,5,100);
	draw_polygon(fig3,linked);
	export_eps(fig3,"draw_polygon.eps");
	

	Color c4={0,1,0};
	Figure *fig4;
	fig4=start_figure(100,100);
	set_color(fig4,c4);
	set_thickness_resolution(fig4,1,100);
	Point2D center,width_height;
	center.x = center.y = 0;
	width_height.x =25;
	width_height.y = 15;
	draw_ellipse(fig4,&center,&width_height);
	export_eps(fig4,"draw_ellipse.eps");


	Point2D start_roi,end_roi;
	start_roi.x = start_roi.y= 0;
	end_roi.x=end_roi.y=50;
	resize_figure(fig4,&start_roi,&end_roi);//canvas değistirme
	export_eps(fig4,"resize_figure.eps");


	Color c5={0.5,0,0.5};
	Figure *fig5;
	fig5=start_figure(100,100);
	set_color(fig5,c5);
	set_thickness_resolution(fig5,0.5,100);
	Tree *lleft=(Tree*)malloc(sizeof(Tree));
	Tree *lrleft=(Tree*)malloc(sizeof(Tree));
	Tree *rright=(Tree*)malloc(sizeof(Tree));
	Tree *lright=(Tree*)malloc(sizeof(Tree));
	Tree *root=(Tree*)malloc(sizeof(Tree)),*left=(Tree*)malloc(sizeof(Tree)),*right=(Tree*)malloc(sizeof(Tree));
	root->number=5;
	lright->number=10;
	rright->number=6;
	lrleft->number=7;
	lleft->number=18;
	right->number=100;
	left->number=999;
	root->left=left;
	root->right=right;
	root->left->left=lleft;
	root->left->right=lright;
	root->left->right->left=lrleft;
	root->right->right=rright;
	draw_binary_tree(fig5,root);
	export_eps(fig5,"draw_binary_tree.eps");

	scale_figure(fig3,2,2);
	export_eps(fig3,"scale_figure.eps");

	append_figures(fig1,fig2);
	export_eps(fig1,"append_figures.eps");
	return 0;
}