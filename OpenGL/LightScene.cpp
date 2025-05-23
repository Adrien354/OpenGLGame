// #include <glad/glad.h>
// #include <GLFW/glfw3.h>
// 
// #include <glm/glm.hpp>
// #include <glm/gtc/matrix_transform.hpp>
// #include <glm/gtc/type_ptr.hpp>
// 
// #include "shaderLoader/shader_c.h"
// #include "camera/camera.h"
// #include "stb_image/stb_image.h"
// 
// #include <iostream>
// 
// void framebuffer_size_callback	(GLFWwindow* window, int width, int height);
// void mouse_callback(GLFWwindow* window, double xpos, double ypos);
// void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
// void processInput(GLFWwindow* window);
// unsigned int loadTexture(char const* path);
// 
// //settings
// const unsigned int SCR_WIDTH = 800;
// const unsigned int SCR_HEIGHT = 600;
// 
// // camera
// Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
// float lastX = SCR_WIDTH / 2.0f;
// float lastY = SCR_HEIGHT / 2.0f;
// bool firstMouse = true;
// 
// // timing
// float deltaTime = 0.0f;
// float lastFrame = 0.0f;
// 
// glm::vec3 lightPos(1.2f, 1.0f, 2.0f);
// 
// int main() {
// glfwInit();
// glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
// glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
// glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
// 
// #ifdef __APPLE__
// glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
// #endif
// 
// //window creation
// GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "OpenGLLightning", NULL, NULL);
// if (window == NULL) {
// 	std::cout << "Failed to create GLFW window" << std::endl;
// 	glfwTerminate();
// 	return -1;
// }
// 
// glfwMakeContextCurrent(window);
// glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
// glfwSetCursorPosCallback(window, mouse_callback);
// glfwSetScrollCallback(window, scroll_callback);
// 
// glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
// 
// if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
// 	std::cout << "Failed to initialize GLAD" << std::endl;
// 	return -1;
// }
// 
// glEnable(GL_DEPTH_TEST);
// 
// Shader lightingShader("../resources/shaders/shader.vs","../resources/shaders/shader.fs");
// Shader lightCubeShader("../resources/shaders/lightCube.vs","../resources/shaders/lightCube.fs");
// 
// float vertices[] = {
// 	// positions          // normals           // texture coords
// 	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
// 	 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
// 	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
// 	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
// 	-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
// 	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
// 
// 	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
// 	 0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
// 	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
// 	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
// 	-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
// 	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
// 
// 	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
// 	-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
// 	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
// 	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
// 	-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
// 	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
// 
// 	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
// 	 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
// 	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
// 	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
// 	 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
// 	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
// 
// 	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
// 	 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
// 	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
// 	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
// 	-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
// 	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
// 
// 	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
// 	 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
// 	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
// 	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
// 	-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
// 	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f
// };
// 
// // positions all containers
// glm::vec3 cubePositions[] = {
// 	glm::vec3(0.0f,  0.0f,  0.0f),
// 	glm::vec3(2.0f,  5.0f, -15.0f),
// 	glm::vec3(-1.5f, -2.2f, -2.5f),
// 	glm::vec3(-3.8f, -2.0f, -12.3f),
// 	glm::vec3(2.4f, -0.4f, -3.5f),
// 	glm::vec3(-1.7f,  3.0f, -7.5f),
// 	glm::vec3(1.3f, -2.0f, -2.5f),
// 	glm::vec3(1.5f,  2.0f, -2.5f),
// 	glm::vec3(1.5f,  0.2f, -1.5f),
// 	glm::vec3(-1.3f,  1.0f, -1.5f)
// };
// 
// glm::vec3 pointLightPositions[] = {
// 	glm::vec3(0.7f, 0.2f, 2.0f),
// 	glm::vec3(2.3f, -3.3f, -4.0f),
// 	glm::vec3(-4.0f, 2.0f, -12.0f),
// 	glm::vec3(0.0f, 0.0f, -3.0f)
// };
// 
// glm::vec3 pointLightColors[] = {
// 	glm::vec3(0.2f, 0.1f, 0.1f),
// 	glm::vec3(0.2f, 0.1f, 0.1f),
// 	glm::vec3(0.2f, 0.1f, 0.1f),
// 	glm::vec3(0.4f, 0.1f, 0.1f)
// };
// 
// unsigned int VBO, cubeVAO;
// glGenVertexArrays(1, &cubeVAO);
// glGenBuffers(1, &VBO);
// 
// glBindBuffer(GL_ARRAY_BUFFER, VBO);
// glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
// 
// glBindVertexArray(cubeVAO);
// 
// glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
// glEnableVertexAttribArray(0);
// 
// glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
// glEnableVertexAttribArray(1);
// glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
// glEnableVertexAttribArray(2);
// 
// unsigned int lightCubeVAO;
// glGenVertexArrays(1, &lightCubeVAO);
// glBindVertexArray(lightCubeVAO);
// 
// glBindBuffer(GL_ARRAY_BUFFER, VBO);
// 
// glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
// glEnableVertexAttribArray(0);
// 
// unsigned int diffuseMap = loadTexture("../resources/textures/container2.png");
// unsigned int specularMap = loadTexture("../resources/textures/container2_specular.png");
// 
// lightingShader.use();
// lightingShader.setInt("material.diffuse", 0);
// lightingShader.setInt("material.specular", 1);
// 
// 
// while (!glfwWindowShouldClose(window))
// {
// 	// per-frame time logic
// 	// --------------------
// 	float currentFrame = static_cast<float>(glfwGetTime());
// 	deltaTime = currentFrame - lastFrame;
// 	lastFrame = currentFrame;
// 
// 	// input
// 	// -----
// 	processInput(window);
// 
// 	// render
// 	// ------
// 	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
// 	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
// 
// 	
// 	/*lightPos.x = 1.0f + sin(glfwGetTime()) * 2.0f;
// 	lightPos.y = sin(glfwGetTime() / 2.0f) * 1.0f;*/
// 
// 	// be sure to activate shader when setting uniforms/drawing objects
// 	lightingShader.use();
// 	lightingShader.setVec3("viewPos", glm::vec3(0.0f, 0.0f, 0.0f));
// 	lightingShader.setFloat("material.shininess", 32.0f);
// 
// 	// view/projection transformations
// 	glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
// 	glm::mat4 view = camera.GetViewMatrix();
// 	lightingShader.setMat4("projection", projection);
// 	lightingShader.setMat4("view", view);
// 
// 	// directional light
// 	lightingShader.setVec3("dirLight.direction", glm::vec3(view * glm::vec4(-0.2f, -1.0f, -0.3f, 0.0f)));
// 	lightingShader.setVec3("dirLight.ambient", 0.0f, 0.0f, 0.0f);
// 	lightingShader.setVec3("dirLight.diffuse", 0.05f, 0.05f, 0.05);
// 	lightingShader.setVec3("dirLight.specular", 0.2f, 0.2f, 0.2f);
// 	// point light 1
// 	lightingShader.setVec3("pointLights[0].position", glm::vec3(view* glm::vec4(pointLightPositions[0], 1.0f)));
// 	lightingShader.setVec3("pointLights[0].ambient", pointLightColors[0] * 0.1f);
// 	lightingShader.setVec3("pointLights[0].diffuse", pointLightColors[0]);
// 	lightingShader.setVec3("pointLights[0].specular", pointLightColors[0]);
// 	lightingShader.setFloat("pointLights[0].constant", 1.0f);
// 	lightingShader.setFloat("pointLights[0].linear", 0.09f);
// 	lightingShader.setFloat("pointLights[0].quadratic", 0.032f);
// 	// point light 2
// 	lightingShader.setVec3("pointLights[1].position", glm::vec3(view * glm::vec4(pointLightPositions[1], 1.0f)));
// 	lightingShader.setVec3("pointLights[1].ambient", pointLightColors[1] * 0.1f);
// 	lightingShader.setVec3("pointLights[1].diffuse", pointLightColors[1]);
// 	lightingShader.setVec3("pointLights[1].specular", pointLightColors[1]);
// 	lightingShader.setFloat("pointLights[1].constant", 1.0f);
// 	lightingShader.setFloat("pointLights[1].linear", 0.09f);
// 	lightingShader.setFloat("pointLights[1].quadratic", 0.032f);
// 	// point light 3
// 	lightingShader.setVec3("pointLights[2].position", glm::vec3(view* glm::vec4(pointLightPositions[2], 1.0f)));
// 	lightingShader.setVec3("pointLights[2].ambient", pointLightColors[2] * 0.1f);
// 	lightingShader.setVec3("pointLights[2].diffuse", pointLightColors[2]);
// 	lightingShader.setVec3("pointLights[2].specular", pointLightColors[2]);
// 	lightingShader.setFloat("pointLights[2].constant", 1.0f);
// 	lightingShader.setFloat("pointLights[2].linear", 0.09f);
// 	lightingShader.setFloat("pointLights[2].quadratic", 0.032f);
// 	// point light 4
// 	lightingShader.setVec3("pointLights[3].position", glm::vec3(view* glm::vec4(pointLightPositions[3], 1.0f)));
// 	lightingShader.setVec3("pointLights[3].ambient", pointLightColors[3] * 0.1f);
// 	lightingShader.setVec3("pointLights[3].diffuse", pointLightColors[3]);
// 	lightingShader.setVec3("pointLights[3].specular", pointLightColors[3]);
// 	lightingShader.setFloat("pointLights[3].constant", 1.0f);
// 	lightingShader.setFloat("pointLights[3].linear", 0.09f);
// 	lightingShader.setFloat("pointLights[3].quadratic", 0.032f);
// 	// spotLight
// 	lightingShader.setVec3("spotLight.position", glm::vec3(view * glm::vec4(camera.Position, 1.0f)));
// 	lightingShader.setVec3("spotLight.direction", glm::vec3(view * glm::vec4(camera.Front,0.0f)));
// 	lightingShader.setVec3("spotLight.ambient", 0.0f, 0.0f, 0.0f);
// 	lightingShader.setVec3("spotLight.diffuse", 1.0f, 1.0f, 1.0f);
// 	lightingShader.setVec3("spotLight.specular", 1.0f, 1.0f, 1.0f);
// 	lightingShader.setFloat("spotLight.constant", 1.0f);
// 	lightingShader.setFloat("spotLight.linear", 0.09f);
// 	lightingShader.setFloat("spotLight.quadratic", 0.032f);
// 	lightingShader.setFloat("spotLight.cutOff", glm::cos(glm::radians(10.0f)));
// 	lightingShader.setFloat("spotLight.outerCutOff", glm::cos(glm::radians(15.0f)));
// 
// 	// world transformation
// 	glm::mat4 model = glm::mat4(1.0f);
// 	lightingShader.setMat4("model", model);
// 
// 	// bind diffuse map
// 	glActiveTexture(GL_TEXTURE0);
// 	glBindTexture(GL_TEXTURE_2D, diffuseMap);
// 	// bind specular map
// 	glActiveTexture(GL_TEXTURE1);
// 	glBindTexture(GL_TEXTURE_2D, specularMap);
// 
// 	// render containers
// 	glBindVertexArray(cubeVAO);
// 	for (unsigned int i = 0; i < 10; i++)
// 	{
// 		// calculate the model matrix for each object and pass it to shader before drawing
// 		glm::mat4 model = glm::mat4(1.0f);
// 		model = glm::translate(model, cubePositions[i]);
// 		float angle = 20.0f * i;
// 		model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
// 		lightingShader.setMat4("model", model);
// 
// 		glDrawArrays(GL_TRIANGLES, 0, 36);
// 	}
// 
// 	lightCubeShader.use();
// 	lightCubeShader.setMat4("projection", projection);
// 	lightCubeShader.setMat4("view", view);
// 
// 	// we now draw as many light bulbs as we have point lights.
// 	glBindVertexArray(lightCubeVAO);
// 	for (unsigned int i = 0; i < 4; i++)
// 	{
// 		glm::mat4 model = glm::mat4(1.0f);
// 		model = glm::translate(model, pointLightPositions[i]);
// 		model = glm::scale(model, glm::vec3(0.2f)); // Make it a smaller cube
// 		lightCubeShader.setMat4("model", model);
// 		glDrawArrays(GL_TRIANGLES, 0, 36);
// 	}
// 
// 	glfwSwapBuffers(window);
// 	glfwPollEvents();
// }
// 
// glDeleteVertexArrays(1, &cubeVAO);
// glDeleteVertexArrays(1, &lightCubeVAO);
// glDeleteBuffers(1, &VBO);
// 
// glfwTerminate();
// return 0;
// }
// 
// 
// void processInput(GLFWwindow* window)
// {
// if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
// 	glfwSetWindowShouldClose(window, true);
// 
// if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
// 	camera.ProcessKeyboard(FORWARD, deltaTime);
// if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
// 	camera.ProcessKeyboard(BACKWARD, deltaTime);
// if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
// 	camera.ProcessKeyboard(LEFT, deltaTime);
// if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
// 	camera.ProcessKeyboard(RIGHT, deltaTime);
// }
// 
// void framebuffer_size_callback(GLFWwindow* window, int width, int height)
// {
// glViewport(0, 0, width, height);
// }
// 
// 
// void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
// {
// float xpos = static_cast<float>(xposIn);
// float ypos = static_cast<float>(yposIn);
// 
// if (firstMouse)
// {
// 	lastX = xpos;
// 	lastY = ypos;
// 	firstMouse = false;
// }
// 
// float xoffset = xpos - lastX;
// float yoffset = lastY - ypos;
// 
// lastX = xpos;
// lastY = ypos;
// 
// camera.ProcessMouseMovement(xoffset, yoffset);
// }
// 
// void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
// {
// camera.ProcessMouseScroll(static_cast<float>(yoffset));
// }
// 
// unsigned int loadTexture(char const* path)
// {
// unsigned int textureID;
// glGenTextures(1, &textureID);
// 
// int width, height, nrComponents;
// unsigned char* data = stbi_load(path, &width, &height, &nrComponents, 0);
// if (data)
// {
// 	GLenum format;
// 	if (nrComponents == 1)
// 		format = GL_RED;
// 	else if (nrComponents == 3)
// 		format = GL_RGB;
// 	else if (nrComponents == 4)
// 		format = GL_RGBA;
// 
// 	glBindTexture(GL_TEXTURE_2D, textureID);
// 	glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
// 	glGenerateMipmap(GL_TEXTURE_2D);
// 
// 	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
// 	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
// 	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
// 	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
// 
// 	stbi_image_free(data);
// }
// else
// {
// 	std::cout << "Texture failed to load at path: " << path << std::endl;
// 	stbi_image_free(data);
// }
// 
// return textureID;
// }
