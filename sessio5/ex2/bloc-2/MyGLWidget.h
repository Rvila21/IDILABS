#define GLM_FORCE_RADIANS
#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLWidget>
#include <QOpenGLShader>
#include <QOpenGLShaderProgram>
#include <QKeyEvent>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "model.h"

class MyGLWidget : public QOpenGLWidget, protected QOpenGLFunctions_3_3_Core 
{
  Q_OBJECT

  public:
    MyGLWidget (QWidget *parent=0);
    ~MyGLWidget ();

  protected:
    // initializeGL - Aqui incluim les inicialitzacions del contexte grafic.
    virtual void initializeGL ( );
    // paintGL - Mètode cridat cada cop que cal refrescar la finestra.
    // Tot el que es dibuixa es dibuixa aqui.
    virtual void paintGL ( );
    // resizeGL - És cridat quan canvia la mida del widget
    virtual void resizeGL (int width, int height);
    // keyPressEvent - Es cridat quan es prem una tecla
    virtual void keyPressEvent (QKeyEvent *event);

  private:
    void createBuffers ();
    void carregaShaders ();
    void modelTransformHomer();
    void projectTransform();
    void viewTransform();
    // attribute locations
    GLuint vertexLoc, colorLoc, projLoc,viewLoc;
    // uniform locations
    GLuint transLoc;
    // VAO i VBO names
    GLuint VAO_Homer, VBO_HomerPos, VBO_HomerCol;
    // Program
    QOpenGLShaderProgram *program;
    // Internal vars
    float scale, angle;
    glm::vec3 pos;
    //Models
    Model m;
    GLuint VAO_Terra, VBO_TerraPos, VBO_TerraCol;   
    void modelTransformTerra();
    float FOV, ra;
    void ini_camera();
    void calculaCapsaModel();
    
    //-------------------MY VARS----------------------------
      glm::vec3 OBS,VRP,UP;
      float znear, zfar;
      glm::vec3 homermin,homermax,homercentre;
      float homerradi,homeraltura;
      float anglex,angley;
    // -----------------MY METODES-------------------------
     glm::vec3 calcula_centre(glm::vec3 pmin, glm::vec3 pmax);
     float calcula_radi(glm::vec3 pmin, glm::vec3 pcentre);
 
};

