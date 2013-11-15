#include "Drawer.h"

#include <iostream>
#include <vector>


/// Buffer sur la fonte TTF System
extern char _TTF_SystemFont_Data[];
/// Taille du buffer de la font TTF System
extern int _TTF_SystemFont_Size;

Drawer::Drawer (void):
   mCairoSurface (NULL),
   mCairoDC (NULL),
   mLibrary (NULL),
   mFontSystem(NULL),
   mFontTest(NULL),
   mAngle(0.0)
{

}

Drawer::~Drawer (void)
{
}

void Drawer::Init (SDL_Surface* aSource)
{
  /* mCairoSurface = cairo_image_surface_create_for_data ( (unsigned char *)aSource->pixels,
                                                                         CAIRO_FORMAT_RGB24,
                                                                         aSource->w,
                                                                         aSource->h,
                                                                         aSource->pitch);*/

   mCairoSurface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, aSource->w, aSource->h);

   mCairoDC = cairo_create (mCairoSurface);

   LoadFonts();
}

void Drawer::LoadFonts(void)
{
   int error = FT_Init_FreeType(&mLibrary);
   if ( error )
   {
      std::cout << "ERROR INIT LIB FONT" << std::endl;
   }
   else
   {
      std::vector<std::string> FontFileName;
      FontFileName.push_back("/usr/share/fonts/truetype/ubuntu-font-family/Ubuntu-R.ttf");
      FontFileName.push_back("/usr/share/fonts/truetype/ubuntu-font-family/Ubuntu-B.ttf");
      FontFileName.push_back("/usr/share/fonts/truetype/ubuntu-font-family/Ubuntu-RI.ttf");
      FontFileName.push_back("/usr/share/fonts/truetype/ubuntu-font-family/Ubuntu-BI.ttf");

      std::vector<std::string> FontName;
      FontName.push_back("Ubuntu-R");
      FontName.push_back("Ubuntu-B");
      FontName.push_back("Ubuntu-RI");
      FontName.push_back("Ubuntu-BI");

      for (unsigned int i = 0; i<FontFileName.size();++i)
      {
         FT_Face     Face = NULL;
         error = FT_New_Face (mLibrary, FontFileName[i].c_str(),  0, &Face);
         if ( error == FT_Err_Unknown_File_Format )
         {
            std::cout << "ERROR LOAD FONT => Format unsupported" << std::endl;
         }
         else if (error)
         {
            std::cout << "ERROR LOAD FONT"  << std::endl;
         }
         else
         {
            mFacesMap.insert (std::pair<std::string,FT_Face>(FontName[i], Face));
         }

/*
         std::cout << "Sizeof *FACE=" << sizeof(*Face) << std::endl;
         std::cout << "Sizeof BITMAPSIZE=" << sizeof(*(*Face).available_sizes) << std::endl;
         std::cout << "Sizeof charmaps=" << sizeof(**(*Face).charmaps) << std::endl;
         std::cout << "Sizeof charmap=" << sizeof(*(*Face).charmap) << std::endl;
         std::cout << "Sizeof glyph=" << sizeof(*(*Face).glyph) << std::endl;
         std::cout << "Sizeof size=" << sizeof(*(*Face).size) << std::endl;

         std::cout << "Sizeof FACE=" << sizeof(*Face) + sizeof(*(*Face).available_sizes) + sizeof(**(*Face).charmaps) + sizeof(*(*Face).charmap) + sizeof(*(*Face).glyph) + sizeof(*(*Face).size) << std::endl;
*/
      }

      error = FT_New_Memory_Face (mLibrary, (const FT_Byte*)&_TTF_SystemFont_Data, _TTF_SystemFont_Size, 0, &mFontSystem);
      if ( error == FT_Err_Unknown_File_Format )
      {
         std::cout << "ERROR LOAD FONTSYSTEM => Format unsupported" << std::endl;
      }
      else if (error)
      {
         std::cout << "ERROR N°:" << error << "LOAD FONTSYSTEM"  << std::endl;
      }

      error = FT_New_Face (mLibrary, "/usr/share/fonts/truetype/ubuntu-font-family/Ubuntu-R.ttf", 0, &mFontTest);
      if ( error == FT_Err_Unknown_File_Format )
      {
         std::cout << "ERROR LOAD FONTTEST => Format unsupported" << std::endl;
      }
      else if (error)
      {
         std::cout << "ERROR N°:" << error << "LOAD FONTTEST"  << std::endl;
      }
   }
}

void Drawer::UnLoadFonts(void)
{

}

void Drawer::Blit (cairo_surface_t* apDest)
{
   /*Uint32 amask = 0xff000000;
   Uint32 rmask = 0x00ff0000;
   Uint32 gmask = 0x0000ff00;
   Uint32 bmask = 0x000000ff;
   unsigned char*    CairoSurfaceData  = cairo_image_surface_get_data(mCairoSurface);
   cairo_surface_t*  CairoSurfaceFormat= cairo_image_surface_get_format(mCairoSurface);
   int               CairoSurfaceWidth = cairo_image_surface_get_width(mCairoSurface);
   int               CairoSurfaceHeight= cairo_image_surface_get_height(mCairoSurface);
   int               CairoSurfaceStride= cairo_image_surface_get_stride(mCairoSurface);*/

   cairo_set_source_surface (mCairoDC, apDest, 0.0,0.0);
   cairo_paint(mCairoDC);
}

