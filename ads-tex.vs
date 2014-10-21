#version 150

in vec4 vPosition;
in vec4 vNormal;
in vec2 vTexCoord;

out vec3 color;
out vec2 texCoord;

uniform mat4 sunModel;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform vec3 lightPos;

uniform vec3 ambientLightIntensity;
uniform vec3 specLightIntensity;
uniform vec3 diffuseLightIntensity;
uniform float shine;

uniform vec3 Ka;  // Ambient reflectivity
uniform vec3 Kd;  // Diffuse reflectivity
uniform vec3 Ks;  // Specular reflectivity

void main()
{
	texCoord = vTexCoord; 
	
	mat4 mv = view * model;
	mat4 smv = view * sunModel;
	// The upper 3x3 of: view * model
	mat3 normMatrix = mat3( vec3(mv[0]), vec3(mv[1]), vec3(mv[2]) );
	
	// The position in eye coordinates
	vec3 p = (mv * vPosition).xyz;
	vec3 lp = (smv * vec4(lightPos.x,lightPos.y,lightPos.z,1)).xyz;
	
	// The normal in eye coordinates
	vec3 n = normalize( normMatrix * vec3(vNormal) );
	
	// The direction towards the light source (assuming that the light
	// is located at the camera position, which is the origin in eye 
	// coordinates.
	vec3 l = normalize(-p);
	
	// The direction of perfect reflection
	vec3 r = normalize( reflect( -l, n ) );
	
	// The direction towards the viewer
	vec3 v = normalize( lp-p );
	
	vec3 diffuse = Kd * diffuseLightIntensity * max( dot(l, n), 0 );
	vec3 spec = Ks * specLightIntensity * pow( max( dot(r,v), 0 ), shine );
	vec3 ambient = Ka * ambientLightIntensity;
		
	// The ADS lighting model
	color = ambient + diffuse + spec;
	
	gl_Position = projection * mv * vPosition;
}