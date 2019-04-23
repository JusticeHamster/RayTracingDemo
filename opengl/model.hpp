#ifndef MODEL_HPP
#define MODEL_HPP

#include <string>
#include <vector>

#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "shader.hpp"
#include "mesh.hpp"
#include "texture.hpp"

class model
{
public:
    model(std::string path, bool gamma = false);
    void draw(shader s);
    void reload();
    bool loaded() const;
private:
    bool init = false;
    bool load();
    std::vector<texture> load(aiMaterial *mat, aiTextureType type, std::string name);
    unsigned load(std::string path, const std::string &directory, bool gamma = false);
    void process(aiNode *node, const aiScene *scene);
    mesh process(aiMesh *m, const aiScene *scene);
    //
    std::string path;
    std::string directory;
    bool gamma;
    std::vector<mesh> meshes;
    std::vector<texture> textures;
};

#endif // MODEL_HPP
