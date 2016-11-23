#include "MyGLWidget.h"

#include <iostream>

MyGLWidget::MyGLWidget (QWidget* parent) : QOpenGLWidget(parent)
{
  setFocusPolicy(Qt::ClickFocus);  // per rebre events de teclat
  scale = 1.0f;
}

MyGLWidget::~MyGLWidget ()
{
  if (program != NULL)
    delete program;
}

void MyGLWidget::initializeGL ()
{
  // Cal inicialitzar l'ús de les funcions d'OpenGL
  initializeOpenGLFunctions();  
  glClearColor(0.5, 0.7, 1.0, 1.0); // defineix color de fons (d'esborrat)
  glEnable(GL_DEPTH_TEST);
  m.load("models/HomerProves.obj");
  angle = 0.0f;
  scale = 1.0f;
  carregaShaders();
  createBuffers();
  projectTransform();
  viewTransform();
}

void MyGLWidget::paintGL () 
{
  // Esborrem el frame-buffer
  glClear (GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);

  // Carreguem la transformació de model
  
 
  modelTransformHomer();
  
  // Activem el VAO per a pintar la caseta 
  glBindVertexArray (VAO_Homer);

  // pintem
  glDrawArrays(GL_TRIANGLES,0, m.faces().size()*3);
  
  
  modelTransformTerra();
  
  glBindVertexArray(VAO_Terra);
  
  glDrawArrays(GL_TRIANGLES,0,6);

  glBindVertexArray (0);
}

void MyGLWidget::modelTransformHomer () 
{
  // Matriu de transformació de model
  glm::mat4 transform (1.0f);
  transform = glm::scale(transform, glm::vec3(scale));
  transform = glm::rotate(transform,angle,glm::vec3(0.,1.,0.));
  glUniformMatrix4fv(transLoc, 1, GL_FALSE, &transform[0][0]);
}

void MyGLWidget::modelTransformTerra () 
{
  // Matriu de transformació de model
  glm::mat4 transform (1.0f);
  transform = glm::scale(transform, glm::vec3(scale));
//   transform = glm::rotate(transform,angle,glm::vec3(0.,1.,0.));
  glUniformMatrix4fv(transLoc, 1, GL_FALSE, &transform[0][0]);
}

void MyGLWidget::projectTransform(){
    glm::mat4 Proj = glm::perspective ((float)M_PI/2.0f, 1.0f, 0.4f, 3.0f);
    glUniformMatrix4fv(projLoc, 1,GL_FALSE,&Proj[0][0]);
}

void MyGLWidget::viewTransform(){
    glm::mat4 View = glm::lookAt (glm::vec3(0,0,1),glm::vec3(0,0,0),glm::vec3(0,1,0));
    glUniformMatrix4fv(viewLoc, 1,GL_FALSE,&View[0][0]);
}

void MyGLWidget::resizeGL (int w, int h) 
{
  glViewport(0, 0, w, h);
}

void MyGLWidget::keyPressEvent(QKeyEvent* event) 
{
  switch (event->key()) {
    makeCurrent();
    case Qt::Key_S: { // escalar a més gran
      scale += 0.05;
      break;
    }
    case Qt::Key_D: { // escalar a més petit
      scale -= 0.05;
      break;
    }
    case Qt::Key_R: { // escalar a més petit
      angle += (M_PI/4);
      break;
    }
    case Qt::Key_Escape: { // escalar a més petit
      exit(0);
      break;
    }
    default: event->ignore(); break;
  }
  update();
}

