#include "Mesh.h"

Mesh::Mesh() {
VAO = 0;
VBO = 0;
IBO = 0;
indexCount = 0;
}

Mesh::~Mesh() {
    ClearMesh();
}

void Mesh::CreateMesh(GLfloat *vertices, unsigned int *indices, unsigned int numOfVertices, unsigned int numOfIndices) {
    
    //Set the index value to current index count
    indexCount = numOfIndices;

    //Create a VAO in the graphics memory
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    //Creat a IBO and, biind to current context and then fill it with the data
    glGenBuffers(1, &IBO);
    glBindBuffer(GL_ARRAY_BUFFER, IBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(indices[0]) * numOfIndices, indices, GL_STATIC_DRAW);

    //Create a VBO, with the target to the gl array buffer type
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    //The static draw makes the vertices static to each draw indicating that they will not change
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * numOfVertices, vertices, GL_STATIC_DRAW);

    //Index of atribute, amount per data group (x,y,z), type of data, normalized?, stride, offset
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    //Enable the atribute with the passed index the one that comes above
    glEnableVertexAttribArray(0);

    //Unbind VAO and VBO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    //WARNING -> The IBO needs to be unbinded

}

void Mesh::RenderMesh() {
        //Bind VAO to give currect context 
        glBindVertexArray(VAO);
        //Bind the IBO to the VAO
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

        glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);

        //UnBind IBO
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        //UnBind VAO
        glBindVertexArray(0);
}

void Mesh::ClearMesh() {

    if(IBO != 0) {
        glDeleteBuffers(1, &IBO);
        IBO = 0;
    }

    if(VBO != 0) {
        glDeleteBuffers(1, &VBO);
        VBO = 0;
    }

    if(VAO != 0) {
        glDeleteBuffers(1, &VAO);
        VAO = 0;
    }

    indexCount = 0;
}