void Drawer::BlitConvert (SDL_Surface* apDest)
{
   if (apDest)
   {
      Uint32 rmask, gmask, bmask, amask;

      amask = 0xff000000;
      rmask = 0x00ff0000;
      gmask = 0x0000ff00;
      bmask = 0x000000ff;

      unsigned char* CairoSurfaceData  = cairo_image_surface_get_data(mCairoSurface);
      int            CairoSurfaceWidth = cairo_image_surface_get_width(mCairoSurface);
      int            CairoSurfaceHeight= cairo_image_surface_get_height(mCairoSurface);
      int            CairoSurfaceStride= cairo_image_surface_get_stride(mCairoSurface);

      SDL_Surface* pCairoSdlSurface = SDL_CreateRGBSurfaceFrom(CairoSurfaceData, CairoSurfaceWidth, CairoSurfaceHeight, 32, CairoSurfaceStride, rmask, gmask, bmask, amask);
      SDL_BlitSurface (pCairoSdlSurface, NULL, apDest, NULL);
      //cairo_set_source_surface(mCairoDC, pCairoSurfaceSDL, 0.0, 0.0);
      //cairo_paint(mCairoDC);
   }
}

void Drawer::DrawRepere (double aR, double aG, double aB)
{
   SetColor(aR, aG, aB);
   /*MoveTo(Point(0,0));
   DrawLine(Point(0,1000), 2);*/
   MoveTo(Point(0,0));
   DrawLine(Point(1000,0), 2);
}

void Drawer::SetColor(double aR, double aG, double aB)
{
   cairo_set_source_rgb (mCairoDC, aR, aG, aB);
}

void Drawer::Clear (void)
{
   cairo_set_source_rgb(mCairoDC, 1.0, 1.0, 1.0);
   cairo_paint (mCairoDC);
}

void Drawer::ClearRotate (void)
{
   cairo_identity_matrix(mCairoDC);
}

void Drawer::MoveTo (const Point& aPoint)
{
   cairo_move_to(mCairoDC, aPoint.X, aPoint.Y);
}

void Drawer::DrawPoint(const Point& aPoint, double aRadius/*=10*/)
{
   cairo_arc (mCairoDC, aPoint.X, aPoint.Y, aRadius, 0, 2*M_PI);
   cairo_fill(mCairoDC);
}

void Drawer::DrawLine(const Point& aEndPoint, double aWidth/*=10*/)
{
   cairo_line_to(mCairoDC, aEndPoint.X, aEndPoint.Y);

   cairo_set_line_width(mCairoDC, aWidth);
   cairo_stroke(mCairoDC);
}

void Drawer::DrawArc(const Point& aPoint, double aRadius, double aRadian, double aWidth/*=10*/)
{
   cairo_arc (mCairoDC, aPoint.X, aPoint.Y, aRadius, 0, aRadian);
   cairo_set_line_width(mCairoDC, aWidth);
   cairo_stroke(mCairoDC);
}

void Drawer::DrawCurve(const Point& aTangPoint1, const Point& aTangPoint2, const Point& aEndPoint)
{
   cairo_curve_to(mCairoDC, aTangPoint1.X, aTangPoint1.Y, aTangPoint2.X, aTangPoint2.Y, aEndPoint.X, aEndPoint.Y);

   cairo_set_line_width(mCairoDC, 10);
   cairo_stroke(mCairoDC);
}

