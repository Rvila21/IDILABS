#version 330 core

in vec3 vertex;
in vec3 normal;

in vec3 matamb;
in vec3 matdiff;
in vec3 matspec;
in float matshin;

uniform mat4 proj;
uniform mat4 view;
uniform mat4 TG;

// Valors per als components que necessitem dels focus de llum
uniform vec3 colFocus;// = vec3(0.8, 0.8, 0.8);


out vec3 fragcolFocus;

out vec4 vertexSCO;
out vec3 normalSCO;

out vec3 fragmatamb;
out vec3 fragmatdiff;
out vec3 fragmatspec;
out float fragmatshin;


void main()
{	
   /* mat3 NormalMatrix = inverse(transpose(mat3(view * TG)));
    vec3 NormSCO = normalize(NormalMatrix * normal);
    vec4 VertexSCO = view * TG * vec4(vertex,1.0);
    vec4  FocusSCO = view * vec4(posFocus,1.0);
    vec3 L = normalize(FocusSCO.xyz - VertexSCO.xyz);
    vec4 vertexSCO = view * vec4(vertex,1.0);
    fcolor = Phong(NormSCO,L,vertexSCO);
    gl_Position = proj * view * TG * vec4 (vertex, 1.0);*/
    
    mat3 NormalMatrix = inverse(transpose(mat3(view * TG)));
    normalSCO = normalize(NormalMatrix * normal);
    vertexSCO =view * TG * vec4(vertex,1.0);
    fragcolFocus = colFocus;
  
 
    gl_Position = proj * view * TG * vec4 (vertex, 1.0);
    
    
    fragmatamb = matamb;
    fragmatdiff = matdiff;
    fragmatspec = matspec;
    fragmatshin = matshin;
}
