#version 120

uniform vec2 mouse;

void main(){

	gl_TexCoord[0] = gl_MultiTexCoord0;
	
	//get our current vertex position so we can modify it
	vec4 pos = gl_ProjectionMatrix * gl_ModelViewMatrix * gl_Vertex;
	
	//lets also figure out the distance between the mouse and the vertex and apply a repelling force away from the mouse
    
    //modify our color
    vec4 col = gl_Color;
    
	vec2 d = vec2(pos.x, pos.y) - mouse;
	float len =  sqrt(d.x*d.x + d.y*d.y);
	if( len < 300 && len > 0  ){
		
		//lets get the distance into 0-1 ranges
		float pct = len / 300.0; 
		
		//this turns our linear 0-1 value into a curved 0-1 value
		pct *= pct;

		//flip it so the closer we are the greater the repulsion
		pct = 1.0 - pct;
		
		//normalize our repulsion vector
		d /= len;
		
		//apply the repulsion to our position
		//pos.x += d.x * pct * 90.0f;
		//pos.y += d.y * pct * 90.0f;
        
        
        col.a = 0.5f;
        
	}

	//modify our position with the smooth noise
	//pos.x += 20.0;
	//pos.y += 10.0;
	
	//finally set the pos to be that actual position rendered
	gl_Position = pos;


	
	gl_FrontColor =  col;	
}
