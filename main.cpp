#include <iostream>

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <arrayfire.h>

#define WIDTH 800
#define HEIGHT 600

using namespace std;
using namespace glm;
using namespace af;

int screenWidth, screenHeight;
int frame = 0;

int main()
{

    if (!glfwInit())
    {
        cout << "no glfw" << endl;
        exit(EXIT_FAILURE);
    }

    GLFWwindow* window;
    window = glfwCreateWindow(WIDTH, HEIGHT, "2dTest", nullptr, nullptr);
    if (!window)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window);
    glClear(GL_COLOR_BUFFER_BIT);

    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwGetFramebufferSize(window, &screenWidth, &screenHeight);
    glViewport(0, 0, screenWidth, screenHeight);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, screenWidth, screenHeight, 0, 0, 1);

    glfwSwapInterval(1);
    glEnable(GL_SMOOTH);
    glDisable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glLineWidth(5.0f);
    glEnable(GL_LINE_SMOOTH);
    glPointSize(5.0f);
    glEnable(GL_POINT_SMOOTH);

    // set random seed
    srand(glfwGetTime());

    float screenSize[] = {(float)screenWidth, (float)screenHeight};
    af::array aScreenSize(1, 2, screenSize);
    af::array aRand;

    while (!glfwWindowShouldClose(window))
    {
        frame++;

        glClear(GL_COLOR_BUFFER_BIT);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        glBegin(GL_LINES);
        {
            glColor3ub(255, 0, 0);
            glVertex2f(0.0f, 0.0f);
            glColor3ub(0, 0, 255);
            glVertex2f(screenWidth, screenHeight);
        }
        glEnd();

        aRand = randu(1, 2);
        aRand *= aScreenSize;

        float fx = aRand(0).scalar<float>();
        float fy = aRand(1).scalar<float>();

        glBegin(GL_POINTS);
        {
            glColor3f(1,1,1);
            glVertex2f(fx, fy);
//            cout << "[" << fx << "x" << fy << "]" << endl;
        }
        glEnd();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();

    exit(EXIT_SUCCESS);
}