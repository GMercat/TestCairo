#include <iostream>
#include <map>
#include "Drawer.h"


void DrawRect (cairo_t *cr, double aX, double aY, double aW, double aH)
{
   cairo_move_to (cr, aX, aY);
   cairo_line_to (cr, aX + aW, aY);
   cairo_line_to (cr, aX + aW, aY + aH);
   cairo_line_to (cr, aX, aY + aH);
   cairo_close_path(cr);

   cairo_set_source_rgb (cr, 1.0, 1.0, 0.0);
   cairo_fill_preserve(cr);
   cairo_set_source_rgb (cr, 1.0, 0, 0);
   cairo_stroke (cr);
}

void TestLine1 (cairo_t* cr, double aY)
{
   double LengthLine = 400.0;

   double dashes[] = {60.0,  /* ink */
                      20.0,  /* skip */
                      40.0,  /* ink */
                      20.0,  /* skip*/
                      20.0,  /* ink */
                      90.0,  /* skip*/
                      20.0,  /* ink */
                      20.0,  /* skip*/
                      40.0,  /* ink */
                      20.0,  /* skip */
                      60.0,  /* ink */
                     };
   int    ndash  = sizeof (dashes)/sizeof(dashes[0]);
   double offset = 0;

   cairo_set_dash (cr, dashes, ndash, offset);

   cairo_set_line_width (cr, 10);
   cairo_move_to (cr, 50, aY);
   cairo_line_to (cr, LengthLine + 50,aY);
   cairo_set_source_rgb (cr, 0, 0, 0);
   cairo_stroke (cr);

   cairo_set_dash (cr, dashes, 0, 0);

   DrawRect (cr, 40, aY-10.0, 20, 20);

   DrawRect (cr, 440, aY-10.0, 20, 20);
}

void TestLine2 (cairo_t* cr, double aY)
{
   double LengthLine = 400.0;

   double dashes[] = {60.0,  /* ink */
                      20.0,  /* skip */
                      40.0,  /* ink */
                      20.0,  /* skip*/
                      20.0,  /* ink */
                      90.0,  /* skip*/
                      20.0,  /* ink */
                      20.0,  /* skip*/
                      40.0,  /* ink */
                      20.0,  /* skip */
                      60.0,  /* ink */
                     };
   int    ndash  = sizeof (dashes)/sizeof(dashes[0]);
   double offset = 0;

   cairo_set_dash (cr, dashes, ndash, offset);

   cairo_set_line_cap (cr, CAIRO_LINE_CAP_ROUND);
   cairo_set_line_width (cr, 10);
   cairo_move_to (cr, 50, aY);
   cairo_line_to (cr, LengthLine + 50,aY);
   cairo_set_source_rgb (cr, 0, 0, 0);
   cairo_stroke (cr);

   cairo_set_line_cap (cr, CAIRO_LINE_CAP_BUTT);
   cairo_set_dash (cr, dashes, 0, 0);

   DrawRect (cr, 40, aY-10.0, 20, 20);

   DrawRect (cr, 440, aY-10.0, 20, 20);
}

void TestLine4 (cairo_t* cr, double aY)
{
   double LengthLine = 400.0;

   double dashes[] = {50.0,  /* ink */
                      25.0,  /* skip */
                      25.0,  /* ink */
                      50.0  /* skip*/
                     };
   int    ndash  = sizeof (dashes)/sizeof(dashes[0]);
   double offset = 0;

   cairo_set_dash (cr, dashes, ndash, offset);

   cairo_set_line_width (cr, 10);
   cairo_move_to (cr, 50, aY);
   cairo_line_to (cr, LengthLine + 50,aY);
   cairo_set_source_rgb (cr, 0, 0, 0);
   cairo_stroke (cr);

   cairo_set_dash (cr, dashes, 0, 0);

   DrawRect (cr, 40, aY-10.0, 20, 20);

   DrawRect (cr, 440, aY-10.0, 20, 20);
}