void Drawer::DrawCurve(const Point& aPrevPoint, const Point& aStartPoint, const Point& aEndPoint, const Point& aNextPoint, double& aCoef)
{
   if (aCoef < 0.0)
      aCoef = 0.0;
   else if (aCoef > 1.0)
      aCoef = 1.0;

   double AngleRadianR0toR1 = 0.0;
   cairo_matrix_t TranslateMatrixR0toR1;
   cairo_matrix_t RotateMatrixR0toR1;
   Point StartPointInR1 = aStartPoint;
   Point EndPointInR1 = aEndPoint;

   double AngleRadianR0toR2 = 0.0;
   cairo_matrix_t TranslateMatrixR0toR2;
   cairo_matrix_t RotateMatrixR0toR2;
   Point StartPointInR2 = aStartPoint;
   Point EndPointInR2 = aEndPoint;

   double DistTanStart  = 0.0;
   double DistTanEnd    = 0.0;

   Point StartTanPoint(0.0,0.0);
   Point StartTanPointInR1(0,0);
   Point EndTanPoint(0.0,0.0);
   Point EndTanPointInR2(0,0);

   // Il faut que 'aPrevPoint' et 'aStartPoint' soit non confondu et 'aEndPoint' et 'aNextPoint' aussi
   if ((aPrevPoint != aStartPoint) && (aEndPoint != aNextPoint))
   {
      // Calcul de l'angle de rotation du nouveau repère R1 (aPrevPoint/aStartPoint)
      AngleRadianR0toR1 = atan2 (aStartPoint.Y - aPrevPoint.Y, aStartPoint.X - aPrevPoint.X);

      // Translation du repère au point 'aPrevPoint'
      cairo_matrix_init_translate(&TranslateMatrixR0toR1, aPrevPoint.X, aPrevPoint.Y);
      // Rotation du repère d'angle 'AngleRadianR1'
      cairo_matrix_init_rotate(&RotateMatrixR0toR1, AngleRadianR0toR1);

      // Calcul des coordonnées des points aStartPoint, aEndPoint, TanStartPointLocal dans le repère R1
      // Point B et C R0 => Point B et C R1
      cairo_matrix_invert(&TranslateMatrixR0toR1);
      cairo_matrix_transform_point(&TranslateMatrixR0toR1, &EndPointInR1.X, &EndPointInR1.Y);
      cairo_matrix_transform_point(&TranslateMatrixR0toR1, &StartPointInR1.X, &StartPointInR1.Y);
      cairo_matrix_invert(&RotateMatrixR0toR1);
      cairo_matrix_transform_point(&RotateMatrixR0toR1, &EndPointInR1.X, &EndPointInR1.Y);
      cairo_matrix_transform_point(&RotateMatrixR0toR1, &StartPointInR1.X, &StartPointInR1.Y);

      // Coordonnées de StartPointTan dans le repère R1
      StartTanPointInR1.X = EndPointInR1.X;
      StartTanPointInR1.Y = 0.0;

      // Sauvegarde de la distance du point pour le tracer de la tangente
      DistTanStart = abs(StartTanPointInR1.X - StartPointInR1.X);

      /////////////

      // Calcul de l'angle de rotation du nouveau repère R1 (aPrevPoint/aStartPoint)
      AngleRadianR0toR2 = atan2 (aEndPoint.Y - aNextPoint.Y, aEndPoint.X - aNextPoint.X);

      // Translation du repère au point 'aNextPoint'
      cairo_matrix_init_translate(&TranslateMatrixR0toR2, aNextPoint.X, aNextPoint.Y);
      // Rotation du repère d'angle 'AngleRadianR0toR2'
      cairo_matrix_init_rotate(&RotateMatrixR0toR2, AngleRadianR0toR2);

      // Calcul des coordonnées du Point aStartPoint dans le repère R2
      // Point B et C R0 => Point B et C R2
      cairo_matrix_invert(&TranslateMatrixR0toR2);
      cairo_matrix_transform_point(&TranslateMatrixR0toR2, &StartPointInR2.X, &StartPointInR2.Y);
      cairo_matrix_transform_point(&TranslateMatrixR0toR2, &EndPointInR2.X, &EndPointInR2.Y);
      cairo_matrix_invert(&RotateMatrixR0toR2);
      cairo_matrix_transform_point(&RotateMatrixR0toR2, &StartPointInR2.X, &StartPointInR2.Y);
      cairo_matrix_transform_point(&RotateMatrixR0toR2, &EndPointInR2.X, &EndPointInR2.Y);

      // Coordonnées de EndPointTan dans le repère R2
      EndTanPointInR2.X = StartPointInR2.X;
      EndTanPointInR2.Y = 0.0;

      // Sauvegarde de la distance du point pour le tracer de la tangente
      DistTanEnd = abs(EndTanPointInR2.X - EndPointInR2.X);

      // Cas : (12) <=> DistTan12 / 2 et (34) <=> DistTan34 / 2
      // Coordonnées de TanStartPoint dans le repère R1
      StartTanPoint.X = StartPointInR1.X + DistTanStart * 0.5 * aCoef;
      StartTanPoint.Y = 0.0;
      cairo_matrix_invert(&RotateMatrixR0toR1);
      cairo_matrix_transform_point(&RotateMatrixR0toR1, &StartTanPoint.X, &StartTanPoint.Y);
      cairo_matrix_invert(&TranslateMatrixR0toR1);
      cairo_matrix_transform_point(&TranslateMatrixR0toR1, &StartTanPoint.X, &StartTanPoint.Y);
      // Coordonnées de TanEndPoint dans le repère R1
      EndTanPoint.X = EndPointInR2.X + DistTanEnd * 0.5 * aCoef;
      EndTanPoint.Y = 0.0;
      cairo_matrix_invert(&RotateMatrixR0toR2);
      cairo_matrix_transform_point(&RotateMatrixR0toR2, &EndTanPoint.X, &EndTanPoint.Y);
      cairo_matrix_invert(&TranslateMatrixR0toR2);
      cairo_matrix_transform_point(&TranslateMatrixR0toR2, &EndTanPoint.X, &EndTanPoint.Y);


      cairo_move_to(mCairoDC, aStartPoint.X, aStartPoint.Y);
      cairo_curve_to(mCairoDC, StartTanPoint.X,StartTanPoint.Y, EndTanPoint.X, EndTanPoint.Y, aEndPoint.X, aEndPoint.Y);
      cairo_set_line_width(mCairoDC, 3);
      cairo_stroke(mCairoDC);
   }
}

