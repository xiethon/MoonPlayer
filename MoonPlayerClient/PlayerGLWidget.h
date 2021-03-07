#ifndef PlayerGLWidget_H
#define PlayerGLWidget_H

#include <QObject>
#include <QWidget>
#include <QOpenGLWidget>
#include <QOpenGLExtraFunctions>
#include <QOpenGLTexture>
#include <QOpenGLShader>
#include <QOpenGLShaderProgram>
#include <QOpenGLFunctions_4_0_Core>
#include <QTime>
#include <QDebug>
#include "Shader.h"

class PlayerGLWidget :public QOpenGLWidget
{
    Q_OBJECT

public:
    PlayerGLWidget(QWidget* parent=nullptr);
    ~PlayerGLWidget();

//    void init(int width, int height);

public slots:
    void repaint();

protected:
    virtual void initializeGL();
    virtual void resizeGL(int w, int h);
    virtual void paintGL();
    void keyPressEvent(QKeyEvent *event);   //键盘按下事件
    void keyReleaseEvent(QKeyEvent *event);  //键盘释放事件
    void mouseMoveEvent(QMouseEvent *event);//鼠标事件
    void wheelEvent(QWheelEvent *event);    //滚轮事件
    void mousePressEvent(QMouseEvent *event);  //鼠标按下事件
    void mouseReleaseEvent(QMouseEvent *event); //鼠标释放事件


private:
    Shader *m_pShader;
    QOpenGLFunctions_4_0_Core *core;
    GLuint VBO, VAO, EBO;
	//材质内存空间
	unsigned char* datas[3] = { 0 };
	//shader中yuv变量地址
	GLuint unis[3] = { 0 };
	//openg的 texture地址
	GLuint texs[3] = { 0 };

	int width = 240;
	int height = 128;

};

#endif //
