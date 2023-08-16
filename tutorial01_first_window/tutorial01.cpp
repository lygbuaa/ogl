// Include standard headers
#include <stdio.h>
#include <stdlib.h>

// Include GLEW, Always include it before gl.h and glfw3.h, since it's a bit magic.
#include <GL/glew.h>

// Include GLFW
#include <GLFW/glfw3.h>
GLFWwindow* window;

// Include GLM
#include <glm/glm.hpp>
using namespace glm;

/**
 * defined in glfw/src/internal.h
 * Window and context structure
	struct _GLFWwindow
	{
		struct _GLFWwindow* next;

		// Window settings and state
		GLFWbool            resizable;
		GLFWbool            decorated;
		GLFWbool            autoIconify;
		GLFWbool            floating;
		GLFWbool            focusOnShow;
		GLFWbool            mousePassthrough;
		GLFWbool            shouldClose;
		void*               userPointer;
		GLFWbool            doublebuffer;
		GLFWvidmode         videoMode;
		_GLFWmonitor*       monitor;
		_GLFWcursor*        cursor;

		int                 minwidth, minheight;
		int                 maxwidth, maxheight;
		int                 numer, denom;

		GLFWbool            stickyKeys;
		GLFWbool            stickyMouseButtons;
		GLFWbool            lockKeyMods;
		int                 cursorMode;
		char                mouseButtons[GLFW_MOUSE_BUTTON_LAST + 1];
		char                keys[GLFW_KEY_LAST + 1];
		// Virtual cursor position when cursor is disabled
		double              virtualCursorPosX, virtualCursorPosY;
		GLFWbool            rawMouseMotion;

		_GLFWcontext        context;

		struct {
			GLFWwindowposfun          pos;
			GLFWwindowsizefun         size;
			GLFWwindowclosefun        close;
			GLFWwindowrefreshfun      refresh;
			GLFWwindowfocusfun        focus;
			GLFWwindowiconifyfun      iconify;
			GLFWwindowmaximizefun     maximize;
			GLFWframebuffersizefun    fbsize;
			GLFWwindowcontentscalefun scale;
			GLFWmousebuttonfun        mouseButton;
			GLFWcursorposfun          cursorPos;
			GLFWcursorenterfun        cursorEnter;
			GLFWscrollfun             scroll;
			GLFWkeyfun                key;
			GLFWcharfun               character;
			GLFWcharmodsfun           charmods;
			GLFWdropfun               drop;
		} callbacks;

		// This is defined in platform.h
		GLFW_PLATFORM_WINDOW_STATE
	};
*/
void framebuffer_size_callback(GLFWwindow* win, int width, int height)
{
	fprintf(stderr, "resize window: %dx%d\n", width, height);
	glViewport(0, 0, width, height);
}

void window_close_callback(GLFWwindow* win)
{
	fprintf(stderr, "window %x closed\n", win);
}

void process_key_input(GLFWwindow* win)
{
	for(int key=GLFW_KEY_SPACE; key<GLFW_KEY_LAST; key+=1)
	{
		if(glfwGetKey(win, key) == GLFW_PRESS)
		{
			/* glfwGetKeyName not public in glfw-3.1 */
			// int scancode = glfwGetKeyScancode(key);
			// const char* keyname = glfwGetKeyName(key, 0);
			fprintf(stderr, "key %d pressed\n", key);
		}
	}
}

int main(int argc, char **argv)
{
	for(int i = 0; i < argc; i++){
        fprintf(stderr, "argv[%d] = %s\n", i, argv[i]);
    }
    // glutInit(&argc, argv);
    // glutCreateWindow("GLUT");
    // glewInit();

	// Initialise GLFW
	if( !glfwInit() )
	{
		fprintf( stderr, "Failed to initialize GLFW\n" );
		getchar();
		return -1;
	}

	glfwWindowHint(GLFW_SAMPLES, 4);  // 4x antialiasing
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);  // We want OpenGL 4.6 on ubuntu 22.04
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // We don't want the old OpenGL 

	// Open a window and create its OpenGL context
	window = glfwCreateWindow( 1024, 768, "Tutorial 01", NULL, NULL);
	if( window == NULL ){
		fprintf( stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n" );
		getchar();
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	// Initialize GLEW
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		getchar();
		glfwTerminate();
		return -1;
	}

	glViewport(0, 0, 640, 480);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetWindowCloseCallback(window, window_close_callback);

	/** until now GL context is ready, so print GL version */
    fprintf(stderr, "OpenGL version: %s \n", glGetString(GL_VERSION));

	// Ensure we can capture the escape key being pressed below
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	// Dark blue background
	// glClearColor(0.0f, 0.0f, 1.0f, 0.0f);
	float r = 0.0f;
	float b = 1.0f;
	do{
		/* make a blue-to-green gradient */
		r += 0.005f;
		b -= 0.005f;
		r = (r > 1.0f) ? 0.0f : r;
		b = (b < 0.0f) ? 1.0f : b;
		/**
		 *  glClearColor() function is a state-setting function,
		 *  and glClear() is a state-using function in that,
		 *  it uses the current state to retrieve the clearing color from.
		*/
		glClearColor(r, 0.0f, b, 0.0f);

		// Clear the screen. It's not mentioned before Tutorial 02, but it can cause flickering, so it's there nonetheless.
		/* The possible bits we can set are GL_COLOR_BUFFER_BIT, GL_DEPTH_BUFFER_BIT and GL_STENCIL_BUFFER_BIT. */
		glClear( GL_COLOR_BUFFER_BIT );

		// Draw nothing, see you in tutorial 2 !
		process_key_input(window);

		// Swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();

	} // Check if the ESC key was pressed or the window was closed
	while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
		   glfwWindowShouldClose(window) == 0 );

	// Close OpenGL window and terminate GLFW
	glfwTerminate();

	return 0;
}

