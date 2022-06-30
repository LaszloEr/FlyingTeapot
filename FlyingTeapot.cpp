#include <iostream> 
#include <GL/freeglut.h>         //lädt alles für OpenGL
#include <math.h> //Für sinus
#include <string>

float fRotation = 315.0;
float  wingrotation = 0;

void Init()	
{
   // Hier finden jene Aktionen statt, die zum Programmstart einmalig 
   // durchgeführt werden müssen
    glEnable(GL_DEPTH_TEST); //Tiefenpuffer
    glClearDepth(1.0); //Tiefenpuffer löschen
    
       glShadeModel (GL_SMOOTH); //Smooth shading aktivieren

       GLfloat light_ambient[] = { 1.0, 1.0, 1.0, .0}; //Lichtquelle
glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
     
 
    GLfloat light_position[] = { 1.0, 3.0, 0.0, 0.0 };
 
       glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    
    glEnable(GL_LIGHTING); //licht aktivieren
   glEnable(GL_LIGHT0);
}


void fluegel(int richtung) //Die beiden Flügel
{
   if (richtung == 0) {
   glBegin(GL_POLYGON); 
   //glNormal3f(0. , 1., 0. );
   glColor4f( 0., 1., 0., 1.);
   glVertex3f(-0.2f, 0.0f, -0.4f);
   glVertex3f( 0.0f, (-sin(wingrotation)*0.5), -.9f);
   glVertex3f(0.2f, 0.0f, -0.4f);
   glEnd();
   }
   else
   {
   glBegin(GL_POLYGON); 
   glColor4f( 0., 1., 0., 1.);
   glVertex3f(-0.2f, 0.0f, 0.4f);
   glVertex3f( 0.0f, (-sin(wingrotation)*0.5), .9f);
   glVertex3f(0.2f, 0.0f, 0.4f);
   glEnd();
   }
   
}


void RenderScene() //Zeichenfunktion
{
   // Hier befindet sich der Code der in jedem Frame ausgefuehrt werden muss
   glClearColor( 0.10, 0, 0.40, 1 ); //Hintergrundfarbe setzen
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   
    glLoadIdentity ();   // Aktuelle Model-/View-Transformations-Matrix zuruecksetzen
   gluLookAt ( 0., 0., 1., 0., 0., 0., 0., 1., 0.); //Kameraposition
    glScalef(.6,.6,.6); //Szene verkleinern
   wingrotation = wingrotation + 0.1; //animation fortsetzen
   
   glTranslatef(0.,sin(wingrotation)*0.2,0.); //Bewegen der Teekanne mit einer Sinusfunktion
   
   glRotatef(fRotation,0.,1.,0.); //Rotation der Szene
   
   fluegel(0); //Die beiden Flügel erstellen und zeichnen
   fluegel(1);
   
   //glColor4f(1.0f,1.0f,0.0f,1.5f); //GELB, bei Beleuchtung nicht verwendet
   

    glutSolidTeapot(0.5); //Utah-Teekanne
    
    
   
    
   glutSwapBuffers(); //Szene neu zeichnen
}

void Reshape(int width,int height)
{
   // Hier finden die Reaktionen auf eine Veränderung der Größe des 
   // Graphikfensters statt
    // Matrix für Transformation: Frustum->viewport
glMatrixMode(GL_PROJECTION);
// Aktuelle Transformations-Matrix zuruecksetzen
glLoadIdentity ();
// Viewport definieren
glViewport(0,0,width,height);
// Frustum definieren (siehe unten)
glOrtho( -1., 1., -1., 1., 0, 20);
// Matrix für Modellierung/Viewing
glMatrixMode(GL_MODELVIEW);
}

void Animate (int value)    
{
   // Hier werden Berechnungen durchgeführt, die zu einer Animation der Szene  
   // erforderlich sind. Dieser Prozess läuft im Hintergrund und wird alle 
   // 1000 msec aufgerufen. Der Parameter "value" wird einfach nur um eins 
   // inkrementiert und dem Callback wieder uebergeben. 
   //std::cout << "value=" << value << std::endl; //Ausgabe der Framenummer
   
   fRotation = fRotation - 1.0; // Rotationswinkel aendern
  
  //Wenn Rotation vollendet, neu starten
if ( fRotation <= 0.0) {
fRotation = fRotation + 360.0;


 
}
   
   // RenderScene aufrufen
   glutPostRedisplay();
   // Timer wieder registrieren - Animate wird so nach 10 msec mit value+=1 aufgerufen.
   int wait_msec = 10;
   glutTimerFunc(wait_msec, Animate, ++value);
}


int main(int argc, char **argv)
{
   glutInit( &argc, argv );                // GLUT initialisieren
   glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
   glutInitWindowSize( 800, 800 );         // Fenster-Konfiguration
   glutCreateWindow( "Fliegende Teekanne" );   // Fenster-Erzeugung
   glutDisplayFunc( RenderScene );         // Zeichenfunktion bekannt machen
   glutReshapeFunc( Reshape );
   // TimerCallback registrieren; wird nach 10 msec aufgerufen mit Parameter 0  
   glutTimerFunc( 10, Animate, 0);
   Init();
   glutMainLoop();
   return 0;
}
