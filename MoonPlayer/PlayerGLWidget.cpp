#include "PlayerGLWidget.h"
#include "MoonPlayer/format/MoonAVFrame.h"
#include "MoonPlayer/format/MoonAVFramePrivate.h"

#include <QDebug>
#include <QtMath>
#include <iostream>
#include <QFile>
#include <QTimer>

//自动加双引号
FILE* fp = NULL;

PlayerGLWidget::PlayerGLWidget(QWidget* parent):QOpenGLWidget(parent)
{
    this->setWindowTitle("LearnOpenGL");

	
}

PlayerGLWidget::~PlayerGLWidget()
{
	if (!m_pShader) 
	{
		delete m_pShader;
		m_pShader = nullptr;
	}
}

void PlayerGLWidget::repaint(MoonAVFrame* frame)
{

}

void PlayerGLWidget::Init(int width, int height)
{

}

void PlayerGLWidget::initializeGL()
{
    core = QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctions_4_0_Core>();//获取上下文
    core->initializeOpenGLFunctions();

	m_pShader = new Shader(":/shader/Player.vert", ":/shader/Player.frag");
	//编译shader
	m_pShader->use();

	//传递顶点和材质坐标
	GLfloat vertices[] = {
		-1.0f,  1.0f, 0.0f, 0.0f, 0.0f,	//top left
		 1.0f,  1.0f, 0.0f, 1.0f, 0.0f,	//top right
	     1.0f, -1.0f, 0.0f, 1.0f, 1.0f,	//bottom right
		-1.0f, -1.0f, 0.0f, 0.0f, 1.0f	//bottom left 
	};

	GLuint indices[] = {
	   0, 1, 2, // first triangle
	   2, 3, 0  // second triangle
	};

	core->glGenVertexArrays(1, &VAO);//两个参数，第一个为需要创建的缓存数量。第二个为用于存储单一ID或多个ID的GLuint变量或数组的地址
	core->glGenBuffers(1, &VBO);
	core->glGenBuffers(1, &EBO);

	core->glBindVertexArray(VAO);

	core->glBindBuffer(GL_ARRAY_BUFFER, VBO);
	core->glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	core->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	core->glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	core->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	core->glEnableVertexAttribArray(0);

	// texture coord attribute
	core->glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));

	core->glEnableVertexAttribArray(1);

	//从shader获取材质
	//unis[0] = m_pShader->shaderProgram.uniformLocation("tex_y");
	//unis[1] = m_pShader->shaderProgram.uniformLocation("tex_u");
	//unis[2] = m_pShader->shaderProgram.uniformLocation("tex_v");

	//创建材质
	core->glGenTextures(3, texs);

	//Y
	core->glBindTexture(GL_TEXTURE_2D, texs[0]);
	//放大过滤，线性插值   GL_NEAREST(效率高，但马赛克严重)
	core->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	core->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	//创建材质显卡空间
	core->glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, width, height, 0, GL_RED, GL_UNSIGNED_BYTE, 0);

	//U
	core->glBindTexture(GL_TEXTURE_2D, texs[1]);
	//放大过滤，线性插值
	core->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	core->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	//创建材质显卡空间
	core->glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, width / 2, height / 2, 0, GL_RED, GL_UNSIGNED_BYTE, 0);

	//V
	core->glBindTexture(GL_TEXTURE_2D, texs[2]);
	//放大过滤，线性插值
	core->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	core->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	//创建材质显卡空间
	core->glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, width / 2, height / 2, 0, GL_RED, GL_UNSIGNED_BYTE, 0);
	
	core->glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	
	///分配材质内存空间
	datas[0] = new unsigned char[width * height];		//Y
	datas[1] = new unsigned char[width * height / 4];	//U
	datas[2] = new unsigned char[width * height / 4];	//V

	fp = fopen("C:\\Users\\DELL\\Desktop\\MoonPlayer\\bin\\debug\\out240x128.yuv", "rb");
	if (!fp)
	{
		qDebug() << "out240x128.yuv file open failed!";
	}


	//启动定时器
	QTimer* ti = new QTimer(this);
	connect(ti, SIGNAL(timeout()), this, SLOT(update()));
	ti->start(40);
}


void PlayerGLWidget::resizeGL(int w, int h)
{
    core->glViewport(0, 0, w, h);
	qDebug() << "resizeGL " << w << ":" << h;
}

void PlayerGLWidget::paintGL()
{
	if (feof(fp))
	{
		fseek(fp, 0, SEEK_SET);
	}
	fread(datas[0], 1, width * height, fp);
	fread(datas[1], 1, width * height / 4, fp);
	fread(datas[2], 1, width * height / 4, fp);
	core->glActiveTexture(GL_TEXTURE0);
	core->glBindTexture(GL_TEXTURE_2D, texs[0]); //0层绑定到Y材质
										   //修改材质内容(复制内存内容)
	core->glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width, height, GL_RED, GL_UNSIGNED_BYTE, datas[0]);
	//与shader uni遍历关联
	//core->glUniform1i(unis[0], 0);
	m_pShader->setInt("tex_y", 0);

	core->glActiveTexture(GL_TEXTURE0 + 1);
	core->glBindTexture(GL_TEXTURE_2D, texs[1]); //1层绑定到U材质
										   //修改材质内容(复制内存内容)
	core->glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width / 2, height / 2, GL_RED, GL_UNSIGNED_BYTE, datas[1]);
	//与shader uni遍历关联
	//core->glUniform1i(unis[1], 1);
	m_pShader->setInt("tex_u", 1);

	core->glActiveTexture(GL_TEXTURE0 + 2);
	core->glBindTexture(GL_TEXTURE_2D, texs[2]); //2层绑定到V材质
										   //修改材质内容(复制内存内容)
	core->glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width / 2, height / 2, GL_RED, GL_UNSIGNED_BYTE, datas[2]);
	//与shader uni遍历关联
	//core->glUniform1i(unis[2], 2);
	m_pShader->setInt("tex_v", 2);

	core->glBindVertexArray(VAO);
	core->glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	qDebug() << "paintGL";
}

void PlayerGLWidget::keyPressEvent(QKeyEvent *event)   //键盘按下事件
{

}
void PlayerGLWidget::keyReleaseEvent(QKeyEvent *event)  //键盘释放事件
{

}
void PlayerGLWidget::mouseMoveEvent(QMouseEvent *event)//鼠标事件
{

}

void PlayerGLWidget::wheelEvent(QWheelEvent *event)    //滚轮事件
{
 
}

void PlayerGLWidget::mousePressEvent(QMouseEvent *event)  //鼠标按下事件
{

}

void PlayerGLWidget::mouseReleaseEvent(QMouseEvent *event) //鼠标释放事件
{
   
}