void MyGLWidget::createBuffers () 
{


  // Creació del Vertex Array Object per pintar
  glGenVertexArrays(1, &VAO_Homer);
  glBindVertexArray(VAO_Homer);

  glGenBuffers(1, &VBO_HomerPos);
  glBindBuffer(GL_ARRAY_BUFFER, VBO_HomerPos);
  glBufferData(GL_ARRAY_BUFFER, sizeof(GL_FLOAT)* m.faces().size() * 3 * 3, m.VBO_vertices(), GL_STATIC_DRAW);

  // Activem l'atribut vertexLoc
  glVertexAttribPointer(vertexLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(vertexLoc);

  glGenBuffers(1, &VBO_HomerCol);
  glBindBuffer(GL_ARRAY_BUFFER, VBO_HomerCol);
  glBufferData(GL_ARRAY_BUFFER, sizeof(GL_FLOAT)* m.faces().size() * 3 * 3, m.VBO_matdiff(), GL_STATIC_DRAW);

  // Activem l'atribut colorLoc
  glVertexAttribPointer(colorLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(colorLoc);
  
// -----------------------------------------TERRA-------------------------------------------
  glm::vec3 vertexTerra[6];
  vertexTerra[0] = glm::vec3(-1.0,-1.0,-1.0);
  vertexTerra[1] = glm::vec3(-1.0,-1.0,1.0);
  vertexTerra[2] = glm::vec3(1.0,-1.0,-1.0);
  vertexTerra[3] = glm::vec3(1.0,-1.0,-1.0);
  vertexTerra[4] = glm::vec3(-1.0,-1.0,1.0);
  vertexTerra[5] = glm::vec3(1.0,-1.0,1.0);
  
  glm::vec3 colorTerra[6];
  colorTerra[0] = glm::vec3(1.0,0.0,1.0);
  colorTerra[1] = glm::vec3(1.0,0.0,1.0);
  colorTerra[2] = glm::vec3(1.0,0.0,1.0);
  colorTerra[3] = glm::vec3(1.0,0.0,1.0);
  colorTerra[4] = glm::vec3(1.0,0.0,1.0);
  colorTerra[5] = glm::vec3(1.0,0.0,1.0);
  
  glGenVertexArrays(1, &VAO_Terra);
  glBindVertexArray(VAO_Terra);
  
  glGenBuffers(1, &VBO_TerraPos);
  glBindBuffer(GL_ARRAY_BUFFER, VBO_TerraPos);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertexTerra),vertexTerra,GL_STATIC_DRAW);
  
  glVertexAttribPointer(vertexLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(vertexLoc);
  
  glGenBuffers(1, &VBO_TerraCol);
  glBindBuffer(GL_ARRAY_BUFFER, VBO_TerraCol);
  glBufferData(GL_ARRAY_BUFFER,sizeof(colorTerra),colorTerra,GL_STATIC_DRAW);
  
  glVertexAttribPointer(colorLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(colorLoc);
  
  glBindVertexArray (0);
}

void MyGLWidget::carregaShaders()
{
  // Creem els shaders per al fragment shader i el vertex shader
  QOpenGLShader fs (QOpenGLShader::Fragment, this);
  QOpenGLShader vs (QOpenGLShader::Vertex, this);
  // Carreguem el codi dels fitxers i els compilem
  fs.compileSourceFile("shaders/fragshad.frag");
  vs.compileSourceFile("shaders/vertshad.vert");
  // Creem el program
  program = new QOpenGLShaderProgram(this);
  // Li afegim els shaders corresponents
  program->addShader(&fs);
  program->addShader(&vs);
  // Linkem el program
  program->link();
  // Indiquem que aquest és el program que volem usar
  program->bind();

  // Obtenim identificador per a l'atribut “vertex” del vertex shader
  vertexLoc = glGetAttribLocation (program->programId(), "vertex");
  // Obtenim identificador per a l'atribut “color” del vertex shader
  colorLoc = glGetAttribLocation (program->programId(), "color");
  // Uniform locations
  transLoc = glGetUniformLocation(program->programId(), "TG");
  //ProjLoc
  projLoc = glGetUniformLocation(program->programId(), "proj");
  //viewLoc
  viewLoc = glGetUniformLocation(program->programId(), "view");

}