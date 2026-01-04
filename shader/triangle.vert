
#version 450

void main() {
	const vec3 positions[3] = vec[3](
		vec3(1.f, 1.f, 0.0f),
		vec3(-1.f, 1.f, 0.0f),
		vec3(0.f, 11.f, 0.0f),
	);

	gl_Position = vec4(positions[gl_VectexIndex], 1.0f);
}
