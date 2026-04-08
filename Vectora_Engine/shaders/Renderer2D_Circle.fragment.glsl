#version 330 core
			
layout(location = 0) out vec4 o_Color;
layout(location = 1) out int o_EntityID;

// Inputs from Vertex Shader
in vec3 v_LocalPosition;
in vec4 v_Color;
in float v_Thickness;
in float v_Fade;
flat in int v_EntityID;


void main()
{
	// Calculate distance (LocalPosition is -1.0 to 1.0)
    float dist = 1.0 - length(v_LocalPosition);
    
    // Antialiasing / Fade
    float circle = smoothstep(0.0, v_Fade, dist);
    
    // Inner thickness (for ring effect)
    circle *= smoothstep(v_Thickness + v_Fade, v_Thickness, dist);

    if (circle == 0.0)
        discard;

    o_Color = v_Color;
    o_Color.a *= circle;

    o_EntityID = v_EntityID;
}