#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <vector>

#include "ShaderClass.hpp"
#include "camera.hpp"
#include "rVectorClass.hpp"
#include "animation.hpp"

#include "stb_image.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


void framebufferSizeCallback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

// settings
//unsigned int SCR_WIDTH = 800;
//unsigned int SCR_HEIGHT = 800;
unsigned int SCR_WIDTH = 1920;
unsigned int SCR_HEIGHT = 1080;



int main()
{
    // glfw: initialize and configure
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    // glfw window creation
    // window
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "AkaWindow", NULL, NULL);
    // full screen
    //GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "AkaWindow", glfwGetPrimaryMonitor(), NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);



    // glad: load all OpenGL function pointers
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glEnable(GL_DEPTH_TEST);


    // program.exe is located under out
    Shader lightShader("..\\..\\..\\src\\vertexLightSourceShader", "..\\..\\..\\src\\fragmentLightSourceShader");
    Shader cShader("..\\..\\..\\src\\vertexShader", "..\\..\\..\\src\\fragmentShader");

    // rectangle with colors and texture mapping drawn using drawElements
    //GLfloat vertices[] = {
    //    // positions          // colors           // texture coords
    //     0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   2.0f, 2.0f, // top right
    //     0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   2.0f, 0.0f, // bottom right
    //    -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
    //    -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 2.0f  // top left 
    //};

    // cube with texture mapping drawn using drawArrays
    GLfloat cubeVertices[] = {
    // position           // texture coords
    -0.5f, -0.5f, -0.5f,  //0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  //1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  //1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  //1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  //0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  //0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f,  //0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  //1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  //1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  //1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  //0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  //0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f,  //1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  //1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  //0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  //0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  //0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  //1.0f, 0.0f,

     0.5f,  0.5f,  0.5f,  //1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  //1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  //0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  //0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  //0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  //1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,  //0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  //1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  //1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  //1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  //0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  //0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f,  //0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  //1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  //1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  //1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  //0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f//,  0.0f, 1.0f
    };


    glm::vec3 cubePositions[] = {
        glm::vec3(0.0f,  0.0f,  0.0f),
        glm::vec3(2.0f,  5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3(2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f,  3.0f, -7.5f),
        glm::vec3(1.3f, -2.0f, -2.5f),
        glm::vec3(1.5f,  2.0f, -2.5f),
        glm::vec3(1.5f,  0.2f, -1.5f),
        glm::vec3(-1.3f,  1.0f, -1.5f)
    };

    std::vector<glm::vec3> animationPath{
        glm::vec3(4.0f,  4.0f,  4.0f),
        glm::vec3(2.0f,  5.0f,  3.0f),
        glm::vec3(2.5f,  2.0f,  2.0f),
        glm::vec3(2.5f,  2.0f,  2.0f),
        glm::vec3(3.0f,  -1.0f,  1.0f),
        glm::vec3(0.5f,  1.3f,  2.0f),
    };

    // indices for drawElements for rectangle
    GLuint rectangleIndices[] = {
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };

    unsigned int VERTICES_PER_AXIS = 100;

    std::vector<glm::vec3> firstRVertices{
        glm::vec3(0.3f, -0.2f, -1.0f),
        glm::vec3(0.0f, 0.2f, -1.0f),
        glm::vec3(-0.3f, -0.2f, -1.0f),
        glm::vec3(1.0f, 1.0f,  0.0f),
        glm::vec3(0.0f, 2.0f,  0.0f),
        glm::vec3(-1.0f, 1.0f,  0.0f),
        glm::vec3(0.8f, 1.0f,  1.0f),
        glm::vec3(0.0f, 1.5f,  1.0f),
        glm::vec3(-0.8f, 1.0f,  1.0f)
    };
    std::vector<glm::vec3> secondRVertices{
        glm::vec3(0.8f, 1.0f,  1.0f),
        glm::vec3(0.0f, 1.5f,  1.0f),
        glm::vec3(-0.8f, 1.0f,  1.0f),
        glm::vec3(1.2f, 1.3f,  2.0f),
        glm::vec3(0.0f, 2.3f,  2.0f),
        glm::vec3(-1.2f, 1.3f,  2.0f),
        glm::vec3(1.3f, 1.5f,  3.0f),
        glm::vec3(0.0f, 2.5f,  3.0f),
        glm::vec3(-1.3f, 1.5f,  3.0f)
    };

    std::vector<std::pair<glm::vec3, glm::vec2>> firstBodyVerticesVector((VERTICES_PER_AXIS + 1) * (VERTICES_PER_AXIS + 1));
    rVector firstBodyRVector(firstRVertices);
    for (size_t u_iter = 0; u_iter <= VERTICES_PER_AXIS; u_iter++)
    {
        for (size_t v_iter = 0; v_iter <= VERTICES_PER_AXIS; v_iter++)
        {
            firstBodyVerticesVector[u_iter * (VERTICES_PER_AXIS + 1) + v_iter] = std::pair<glm::vec3, glm::vec2>{ firstBodyRVector.getVertex(static_cast<float>(u_iter) / VERTICES_PER_AXIS, static_cast<float>(v_iter) / VERTICES_PER_AXIS), glm::vec2(static_cast<float>(u_iter) / VERTICES_PER_AXIS , static_cast<float>(v_iter) / VERTICES_PER_AXIS)};
        }
    }

    std::vector<std::pair<glm::vec3, glm::vec2>> secondBodyVerticesVector((VERTICES_PER_AXIS + 1) * (VERTICES_PER_AXIS + 1));
    rVector secondBodyRVector(secondRVertices);
    for (size_t u_iter = 0; u_iter <= VERTICES_PER_AXIS; u_iter++)
    {
        for (size_t v_iter = 0; v_iter <= VERTICES_PER_AXIS; v_iter++)
        {
            secondBodyVerticesVector[u_iter * (VERTICES_PER_AXIS + 1) + v_iter] = std::pair<glm::vec3, glm::vec2>{ secondBodyRVector.getVertex(static_cast<float>(u_iter) / VERTICES_PER_AXIS, static_cast<float>(v_iter) / VERTICES_PER_AXIS), glm::vec2(static_cast<float>(u_iter) / VERTICES_PER_AXIS+1, static_cast<float>(v_iter) / VERTICES_PER_AXIS + 1) };
        }
    }



    GLfloat* bodyVerticesArray = new GLfloat[(firstBodyVerticesVector.size() + secondBodyVerticesVector.size()) * 5];
    unsigned int firstVBOindex = 0;
    for (auto& vec : firstBodyVerticesVector)
    {
        bodyVerticesArray[firstVBOindex++] = vec.first.x;
        bodyVerticesArray[firstVBOindex++] = vec.first.y;
        bodyVerticesArray[firstVBOindex++] = vec.first.z;
        bodyVerticesArray[firstVBOindex++] = vec.second.x;
        bodyVerticesArray[firstVBOindex++] = vec.second.y;
    }
    for (auto& vec : secondBodyVerticesVector)
    {
        bodyVerticesArray[firstVBOindex++] = vec.first.x;
        bodyVerticesArray[firstVBOindex++] = vec.first.y;
        bodyVerticesArray[firstVBOindex++] = vec.first.z;
        bodyVerticesArray[firstVBOindex++] = vec.second.x;
        bodyVerticesArray[firstVBOindex++] = vec.second.y;
    }


    //glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);

    unsigned int bodyEBOSize = 2 * 6 * VERTICES_PER_AXIS * VERTICES_PER_AXIS + 6 * VERTICES_PER_AXIS;
    unsigned int* bodyEBO = new unsigned int[bodyEBOSize];
    unsigned int EBOindex = 0;

    bool parity = true;
    for (size_t u = 0; u < VERTICES_PER_AXIS*2+1; u++)
    {
        for (size_t v = 0; v < VERTICES_PER_AXIS; v++)
        {
            if (parity)
            {
                bodyEBO[EBOindex++] = u * (VERTICES_PER_AXIS + 1) + v;
                bodyEBO[EBOindex++] = (u + 1) * (VERTICES_PER_AXIS + 1) + v;
                bodyEBO[EBOindex++] = u * (VERTICES_PER_AXIS + 1) + v + 1;
                bodyEBO[EBOindex++] = u * (VERTICES_PER_AXIS + 1) + v + 1;
                bodyEBO[EBOindex++] = (u + 1) * (VERTICES_PER_AXIS + 1) + v;
                bodyEBO[EBOindex++] = (u + 1) * (VERTICES_PER_AXIS + 1) + v + 1;
            }
            else
            {
                bodyEBO[EBOindex++] = (1 + u) * (VERTICES_PER_AXIS + 1) - v-1;
                bodyEBO[EBOindex++] = (1 + u + 1) * (VERTICES_PER_AXIS + 1) - v - 1 - 1;
                bodyEBO[EBOindex++] = (1 + u + 1) * (VERTICES_PER_AXIS + 1) - v - 1;
                bodyEBO[EBOindex++] = (1 + u) * (VERTICES_PER_AXIS + 1) - v - 1;
                bodyEBO[EBOindex++] = (1 + u) * (VERTICES_PER_AXIS + 1) - v - 1 - 1;
                bodyEBO[EBOindex++] = (1 + u + 1) * (VERTICES_PER_AXIS + 1) - v - 1 - 1;
            }
        }
        parity = !parity;
    }


    GLuint VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)* firstVBOindex, bodyVerticesArray, GL_STATIC_DRAW);
    delete[] bodyVerticesArray;

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLfloat)* EBOindex, bodyEBO, GL_STATIC_DRAW);
    delete[] bodyEBO;

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);


    //glBindBuffer(GL_ARRAY_BUFFER, 0);
    //glBindVertexArray(0);



    GLuint VBOl, VAOl, EBOl;
    glGenVertexArrays(1, &VAOl);
    glGenBuffers(1, &VBOl);
    glGenBuffers(1, &EBOl);

    glBindVertexArray(VAOl);

    glBindBuffer(GL_ARRAY_BUFFER, VBOl);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);

    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOl);
    //glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLfloat) * EBOindex, bodyEBO, GL_STATIC_DRAW);
    //delete[] bodyEBO;

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    //glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    //glEnableVertexAttribArray(1);




    stbi_set_flip_vertically_on_load(true);

    unsigned int textureContainer[2];
    glGenTextures(2, textureContainer);
    glBindTexture(GL_TEXTURE_2D, textureContainer[0]);
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    int width, height, nrChannels;
    unsigned char* data = stbi_load("..\\..\\..\\textures\\container.jpg", &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);


    glBindTexture(GL_TEXTURE_2D, textureContainer[1]);
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    data = stbi_load("..\\..\\..\\textures\\awesomeface.png", &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);


    cShader.use();
    glUniform1i(glGetUniformLocation(cShader.getProgramID(), "texture1"), 0);
    glUniform1i(glGetUniformLocation(cShader.getProgramID(), "texture2"), 1);


    Camera camera(width, height, glm::vec3(0.0f, 0.0f, 2.0f));
    Animation animation(animationPath);

    float deltaTime = 0.0f;
    float lastFrame = deltaTime;
    // render loop
    while (!glfwWindowShouldClose(window))
    {
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        camera.SetDelta(deltaTime);
        // input
        processInput(window);

        // render
        glClearColor(0.1f, 0.001f, 0.2f, 0.5f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, textureContainer[0]);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, textureContainer[1]);


        glm::mat4 aspectRatioScale = glm::mat4(1.0f);
        aspectRatioScale = glm::scale(aspectRatioScale, glm::vec3(static_cast<float>(SCR_HEIGHT) / SCR_WIDTH, 1.0f, 1.0f));


        // drawing light source
        lightShader.use();
        glBindVertexArray(VAOl);
        glm::mat4 modelLight = glm::mat4(1.0f);
        glm::vec3 lightR = glm::vec3(5.0f, 5.0f, 5.0f);
        glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
        modelLight = glm::translate(modelLight, lightR);
        camera.updateMatrix(45.0f, 0.1f, 100.0f, lightShader, "camMatrix");
        glUniformMatrix4fv(glGetUniformLocation(lightShader.getProgramID(), "aspectRatioScale"), 1, GL_FALSE, glm::value_ptr(aspectRatioScale));
        glUniformMatrix4fv(glGetUniformLocation(lightShader.getProgramID(), "model"), 1, GL_FALSE, glm::value_ptr(modelLight));
        glUniform4fv(glGetUniformLocation(lightShader.getProgramID(), "lightColor"), 1, glm::value_ptr(lightColor));
        glDrawArrays(GL_TRIANGLES, 0, 36);


        //glUseProgram(shaderProgram);
        cShader.use();

        glm::mat4 view = glm::mat4(1.0f);
        glm::mat4 projection = glm::mat4(1.0f);

        //model = glm::translate(model, glm::vec3(0.0f, 0.0f, -1.0f));
        //model = glm::rotate(model, (float)(glfwGetTime()), glm::normalize(glm::vec3(1.0f, 0.6f, 0.2f)));

        //view = camera.GetViewMatrix();
        //projection = glm::perspective(glm::radians(60.0f), (float)(SCR_WIDTH / SCR_HEIGHT), 0.1f, 100.0f);
        //unsigned int viewLoc = glGetUniformLocation(cShader.getProgramID(), "view");
        //glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        //unsigned int projectionLoc = glGetUniformLocation(cShader.getProgramID(), "projection");
        //glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
        camera.Inputs(window);
        // Updates and exports the camera matrix to the Vertex Shader
        camera.updateMatrix(45.0f, 0.1f, 100.0f, cShader, "camMatrix");
        glUniformMatrix4fv(glGetUniformLocation(cShader.getProgramID(), "aspectRatioScale"), 1, GL_FALSE, glm::value_ptr(aspectRatioScale));
        glUniform4fv(glGetUniformLocation(lightShader.getProgramID(), "lightColor"), 1, glm::value_ptr(lightColor));



        glBindVertexArray(VAO);

        // 10 bodies for fun)
        for (size_t i = 0; i < 10; i++)
        {
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, cubePositions[i]);
            model = glm::rotate(model, static_cast<float>(i * 20), glm::normalize(glm::vec3(1.0f, 0.6f, 0.2f)));
            unsigned int modelLoc = glGetUniformLocation(cShader.getProgramID(), "model");
            glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
            //glDrawArrays(GL_TRIANGLES, 0, VBOindex);
            glDrawElements(GL_TRIANGLES, EBOindex, GL_UNSIGNED_INT, 0);
        }

        // drawing animated body
        std::pair<glm::vec3, glm::vec3> posDirection = animation.getPosDirection(sin(glfwGetTime()) + 1);
        glm::mat4 animationModel = glm::mat4(1.0f);
        animationModel = glm::translate(animationModel, posDirection.first);
        glm::vec3 bodyOrientation(0.0f, 0.0f, 1.0f);
        animationModel = glm::rotate(animationModel, acosf(glm::dot(bodyOrientation, posDirection.second) / glm::length(bodyOrientation) / glm::length(posDirection.second)), glm::cross(bodyOrientation, posDirection.second));
        glUniformMatrix4fv(glGetUniformLocation(cShader.getProgramID(), "model"), 1, GL_FALSE, glm::value_ptr(animationModel));
        glDrawElements(GL_TRIANGLES, EBOindex, GL_UNSIGNED_INT, 0);



        //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // glfw: terminate, clearing all previously allocated GLFW resources.
    glfwTerminate();
    return 0;
}

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

}

void framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
    SCR_WIDTH = width;
    SCR_HEIGHT = height;
    glViewport(0, 0, width, height);
}