void Drawer::DrawCurveDebug(const Point& aPrevPoint, const Point& aStartPoint, const Point& aEndPoint, const Point& aNextPoint, double& aCoef)
{
   if (aCoef < 0.0)
      aCoef = 0.0;
   else if (aCoef > 1.0)
      aCoef = 1.0;

   Point PrevPointLocal = aPrevPoint;
   Point StartPointLocal = aStartPoint;
   Point EndPointLocal = aEndPoint;
   Point NextPointLocal = aNextPoint;

   Point TanStartPointLocalCas1(0.0,0.0);
   Point TanStartPointLocalCas1R1(0.0,0.0);
   Point TanEndPointLocalCas1(0.0,0.0);
   Point TanEndPointLocalCas1R2(0.0,0.0);

   Point TanStartPointLocalCas2(0.0,0.0);
   Point TanStartPointLocalCas2R1(0.0,0.0);
   Point TanEndPointLocalCas2(0.0,0.0);
   Point TanEndPointLocalCas2R2(0.0,0.0);

   Point TanStartPointLocalCas3(0.0,0.0);
   Point TanStartPointLocalCas3R1(0.0,0.0);
   Point TanEndPointLocalCas3(0.0,0.0);
   Point TanEndPointLocalCas3R2(0.0,0.0);

   Point TanStartPointLocalCas4(0.0,0.0);
   Point TanEndPointLocalCas4(0.0,0.0);
   /* DEBUG
   std::cout << "PrevPointLocal  = (" << PrevPointLocal.X << "," << PrevPointLocal.Y << ")" << std::endl;
   std::cout << "StartPointLocal = (" << StartPointLocal.X << "," << StartPointLocal.Y << ")" << std::endl;
   std::cout << "EndPointLocal   = (" << EndPointLocal.X << "," << EndPointLocal.Y << ")" << std::endl;
   std::cout << "NextPointLocal  = (" << NextPointLocal.X << "," << NextPointLocal.Y << ")" << std::endl << std::endl; */

   Point StartPointTan(0,0);
   Point EndPointTan(0,0);

   double DistTan12  = 0.0;
   double DistTan34  = 0.0;
   double MinDistTan = 0.0;

   double AngleRadianR1 = 0.0;
   cairo_matrix_t TranslateMatrixR0toR1;
   cairo_matrix_t RotateMatrixR0toR1;
   Point StartPointLocalR1 = StartPointLocal;
   Point EndPointR1(0,0);
   Point StartPointTanR1(0,0);

   double AngleRadianR2 = 0.0;
   cairo_matrix_t TranslateMatrixR0toR2;
   cairo_matrix_t RotateMatrixR0toR2;
   Point StartPointLocalR2(0,0);
   Point EndPointR2 = EndPointLocal;
   Point EndPointTanR2(0,0);

   // Il faut que 'aPrevPoint' et 'aStartPoint' soit non confondu et 'aEndPoint' et 'aNextPoint' aussi
   if ((PrevPointLocal != StartPointLocal) && (EndPointLocal != NextPointLocal))
   {
      // Calcul de l'angle de rotation du nouveau repère R1 (aPrevPoint/aStartPoint)
      AngleRadianR1 = atan2 (StartPointLocal.Y - PrevPointLocal.Y, StartPointLocal.X - PrevPointLocal.X);

      /* DEBUG
      std::cout << "AngleRadianR1 = " << AngleRadianR1 << std::endl << std::endl;*/
      SetColor(0,0,0);
      MoveTo(PrevPointLocal);
      DrawLine(StartPointLocal,1);
      //DrawArc (PrevPointLocal,30, AngleRadianR1,1);

      // Translation du repère au point 'aPrevPoint'
      cairo_matrix_init_translate(&TranslateMatrixR0toR1, PrevPointLocal.X, PrevPointLocal.Y);
//      cairo_transform(mCairoDC, &TranslateMatrixR1);

      // Rotation du repère d'angle 'AngleRadianR1'
      cairo_matrix_init_rotate(&RotateMatrixR0toR1, AngleRadianR1);
//      cairo_transform(mCairoDC, &RotateMatrixR1);

      // Calcul des coordonnées des points StartPointLocal, EndPointLocal, TanStartPointLocal dans le repère R1
      // Point B et C R0 => Point B et C R1
      cairo_matrix_invert(&TranslateMatrixR0toR1);
      cairo_matrix_transform_point(&TranslateMatrixR0toR1, &EndPointLocal.X, &EndPointLocal.Y);
      cairo_matrix_transform_point(&TranslateMatrixR0toR1, &StartPointLocalR1.X, &StartPointLocalR1.Y);
      cairo_matrix_invert(&RotateMatrixR0toR1);
      cairo_matrix_transform_point(&RotateMatrixR0toR1, &EndPointLocal.X, &EndPointLocal.Y);
      cairo_matrix_transform_point(&RotateMatrixR0toR1, &StartPointLocalR1.X, &StartPointLocalR1.Y);
      EndPointR1 = EndPointLocal;
      // Reset du EndPointLocal
      EndPointLocal = aEndPoint;

      /* DEBUG
      std::cout << "EndPointR1     = (" << EndPointR1.X << "," << EndPointR1.Y << ")" << std::endl;*/
//      DrawRepere(0.0,0.0,0.6);

      // Coordonnées de StartPointTan dans le repère R1
      StartPointTanR1.X = EndPointR1.X;
      StartPointTanR1.Y = 0.0;

      // Sauvegarde de la distance du point pour le tracer de la tangente
      DistTan12 = abs(StartPointTanR1.X - StartPointLocalR1.X);
      MinDistTan = DistTan12;

      /* DEBUG
      std::cout << "StartPointTanR1= (" << StartPointTanR1.X << "," << StartPointTanR1.Y << ")" << std::endl << std::endl;*/
//      MoveTo(StartPointTanR1);
//      DrawLine(EndPointR1,1);

      // Calcul des coordonnées de StartPointTan dans le repère R0 (Origine)
//      StartPointTan = StartPointTanR1;
//      cairo_matrix_invert(&RotateMatrixR1);
//      cairo_matrix_transform_point(&RotateMatrixR1, &StartPointTan.X, &StartPointTan.Y);
//      cairo_matrix_invert(&TranslateMatrixR1);
//      cairo_matrix_transform_point(&TranslateMatrixR1, &StartPointTan.X, &StartPointTan.Y);

//      cairo_identity_matrix(mCairoDC);

      /* DEBUG
      std::cout << "StartPointTan = (" << StartPointTan.X << "," << StartPointTan.Y << ")" << std::endl << std::endl << std::endl;*/
//      SetColor(0,0,0);
//      DrawPoint(StartPointTan,3);

      /////////////

      // Calcul de l'angle de rotation du nouveau repère R1 (aPrevPoint/aStartPoint)
      AngleRadianR2 = atan2 (EndPointLocal.Y - NextPointLocal.Y, EndPointLocal.X - NextPointLocal.X);

      /* DEBUG
      std::cout << "AngleRadianR1 = " << AngleRadianR1 << std::endl << std::endl;*/
//      SetColor(0,0,0);
//      MoveTo(NextPointLocal);
//      DrawLine(EndPointLocal,1);
      //DrawArc (NextPointLocal,30, AngleRadianR2,1);

      // Translation du repère au point 'aNextPoint'
      cairo_matrix_init_translate(&TranslateMatrixR0toR2, NextPointLocal.X, NextPointLocal.Y);
//      cairo_transform(mCairoDC, &TranslateMatrixR2);

      // Rotation du repère d'angle 'AngleRadianR2'
      cairo_matrix_init_rotate(&RotateMatrixR0toR2, AngleRadianR2);
//      cairo_transform(mCairoDC, &RotateMatrixR2);

      // Calcul des coordonnées du Point StartPointLocal dans le repère R2
      // Point B et C R0 => Point B et C R2
      cairo_matrix_invert(&TranslateMatrixR0toR2);
      cairo_matrix_transform_point(&TranslateMatrixR0toR2, &StartPointLocal.X, &StartPointLocal.Y);
      cairo_matrix_transform_point(&TranslateMatrixR0toR2, &EndPointR2.X, &EndPointR2.Y);
      cairo_matrix_invert(&RotateMatrixR0toR2);
      cairo_matrix_transform_point(&RotateMatrixR0toR2, &StartPointLocal.X, &StartPointLocal.Y);
      cairo_matrix_transform_point(&RotateMatrixR0toR2, &EndPointR2.X, &EndPointR2.Y);
      StartPointLocalR2 = StartPointLocal;
      // Reset du StartPointLocal
      StartPointLocal = aStartPoint;

      /* DEBUG
      std::cout << "StartPointLocalR2 = (" << StartPointLocalR2.X << "," << StartPointLocalR2.Y << ")" << std::endl;*/
//      DrawRepere(0.0,0.0,0.6);

      // Coordonnées de EndPointTan dans le repère R2
      EndPointTanR2.X = StartPointLocalR2.X;
      EndPointTanR2.Y = 0.0;

      // Sauvegarde de la distance du point pour le tracer de la tangente
      DistTan34 = abs(EndPointTanR2.X - EndPointR2.X);
      if(DistTan34 < MinDistTan)
         MinDistTan = DistTan34;

      /* DEBUG
      std::cout << "EndPointTanR2     = (" << EndPointTanR2.X << "," << EndPointTanR2.Y << ")" << std::endl << std::endl;*/
//      MoveTo(EndPointTanR2);
//      DrawLine(StartPointLocalR2,1);

      // Calcul des coordonnées de EndPointTan dans le repère R0 (Origine)
//      EndPointTan = EndPointTanR2;
//      cairo_matrix_invert(&RotateMatrixR2);
//      cairo_matrix_transform_point(&RotateMatrixR2, &EndPointTan.X, &EndPointTan.Y);
//      cairo_matrix_invert(&TranslateMatrixR2);
//      cairo_matrix_transform_point(&TranslateMatrixR2, &EndPointTan.X, &EndPointTan.Y);

//      cairo_identity_matrix(mCairoDC);

      /* DEBUG
      std::cout << "EndPointTan = (" << EndPointTan.X << "," << EndPointTan.Y << ")" << std::endl;
      std::cout << "MinDistTan = " << MinDistTan << std::endl << std::endl << std::endl;*/
//      DrawPoint(EndPointTan,3);

      /* DEBUG
      std::cout << "Valeurs : " << std::endl;
      std::cout << "DistTan (1->2) = " << DistTan12 << std::endl;
      std::cout << "DistTan (3->4) = " << DistTan34 << std::endl;
      std::cout << "MinDistTan     = " << MinDistTan << std::endl << std::endl;*/

      cairo_matrix_invert(&RotateMatrixR0toR1);
      cairo_matrix_invert(&TranslateMatrixR0toR1);
      cairo_matrix_invert(&RotateMatrixR0toR2);
      cairo_matrix_invert(&TranslateMatrixR0toR2);

// 1er cas : (12) <=> DistTan12 et (34) <=> DistTan34
   // Coordonnées de TanStartPointLocal dans le repère R1
      TanStartPointLocalCas1R1.X = StartPointLocalR1.X + DistTan12 * aCoef;
      TanStartPointLocalCas1R1.Y = 0.0;
      TanStartPointLocalCas1 = TanStartPointLocalCas1R1;
      cairo_matrix_transform_point(&RotateMatrixR0toR1, &TanStartPointLocalCas1.X, &TanStartPointLocalCas1.Y);
      cairo_matrix_transform_point(&TranslateMatrixR0toR1, &TanStartPointLocalCas1.X, &TanStartPointLocalCas1.Y);
   // Coordonnées de TanEndPointLocal dans le repère R1
      TanEndPointLocalCas1R2.X = EndPointR2.X + DistTan34 * aCoef;
      TanEndPointLocalCas1R2.Y = 0.0;
      TanEndPointLocalCas1 = TanEndPointLocalCas1R2;
      cairo_matrix_transform_point(&RotateMatrixR0toR2, &TanEndPointLocalCas1.X, &TanEndPointLocalCas1.Y);
      cairo_matrix_transform_point(&TranslateMatrixR0toR2, &TanEndPointLocalCas1.X, &TanEndPointLocalCas1.Y);

      SetColor(1,0,0);
      DrawPoint(TanStartPointLocalCas1,3);
      DrawPoint(TanEndPointLocalCas1,3);

      cairo_move_to(mCairoDC, aStartPoint.X, aStartPoint.Y);
      cairo_curve_to(mCairoDC, TanStartPointLocalCas1.X,TanStartPointLocalCas1.Y, TanEndPointLocalCas1.X, TanEndPointLocalCas1.Y, aEndPoint.X, aEndPoint.Y);
      cairo_set_line_width(mCairoDC, 3);
      cairo_stroke(mCairoDC);

// 2eme cas : (12) <=> DistTan12 / 2 et (34) <=> DistTan34 / 2
   // Coordonnées de TanStartPointLocal dans le repère R1
      TanStartPointLocalCas2R1.X = StartPointLocalR1.X + DistTan12 * 0.5 * aCoef;
      TanStartPointLocalCas2R1.Y = 0.0;
      TanStartPointLocalCas2 = TanStartPointLocalCas2R1;
      cairo_matrix_transform_point(&RotateMatrixR0toR1, &TanStartPointLocalCas2.X, &TanStartPointLocalCas2.Y);
      cairo_matrix_transform_point(&TranslateMatrixR0toR1, &TanStartPointLocalCas2.X, &TanStartPointLocalCas2.Y);
   // Coordonnées de TanEndPointLocal dans le repère R1
      TanEndPointLocalCas2R2.X = EndPointR2.X + DistTan34 * 0.5 * aCoef;
      TanEndPointLocalCas2R2.Y = 0.0;
      TanEndPointLocalCas2 = TanEndPointLocalCas2R2;
      cairo_matrix_transform_point(&RotateMatrixR0toR2, &TanEndPointLocalCas2.X, &TanEndPointLocalCas2.Y);
      cairo_matrix_transform_point(&TranslateMatrixR0toR2, &TanEndPointLocalCas2.X, &TanEndPointLocalCas2.Y);

      SetColor(0,1,0);
      DrawPoint(TanStartPointLocalCas2,3);
      DrawPoint(TanEndPointLocalCas2,3);

      cairo_move_to(mCairoDC, aStartPoint.X, aStartPoint.Y);
      cairo_curve_to(mCairoDC, TanStartPointLocalCas2.X,TanStartPointLocalCas2.Y, TanEndPointLocalCas2.X, TanEndPointLocalCas2.Y, aEndPoint.X, aEndPoint.Y);
      cairo_set_line_width(mCairoDC, 3);
      cairo_stroke(mCairoDC);



// 3ème cas : (12) <=> MinDistTan et (34) <=> MinDistTan
   // Coordonnées de TanStartPointLocal dans le repère R1
      TanStartPointLocalCas3.X = StartPointLocalR1.X + MinDistTan * aCoef;
      TanStartPointLocalCas3.Y = 0.0;
      cairo_matrix_transform_point(&RotateMatrixR0toR1, &TanStartPointLocalCas3.X, &TanStartPointLocalCas3.Y);
      cairo_matrix_transform_point(&TranslateMatrixR0toR1, &TanStartPointLocalCas3.X, &TanStartPointLocalCas3.Y);
   // Coordonnées de TanEndPointLocal dans le repère R1
      TanEndPointLocalCas3.X = EndPointR2.X + MinDistTan * aCoef;
      TanEndPointLocalCas3.Y = 0.0;
      cairo_matrix_transform_point(&RotateMatrixR0toR2, &TanEndPointLocalCas3.X, &TanEndPointLocalCas3.Y);
      cairo_matrix_transform_point(&TranslateMatrixR0toR2, &TanEndPointLocalCas3.X, &TanEndPointLocalCas3.Y);

      SetColor(0,0,1);
      DrawPoint(TanStartPointLocalCas3,3);
      DrawPoint(TanEndPointLocalCas3,3);

      cairo_move_to(mCairoDC, aStartPoint.X, aStartPoint.Y);
      cairo_curve_to(mCairoDC, TanStartPointLocalCas3.X,TanStartPointLocalCas3.Y, TanEndPointLocalCas3.X, TanEndPointLocalCas3.Y, aEndPoint.X, aEndPoint.Y);
      cairo_set_line_width(mCairoDC, 3);
      cairo_stroke(mCairoDC);

// 4ème cas : (12) <=> MinDistTan / 2 et (34) <=> MinDistTan / 2
   // Coordonnées de TanStartPointLocal dans le repère R1
      TanStartPointLocalCas4.X = StartPointLocalR1.X + MinDistTan * 0.5 * aCoef;
      TanStartPointLocalCas4.Y = 0.0;
      cairo_matrix_transform_point(&RotateMatrixR0toR1, &TanStartPointLocalCas4.X, &TanStartPointLocalCas4.Y);
      cairo_matrix_transform_point(&TranslateMatrixR0toR1, &TanStartPointLocalCas4.X, &TanStartPointLocalCas4.Y);
   // Coordonnées de TanEndPointLocal dans le repère R1
      TanEndPointLocalCas4.X = EndPointR2.X + MinDistTan * 0.5 * aCoef;
      TanEndPointLocalCas4.Y = 0.0;
      cairo_matrix_transform_point(&RotateMatrixR0toR2, &TanEndPointLocalCas4.X, &TanEndPointLocalCas4.Y);
      cairo_matrix_transform_point(&TranslateMatrixR0toR2, &TanEndPointLocalCas4.X, &TanEndPointLocalCas4.Y);

      SetColor(0,1,1);
      DrawPoint(TanStartPointLocalCas4,3);
      DrawPoint(TanEndPointLocalCas4,3);

      cairo_move_to(mCairoDC, aStartPoint.X, aStartPoint.Y);
      cairo_curve_to(mCairoDC, TanStartPointLocalCas4.X,TanStartPointLocalCas4.Y, TanEndPointLocalCas4.X, TanEndPointLocalCas4.Y, aEndPoint.X, aEndPoint.Y);
      cairo_set_line_width(mCairoDC, 3);
      cairo_stroke(mCairoDC);

   }
}

