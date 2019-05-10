#ifndef __Mesh_H__
#define __Mesh_H__

class CameraComponent;
class Material;
class Texture;
class VertexFormat;

class Mesh
{
protected:
    GLuint m_VBO;
    GLuint m_IBO;

    unsigned int m_NumVerts;
    unsigned int m_NumIndices;

    GLenum m_PrimitiveType;

public:
    Mesh();
    virtual ~Mesh();

    void Init(VertexFormat* verts, int numVerts, unsigned int* indices, int numIndices, GLenum primitiveType, GLenum usage);
    void Init(const void* verts, int numVerts, GLenum primitiveType, GLenum usage);

    void SetupAttributes(Material* pMaterial);
    void SetupUniforms(Material* pMaterial, mat4* worldMat, CameraComponent* pCamera, vec2 uvScale, vec2 uvOffset, LightManager* aLight);
    void Draw(Material* pMaterial);

    // The following functions are defined in MeshShapes.cpp:
    void CreateBox(vec2 size, vec2 offset);
    void CreateBoxWithFlippedHorizontalUVs(vec2 size, vec2 offset);
    void CreateCube(vec3 size);
    void CreatePlane(vec2 worldSize, ivec2 vertexCount, vec2 pivotPoint, vec2 uvRepeat = 5);
    void CreateOBJ(const char* objFilename, vec3 scale);
    void CreateRing(float innerradius, float outerradius, int numsegments, MyColor color);
    void CreateArc(float outerradius, int degrees, int numsegments, MyColor color);
};

#endif //__Mesh_H__
