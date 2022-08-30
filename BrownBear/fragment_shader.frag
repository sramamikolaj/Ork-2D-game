in vec4 vert_pos;

uniform sampler2D texture;
uniform bool hasTexture;
uniform vec2 light;

void main()
{
 vec4 ambient = vec4(0.15, 0.15, 0.15, 1);
 vec2 light_tmp =  (gl_ModelViewProjectionMatrix * vec4(light, 0, 1)).xy;
 vec2 lightToFrag = light_tmp - vert_pos.xy;
 lightToFrag.y = lightToFrag.y;
 float vecLength = clamp(length(lightToFrag) * 0.7, 0, 1);
 vec4 pixel = texture2D(texture, gl_TexCoord[0].xy);
 if(hasTexture == true)
 {
  gl_FragColor = gl_Color * pixel * (clamp(ambient + vec4(1-vecLength, 1-vecLength, 1-vecLength, 1), 0, 1));
 }
 else
 {
  gl_FragColor = gl_Color;
 }
}