void Drawer::DrawCurve2(const Point& aPrevPoint, const Point& aStartPoint, const Point& aEndPoint, const Point& aNextPoint, double& aCoef)
{
   if (aCoef < 0.0)
      aCoef = 0.0;
   else if (aCoef > 1.0)
      aCoef = 1.0;

   Point PointTanStart(0,0);
   Point PointTanEnd(0,0);

   double GapTanStart;
   double GapTanEnd;


   PointTanStart.X  = aEndPoint.X * aCoef   + aStartPoint.X * (1.0 - aCoef);
   PointTanEnd.X    = aStartPoint.X * aCoef + aEndPoint.X * (1.0 - aCoef);

   GapTanStart = abs(aStartPoint.X - PointTanStart.X) * abs(aStartPoint.Y - aPrevPoint.Y) / abs(aStartPoint.X - aPrevPoint.X);
   GapTanEnd = abs(aEndPoint.X - PointTanEnd.X) * abs(aNextPoint.Y - aEndPoint.Y) / abs(aNextPoint.X - aEndPoint.X);

   if (aStartPoint.Y < aPrevPoint.Y)
      PointTanStart.Y = aStartPoint.Y - GapTanStart;
   else
      PointTanStart.Y = aStartPoint.Y + GapTanStart;

   if (aNextPoint.Y > aEndPoint.Y)
      PointTanEnd.Y = aEndPoint.Y - GapTanEnd;
   else
      PointTanEnd.Y = aEndPoint.Y + GapTanEnd;


   cairo_set_line_width(mCairoDC, 10);
   cairo_move_to(mCairoDC, aStartPoint.X, aStartPoint.Y);
   cairo_curve_to(mCairoDC, PointTanStart.X, PointTanStart.Y, PointTanEnd.X, PointTanEnd.Y, aEndPoint.X, aEndPoint.Y);
   cairo_stroke(mCairoDC);

   SetColor(0.0,0.0,1.0);
   MoveTo(aStartPoint);
   DrawLine(PointTanStart, 2);
   MoveTo(aEndPoint);
   DrawLine(PointTanEnd, 2);
   DrawPoint(PointTanStart);
   DrawPoint(PointTanEnd);
}