void TestLine5 (cairo_t* cr, double aY)
{
   double LengthLine = 400.0;

   cairo_set_line_width (cr, 10);
   cairo_move_to (cr, 50, aY);
   cairo_line_to (cr, (LengthLine+100) / 2.0 - 60, aY);
   cairo_line_to (cr, (LengthLine+100) / 2.0 - 30, aY + 40);
   cairo_line_to (cr, (LengthLine+100) / 2.0     , aY + 40);
   cairo_line_to (cr, (LengthLine+100) / 2.0 + 30, aY + 40);
   cairo_line_to (cr, (LengthLine+100) / 2.0 + 60, aY);
   cairo_line_to (cr, LengthLine + 50,aY);
   cairo_set_source_rgb (cr, 0, 0, 0);
   cairo_stroke (cr);

   DrawRect (cr, 40, aY-10.0, 20, 20);

   DrawRect (cr, 400/2.0-10+50 , aY-10.0, 20, 20);

   DrawRect (cr, 440, aY-10.0, 20, 20);
}

void TestLine6 (cairo_t* cr, double aY)
{
   double LengthLine = 400.0;

   cairo_set_line_width (cr, 10);
   cairo_move_to (cr, 50, aY);
   cairo_line_to (cr, (LengthLine+100) / 2.0 - 75, aY);
   cairo_curve_to (cr, (LengthLine+100) / 2.0 - 75, aY, (LengthLine+100) / 2.0 - 30, aY, (LengthLine+100) / 2.0 - 30, aY + 20);
   cairo_curve_to (cr, (LengthLine+100) / 2.0 - 30, aY + 40, (LengthLine+100) / 2.0, aY + 40, (LengthLine+100) / 2.0, aY + 40);
   cairo_curve_to (cr, (LengthLine+100) / 2.0, aY + 40, (LengthLine+100) / 2.0 + 30, aY + 40, (LengthLine+100) / 2.0 + 30, aY + 20);
   cairo_curve_to (cr, (LengthLine+100) / 2.0 + 30, aY + 20, (LengthLine+100) / 2.0 + 30, aY, (LengthLine+100) / 2.0 + 75, aY);
   cairo_line_to (cr, LengthLine -10 + 50 , aY);
   cairo_set_source_rgb (cr, 0, 0, 0);
   cairo_stroke (cr);

   DrawRect (cr, 40, aY-10.0, 20, 20);

   DrawRect (cr, 400/2.0-10+50 , aY-10.0, 20, 20);

   DrawRect (cr, 440, aY-10.0, 20, 20);
}

void TestImageSDL1 (cairo_t *cr)
{
   SDL_Surface *ImageSDL =SDL_LoadBMP("/home/ineo/Images/cairo.bmp");
   cairo_surface_t *Cairo_Surface = cairo_image_surface_create_for_data ( (unsigned char *)ImageSDL->pixels,
                                                                      CAIRO_FORMAT_RGB24,
                                                                      ImageSDL->w,
                                                                      ImageSDL->h,
                                                                      ImageSDL->pitch);

   double X,Y;
   cairo_get_current_point(cr,&X,&Y);

   std::cout << "TestImageSDL1 : X=" << X << "; Y=" << Y <<  std::endl;

   cairo_set_source_surface (cr, Cairo_Surface, X, Y - ImageSDL->h / 2.0);

}

void TestRotationTexteImage (cairo_t* cr)
{
   cairo_translate (cr, 50,400);
   cairo_rotate (cr, -M_PI/6);

   TestImageSDL1  (cr);
   cairo_paint (cr);
}

void TestRotationMaticeTexteImage (cairo_t* cr)
{
   cairo_matrix_t Matrice;

   double Angle = -M_PI/6;
   double CentreX = 50;
   double CentreY = 400;

   cairo_matrix_init (&Matrice, cos (Angle), sin (Angle), -sin (Angle), cos(Angle), CentreX * (1 - cos (Angle)) + sin (Angle) * CentreY, CentreY * ( 1 - cos (Angle)) - sin (Angle));

   cairo_transform (cr, &Matrice);

   TestImageSDL1  (cr);


   cairo_paint (cr);
}

