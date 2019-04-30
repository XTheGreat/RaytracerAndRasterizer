/*
 *  main.cpp
 *
 *  Created by Christianah Adigun
 *  Copyright 2018. All rights reserved.
 *
 * This file is part of CS5721 Computer Graphics library (cs5721Graphics).
 * 
 * Implementation of the rasterization algorithm.
 *
 */

#include "handleGraphicsArgs.h"

#include "GLSLObject.h"
#include "camera.h"
#include "shape.h"
#include "png++/png.hpp"

using namespace sivelab;

// Creating camera objects and Triangles
cameraData cam;
Triangle triangles;

float oldX = 0, oldY = 0;

// getting callbacks from mouse position
static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
    /***
    float newX, newY, thisX, thisY;
    newX = xpos;
    newY = ypos;

    thisX = newX - oldX;
    thisY = newY- oldY;
    
    if(thisX < 0)
    {
        glm::vec3 W = glm::vec3(thisX/100.0f, 0.0f, -0.1f);
        cam.glpos += W;
    }
    if(thisX > 0)
    {
        glm::vec3 W = glm::vec3(thisX/100.0f, 0.0f, -0.1f);
        cam.glpos -= W;

    }
    if(thisY < 0)
    {
        glm::vec3 W = glm::vec3(0.0f, thisY/1000.0f, -0.1f);
        cam.glpos += W;
    }
    if(thisY > 0)
    {
        glm::vec3 W = glm::vec3(0.0f, thisY/1000.0f, -0.1f);
        cam.glpos -= W;
    }
    std::cout << thisX << " " << thisY << " " << std::endl;
        oldX = newX;
        oldY = newY;
    ****/
}

// get notified of key press
void updatePosition(char keyPress)
{
    // orthonormal basis
    glm::vec3 U, V, W;
    U = glm::vec3(0.01f, 0.0f, 0.0f);
    W = glm::vec3(0.0f, 0.0f, -0.1f);
    V = glm::vec3(0.0f, -1.0f, 0.0f);

    // Forward motion
    if(keyPress == 'W')
    {
      cam.glpos = cam.glpos - W;
    }

    // Backward motion
    else if(keyPress == 'S')
    {
      cam.glpos = cam.glpos + W;
    }

    // left motion
    else if(keyPress == 'A')
    {
      cam.glpos = cam.glpos + U;
    }

    // Right motion
    else if(keyPress == 'D')
    {
      cam.glpos = cam.glpos - U;
    }

    else{}
}

void glfwErrorCallback(int error, const char* description)
{
    std::cerr << "GLFW ERROR: " << description << std::endl;
}

/**
 * main entry function - Establishes the OpenGL context with the GLFW
 * (http://www.glfw.org/) and creates a window within this context.
 *
 * 
 */

