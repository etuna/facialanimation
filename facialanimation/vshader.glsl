attribute  vec4 vPosition;
attribute  vec3 vNormal;
attribute  vec4 vColor;
attribute  vec2 vTexCoord;
varying vec4 color;

// output values that will be interpretated per-fragment
varying  vec3 fN;
varying  vec3 fV;
varying  vec3 fL;
varying float porg;
varying float material;

varying  vec3 fN2;
varying  vec3 fL2;
varying  vec3 fV2;

varying vec2 texCoord;


varying float mlights;


uniform vec4 AmbientProduct, DiffuseProduct, SpecularProduct;
uniform mat4 ModelView;
uniform mat4 Projection;
uniform vec4 LightPosition;
uniform vec4 Light2Position;
uniform float Shininess;
uniform float metal_plastic  = 1.0;
uniform float Shading =0.0 ;
varying float shading;
uniform float ph_go = 0.0;
uniform float lights = 1.0;
void main()
{
material = metal_plastic;

if(Shading == 0.0){
gl_Position = Projection * ModelView * vPosition;
color =vec4(1.0, 1.0, 1.0, 1.0);
porg = 1.0;
shading = 0.0;

}else if(Shading == 1.0){

shading = 1.0;
if(ph_go == 0.0){

if(lights == 0.0){

mlights = 0.0;
porg = 0.0;

   vec3 pos = ( vPosition).xyz;
    
    fN = (ModelView * vec4(vNormal, 0.0)).xyz; // normal direction in camera coordinates

    fV = -pos; //viewer direction in camera coordinates

    fL = LightPosition.xyz; // light direction

    if( LightPosition.w != 0.0 ) {
        fL = LightPosition.xyz - pos;  //directional light source
    }
    
    gl_Position = Projection * ModelView * vPosition;


}else if(lights == 1.0){//one light with phong

mlights = 1.0;
porg = 0.0;

   vec3 pos = ( vPosition).xyz;
    
    fN = (ModelView * vec4(vNormal, 0.0)).xyz; // normal direction in camera coordinates

    fV = -pos; //viewer direction in camera coordinates

    fL = LightPosition.xyz; // light direction

    if( LightPosition.w != 0.0 ) {
        fL = LightPosition.xyz - pos;  //directional light source
    }
    
    gl_Position = Projection * ModelView * vPosition;
	color = vColor;

} else { // two lights with phong

mlights = 2.0;
porg = 0.0;
	vec3 pos = ( vPosition).xyz;
    
    fN = (ModelView * vec4(vNormal, 0.0)).xyz; // normal direction in camera coordinates

    fV = -pos; //viewer direction in camera coordinates

    fL = LightPosition.xyz; // light direction







    if( LightPosition.w != 0.0 ) {
        fL = LightPosition.xyz - pos;  //directional light source
    }
    




	
    fN2 = (ModelView * vec4(vNormal, 0.0)).xyz; // normal direction in camera coordinates

    fV2 = -pos; //viewer direction in camera coordinates

    fL2 = Light2Position.xyz; // light direction







    if( Light2Position.w != 0.0 ) {
        fL2 = Light2Position.xyz - pos;  //directional light source
    }




    gl_Position = Projection * ModelView * vPosition;










}


} else {//-GOURAUD-------------------------------------------------------------------------------------------------------------------


if(lights == 0.0){

// Transform vertex position into camera (eye) coordinates
    vec3 pos = (vPosition).xyz;
	
    vec3 L = normalize( LightPosition.xyz - pos ); //light direction
    vec3 V = normalize( -pos ); // viewer direction
    vec3 H = normalize( L + V ); // halfway vector

    // Transform vertex normal into camera coordinates
    vec3 N = normalize( ModelView * vec4(vNormal, 0.0) ).xyz;

    // Compute terms in the illumination equation
    vec4 ambient = AmbientProduct;

    float Kd = max( dot(L, N), 0.0 ); //set diffuse to 0 if light is behind the surface point
    vec4  diffuse = Kd*DiffuseProduct;

    float Ks = pow( max(dot(N, H), 0.0), Shininess );
    vec4  specular = Ks*metal_plastic * SpecularProduct;
    
    //ignore also specular component if light is behind the surface point
    if( dot(L, N) < 0.0 ) {
        specular = vec4(0.0, 0.0, 0.0, 1.0);
    } 

    gl_Position = Projection * ModelView * vPosition;

    color = ambient;
    color.a = 1.0;
	porg = 1.0;


}
else if(lights == 1.0) // one light with gouraud
{

// Transform vertex position into camera (eye) coordinates
    vec3 pos = (vPosition).xyz;
	
    vec3 L = normalize( LightPosition.xyz - pos ); //light direction
    vec3 V = normalize( -pos ); // viewer direction
    vec3 H = normalize( L + V ); // halfway vector

    // Transform vertex normal into camera coordinates
    vec3 N = normalize( ModelView * vec4(vNormal, 0.0) ).xyz;

    // Compute terms in the illumination equation
    vec4 ambient = AmbientProduct;

    float Kd = max( dot(L, N), 0.0 ); //set diffuse to 0 if light is behind the surface point
    vec4  diffuse = Kd*DiffuseProduct;

    float Ks = pow( max(dot(N, H), 0.0), Shininess );
    vec4  specular = Ks*metal_plastic * SpecularProduct;
    
    //ignore also specular component if light is behind the surface point
    if( dot(L, N) < 0.0 ) {
        specular = vec4(0.0, 0.0, 0.0, 1.0);
    } 

    gl_Position = Projection * ModelView * vPosition;

    color = ambient + diffuse + specular;
    color.a = 1.0;
	porg = 1.0;






	} else { // two lights with gouraud
	
	// Transform vertex position into camera (eye) coordinates
    vec3 pos = (vPosition).xyz;
	
    vec3 L = normalize( LightPosition.xyz - pos ); //light direction
    vec3 V = normalize( -pos ); // viewer direction
    vec3 H = normalize( L + V ); // halfway vector

    // Transform vertex normal into camera coordinates
    vec3 N = normalize( ModelView * vec4(vNormal, 0.0) ).xyz;

    // Compute terms in the illumination equation
    vec4 ambient = AmbientProduct;

    float Kd = max( dot(L, N), 0.0 ); //set diffuse to 0 if light is behind the surface point
    vec4  diffuse = Kd*DiffuseProduct;

    float Ks = pow( max(dot(N, H), 0.0), Shininess );
    vec4  specular = Ks*metal_plastic * SpecularProduct;
    
    //ignore also specular component if light is behind the surface point
    if( dot(L, N) < 0.0 ) {
        specular = vec4(0.0, 0.0, 0.0, 1.0);
    } 

    gl_Position = Projection * ModelView * vPosition;

    color = ambient + diffuse + specular;
    color.a = 1.0;
	porg = 1.0;

	





	

	// Transform vertex position into camera (eye) coordinates
     pos = (vPosition).xyz;
	
    L = normalize( Light2Position.xyz - pos ); //light direction
     V = normalize( -pos ); // viewer direction
     H = normalize( L + V ); // halfway vector

    // Transform vertex normal into camera coordinates
     N = normalize( ModelView * vec4(vNormal, 0.0) ).xyz;

    // Compute terms in the illumination equation
    ambient = AmbientProduct;

    Kd = max( dot(L, N), 0.0 ); //set diffuse to 0 if light is behind the surface point
    diffuse += Kd*DiffuseProduct;

    Ks = pow( max(dot(N, H), 0.0), Shininess );
    specular += Ks*metal_plastic * SpecularProduct;
    
    //ignore also specular component if light is behind the surface point
    if( dot(L, N) < 0.0 ) {
       specular = vec4(0.0, 0.0, 0.0, 1.0);
    } 

    gl_Position = Projection * ModelView * vPosition;

    color = ambient + diffuse + specular;
    color.a = 1.0;
	porg = 1.0;










	
	}//two lights gouraud ends




}//gouraud ends

}//shading ends

else {//Texture

    texCoord    = vTexCoord;
    gl_Position = Projection * ModelView * vPosition;
	shading = 2.0;
	porg = 5.0;



}//texture ends
    
}//main ends
