#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<stb/stb_image.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>

#include <vector>

#include"Texture.h"
#include"shaderClass.h"
#include"VAO.h"
#include"VBO.h"
#include"EBO.h"
#include"Camera.h"
#include "Cube.h"
#include "bodyPart.h"

// Tamanio de la ventana
const unsigned int width = 1500;
const unsigned int height = 1500;

int main()
{	
	// # # # Inicio del programa # # # //

	// Inicializacion de GLFW
	glfwInit();

	// Version que se estara usando en OpenGL
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Creacion de la ventana
	GLFWwindow* window = glfwCreateWindow(width, height, "Proyecto de Josue SA de CV", NULL, NULL);

	// Verificamos que no hubo error
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	// Mandamos la ventana en nuestro contexto actual
	glfwMakeContextCurrent(window);

	// Cargamos GLAD
	gladLoadGL();

	// Mostramos el viewport de los extremos seleccionados
	glViewport(0, 0, width, height);


	// # # # Inicializacion de cada parte con el objeto primitivo # # # //
	float color[] = { 0.83f, 0.70f, 0.44f };
	Cube dorso(-4.0f, 4.0f, 0.0f, 8.0f, 4.0f, -4.0f, color, "ropa.png", "down");
	Cube cintura(-5.0f, 5.0f, -1.0f, 0.0f, 5.0f, -5.0f, color, "white.png", "top");
	Cube musloIzq(-4.0f, -1.0f, -4.0f, -1.0f, 1.5f, -1.5f, color, "white.png", "top");
	Cube musloDer(1.0f, 4.0f, -4.0f, -1.0f, 1.5f, -1.5, color, "white.png", "top");
	Cube piernaIzq(-4.0f, -1.0f, -7.0f, -4.0f, 1.5f, -1.5f, color, "white.png", "top");
	Cube piernaDer(1.0f, 4.0f, -7.0f, -4.0f, 1.5f, -1.5, color, "white.png", "top");
	Cube pieIzq(-4.0f, -1.0f, -8.0f, -7.0f, 2.5f, -1.5f, color, "negro.png", "top");
	Cube pieDer(1.0f, 4.0f, -8.0f, -7.0f, 2.5f, -1.5, color, "negro.png", "top");
	Cube anteBrazoIzq(-7.0f, -4.0f, 5.0f, 8.0f, 1.5f, -1.5f, color, "white.png", "right");
	Cube anteBrazoDer(4.0f, 7.0f, 5.0f, 8.0f, 1.5f, -1.5f, color, "white.png", "left");
	Cube brazoIzq(-10.0f, -7.0f, 5.0f, 8.0f, 1.5f, -1.5f, color, "white.png", "right");
	Cube brazoDer(7.0f, 10.0f, 5.0f, 8.0f, 1.5f, -1.5f, color, "white.png", "left");
	Cube manoIzq(-13.f, -10.0f, 5.0f, 8.0f, 1.5f, -1.5f, color, "manoder.png", "right");
	Cube cabeza(-3.0f, 3.0f, 8.0f, 14.0f, 3.0f, -3.0f, color, "carasimi.png", "down");
	Cube manoDer(10.0f, 13.f, 5.0f, 8.0f, 1.5f, -1.5f, color, "manoizq.png", "left");


	// # # # Inicializacion de partes conjuntas del cuerpo # # # //
	bodyPart BmanoDer(&manoDer);
	bodyPart BbrazoDer(&brazoDer);
	BbrazoDer.next.push_back(&BmanoDer);
	bodyPart BanteBrazoDer(&anteBrazoDer);
	BanteBrazoDer.next.push_back(&BbrazoDer);

	bodyPart BmanoIzq(&manoIzq);
	bodyPart BbrazoIzq(&brazoIzq);
	BbrazoIzq.next.push_back(&BmanoIzq);
	bodyPart BanteBrazoIzq(&anteBrazoIzq);
	BanteBrazoIzq.next.push_back(&BbrazoIzq);

	bodyPart BpieIzq(&pieIzq);
	bodyPart BpiernaIzq(&piernaIzq);
	BpiernaIzq.next.push_back(&BpieIzq);
	bodyPart BmusloIzq(&musloIzq);
	BmusloIzq.next.push_back(&BpiernaIzq);

	bodyPart BpieDer(&pieDer);
	bodyPart BpiernaDer(&piernaDer);
	BpiernaDer.next.push_back(&BpieDer);
	bodyPart BmusloDer(&musloDer);
	BmusloDer.next.push_back(&BpiernaDer);

	bodyPart Bcintura(&cintura);
	Bcintura.next.push_back(&BmusloDer);
	Bcintura.next.push_back(&BmusloIzq);

	bodyPart Bcabeza(&cabeza);
	bodyPart Bdorso(&dorso);
	Bdorso.next.push_back(&Bcabeza);
	Bdorso.next.push_back(&BanteBrazoDer);
	Bdorso.next.push_back(&BanteBrazoIzq);
	Bdorso.next.push_back(&Bcintura);


	// # # # Creacion del shader de iluminacion # # # //
	Shader lightShader("light.vert", "light.frag");

	glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	glm::vec3 lightPos = glm::vec3(0.0f, 5.0f, -12.0f);

	lightShader.Activate();
	glUniform4f(glGetUniformLocation(lightShader.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);


	// # # # Creacion del Buffer Z # # # //
		glEnable(GL_DEPTH_TEST);


	// # # # Creacion la camara # # # //
	Camera camera(width, height, glm::vec3(0.0f, 0.0f, 2.0f));


	// # # # Creacion de la interfaz # # # //
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 330");

	// Loop mientras la ventana este abierta
	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.03f, 0.3f, 0.3f, 1.0f);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Inicializacion de la interfaz
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		// Poner camara
		camera.Inputs(window);
		camera.updateMatrix(45.0f, 0.1f, 100.0f);

		// Dibujamos partes del cuerpo
		dorso.draw(camera);
		cintura.draw(camera);
		musloIzq.draw(camera);
		musloDer.draw(camera);
		piernaIzq.draw(camera);
		piernaDer.draw(camera);
		pieIzq.draw(camera);
		pieDer.draw(camera);
		anteBrazoIzq.draw(camera);
		anteBrazoDer.draw(camera);
		brazoIzq.draw(camera);
		brazoDer.draw(camera);
		manoIzq.draw(camera);
		manoDer.draw(camera);
		cabeza.draw(camera);

		// Configuramos interfaz
		ImGui::Begin("Rotaciones de Simi");
		Bcabeza.showInterface("Cabeza","Reset Cabeza", "Cabeza Eje X", "Cabeza Eje Y", "Cabeza Eje Z", -45.0f, 45.0f, -90.0f, 90.0f, -45.0f, 45.0f);
		Bdorso.showInterface("Dorso", "Reset Dorso", "Dorso Eje X", "Dorso Eje Y", "Dorso Eje Z", -180.0f, 180.0f, -180.0f, 180.0f, -180.0f, 180.0f);
		BanteBrazoIzq.showInterface("Ante Brazo Izquierdo", "Reset Ante Brazo Izquierdo", "Ante Brazo Izquierdo Eje X", "Ante Brazo Izquierdo Eje Y", "Ante Brazo Izquierdo Eje Z", -45.0f, 45.0f, -45.0f, 135.0f, -90.0f, 90.0f);
		BbrazoIzq.showInterface("Brazo Izquierdo", "Reset Brazo Izquierdo", "Brazo Izquierdo Eje X", "Brazo Izquierdo Eje Y", "Brazo Izquierdo Eje Z", -90.0f, 90.0f, 0.0f, 135.0f, -135.0f, 0.0f);
		BmanoIzq.showInterface("Mano Izquierda", "Reset Mano Izquierda", "Mano Izquierda Eje X", "Mano Izquierda Eje Y", "Mano Izquierda Eje Z", 0.0f, 0.0f, -90.0f, 90.0f, -45.0f, 45.0f);
		BanteBrazoDer.showInterface("Ante Brazo Derecho", "Reset Ante Brazo Derecho", "Ante Brazo Derecho Eje X", "Ante Brazo Derecho Eje Y", "Ante Brazo Derecho Eje Z", -45.0f, 45.0f, -135.0f, 45.0f, -90.0f, 90.0f);
		BbrazoDer.showInterface("Brazo Derecho", "Reset Brazo Derecho", "Brazo Derecho Eje X", "Brazo Derecho Eje Y", "Brazo Derecho Eje Z", -90.0f, 90.0f, -135.0f, 0.0f, 0.0f, 135.0f);
		BmanoDer.showInterface("Mano Derecha", "Reset Mano Derecha", "Mano Derecha Eje X", "Mano Derecha Eje Y", "Mano Derecha Eje Z", 0.0f, 0.0f, -90.0f, 90.0f, -45.0f, 45.0f);
		Bcintura.showInterface("Cintura", "Reset Cintura", "Cintura Eje X", "Cintura Eje Y", "Cintura Eje Z", -90.0f, 45.0f, -90.0f, 90.0f, -45.0f, 45.0f);
		BmusloIzq.showInterface("Muslo Izquierda", "Reset Muslo Izquierdo", "Muslo Izquierda Eje X", "Muslo Izquierda Eje Y", "Muslo Izquierda Eje Z", -90.0f, 45.0f, -90.0f, 90.0f, -45.0f, 45.0f);
		BpiernaIzq.showInterface("Pierna Izquierda", "Reset Pierna Izquierda", "Pierna Izquierda Eje X", "Pierna Izquierda Eje Y", "Pierna Izquierda Eje Z", -15.0f, 90.0f, 0.0f, 0.0f, 0.0f, 0.0f);
		BpieIzq.showInterface("Pie Izquierdo", "Reset Pie Izquierdo", "Pie Izquierdo Eje X", "Pie Izquierdo Eje Y", "Pie Izquierdo Eje Z", -15.0f, 15.0f, 0.0f, 0.0f, 0.0f, 0.0f);
		BmusloDer.showInterface("Muslo Derecha", "Reset Muslo Derecho", "Muslo Derecha Eje X", "Muslo Derecha Eje Y", "Muslo Derecha Eje Z", -90.0f, 45.0f, -90.0f, 90.0f, -45.0f, 45.0f);
		BpiernaDer.showInterface("Pierna Derecha", "Reset Pierna Derecha", "Pierna Derecha Eje X", "Pierna Derecha Eje Y", "Pierna Derecha Eje Z", -15.0f, 90.0f, 0.0f, 0.0f, 0.0f, 0.0f);
		BpieDer.showInterface("Pie Derecho", "Reset Pie Derecho", "Pie Derecho Eje X", "Pie Derecho Eje Y", "Pie Derecho Eje Z", -15.0f, 15.0f, 0.0f, 0.0f, 0.0f, 0.0f);

		ImGui::End();

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		// Configuramos camara con iluminacion
		lightShader.Activate();
		camera.Matrix(lightShader, "camMatrix");

		// Cambio de Buffers
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// Concluimos la interfaz
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	// Cerramos window y terminamos programa
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}