int main(int argc, char *argv[])
{
    GraphicsArgs args;
    args.process(argc, argv);


    // Initialize the GLFW library
    if ( !glfwInit() )
        exit(EXIT_FAILURE);

    // Request a specific OpenGL context when the window is created
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    glfwSetErrorCallback( glfwErrorCallback );

    /* Create a windowed mode window and its OpenGL context */
    int winWidth = 800;
    float aspectRatio = 9.0 / 16.0; // winWidth / (float)winHeight;
    int winHeight = winWidth * aspectRatio;
    
    GLFWwindow* window = glfwCreateWindow(winWidth, winHeight, "OpenGL Example", NULL, NULL);
    if (!window) {
        std::cerr << "ERROR: GLFW did not create a window!" << std::endl;
        
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    // Make the window's context current
    glfwMakeContextCurrent(window);

    glewExperimental = GL_TRUE; 
    glewInit();
    

    const GLubyte* renderer = glGetString (GL_RENDERER);
    const GLubyte* version = glGetString (GL_VERSION);
    // Need to tell OpenGL how big the window is going to be so it can
    // create enough memory on the graphics card to store the pixel
    // colors.
    //
    // We will query glfw to see how big the window was when we
    // created it and then pass that info to OpenGL's viewport function.

    // texture code
    /**** Texture File ******/
    // std::string texFilename = "textureMapCalibration_1024x1024.png";
    std::string texFilename = "texture-02.png";
    std::cout << "Reading texture map data from file: " << texFilename << std::endl;
    png::image< png::rgb_pixel > texPNGImage;
    texPNGImage.read( texFilename );

    int pngWidth = texPNGImage.get_width();
    int pngHeight = texPNGImage.get_height();
    float *copiedPNGData = new float[ pngHeight * pngWidth * 3 ];

    int tIdx = 0;

    for (unsigned int idx=0; idx<pngHeight*pngWidth; ++idx) {
        size_t col = idx % pngWidth;
        size_t row = static_cast<size_t>( floor(idx / static_cast<float>(pngWidth)) );
        
        png::rgb_pixel texel = texPNGImage[ pngHeight-1 - row ][col];
        
        copiedPNGData[tIdx++] = texel.red/255.0;
        copiedPNGData[tIdx++] = texel.green/255.0;
        copiedPNGData[tIdx++] = texel.blue/255.0;
    } 


    GLuint texID;
    
    glGenTextures(1, &texID);

    glBindTexture(GL_TEXTURE_2D, texID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, pngWidth, pngHeight, 0, GL_RGB, GL_FLOAT, copiedPNGData);
    glBindTexture(GL_TEXTURE_2D, 0);
    delete [] copiedPNGData;

     /**************** code for this lab **************************/
    GLuint m_triangleVBO;
    glGenBuffers(1, &m_triangleVBO);

    glBindBuffer(GL_ARRAY_BUFFER, m_triangleVBO);

    if (args.inputFileName != "" && args.inputFileName.substr(args.inputFileName.find_last_of(".") + 1) == "obj")
    {
        triangles.initialize(args.inputFileName);
    }

    glBufferData(GL_ARRAY_BUFFER, triangles.numBytes, triangles.host_VertexBuffer, GL_STATIC_DRAW);
    delete [] triangles.host_VertexBuffer;

    GLuint m_VAO;
    glGenVertexArrays(1, &m_VAO);
    glBindVertexArray(m_VAO);

    
    
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), 0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (const GLvoid *)12);
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (const GLvoid *)24);
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, m_triangleVBO);
    

    sivelab::GLSLObject shader;
    shader.addShader( "./HwRasterize/vertexShader_passthrough.glsl", sivelab::GLSLObject::VERTEX_SHADER );
    shader.addShader( "./HwRasterize/fragmentShader_passthrough.glsl", sivelab::GLSLObject::FRAGMENT_SHADER );
    shader.createProgram();


    /**************code here ***/
    GLint texUnitID = shader.createUniform( "textureUnit" );
    GLint projMatrixID = shader.createUniform( "projMatrix" );
    GLint viewMatrixID = shader.createUniform( "viewMatrix" );
    GLint modelMatrixID = shader.createUniform( "modelMatrix" );
    // adding light
    GLint lightPosID = shader.createUniform( "light.position" );
    GLint lightIntensityID = shader.createUniform( "light.intensity" );
    GLint viewID = shader.createUniform( "viewDir" );


    int fb_width, fb_height;
    glfwGetFramebufferSize(window, &fb_width, &fb_height);
    glViewport(0, 0, fb_width, fb_height);
    
    //setting position of camera
    cam.glpos = glm::vec3(0.0f, 0.0f, -5.0f);
    

    // Set the background color for our window
    glClearColor(0.5, 0.5, 0.5, 1.0);

    // Loop until the user closes the window 
    while (!glfwWindowShouldClose(window))
    {
        // Clear the window's buffer (or clear the screen to our
        // background color)
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //
        // Eventually, any OpenGL code that renders your scene can go here
        // 
        shader.activate();

        // Projection, view and model matrices
        // glm::mat4 projMatrix = glm::ortho(-5.0f, 5.0f, -5.0f, 5.0f, -10.0f, 10.0f);
        glm::mat4 modelTransform = glm::mat4(1.0f);

        // Light Position
        glm::vec3 lightPosition = glm::vec3(-5.0f, 100.0f, 0.0f);
        glm::vec3 lightIntensity = glm::vec3(1.0f, 1.0f, 1.0f);

        // set pointer value to it
        // lUniformMatrix4fv(projMatrixID, 1, GL_FALSE, glm::value_ptr(projMatrix));
        glUniformMatrix4fv(projMatrixID, 1, GL_FALSE, glm::value_ptr(cam.getProjectionMatrix()));
        glUniformMatrix4fv(viewMatrixID, 1, GL_FALSE, glm::value_ptr(cam.getViewMatrix() ));
        glUniformMatrix4fv(modelMatrixID, 1, GL_FALSE, glm::value_ptr(modelTransform));
        glUniform3f(lightPosID, lightPosition.x, lightPosition.y, lightPosition.z);
        glUniform3f(lightIntensityID, lightIntensity.x, lightIntensity.y, lightIntensity.z);
        // get view Dir
        glUniform3f(viewID, 0.0f, 0.0f, -0.1f);

        // Texture ID
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texID);
        glUniform1i(texUnitID, 0);

        glBindVertexArray(m_VAO);
        glDrawArrays(GL_TRIANGLES, 0, triangles.numFloatsNeeded);
        glBindVertexArray(0);

        glBindTexture(GL_TEXTURE_2D, 0);

        shader.deactivate();

        
        // Swap the front and back buffers
        glfwSwapBuffers(window);

        // Poll for and process any events that may have occured with
        // the mouse or keyboard 

        int forward = glfwGetKey(window, GLFW_KEY_W);
        int left = glfwGetKey(window, GLFW_KEY_A);
        int backward = glfwGetKey(window, GLFW_KEY_S);
        int right = glfwGetKey(window, GLFW_KEY_D);

        if(forward == GLFW_PRESS)
        {
            updatePosition('W');
        }
        else if(left == GLFW_PRESS)
        {
            updatePosition('A');
        }
        else if(backward == GLFW_PRESS)
        {
            updatePosition('S');
        }
        else if(right == GLFW_PRESS)
        {
            updatePosition('D');
        }
        else{}

        glfwPollEvents();
        if (glfwGetKey( window, GLFW_KEY_ESCAPE ) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, 1);

        glfwSetCursorPosCallback(window, cursor_position_callback);
    }
  
    // Terminate the application, close the window and clean-up any
    // OpenGL context memory
    glfwTerminate();
    
    exit(EXIT_SUCCESS);
}