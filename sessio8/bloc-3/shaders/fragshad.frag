#version 330 core

in vec4 vertexSCO;
in vec3 normalSCO;


in vec3 fragmatamb;
in vec3 fragmatdiff;
in vec3 fragmatspec;
in float fragmatshin;

in vec3 fragcolFocus;

out vec4 FragColor;

vec3 llumAmbient = vec3(0.2, 0.2, 0.2);
vec3 posFocus = vec3(0, 0, 0);  // en SCA

vec3 Lambert (vec3 NormSCO, vec3 L) 
{
    // S'assumeix que els vectors que es reben com a paràmetres estan normalitzats

    // Inicialitzem color a component ambient
    vec3 colRes = llumAmbient * fragmatamb;

    // Afegim component difusa, si n'hi ha
    if (dot (L, NormSCO) > 0)
      colRes = colRes + fragcolFocus * fragmatdiff * dot (L, NormSCO);
    return (colRes);
}

vec3 Phong (vec3 NormSCO, vec3 L, vec4 vertSCO) 
{
    // Els vectors estan normalitzats

    // Inicialitzem color a Lambert
    vec3 colRes = Lambert (NormSCO, L);

    // Calculem R i V
    if (dot(NormSCO,L) < 0)
      return colRes;  // no hi ha component especular

    vec3 R = reflect(-L, NormSCO); // equival a: normalize (2.0*dot(NormSCO,L)*NormSCO - L);
    vec3 V = normalize(-vertexSCO.xyz);

    if ((dot(R, V) < 0) || (fragmatshin == 0))
      return colRes;  // no hi ha component especular
    
    // Afegim la component especular
    float shine = pow(max(0.0, dot(R, V)), fragmatshin);
    return (colRes + fragmatspec * fragcolFocus * shine); 
}

void main()
{
    vec3 L = normalize(posFocus.xyz - vertexSCO.xyz);
    vec3 fcolor = Phong(normalSCO,L ,vertexSCO);
    FragColor = vec4(fcolor,1);	
}
