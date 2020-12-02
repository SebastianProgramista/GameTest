#version 330                                                                                                                                                                                                        
                                                                                                                                                
in vec2 TexCoord0;                                                                  
                                                             
out vec4 FragColor;                                                                 
                                                                                                                                                                                                                     
uniform sampler2D gSampler;                                                                                                                                                                                                                                                                                                              
                                                                                                                                                                                                                                                                            
void main()                                                                                 
{      
	vec4 color = texture2D(gSampler, TexCoord0.xy);
	//if(color.a < 0.9)
	//discard;

	FragColor = color;
}