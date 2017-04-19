#include <glut.h>

#define WIDTH 400
#define HEIGHT 400

static GLfloat angle = 0.0f;

void myDisplay(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// 创建透视效果视图
	glMatrixMode(GL_PROJECTION);//就是要对投影相关进行操作，也就是把物体投影到一个平面上，就像我们照相一样，把3维物体投到2维的平面上。这样，接下来的语句可以是跟透视相关的函数，比如glFrustum()或gluPerspective()；
	glLoadIdentity();//重置当前指定的矩阵为单位矩阵。
	gluPerspective(90.0f, 1.0f, 1.0f, 20.0f);//void gluPerspective( GLdouble fovy, GLdouble aspect, GLdouble zNear, GLdouble zFar )near 和 far 决定了投影参考点与裁剪窗口的距离，fovy决定了裁剪窗口的高度，还有个参数 aspect 确定了裁剪窗口的长宽比例。

	glMatrixMode(GL_MODELVIEW);//这个是对模型视景的操作，接下来的语句描绘一个以模型为基础的适应，这样来设置参数，接下来用到的就是像gluLookAt()这样的函数；
	glLoadIdentity();
	gluLookAt(0.0, 5.0, -10.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	// 定义太阳光源，它是一种白色的光源
	{
		GLfloat sun_light_position[] = { 1.0f, 1.0f, 0.0f, 0.0f };
		GLfloat sun_light_ambient[] = { 0.0f, 0.0f, 0.0f, 1.0f }; //RGBA模式的环境光，为0  
		GLfloat sun_light_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f }; //RGBA模式的漫反射光，全白光  
		GLfloat sun_light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };

		glLightfv(GL_LIGHT0, GL_POSITION, sun_light_position);//使用GL_LIGHT0表示第0号光源，GL_LIGHT1表示第1号光源，依次类推，OpenGL至少会支持8个光源，即GL_LIGHT0到GL_LIGHT7。使用glEnable函数可以开启它们。
		glLightfv(GL_LIGHT0, GL_AMBIENT, sun_light_ambient);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, sun_light_diffuse);
		glLightfv(GL_LIGHT0, GL_SPECULAR, sun_light_specular);

		glEnable(GL_LIGHT0);//开启第0号光源,使用glDisable函数则可以关闭光源
		glEnable(GL_LIGHTING);//要打开光照处理功能，使用这条的语句
		glEnable(GL_DEPTH_TEST);
	}

	// 定义太阳的材质并绘制太阳
	{
		GLfloat sun_mat_ambient[] = { 0.0f, 0.0f, 0.0f, 1.0f };
		GLfloat sun_mat_diffuse[] = { 0.0f, 0.0f, 0.0f, 1.0f };
		GLfloat sun_mat_specular[] = { 0.0f, 0.0f, 0.0f, 1.0f };
		GLfloat sun_mat_emission[] = { 0.5f, 0.0f, 0.0f, 1.0f };
		GLfloat sun_mat_shininess = 0.0f;//该属性只有一个值，称为“镜面指数”，取值范围是0到128。该值越小，表示材质越粗糙，点光源发射的光线照射到上面，也可以产生较大的亮点。该值越大，表示材质越类似于镜面，光源照射到上面后，产生较小的亮点。
										 //材质定义
		glMaterialfv(GL_FRONT, GL_AMBIENT, sun_mat_ambient);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, sun_mat_diffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, sun_mat_specular);
		glMaterialfv(GL_FRONT, GL_EMISSION, sun_mat_emission);//GL_EMISSION属性。该属性由四个值组成，表示一种颜色。OpenGL认为该材质本身就微微的向外发射光线，以至于眼睛感觉到它有这样的颜色，但这光线又比较微弱，以至于不会影响到其它物体的颜色。
		glMaterialf(GL_FRONT, GL_SHININESS, sun_mat_shininess);

		glutSolidSphere(2.0, 40, 32);//渲染一个球体
	}

	// 定义地球的材质并绘制地球
	{
		GLfloat earth_mat_ambient[] = { 0.0f, 0.0f, 0.5f, 1.0f };
		GLfloat earth_mat_diffuse[] = { 0.0f, 0.0f, 0.5f, 1.0f };
		GLfloat earth_mat_specular[] = { 0.0f, 0.0f, 1.0f, 1.0f };
		GLfloat earth_mat_emission[] = { 0.0f, 0.0f, 0.0f, 1.0f };
		GLfloat earth_mat_shininess = 50.0f;

		glMaterialfv(GL_FRONT, GL_AMBIENT, earth_mat_ambient);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, earth_mat_diffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, earth_mat_specular);
		glMaterialfv(GL_FRONT, GL_EMISSION, earth_mat_emission);
		glMaterialf(GL_FRONT, GL_SHININESS, earth_mat_shininess);

		glRotatef(angle, 0.0f, -1.0f, 0.0f);//使用glTranslate*函数或者glRotate*函数可以改变物体的外观，但法线向量并不会随之改变。
		glTranslatef(5.0f, 0.0f, 0.0f);
		glutSolidSphere(2.0, 40, 32);
	}

	glutSwapBuffers();
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutCreateWindow("gouraud光照演示");
	glutDisplayFunc(&myDisplay);
	glutMainLoop();//这里让整个绘图循环进行，相当于死循环
	return 0;
}