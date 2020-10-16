#version 150

uniform mat4 projectionMatrix;
uniform mat4 modelViewMatrix;
uniform mat4 modelViewProjectionMatrix;

uniform vec4 globalColor = vec4(1.0);
uniform int iCount;
//uniform vec4 lookAtPos vec4(0.0);

in vec4  position;
in vec2  texcoord;
in vec4  color_coord;
in vec3  normal;

out vec4 colorVarying;
out vec2 texCoordVarying;

void main() {
	const float PI = 3.1415926535897932384626433832795;
	float rho = 2;
	float theta = PI/6;
	float rad = theta * gl_InstanceID;

	for(int i = 0; i < gl_InstanceID; i++) {
		rad += theta;
		if(rad > 2 * PI) {
			rad -= 2 * PI;
			theta *= 0.5;
			rho += 0.75;
		}
	}

	float instanceX = rho * cos(rad);
	float instanceY = rho * sin(rad);

	colorVarying = globalColor;
	
	vec4 vPos = position;
	vPos = vPos + vec4(instanceX * 5 * iCount, 0, instanceY * 5 * iCount, 0);
	gl_Position = projectionMatrix * modelViewMatrix * vPos;

}