void Drawer::DrawEllipse (double aWidth, double aHeight)
{
   double X = 0.0;
   double Y = 0.0;
   cairo_get_current_point(mCairoDC, &X, &Y);
   cairo_save (mCairoDC);
   cairo_translate (mCairoDC, X, Y);
   cairo_scale (mCairoDC, aWidth / 2., aHeight / 2.);
   cairo_new_sub_path(mCairoDC);
   cairo_arc (mCairoDC, 0.0, 0.0, 1., 0., 2 * M_PI);
   cairo_scale (mCairoDC, 1.0/ (aWidth / 2.0), 1.0 / ( aHeight / 2.0));
   cairo_restore (mCairoDC);

   cairo_stroke (mCairoDC);
}

void Drawer::DrawText(std::string& aTexte)
{
   Point Point1      (100,100);

   FacesMap::iterator IterFont;

   cairo_text_extents_t te;
   cairo_font_face_t* Cairo_font_face = NULL;

   for (IterFont = mFacesMap.begin();IterFont != mFacesMap.end(); ++IterFont)
   {
      cairo_user_data_key_t Key;
      FT_Face FaceFind = IterFont->second;

      if (FaceFind)
      {
         Cairo_font_face = cairo_ft_font_face_create_for_ft_face (FaceFind,0);
         cairo_font_face_set_user_data (Cairo_font_face, &Key, FaceFind, NULL);

         cairo_set_font_size (mCairoDC, 75);
         cairo_set_source_rgb (mCairoDC, 0.0, 0.0, 0.0);

         MoveTo(Point1);

         std::string StrTmp = IterFont->first;
         StrTmp += "||";

         cairo_ft_font_face_set_synthesize   (Cairo_font_face, CAIRO_FT_SYNTHESIZE_BOLD);
         cairo_ft_font_face_set_synthesize (Cairo_font_face, CAIRO_FT_SYNTHESIZE_OBLIQUE);

         cairo_set_font_face(mCairoDC, Cairo_font_face);
         cairo_text_path (mCairoDC, StrTmp.c_str());
         cairo_fill(mCairoDC);

         cairo_text_extents(mCairoDC,StrTmp.c_str(),&te);
         Point1.X += (te.width + 10);
         MoveTo(Point1);

         cairo_text_path (mCairoDC, IterFont->first.c_str());
         cairo_fill(mCairoDC);

         Point1.X -= (te.width + 10);
         Point1.Y += 100;

         cairo_font_face_set_user_data (Cairo_font_face, &Key, NULL, NULL);
         cairo_font_face_destroy(Cairo_font_face);
      }
   }

   cairo_user_data_key_t KeyFontSystem;
   if (mFontSystem)
   {
      Cairo_font_face = cairo_ft_font_face_create_for_ft_face (mFontSystem,0);
      cairo_font_face_set_user_data (Cairo_font_face, &KeyFontSystem, mFontSystem, NULL);

      cairo_set_font_size (mCairoDC, 75);
      cairo_set_source_rgb (mCairoDC, 0.0, 0.0, 0.0);

      MoveTo(Point1);

      cairo_set_font_face(mCairoDC, Cairo_font_face);
      cairo_text_path (mCairoDC, "FontSystem");
      cairo_fill(mCairoDC);

      cairo_font_face_set_user_data (Cairo_font_face, &KeyFontSystem, NULL, NULL);
      cairo_font_face_destroy(Cairo_font_face);
   }

   Point1.X -= (100);
   Point1.Y += 100;

   cairo_user_data_key_t KeyFontTest;
   if (mFontTest)
   {
      Cairo_font_face = cairo_ft_font_face_create_for_ft_face (mFontTest,0);
      cairo_font_face_set_user_data (Cairo_font_face, &KeyFontTest, mFontTest, NULL);

      cairo_set_font_size (mCairoDC, 75);
      cairo_set_source_rgb (mCairoDC, 0.0, 0.0, 0.0);

      MoveTo(Point1);

      cairo_set_font_face(mCairoDC, Cairo_font_face);
      cairo_text_path (mCairoDC, "FontTest");
      cairo_fill(mCairoDC);

      cairo_font_face_set_user_data (Cairo_font_face, &KeyFontTest, NULL, NULL);
      cairo_font_face_destroy(Cairo_font_face);
   }
}