void TestResultatDansPNG (void)
{
   cairo_surface_t *surface;
   cairo_t *cr;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   surface = cairo_image_surface_create (CAIRO_FORMAT_ARGB32, 750, 500);
   cr = cairo_create (surface);

   /* Examples are in 1.0 x 1.0 coordinate space */
   //cairo_scale (cr, 500, 500);

   cairo_translate (cr, 50,250);
   cairo_rotate (cr, -M_PI/6);
   cairo_set_line_width (cr, 10);
   cairo_set_source_rgb (cr, 0, 0, 0);
   cairo_move_to (cr, 0, 0);
   cairo_line_to (cr, 400, 0);
   cairo_stroke (cr);

   cairo_surface_write_to_png (surface, "TestRotation.png");

   cairo_destroy (cr);
   cairo_surface_destroy (surface);
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   surface = cairo_image_surface_create (CAIRO_FORMAT_ARGB32, 500, 500);
   cr = cairo_create (surface);

   cairo_set_source_rgb (cr, 1.0, 1.0, 1.0);
   cairo_paint (cr);

   TestLine1 (cr,50);
   TestLine2 (cr,100);
   TestLine4 (cr,200);
   TestLine5 (cr, 250);
   TestLine6 (cr, 350);

   /* Write output and clean up */
   cairo_surface_write_to_png (surface, "TestLines.png");
   cairo_destroy (cr);
   cairo_surface_destroy (surface);
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   surface = cairo_image_surface_create (CAIRO_FORMAT_ARGB32, 500, 500);
   cr = cairo_create (surface);





   cairo_surface_write_to_png (surface, "TestFonts.png");

   cairo_destroy (cr);
   cairo_surface_destroy (surface);
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   surface = cairo_image_surface_create_from_png ("/home/ineo/Images/cairo.png");
   cairo_surface_write_to_png (surface, "TestImages.png");
   cairo_surface_destroy (surface);
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   surface = cairo_image_surface_create (CAIRO_FORMAT_ARGB32, 750, 500);
   cr = cairo_create (surface);
   TestRotationTexteImage (cr);
   cairo_surface_write_to_png (surface, "TestImagesSDLTexte.png");
   cairo_destroy (cr);
   cairo_surface_destroy (surface);
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   surface = cairo_image_surface_create (CAIRO_FORMAT_ARGB32, 750, 500);
   cr = cairo_create (surface);
   TestRotationMaticeTexteImage (cr);
   cairo_surface_write_to_png (surface, "TestImagesSDLTexteMatrice.png");
   cairo_destroy (cr);
   cairo_surface_destroy (surface);
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}
void TestRectRound (cairo_t* cr, double aW, double aH)
{
   double radius           = 20.0;
   double x,y;

   cairo_get_current_point (cr, &x, &y);

   cairo_new_sub_path (cr);
   cairo_arc (cr, x + aW - radius, y + radius, radius, -M_PI /2.0, 0.0);
   cairo_arc (cr, x + aW - radius, y + aH - radius, radius, 0.0, M_PI /2.0);
   cairo_arc (cr, x + radius, y + aH - radius, radius, M_PI /2.0, M_PI);
   cairo_arc (cr, x + radius, y + radius, radius, M_PI, 3.0 * M_PI / 2.0);
   cairo_close_path (cr);

   cairo_set_source_rgb (cr, 0.5, 0.5, 1);
   cairo_fill_preserve (cr);
   cairo_set_source_rgb (cr, 1.0, 0, 0);
   cairo_set_line_width (cr, 2.0);
   cairo_stroke (cr);
}

