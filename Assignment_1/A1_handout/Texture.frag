#version 420 core

// Input
in vec2 UV;
// Output
out vec3 color;
layout (binding=1) uniform sampler2D DiffuseTextureSampler;// 注意这里binding改为了1, 因为c++里修改了岩石纹理的层级: glGenTextures(1, &textureID);
in vec3 normalVector;// Task2: 从顶点着色器中接受传递过来的法向量?
layout (binding=2) uniform sampler2D RoughnessTextureSampler;// Task3: 获取粗糙度纹理 RoughnessTextureSampler
in vec3 lightDir_Camera;
in vec3 viewDir_Camera;

void main(){
	// 输出岩石的颜色
	//color = texture(DiffuseTextureSampler,vec2(UV.x,UV.y)).rgb;
	

	/* -- Task2 -- START -- */
	// 输出法线的颜色, 需将其他修改颜色的注释掉
	//color = vec3(abs(normalVector.x), abs(normalVector.y), abs(normalVector.z));
	/* -- Task2 --- END --- */


	/* -- Task3 -- START -- */
	// 新建光照颜色,光照强度
	vec3 LightColor = vec3(1, 1, 1);
	float LightPower = 1.0;
	// 由于需要纹理平铺而不是拉伸, 所以调整UV坐标, 并设置重复平铺的次数
	int repeatTimes = 2;
	// 使用fract函数确保UV坐标在[0,1]范围内
	vec2 tiledUV = fract(UV * repeatTimes);
	// 通过灰度图获取粗糙度Roughness的值
	float roughness = texture(RoughnessTextureSampler,vec2(tiledUV.x,tiledUV.y)).r;
	// 计算光泽度
	float shininess = clamp((2 / (pow(roughness, 4) + 1e-2)) - 2, 0, 500.0f);
	// 新建漫反射Diffuse颜色, 即是它本身显示的纹理的颜色, 这里只是为了代码可读性
	vec3 diffuseColor = texture(DiffuseTextureSampler,vec2(UV.x,UV.y)).rgb;
	// 定义镜面反射Specular颜色
	vec3 specularColor = vec3(0.01, 0.01, 0.01);
	// 实现Blinn-Phong着色
	// 计算漫反射项
	float diff = clamp(dot(normalVector, lightDir_Camera), 0, 1);
    vec3 diffuse = diffuseColor * LightColor * LightPower * diff;
	// 计算镜面反射项
	// 半程向量
	vec3 halfwayDir = normalize(lightDir_Camera + viewDir_Camera);
    float spec = clamp(pow(clamp(dot(normalVector, halfwayDir), 0, 1), shininess),0 ,1);
    vec3 specular = specularColor * LightPower * (spec * diff * (shininess+2)/(2*radians(180.0f)));
	// 计算环境光
	//vec3 AmbientColor = vec3(0.1,0.1,0.1) * diffuseColor;
	// 计算最终颜色
	color = diffuse + specular;// + AmbientColor;
	/* -- Task3 --- END --- */


	/* -- Task4 -- START -- */
	/* -- Task4 --- END --- */
	

	/* -- Task5 -- START -- */
	/* -- Task5 --- END --- */


	/* -- Task6 -- START -- */
	/* -- Task6 --- END --- */
}