void Drawer::DrawTriangle (double aWidth, double aHeight)
{
   double X = 0.0;
   double Y = 0.0;
   cairo_get_current_point(mCairoDC, &X, &Y);
}

void Drawer::RotationOLD(double aAngle)
{
   mAngle = aAngle * M_PI / 180;

   double CentreX = 0.0;
   double CentreY = 0.0;
   cairo_matrix_t Matrice;

   cairo_get_current_point(mCairoDC, &CentreX, &CentreY);

   cairo_matrix_init (&Matrice, cos (mAngle), sin (mAngle), -sin (mAngle), cos(mAngle), CentreX * (1 - cos (mAngle)) + sin (mAngle) * CentreY, CentreY * ( 1 - cos (mAngle)) - sin (mAngle) * CentreX);

   cairo_transform (mCairoDC, &Matrice);
}

void Drawer::Rotation(double aAngle)
{
   mAngle = aAngle * M_PI / 180;

   double CentreX = 0.0;
   double CentreY = 0.0;
   cairo_matrix_t MatriceTranslate;
   cairo_matrix_t MatriceRotate;

   cairo_get_current_point(mCairoDC, &CentreX, &CentreY);

   cairo_matrix_init_translate(&MatriceTranslate,CentreX,CentreY);
   cairo_transform (mCairoDC, &MatriceTranslate);
   cairo_matrix_init_rotate(&MatriceRotate, mAngle);
   cairo_transform (mCairoDC, &MatriceRotate);
}

void Drawer::TestCurve(const Point& aPoint1, const Point& aPoint2, const Point& aPoint3, const Point& aPoint4, const Point& aPoint5, const Point& aPoint6, double& aCoef)
{
   SetColor(1.0,0,0);
   DrawCurve2(aPoint1, aPoint2, aPoint3, aPoint4, aCoef);
   SetColor(1.0,0,0);
   DrawCurve2(aPoint3, aPoint4, aPoint5, aPoint6, aCoef);

   SetColor(1.0,0,0);
   MoveTo(aPoint1);
   DrawLine(aPoint2);
   MoveTo(aPoint3);
   DrawLine(aPoint4);
   MoveTo(aPoint5);
   DrawLine(aPoint6);
   SetColor(0.0,0.0,0.0);
   DrawPoint(aPoint1);
   DrawPoint(aPoint2);
   DrawPoint(aPoint3);
   DrawPoint(aPoint4);
   DrawPoint(aPoint5);
   DrawPoint(aPoint6);
}