void TestRotation (cairo_surface_t * Cairo_Surface, double aW, double aH, double aAngle)
{
   cairo_t *cr = cairo_create (Cairo_Surface);

   cairo_translate(cr, 320 - aW / 2.0 , 240 - aH / 2.0);

   cairo_matrix_t Matrice;

   double CentreX = aW / 2.0;
   double CentreY = aH / 2.0;

   cairo_matrix_init (&Matrice, cos (aAngle), sin (aAngle), -sin (aAngle), cos(aAngle), CentreX * (1 - cos (aAngle)) + sin (aAngle) * CentreY, CentreY * ( 1 - cos (aAngle)) - sin (aAngle) * CentreX);

   cairo_transform (cr, &Matrice);

   TestRectRound (cr, aW, aH);

}

void TestArc (cairo_t* cr, double aXC,double aYC, double rayon)
{
   cairo_set_source_rgb (cr, 1.0, 1.0, 1.0);
   cairo_set_line_width (cr,5.0);
   cairo_curve_to (cr, aXC, aYC - rayon, aXC + rayon, aYC - rayon, aXC + rayon, aYC);
   cairo_stroke(cr);
}

void TestArc2 (cairo_t* cr, double aXC,double aYC, double rayon)
{
   cairo_set_source_rgb (cr, 1.0, 1.0, 1.0);
   cairo_set_line_width (cr,5.0);
   //cairo_arc (cr, aXC, aYC, rayon,
   cairo_stroke(cr);
}

