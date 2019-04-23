#include "model.hpp"

#include <assimp/Importer.hpp>
#include "stb/stb_image.h"

using namespace std;

model::model(string path, bool gamma): path(path), gamma(gamma) {
    ;
}

void model::reload() {
    init = false;
}

bool model::loaded() const {
    return init;
}

bool model::load() {
    Assimp::Importer importer;
    const aiScene *scene = importer.ReadFile(path,
        aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace
    );
    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        cout << "scene not loaded";
        return false;
    }
    directory = path.substr(0, path.find_last_of('/'));
    process(scene->mRootNode, scene);
    return true;
}

void model::process(aiNode *node, const aiScene *scene) {
    for (unsigned i = 0; i < node->mNumMeshes; i++) {
        aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
        meshes.push_back(process(mesh, scene));
    }
    for (unsigned i = 0; i < node->mNumChildren; i++) {
        process(node->mChildren[i], scene);
    }
}

mesh model::process(aiMesh *m, const aiScene *scene) {
    vector<vertex>  vertices;
    vector<unsigned> indices;
    vector<texture> textures;

    for (unsigned i = 0; i < m->mNumVertices; i++) {
        glm::vec3 position(
            m->mVertices[i].x,
            m->mVertices[i].y,
            m->mVertices[i].z
        );
        glm::vec3 normal(
            m->mNormals[i].x,
            m->mNormals[i].y,
            m->mNormals[i].z
        );
        glm::vec2 texture(0.0f);
        if (m->mTextureCoords[0]) {
            texture.x = m->mTextureCoords[0][i].x;
            texture.y = m->mTextureCoords[0][i].y;
        }
        glm::vec3 tangent(
            m->mTangents[i].x,
            m->mTangents[i].y,
            m->mTangents[i].z
        );
        glm::vec3 bitangent(
            m->mBitangents[i].x,
            m->mBitangents[i].y,
            m->mBitangents[i].z
        );
        vertices.push_back(vertex(position, normal, texture, tangent, bitangent));
    }

    for (unsigned i = 0; i < m->mNumFaces; i++) {
        const aiFace &face = m->mFaces[i];
        for (unsigned j = 0; j < face.mNumIndices; j++) {
            indices.push_back(face.mIndices[j]);
        }
    }

    aiMaterial *material = scene->mMaterials[m->mMaterialIndex];

    vector<texture> diffuses  = load(material, aiTextureType_DIFFUSE , "texture_diffuse" );
    vector<texture> speculars = load(material, aiTextureType_SPECULAR, "texture_specular");
    vector<texture> normals   = load(material, aiTextureType_NORMALS , "texture_normal"  );
    vector<texture> heights   = load(material, aiTextureType_HEIGHT  , "texture_height"  );

    textures.insert(textures.end(), diffuses.begin() , diffuses.end() );
    textures.insert(textures.end(), speculars.begin(), speculars.end());
    textures.insert(textures.end(), normals.begin()  , normals.end()  );
    textures.insert(textures.end(), heights.begin()  , heights.end()  );

    return mesh(vertices, indices, textures);
}

vector<texture> model::load(aiMaterial *mat, aiTextureType type, string name) {
    vector<texture> ts;

    for (unsigned i = 0; i < mat->GetTextureCount(type); i++) {
        aiString str;
        mat->GetTexture(type, i, &str);
        bool skip = false;
        for (unsigned j = 0; j < textures.size(); j++) {
            if (strcmp(textures[j].path.data(), str.C_Str()) == 0) {
                ts.push_back(textures[j]);
                skip = true;
                break;
            }
        }
        if (!skip) {
            texture t(
                load(str.C_Str(), directory),
                name, str.C_Str()
            );
            ts.push_back(t);
            textures.push_back(t);
        }
    }

    return ts;
}

unsigned model::load(string path, const string &directory, bool gamma) {
    string filename = directory + '/' + path;
    unsigned textureID = 0;

    glGenTextures(1, &textureID);

    int width, height, nrComponents;
    void *data = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);

    if (data) {
        GLenum format;
        if (nrComponents == 1) {
            format = GL_RED;
        } else if (nrComponents == 3) {
            format = GL_RGB;
        } else if (nrComponents == 4) {
            format = GL_RGBA;
        } else {
            format = GL_NONE;
        }

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, static_cast<int>(format), width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    } else {
        cout << "failed to load Texture: " << path << endl;
    }

    stbi_image_free(data);
    return textureID;
}

void model::draw(shader s) {
    if (!init) {
        if (!load()) {
            return;
        }
        init = true;
    }
    for (unsigned i = 0; i < meshes.size(); i++) {
        meshes[i].draw(s);
    }
}
