/*    
    Copyright (c) 2020 Patryk Cieslak. All rights reserved.

    This file is a part of Stonefish.

    Stonefish is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Stonefish is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#version 330

layout(location = 0) in vec3 vt;
layout(location = 1) in vec3 n;
layout(location = 2) in vec2 uv;
layout(location = 3) in vec3 t;

out mat3 TBN;
out vec2 texCoord;
out vec3 fragPos;

uniform mat4 MVP;
uniform mat4 M;
uniform mat3 N;

void main()
{
	vec3 normal = normalize(N * n);
    vec3 tangent = normalize(N * t);
    vec3 bitangent = cross(normal, tangent);
    TBN = mat3(tangent, bitangent, normal);
	texCoord = uv;
	fragPos = (M * vec4(vt, 1.0)).xyz;
    gl_Position = MVP * vec4(vt, 1.0); 
}
