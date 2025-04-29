//#include <glad/glad.h>
//#include <GLFW/glfw3.h>
//#include <stb_image/stb_image.h>
//
//#include <glm/glm.hpp>
//#include <glm/gtc/matrix_transform.hpp>
//#include <glm/gtc/type_ptr.hpp>
//
//#include <shaderLoader/shader_c.h>
//#include <camera/camera.h>
//#include <learnopengl/model.h>
//
//#include <iostream>
//
//void framebuffer_size_callback(GLFWwindow* window, int width, int height);
//void mouse_callback(GLFWwindow* window, double xpos, double ypos);
//void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
//void processInput(GLFWwindow* window);
//unsigned int myLoadTexture(const char *path, GLint wrapParam = GL_REPEAT);
//
//// settings
//const unsigned int SCR_WIDTH = 800;
//const unsigned int SCR_HEIGHT = 600;
//
//// camera
//Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
//float lastX = SCR_WIDTH / 2.0f;
//float lastY = SCR_HEIGHT / 2.0f;
//bool firstMouse = true;
//
//// timing
//float deltaTime = 0.0f;
//float lastFrame = 0.0f;
//
//int main(){
//    glfwInit();
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//
//#ifdef __APPLE__
//    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
//#endif
//
//    // glfw window creation
//    // --------------------
//    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
//    if (window == NULL)
//    {
//        std::cout << "Failed to create GLFW window" << std::endl;
//        glfwTerminate();
//        return -1;
//    }
//    glfwMakeContextCurrent(window);
//    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
//    glfwSetCursorPosCallback(window, mouse_callback);
//    glfwSetScrollCallback(window, scroll_callback);
//
//    // tell GLFW to capture our mouse
//    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
//
//    // glad: load all OpenGL function pointers
//    // ---------------------------------------
//    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
//    {
//        std::cout << "Failed to initialize GLAD" << std::endl;
//        return -1;
//    }
//
//    // configure global opengl state
//    // -----------------------------
//    glEnable(GL_DEPTH_TEST);
//    glDepthFunc(GL_LESS);
//
//	glEnable(GL_STENCIL_TEST);
//	glStencilFunc(GL_ALWAYS, 1, 0xFF);
//	glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
//
//	glEnable(GL_CULL_FACE);
//	glCullFace(GL_FRONT);
//	glFrontFace(GL_CCW);
//
//    Shader shader("../resources/shaders/framebuffer/framebuffer.vs", "../resources/shaders/framebuffer/framebuffer.fs");
//    Shader screenShader("../resources/shaders/framebuffer/framebufferScreen.vs", "../resources/shaders/framebuffer/framebufferScreen.fs");
//
//	float cubeVertices[] = {
//		// back face
//		-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, // bottom-left
//		0.5f, -0.5f, -0.5f, 1.0f, 0.0f, // bottom-right
//        0.5f, 0.5f, -0.5f, 1.0f, 1.0f, // top-right
//		0.5f, 0.5f, -0.5f, 1.0f, 1.0f, // top-right
//		-0.5f, 0.5f, -0.5f, 0.0f, 1.0f, // top-left
//        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, // bottom-left
//		// front face
//		-0.5f, -0.5f, 0.5f, 0.0f, 0.0f, // bottom-left
//		0.5f, 0.5f, 0.5f, 1.0f, 1.0f, // top-right
//        0.5f, -0.5f, 0.5f, 1.0f, 0.0f, // bottom-right
//		0.5f, 0.5f, 0.5f, 1.0f, 1.0f, // top-right   
//		-0.5f, -0.5f, 0.5f, 0.0f, 0.0f, // bottom-left
//         -0.5f, 0.5f, 0.5f, 0.0f, 1.0f, // top-left
//		// left face
//		-0.5f, 0.5f, 0.5f, 1.0f, 0.0f, // top-right
//		-0.5f, -0.5f, -0.5f, 0.0f, 1.0f, // bottom-left
//        -0.5f, 0.5f, -0.5f, 1.0f, 1.0f, // top-left
//		-0.5f, -0.5f, -0.5f, 0.0f, 1.0f, // bottom-left
//		-0.5f, 0.5f, 0.5f, 1.0f, 0.0f, // top-right
//        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, // bottom-right
//		// right face
//		0.5f, 0.5f, 0.5f, 1.0f, 0.0f, // top-left
//		0.5f, 0.5f, -0.5f, 1.0f, 1.0f, // top-right
//        0.5f, -0.5f, -0.5f, 0.0f, 1.0f, // bottom-right
//		0.5f, -0.5f, -0.5f, 0.0f, 1.0f, // bottom-right
//		0.5f, -0.5f, 0.5f, 0.0f, 0.0f, // bottom-left
//        0.5f, 0.5f, 0.5f, 1.0f, 0.0f, // top-left
//		// bottom face
//		-0.5f, -0.5f, -0.5f, 0.0f, 1.0f, // top-right
//		0.5f, -0.5f, 0.5f, 1.0f, 0.0f, // bottom-left
//        0.5f, -0.5f, -0.5f, 1.0f, 1.0f, // top-left
//		0.5f, -0.5f, 0.5f, 1.0f, 0.0f, // bottom-left
//		-0.5f, -0.5f, -0.5f, 0.0f, 1.0f, // top-right
//        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, // bottom-right
//		// top face
//		-0.5f, 0.5f, -0.5f, 0.0f, 1.0f, // top-left
//		0.5f, 0.5f, -0.5f, 1.0f, 1.0f, // top-right
//        0.5f, 0.5f, 0.5f, 1.0f, 0.0f, // bottom-right
//		0.5f, 0.5f, 0.5f, 1.0f, 0.0f, // bottom-right
//		-0.5f, 0.5f, 0.5f, 0.0f, 0.0f, // bottom-left
//        -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, // top-left
//	};
//
//    float planeVertices[] = {
//        // positions          // texture Coords (note we set these higher than 1 (together with GL_REPEAT as texture wrapping mode). this will cause the floor texture to repeat)
//         5.0f, -0.5f,  5.0f,  2.0f, 0.0f,
//        -5.0f, -0.5f,  5.0f,  0.0f, 0.0f,
//        -5.0f, -0.5f, -5.0f,  0.0f, 2.0f,
//
//         5.0f, -0.5f,  5.0f,  2.0f, 0.0f,
//        -5.0f, -0.5f, -5.0f,  0.0f, 2.0f,
//         5.0f, -0.5f, -5.0f,  2.0f, 2.0f,								
//    };
//	float transparentVertices[] = {
//		// positions         // texture Coords (swapped y coordinates because texture is flipped upside down)
//		0.0f,  0.5f,  0.0f,  0.0f,  0.0f,
//		0.0f, -0.5f,  0.0f,  0.0f,  1.0f,
//		1.0f, -0.5f,  0.0f,  1.0f,  1.0f,
//
//		0.0f,  0.5f,  0.0f,  0.0f,  0.0f,
//		1.0f, -0.5f,  0.0f,  1.0f,  1.0f,
//		1.0f,  0.5f,  0.0f,  1.0f,  0.0f
//	};
//	float quadVertices[] = { // vertex attributes for a quad that fills the entire screen in Normalized Device Coordinates. NOTE that this plane is now much smaller and at the top of the screen
//		// positions   // texCoords
//		-1.0f,  1.0f,  0.0f, 1.0f,
//		-1.0f,  -1.0f,  0.0f, 0.0f,
//		 1.0f,  -1.0f,  1.0f, 0.0f,
//
//		 1.0f,  1.0f,  1.0f, 1.0f,
//		 -1.0f,  1.0f,  0.0f, 1.0f,
//		 1.0f,  -1.0f,  1.0f, 0.0f,
//	};
//	// cube VAO
//	unsigned int cubeVAO, cubeVBO;
//	glGenVertexArrays(1, &cubeVAO);
//	glGenBuffers(1, &cubeVBO);
//	glBindVertexArray(cubeVAO);
//	glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), &cubeVertices, GL_STATIC_DRAW);
//	glEnableVertexAttribArray(0);
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
//	glEnableVertexAttribArray(1);
//	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
//	// plane VAO
//	unsigned int planeVAO, planeVBO;
//	glGenVertexArrays(1, &planeVAO);
//	glGenBuffers(1, &planeVBO);
//	glBindVertexArray(planeVAO);
//	glBindBuffer(GL_ARRAY_BUFFER, planeVBO);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(planeVertices), &planeVertices, GL_STATIC_DRAW);
//	glEnableVertexAttribArray(0);
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
//	glEnableVertexAttribArray(1);
//	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
//	// screen quad VAO
//	unsigned int quadVAO, quadVBO;
//	glGenVertexArrays(1, &quadVAO);
//	glGenBuffers(1, &quadVBO);
//	glBindVertexArray(quadVAO);
//	glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
//	glEnableVertexAttribArray(0);
//	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
//	glEnableVertexAttribArray(1);
//	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
//       
//    unsigned int cubeTexture = myLoadTexture("../resources/textures/container.jpg");
//    unsigned int floorTexture = myLoadTexture("../resources/textures/metal.png");
//    unsigned int grassTexture = myLoadTexture("../resources/textures/blending_transparent_window.png", GL_CLAMP_TO_EDGE);
//
//	vector<glm::vec3> vegetation
//	{
//		glm::vec3(-1.5f, 0.0f, -0.48f),
//		glm::vec3(1.5f, 0.0f, 0.51f),
//		glm::vec3(0.0f, 0.0f, 0.7f),
//		glm::vec3(-0.3f, 0.0f, -2.3f),
//		glm::vec3(0.5f, 0.0f, -0.6f)
//	};
//
//    
//
//    shader.use();
//    shader.setInt("texture1", 0);
//
//    screenShader.use();
//    screenShader.setInt("screenTexture", 0);
//
//	unsigned int framebuffer;
//	glGenFramebuffers(1, &framebuffer);
//	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
//	// create a color attachment texture
//	unsigned int textureColorbuffer;
//	glGenTextures(1, &textureColorbuffer);
//	glBindTexture(GL_TEXTURE_2D, textureColorbuffer);
//	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, SCR_WIDTH, SCR_HEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureColorbuffer, 0);
//	// create a renderbuffer object for depth and stencil attachment (we won't be sampling these)
//	unsigned int rbo;
//	glGenRenderbuffers(1, &rbo);
//	glBindRenderbuffer(GL_RENDERBUFFER, rbo);
//	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, SCR_WIDTH, SCR_HEIGHT); // use a single renderbuffer object for both a depth AND stencil buffer.
//	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo); // now actually attach it
//	// now that we actually created the framebuffer and added all attachments we want to check if it is actually complete now
//	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
//		cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << endl;
//	glBindFramebuffer(GL_FRAMEBUFFER, 0);
//    // render loop
//    // -----------
//    while(!glfwWindowShouldClose(window))
//    {
//        // per-frame time logic
//        // --------------------
//        float currentFrame = static_cast<float>(glfwGetTime());
//        deltaTime = currentFrame - lastFrame;
//        lastFrame = currentFrame;
//
//        // input
//        // -----
//        processInput(window);
//
//		glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
//		glEnable(GL_DEPTH_TEST); // enable depth testing (is disabled for rendering screen-space quad)
//		glEnable(GL_CULL_FACE);
//		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
//		
//		// make sure we clear the framebuffer's content
//		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
//		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
//
//		shader.use();
//		glm::mat4 model = glm::mat4(1.0f);
//		glm::mat4 view = camera.GetViewMatrix();
//		glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
//		shader.setMat4("view", view);
//		shader.setMat4("projection", projection);
//		// cubes
//		glBindVertexArray(cubeVAO);
//		glActiveTexture(GL_TEXTURE0);
//		glBindTexture(GL_TEXTURE_2D, cubeTexture);
//		model = glm::translate(model, glm::vec3(-1.0f, 0.0f, -1.0f));
//		shader.setMat4("model", model);
//		glDrawArrays(GL_TRIANGLES, 0, 36);
//		model = glm::mat4(1.0f);
//		model = glm::translate(model, glm::vec3(2.0f, 0.0f, 0.0f));
//		shader.setMat4("model", model);
//		glDrawArrays(GL_TRIANGLES, 0, 36);
//		// floor
//		glBindVertexArray(planeVAO);
//		glBindTexture(GL_TEXTURE_2D, floorTexture);
//		shader.setMat4("model", glm::mat4(1.0f));
//		glDrawArrays(GL_TRIANGLES, 0, 6);
//		glBindVertexArray(0);
//
//		glBindFramebuffer(GL_FRAMEBUFFER, 0);
//		glDisable(GL_DEPTH_TEST); 
//		glClear(GL_COLOR_BUFFER_BIT);
//		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // Return to normal rendering
//		glDisable(GL_CULL_FACE);
//
//		screenShader.use();
//		glBindVertexArray(quadVAO);
//		glBindTexture(GL_TEXTURE_2D, textureColorbuffer);	// use the color attachment texture as the texture of the quad plane
//		glDrawArrays(GL_TRIANGLES, 0, 6);
//
//        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
//        // -------------------------------------------------------------------------------
//        glfwSwapBuffers(window);
//        glfwPollEvents();
//    }
//
//    // optional: de-allocate all resources once they've outlived their purpose:
//    // ------------------------------------------------------------------------
//	glDeleteVertexArrays(1, &cubeVAO);
//	glDeleteVertexArrays(1, &planeVAO);
//	glDeleteVertexArrays(1, &quadVAO);
//	glDeleteBuffers(1, &cubeVBO);
//	glDeleteBuffers(1, &planeVBO);
//	glDeleteBuffers(1, &quadVBO);
//	glDeleteRenderbuffers(1, &rbo);
//	glDeleteFramebuffers(1, &framebuffer);
//
//    glfwTerminate();
//    return 0;
//}
//
//void processInput(GLFWwindow* window)
//{
//        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
//                glfwSetWindowShouldClose(window, true);
//
//        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
//                camera.ProcessKeyboard(FORWARD, deltaTime);
//        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
//                camera.ProcessKeyboard(BACKWARD, deltaTime);
//        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
//                camera.ProcessKeyboard(LEFT, deltaTime);
//        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
//                camera.ProcessKeyboard(RIGHT, deltaTime);
//}
//
//void framebuffer_size_callback(GLFWwindow* window, int width, int height)
//{
//    // make sure the viewport matches the new window dimensions; note that width and 
//    // height will be significantly larger than specified on retina displays.
//    glViewport(0, 0, width, height);
//}
//
//// glfw: whenever the mouse moves, this callback is called
//// -------------------------------------------------------
//void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
//{
//    float xpos = static_cast<float>(xposIn);
//    float ypos = static_cast<float>(yposIn);
//
//    if (firstMouse)
//    {
//        lastX = xpos;
//        lastY = ypos;
//        firstMouse = false;
//    }
//
//    float xoffset = xpos - lastX;
//    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top
//
//    lastX = xpos;
//    lastY = ypos;
//
//    camera.ProcessMouseMovement(xoffset, yoffset);
//}
//
//// glfw: whenever the mouse scroll wheel scrolls, this callback is called
//// ----------------------------------------------------------------------
//void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
//{
//    camera.ProcessMouseScroll(static_cast<float>(yoffset));
//}
//
//// utility function for loading a 2D texture from file
//// ---------------------------------------------------
//unsigned int myLoadTexture(char const *path, GLint wrapParam)
//{
//    unsigned int textureID;
//    glGenTextures(1, &textureID);
//
//    int width, height, nrComponents;
//    unsigned char *data = stbi_load(path, &width, &height, &nrComponents, 0);
//    if (data)
//    {
//        GLenum format = GL_RGB;
//        if (nrComponents == 1)
//            format = GL_RED;
//        else if (nrComponents == 3)
//            format = GL_RGB;
//        else if (nrComponents == 4)
//            format = GL_RGBA;
//
//        glBindTexture(GL_TEXTURE_2D, textureID);
//        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
//        glGenerateMipmap(GL_TEXTURE_2D);
//
//        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapParam);
//        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapParam);
//        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
//        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//
//        stbi_image_free(data);
//    }
//    else
//    {
//        std::cout << "Texture failed to load at path: " << path << std::endl;
//        stbi_image_free(data);
//    }
//
//    return textureID;
//}