int main (int argc, char *argv[])
{
   Drawer Drawer;

   int Width = 2000;
   int Height = 1000;

   //Un moyen de s'assurer que le programme va nous attendre pour quitter
   bool quit = false;
   bool b4pt = false;
   //La structure d'événements qu'on va utiliser
   SDL_Event event;

   Point PointA   (0,0);
   Point PointB   (0,0);
   Point PointC   (0,0);
   Point PointD   (0,0);

   SDL_Rect offset;
   offset.x = 0;
   offset.y = 0;

   double Coef = 0.0;
   std::cout << "Coef = " << Coef << std::endl;

   SDL_Init( SDL_INIT_VIDEO );
   SDL_Surface* screen = SDL_SetVideoMode( Width, Height, 32, SDL_SWSURFACE );
   SDL_Surface* source= SDL_CreateRGBSurface (SDL_SWSURFACE, Width, Height, 32, 0,0,0,255);

   /*cairo_surface_t* CairoSurface = cairo_image_surface_create_for_data ( (unsigned char *)source->pixels,
                                                                            CAIRO_FORMAT_ARGB32,
                                                                            source->w,
                                                                            source->h,
                                                                            source->pitch);*/

   Drawer.Init (source);

   //Tant que l'utilisateur ne veut pas quitter
   while( quit == false )
   {
      //Tant qu'il y a un événement à traiter
      while( SDL_PollEvent( &event ) )
      {
         //Si l'utilisateur a cliqué sur le X de la fenêtre
         if( event.type == SDL_QUIT )
         {
            //On quitte le programme
            quit = true;
         }
         else if (event.type == SDL_MOUSEBUTTONUP)
         {
            if ( event.button.x > 0 && event.button.x < Width && event.button.y > 0 && event.button.y <Height)
            {
               if (PointA.X == 0 && PointA.Y == 0)
               {
                  PointA.X = event.button.x;
                  PointA.Y = event.button.y;
               }
               else if (PointB.X == 0 && PointB.Y == 0)
               {
                  PointB.X = event.button.x;
                  PointB.Y = event.button.y;
               }
               else if (PointC.X == 0 && PointC.Y == 0)
               {
                  PointC.X = event.button.x;
                  PointC.Y = event.button.y;
               }
               else if (PointD.X == 0 && PointD.Y == 0)
               {
                  PointD.X = event.button.x;
                  PointD.Y = event.button.y;
               }
               else
               {
                  b4pt = true;
               }
            }
         }

      }

      Drawer.Clear();
      Drawer.ClearRotate();


      /*if (b4pt == false)
      {
         Drawer.SetColor(0.0,0.0,0.0);
         Drawer.DrawPoint(PointA);
         Drawer.DrawPoint(PointB);
         Drawer.DrawPoint(PointC);
         Drawer.DrawPoint(PointD);
      }
      else*/
      if (b4pt == false || b4pt)
      {
         Uint8 *keystates = SDL_GetKeyState( NULL );
         if (keystates)
         {
            if ( keystates[ SDLK_UP ])
            {
               Coef += 0.02;
            }
            else if ( keystates[ SDLK_DOWN ])
            {
               Coef -= 0.02;
            }
            else if ( keystates[ SDLK_F5 ])
            {
               PointA = Point(0.0,0.0);
               PointB = Point(0.0,0.0);
               PointC = Point(0.0,0.0);
               PointD = Point(0.0,0.0);
               b4pt = false;
               Coef = 0.0;
            }
         }

         //std::string Str = "Test";


         //Drawer.DrawText (Str);

         /*
         Point Point1      (100,100);
         Point PointTang1  (200,100);
         Point PointTang2  (400,300);
         Point Point2      (500,300);
         Drawer.SetColor(1.0,0,0);
         Drawer.MoveTo(Point1);
         Drawer.DrawCurve(PointTang1, PointTang2, Point2);
         Drawer.MoveTo(Point1);
         Drawer.SetColor(1.0,1.0,1.0);
         Drawer.DrawLine(PointTang1, 2);
         Drawer.MoveTo(Point2);
         Drawer.DrawLine(PointTang2, 2);
         Drawer.DrawPoint(Point1);
         Drawer.DrawPoint(PointTang1);
         Drawer.DrawPoint(PointTang2);
         Drawer.DrawPoint(Point2);*/

         /*Point PointA   (50,50);
         Point PointB   (200,50);
         Point PointC   (350,200);
         Point PointD   (500,200);
         Point PointE   (650,50);
         Point PointF   (800,50);
         Point PointA1   (200,200);
         Point PointB1   (300,100);
         Point PointC1   (425,200);
         Point PointD1   (550,200);
         Point PointE1   (600,0);
         Point PointF1   (750,0);

         Point PointG   (100,100);
         Point PointH   (300,100);
         Point PointI   (500,200);
         Point PointJ   (700,200);
         Point PointK   (900,100);
         Point PointL   (1100,100);
*/

        /*Drawer.DrawRepere(0.0,0.6,0.0);

         Drawer.SetColor(1.0,0,0);
         Drawer.MoveTo(PointA);
         Drawer.DrawLine(PointB,3);
         Drawer.MoveTo(PointC);
         Drawer.DrawLine(PointD,3);
         Drawer.SetColor(0.0,0.0,0.0);
         Drawer.DrawPoint(PointA);
         Drawer.DrawPoint(PointB);
         Drawer.DrawPoint(PointC);
         Drawer.DrawPoint(PointD);*/

         //Drawer.DrawCurveDebug(PointA, PointB, PointC, PointD, Coef);
         //Drawer.DrawCurve(PointA, PointB, PointC, PointD, Coef);


   /*      Drawer.MoveTo(PointA);
         Drawer.Rotation(45.0);
         Drawer.TestCurve (PointA, PointB, PointC, PointD, PointE, PointF, Coef);
         Drawer.ClearRotate();
         Drawer.MoveTo(PointA);
         Drawer.Rotation2(45.0);
         Drawer.TestCurve (PointA1, PointB1, PointC1, PointD1, PointE1, PointF1, Coef);
         Drawer.ClearRotate();

         //Drawer.TestCurve (PointG, PointH, PointI, PointJ, PointK, PointL, Coef);
    */

         std::cout << "Coef = " << Coef << std::endl;
      }

      Drawer.MoveTo(Point(200,200));
      Drawer.SetColor(0.0,0.0,0.0);
      Drawer.DrawEllipse(100, 100);

      //Drawer.Blit(CairoSurface);
      Drawer.BlitConvert(source);
      SDL_BlitSurface( source, NULL, screen, &offset );

      SDL_Flip( screen );
      SDL_Delay( 100 );
   }

   SDL_FreeSurface( source);
   SDL_FreeSurface( screen );
   //On quitte SDL
   SDL_Quit();

   std::cout << "FINI" << std::endl;

   return 0;
}
