xof 0302txt 0064
template Header {
 <3D82AB43-62DA-11cf-AB39-0020AF71E433>
 WORD major;
 WORD minor;
 DWORD flags;
}

template Vector {
 <3D82AB5E-62DA-11cf-AB39-0020AF71E433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template Coords2d {
 <F6F23F44-7686-11cf-8F52-0040333594A3>
 FLOAT u;
 FLOAT v;
}

template Matrix4x4 {
 <F6F23F45-7686-11cf-8F52-0040333594A3>
 array FLOAT matrix[16];
}

template ColorRGBA {
 <35FF44E0-6C7C-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <D3E16E81-7835-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template IndexedColor {
 <1630B820-7842-11cf-8F52-0040333594A3>
 DWORD index;
 ColorRGBA indexColor;
}

template Boolean {
 <4885AE61-78E8-11cf-8F52-0040333594A3>
 WORD truefalse;
}

template Boolean2d {
 <4885AE63-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template MaterialWrap {
 <4885AE60-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template TextureFilename {
 <A42790E1-7810-11cf-8F52-0040333594A3>
 STRING filename;
}

template Material {
 <3D82AB4D-62DA-11cf-AB39-0020AF71E433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template MeshFace {
 <3D82AB5F-62DA-11cf-AB39-0020AF71E433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template MeshFaceWraps {
 <4885AE62-78E8-11cf-8F52-0040333594A3>
 DWORD nFaceWrapValues;
 Boolean2d faceWrapValues;
}

template MeshTextureCoords {
 <F6F23F40-7686-11cf-8F52-0040333594A3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}

template MeshMaterialList {
 <F6F23F42-7686-11cf-8F52-0040333594A3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material]
}

template MeshNormals {
 <F6F23F43-7686-11cf-8F52-0040333594A3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template MeshVertexColors {
 <1630B821-7842-11cf-8F52-0040333594A3>
 DWORD nVertexColors;
 array IndexedColor vertexColors[nVertexColors];
}

template Mesh {
 <3D82AB44-62DA-11cf-AB39-0020AF71E433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

Header{
1;
0;
1;
}

Mesh {
 304;
 78.70504;7.89094;-8.83445;,
 66.01727;7.89094;-8.83445;,
 66.01727;9.48767;-5.87715;,
 78.70505;9.48767;-5.87715;,
 53.32965;7.89093;-8.83445;,
 53.32965;9.48767;-5.87715;,
 40.64198;7.89094;-8.83445;,
 40.64198;9.48767;-5.87715;,
 27.18551;8.37730;-10.31788;,
 27.18551;11.73449;-6.86612;,
 18.05651;8.37730;-10.31786;,
 18.05651;11.73448;-6.86612;,
 8.92755;8.37730;-10.31788;,
 8.92755;11.73449;-6.86611;,
 66.01729;9.48767;-2.91987;,
 78.70505;9.48767;-2.91988;,
 53.32964;9.48767;-2.91987;,
 40.64198;9.48767;-2.91988;,
 27.18551;13.21870;-3.41436;,
 18.05651;13.21870;-3.41436;,
 8.92755;13.21872;-3.41435;,
 66.01727;9.48767;0.03741;,
 78.70505;9.48767;0.03741;,
 53.32965;9.48767;0.03741;,
 40.64198;9.48767;0.03741;,
 27.18551;13.82272;0.03741;,
 18.05651;13.82271;0.03741;,
 8.92754;13.82272;0.03741;,
 66.01727;9.48767;2.99470;,
 78.70505;9.48767;2.99470;,
 53.32964;9.48767;2.99470;,
 40.64198;9.48767;2.99470;,
 27.18551;13.21872;3.48918;,
 18.05651;13.21872;3.48918;,
 8.92755;13.21872;3.48918;,
 66.01727;9.48767;5.95197;,
 78.70505;9.48767;5.95197;,
 53.32965;9.48767;5.95197;,
 40.64198;9.48767;5.95197;,
 27.18551;11.73449;6.94093;,
 18.05651;11.73449;6.94093;,
 8.92755;11.73449;6.94093;,
 66.01727;7.89094;8.90926;,
 78.70504;7.89094;8.90926;,
 53.32964;7.89094;8.90926;,
 40.64198;7.89094;8.90926;,
 27.18551;8.37730;10.39270;,
 18.05651;8.37730;10.39269;,
 8.92755;8.37730;10.39269;,
 8.92755;8.37730;-10.31788;,
 8.92755;5.60568;-11.81055;,
 4.54069;7.84381;-7.86127;,
 8.92755;11.73449;-6.86611;,
 8.92755;2.83407;-12.79479;,
 4.54069;3.95313;-8.51742;,
 8.92755;0.06244;-12.98825;,
 4.54069;0.06245;-8.64637;,
 8.92755;-2.70917;-12.79479;,
 4.54069;-3.82823;-8.51742;,
 8.92755;-5.48081;-11.81057;,
 4.54069;-7.71893;-7.86127;,
 8.92755;-8.25242;-10.31787;,
 8.92755;-11.60959;-6.86611;,
 4.54069;8.83328;-3.91193;,
 8.92755;13.21872;-3.41435;,
 1.22968;4.44787;-4.23999;,
 1.22970;0.06244;-4.30446;,
 1.22968;-4.32297;-4.23999;,
 4.54069;-8.70840;-3.91193;,
 8.92755;-13.09382;-3.41435;,
 4.54069;9.23598;0.03741;,
 8.92754;13.82272;0.03741;,
 1.22967;4.64920;0.03741;,
 -0.07682;0.06244;0.03741;,
 1.22968;-4.52431;0.03741;,
 4.54069;-9.11109;0.03741;,
 8.92755;-13.69782;0.03740;,
 4.54069;8.83328;3.98675;,
 8.92755;13.21872;3.48918;,
 1.22970;4.44786;4.31484;,
 1.22967;0.06245;4.37931;,
 1.22968;-4.32297;4.31484;,
 4.54069;-8.70840;3.98675;,
 8.92755;-13.09382;3.48919;,
 4.54069;7.84381;7.93609;,
 8.92755;11.73449;6.94093;,
 4.54069;3.95313;8.59223;,
 4.54069;0.06244;8.72120;,
 4.54069;-3.82825;8.59223;,
 4.54069;-7.71893;7.93609;,
 8.92755;-11.60959;6.94093;,
 8.92755;5.60568;11.88541;,
 8.92755;8.37730;10.39269;,
 8.92755;2.83407;12.86965;,
 8.92755;0.06244;13.06310;,
 8.92755;-2.70919;12.86965;,
 8.92755;-5.48079;11.88541;,
 8.92755;-8.25243;10.39270;,
 8.92755;-8.25242;-10.31787;,
 18.05651;-8.25241;-10.31786;,
 18.05651;-11.60959;-6.86612;,
 8.92755;-11.60959;-6.86611;,
 27.18551;-8.25241;-10.31786;,
 27.18551;-11.60959;-6.86612;,
 40.64198;-0.01843;-8.83444;,
 40.64198;-1.61517;-5.87715;,
 53.32965;-0.01844;-8.83444;,
 53.32965;-1.61517;-5.87715;,
 66.01729;-0.01844;-8.83444;,
 66.01727;-1.61517;-5.87715;,
 78.70505;-0.01845;-8.83445;,
 78.70505;-1.61517;-5.87715;,
 18.05651;-13.09381;-3.41435;,
 8.92755;-13.09382;-3.41435;,
 27.18551;-13.09382;-3.41436;,
 40.64198;-1.61517;-2.91988;,
 53.32965;-1.61517;-2.91988;,
 66.01727;-1.61517;-2.91987;,
 78.70505;-1.61517;-2.91988;,
 18.05651;-13.69782;0.03740;,
 8.92755;-13.69782;0.03740;,
 27.18551;-13.69782;0.03740;,
 40.64198;-1.61517;0.03741;,
 53.32964;-1.61517;0.03742;,
 66.01727;-1.61517;0.03741;,
 78.70505;-1.61517;0.03742;,
 18.05651;-13.09381;3.48919;,
 8.92755;-13.09382;3.48919;,
 27.18551;-13.09382;3.48919;,
 40.64198;-1.61517;2.99469;,
 53.32965;-1.61517;2.99469;,
 66.01727;-1.61517;2.99469;,
 78.70505;-1.61517;2.99469;,
 18.05651;-11.60959;6.94093;,
 8.92755;-11.60959;6.94093;,
 27.18551;-11.60959;6.94093;,
 40.64198;-1.61517;5.95197;,
 53.32965;-1.61517;5.95197;,
 66.01727;-1.61517;5.95197;,
 78.70505;-1.61517;5.95197;,
 18.05651;-8.25243;10.39269;,
 8.92755;-8.25243;10.39270;,
 27.18551;-8.25243;10.39269;,
 40.64198;-0.01843;8.90926;,
 53.32964;-0.01844;8.90926;,
 66.01729;-0.01844;8.90926;,
 78.70505;-0.01845;8.90926;,
 78.70505;-0.01845;-8.83445;,
 78.70505;1.29980;-8.83445;,
 78.70505;1.16497;-6.53025;,
 78.70505;-1.61517;-5.87715;,
 78.70505;2.61802;-8.83445;,
 78.70505;2.55061;-6.53025;,
 78.70504;3.93626;-8.83445;,
 78.70504;3.93626;-6.53025;,
 78.70505;5.25448;-8.83445;,
 78.70504;5.32190;-6.53025;,
 78.70505;6.57272;-8.83445;,
 78.70504;6.70754;-6.53025;,
 78.70504;7.89094;-8.83445;,
 78.70505;9.48767;-5.87715;,
 78.70505;1.16497;-3.24642;,
 78.70505;-1.61517;-2.91988;,
 78.70505;9.48767;-2.91988;,
 78.70504;6.70754;-3.24642;,
 78.70505;1.16497;0.03741;,
 78.70505;-1.61517;0.03742;,
 78.70505;9.48767;0.03741;,
 78.70504;6.70754;0.03741;,
 78.70505;1.16497;3.32125;,
 78.70505;-1.61517;2.99469;,
 78.70505;9.48767;2.99470;,
 78.70504;6.70754;3.32125;,
 78.70505;1.16497;6.60506;,
 78.70505;-1.61517;5.95197;,
 78.70505;9.48767;5.95197;,
 78.70504;6.70754;6.60508;,
 78.70505;1.29978;8.90926;,
 78.70505;-0.01845;8.90926;,
 78.70505;2.55061;6.60506;,
 78.70505;2.61802;8.90926;,
 78.70504;3.93626;6.60508;,
 78.70504;3.93626;8.90926;,
 78.70504;5.32190;6.60506;,
 78.70505;5.25448;8.90926;,
 78.70505;6.57272;8.90926;,
 78.70504;7.89094;8.90926;,
 66.01729;-0.01844;-8.83444;,
 66.01729;1.29980;-8.83443;,
 78.70505;1.29980;-8.83445;,
 53.32965;-0.01844;-8.83444;,
 53.32965;1.29980;-8.83443;,
 40.64198;1.29980;-8.83443;,
 27.18551;-8.25241;-10.31786;,
 27.18551;-5.48080;-11.81058;,
 18.05651;-8.25241;-10.31786;,
 18.05651;-5.48080;-11.81057;,
 8.92755;-5.48081;-11.81057;,
 66.01727;2.61802;-8.83444;,
 78.70505;2.61802;-8.83445;,
 53.32965;2.61803;-8.83444;,
 40.64198;2.61802;-8.83444;,
 27.18551;-2.70917;-12.79479;,
 18.05651;-2.70917;-12.79479;,
 8.92755;-2.70917;-12.79479;,
 66.01727;3.93625;-8.83444;,
 78.70504;3.93626;-8.83445;,
 53.32965;3.93625;-8.83444;,
 40.64198;3.93625;-8.83444;,
 27.18551;0.06244;-12.98825;,
 18.05651;0.06244;-12.98825;,
 8.92755;0.06244;-12.98825;,
 66.01727;5.25448;-8.83444;,
 78.70505;5.25448;-8.83445;,
 53.32965;5.25448;-8.83444;,
 40.64198;5.25448;-8.83444;,
 27.18551;2.83407;-12.79479;,
 18.05651;2.83407;-12.79479;,
 8.92755;2.83407;-12.79479;,
 66.01727;6.57271;-8.83445;,
 78.70505;6.57272;-8.83445;,
 53.32965;6.57271;-8.83445;,
 40.64198;6.57271;-8.83445;,
 27.18551;5.60569;-11.81056;,
 18.05651;5.60568;-11.81055;,
 8.92755;5.60568;-11.81055;,
 66.01727;7.89094;-8.83445;,
 78.70504;7.89094;-8.83445;,
 53.32965;7.89093;-8.83445;,
 40.64198;7.89094;-8.83445;,
 27.18551;8.37730;-10.31788;,
 18.05651;8.37730;-10.31786;,
 8.92755;8.37730;-10.31788;,
 78.70505;1.29978;8.90926;,
 66.01729;1.29979;8.90926;,
 66.01729;-0.01844;8.90926;,
 53.32964;1.29980;8.90926;,
 53.32964;-0.01844;8.90926;,
 40.64197;1.29979;8.90926;,
 27.18551;-5.48079;11.88541;,
 27.18551;-8.25243;10.39269;,
 18.05651;-5.48079;11.88541;,
 18.05651;-8.25243;10.39269;,
 8.92755;-5.48079;11.88541;,
 78.70505;2.61802;8.90926;,
 66.01727;2.61802;8.90926;,
 53.32965;2.61803;8.90925;,
 40.64198;2.61802;8.90926;,
 27.18551;-2.70919;12.86965;,
 18.05651;-2.70917;12.86964;,
 8.92755;-2.70919;12.86965;,
 78.70504;3.93626;8.90926;,
 66.01727;3.93625;8.90926;,
 53.32965;3.93625;8.90926;,
 40.64198;3.93625;8.90926;,
 27.18551;0.06244;13.06310;,
 18.05651;0.06244;13.06310;,
 8.92755;0.06244;13.06310;,
 78.70505;5.25448;8.90926;,
 66.01727;5.25448;8.90926;,
 53.32964;5.25448;8.90926;,
 40.64198;5.25448;8.90926;,
 27.18551;2.83406;12.86965;,
 18.05651;2.83407;12.86964;,
 8.92755;2.83407;12.86965;,
 78.70505;6.57272;8.90926;,
 66.01727;6.57271;8.90926;,
 53.32965;6.57271;8.90926;,
 40.64198;6.57271;8.90926;,
 27.18550;5.60569;11.88541;,
 18.05651;5.60568;11.88541;,
 8.92755;5.60568;11.88541;,
 78.70504;7.89094;8.90926;,
 66.01727;7.89094;8.90926;,
 53.32964;7.89094;8.90926;,
 40.64198;7.89094;8.90926;,
 27.18551;8.37730;10.39270;,
 18.05651;8.37730;10.39269;,
 8.92755;8.37730;10.39269;,
 71.04804;2.55061;-6.53025;,
 71.04802;1.16497;-6.53025;,
 71.04802;1.16497;-3.24642;,
 71.04804;2.55061;-3.24642;,
 71.04802;3.93625;-6.53025;,
 71.04802;3.93625;-3.24642;,
 71.04804;5.32189;-6.53025;,
 71.04804;5.32189;-3.24642;,
 71.04804;6.70753;-6.53025;,
 71.04804;6.70753;-3.24642;,
 71.04802;1.16497;0.03741;,
 71.04804;2.55061;0.03741;,
 71.04802;3.93625;0.03741;,
 71.04804;5.32189;0.03741;,
 71.04804;6.70753;0.03741;,
 71.04802;1.16497;3.32124;,
 71.04804;2.55060;3.32124;,
 71.04802;3.93625;3.32125;,
 71.04804;5.32189;3.32124;,
 71.04804;6.70753;3.32125;,
 71.04802;1.16497;6.60506;,
 71.04804;2.55061;6.60506;,
 71.04802;3.93625;6.60508;,
 71.04804;5.32189;6.60506;,
 71.04804;6.70754;6.60508;;
 
 232;
 4;0,1,2,3;,
 4;1,4,5,2;,
 4;4,6,7,5;,
 4;6,8,9,7;,
 4;8,10,11,9;,
 4;10,12,13,11;,
 4;3,2,14,15;,
 4;2,5,16,14;,
 4;5,7,17,16;,
 4;7,9,18,17;,
 4;9,11,19,18;,
 4;11,13,20,19;,
 4;15,14,21,22;,
 4;14,16,23,21;,
 4;16,17,24,23;,
 4;17,18,25,24;,
 4;18,19,26,25;,
 4;19,20,27,26;,
 4;22,21,28,29;,
 4;21,23,30,28;,
 4;23,24,31,30;,
 4;24,25,32,31;,
 4;25,26,33,32;,
 4;26,27,34,33;,
 4;29,28,35,36;,
 4;28,30,37,35;,
 4;30,31,38,37;,
 4;31,32,39,38;,
 4;32,33,40,39;,
 4;33,34,41,40;,
 4;36,35,42,43;,
 4;35,37,44,42;,
 4;37,38,45,44;,
 4;38,39,46,45;,
 4;39,40,47,46;,
 4;40,41,48,47;,
 4;49,50,51,52;,
 4;50,53,54,51;,
 4;53,55,56,54;,
 4;55,57,58,56;,
 4;57,59,60,58;,
 4;59,61,62,60;,
 4;52,51,63,64;,
 4;51,54,65,63;,
 4;54,56,66,65;,
 4;56,58,67,66;,
 4;58,60,68,67;,
 4;60,62,69,68;,
 4;64,63,70,71;,
 4;63,65,72,70;,
 4;65,66,73,72;,
 4;66,67,74,73;,
 4;67,68,75,74;,
 4;68,69,76,75;,
 4;71,70,77,78;,
 4;70,72,79,77;,
 4;72,73,80,79;,
 4;73,74,81,80;,
 4;74,75,82,81;,
 4;75,76,83,82;,
 4;78,77,84,85;,
 4;77,79,86,84;,
 4;79,80,87,86;,
 4;80,81,88,87;,
 4;81,82,89,88;,
 4;82,83,90,89;,
 4;85,84,91,92;,
 4;84,86,93,91;,
 4;86,87,94,93;,
 4;87,88,95,94;,
 4;88,89,96,95;,
 4;89,90,97,96;,
 4;98,99,100,101;,
 4;99,102,103,100;,
 4;102,104,105,103;,
 4;104,106,107,105;,
 4;106,108,109,107;,
 4;108,110,111,109;,
 4;101,100,112,113;,
 4;100,103,114,112;,
 4;103,105,115,114;,
 4;105,107,116,115;,
 4;107,109,117,116;,
 4;109,111,118,117;,
 4;113,112,119,120;,
 4;112,114,121,119;,
 4;114,115,122,121;,
 4;115,116,123,122;,
 4;116,117,124,123;,
 4;117,118,125,124;,
 4;120,119,126,127;,
 4;119,121,128,126;,
 4;121,122,129,128;,
 4;122,123,130,129;,
 4;123,124,131,130;,
 4;124,125,132,131;,
 4;127,126,133,134;,
 4;126,128,135,133;,
 4;128,129,136,135;,
 4;129,130,137,136;,
 4;130,131,138,137;,
 4;131,132,139,138;,
 4;134,133,140,141;,
 4;133,135,142,140;,
 4;135,136,143,142;,
 4;136,137,144,143;,
 4;137,138,145,144;,
 4;138,139,146,145;,
 4;147,148,149,150;,
 4;148,151,152,149;,
 4;151,153,154,152;,
 4;153,155,156,154;,
 4;155,157,158,156;,
 4;157,159,160,158;,
 4;150,149,161,162;,
 4;158,160,163,164;,
 4;162,161,165,166;,
 4;164,163,167,168;,
 4;166,165,169,170;,
 4;168,167,171,172;,
 4;170,169,173,174;,
 4;172,171,175,176;,
 4;174,173,177,178;,
 4;173,179,180,177;,
 4;179,181,182,180;,
 4;181,183,184,182;,
 4;183,176,185,184;,
 4;176,175,186,185;,
 4;147,187,188,189;,
 4;187,190,191,188;,
 4;190,104,192,191;,
 4;104,193,194,192;,
 4;193,195,196,194;,
 4;195,61,197,196;,
 4;189,188,198,199;,
 4;188,191,200,198;,
 4;191,192,201,200;,
 4;192,194,202,201;,
 4;194,196,203,202;,
 4;196,197,204,203;,
 4;199,198,205,206;,
 4;198,200,207,205;,
 4;200,201,208,207;,
 4;201,202,209,208;,
 4;202,203,210,209;,
 4;203,204,211,210;,
 4;206,205,212,213;,
 4;205,207,214,212;,
 4;207,208,215,214;,
 4;208,209,216,215;,
 4;209,210,217,216;,
 4;210,211,218,217;,
 4;213,212,219,220;,
 4;212,214,221,219;,
 4;214,215,222,221;,
 4;215,216,223,222;,
 4;216,217,224,223;,
 4;217,218,225,224;,
 4;220,219,226,227;,
 4;219,221,228,226;,
 4;221,222,229,228;,
 4;222,223,230,229;,
 4;223,224,231,230;,
 4;224,225,232,231;,
 4;233,234,235,178;,
 4;234,236,237,235;,
 4;236,238,143,237;,
 4;238,239,240,143;,
 4;239,241,242,240;,
 4;241,243,97,242;,
 4;244,245,234,233;,
 4;245,246,236,234;,
 4;246,247,238,236;,
 4;247,248,239,238;,
 4;248,249,241,239;,
 4;249,250,243,241;,
 4;251,252,245,244;,
 4;252,253,246,245;,
 4;253,254,247,246;,
 4;254,255,248,247;,
 4;255,256,249,248;,
 4;256,257,250,249;,
 4;258,259,252,251;,
 4;259,260,253,252;,
 4;260,261,254,253;,
 4;261,262,255,254;,
 4;262,263,256,255;,
 4;263,264,257,256;,
 4;265,266,259,258;,
 4;266,267,260,259;,
 4;267,268,261,260;,
 4;268,269,262,261;,
 4;269,270,263,262;,
 4;270,271,264,263;,
 4;272,273,266,265;,
 4;273,274,267,266;,
 4;274,275,268,267;,
 4;275,276,269,268;,
 4;276,277,270,269;,
 4;277,278,271,270;,
 4;279,280,149,152;,
 4;280,281,161,149;,
 4;280,279,282,281;,
 4;283,279,152,154;,
 4;279,283,284,282;,
 4;285,283,154,156;,
 4;283,285,286,284;,
 4;287,285,156,158;,
 4;288,287,158,164;,
 4;285,287,288,286;,
 4;281,289,165,161;,
 4;281,282,290,289;,
 4;282,284,291,290;,
 4;284,286,292,291;,
 4;293,288,164,168;,
 4;286,288,293,292;,
 4;289,294,169,165;,
 4;289,290,295,294;,
 4;290,291,296,295;,
 4;291,292,297,296;,
 4;298,293,168,172;,
 4;292,293,298,297;,
 4;299,300,179,173;,
 4;294,299,173,169;,
 4;294,295,300,299;,
 4;300,301,181,179;,
 4;295,296,301,300;,
 4;301,302,183,181;,
 4;296,297,302,301;,
 4;303,298,172,176;,
 4;302,303,176,183;,
 4;297,298,303,302;;
 
 MeshMaterialList {
  5;
  232;
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1;;
  Material {
   0.000000;0.800000;0.006400;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data/TEXTURE/���b.png";
   }
  }
  Material {
   0.160000;0.160000;0.160000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data/TEXTURE/���b.png";
   }
  }
  Material {
   0.780800;0.800000;0.000000;0.700000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   1.000000;1.000000;1.000000;1.000000;;
   0.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  218;
  -0.000000;0.879931;-0.475101;,
  -0.000000;0.879931;-0.475102;,
  -0.000000;0.879931;-0.475102;,
  0.078051;0.534368;-0.841641;,
  0.072814;0.579346;-0.811823;,
  -0.000000;0.602518;-0.798105;,
  -0.000000;0.969518;-0.245018;,
  -0.000000;0.969518;-0.245019;,
  0.000000;0.969518;-0.245019;,
  0.095835;0.940386;-0.326329;,
  0.095132;0.870653;-0.482611;,
  0.000000;0.831608;-0.555364;,
  -0.000000;1.000000;0.000000;,
  -0.000000;1.000000;0.000000;,
  0.000000;1.000000;-0.000000;,
  0.130038;0.988959;-0.071063;,
  0.130468;0.967781;-0.215358;,
  0.000000;0.958341;-0.285627;,
  -0.000000;1.000000;-0.000001;,
  -0.000000;1.000000;-0.000001;,
  0.000000;1.000000;-0.000001;,
  0.144702;0.989475;-0.000001;,
  0.145795;0.989315;-0.000002;,
  0.000000;1.000000;-0.000002;,
  0.000000;1.000000;0.000000;,
  0.130038;0.988959;0.071063;,
  0.130468;0.967780;0.215358;,
  0.000000;0.958341;0.285627;,
  -0.000000;0.969518;0.245020;,
  -0.000000;0.969518;0.245020;,
  0.000000;0.969518;0.245020;,
  0.095835;0.940385;0.326330;,
  0.095132;0.870652;0.482613;,
  -0.000000;0.831607;0.555365;,
  -0.000000;0.879931;0.475102;,
  -0.000000;0.879931;0.475102;,
  0.000000;0.879930;0.475103;,
  0.078051;0.534368;0.841641;,
  0.072815;0.579349;0.811821;,
  -0.000000;0.602522;0.798102;,
  -0.158951;0.595415;-0.787538;,
  -0.289623;0.406757;-0.866410;,
  -0.359487;0.171140;-0.917322;,
  -0.377894;-0.000000;-0.925849;,
  -0.359487;-0.171136;-0.917323;,
  -0.289624;-0.406757;-0.866410;,
  -0.297580;0.780189;-0.550229;,
  -0.677514;0.482463;-0.555161;,
  -0.756553;0.158825;-0.634352;,
  -0.747851;-0.000000;-0.663866;,
  -0.756554;-0.158823;-0.634351;,
  -0.677514;-0.482463;-0.555161;,
  -0.365320;0.898070;-0.244973;,
  -0.764359;0.612122;-0.202638;,
  -0.899245;0.297379;-0.320817;,
  -0.918377;-0.000000;-0.395706;,
  -0.899246;-0.297378;-0.320817;,
  -0.764358;-0.612123;-0.202638;,
  -0.388442;0.921473;-0.000001;,
  -0.760361;0.649500;0.000000;,
  -0.924241;0.381810;-0.000000;,
  -1.000000;-0.000000;-0.000002;,
  -0.924241;-0.381810;-0.000001;,
  -0.760361;-0.649501;-0.000000;,
  -0.365321;0.898070;0.244973;,
  -0.764359;0.612121;0.202639;,
  -0.899244;0.297381;0.320818;,
  -0.918377;0.000000;0.395707;,
  -0.899245;-0.297380;0.320818;,
  -0.764358;-0.612123;0.202639;,
  -0.297580;0.780189;0.550228;,
  -0.677515;0.482463;0.555160;,
  -0.756553;0.158825;0.634351;,
  -0.747850;0.000000;0.663867;,
  -0.756553;-0.158825;0.634352;,
  -0.677515;-0.482464;0.555160;,
  -0.158950;0.595419;0.787534;,
  -0.289625;0.406760;0.866409;,
  -0.359489;0.171138;0.917322;,
  -0.377895;-0.000000;0.925848;,
  -0.359489;-0.171139;0.917322;,
  -0.289625;-0.406759;0.866409;,
  -0.158950;-0.595419;-0.787535;,
  0.000000;-0.602521;-0.798103;,
  0.214329;-0.560603;-0.799867;,
  0.229594;-0.512083;-0.827682;,
  -0.000000;-0.879930;-0.475103;,
  -0.000000;-0.879931;-0.475102;,
  -0.297579;-0.780190;-0.550227;,
  -0.000000;-0.831608;-0.555363;,
  0.301834;-0.829257;-0.470349;,
  0.304176;-0.901591;-0.307589;,
  -0.000000;-0.969518;-0.245020;,
  -0.000000;-0.969518;-0.245020;,
  -0.365319;-0.898070;-0.244972;,
  -0.000000;-0.958341;-0.285626;,
  0.341078;-0.916074;-0.210888;,
  0.339912;-0.938609;-0.058932;,
  0.000000;-1.000000;-0.000000;,
  -0.388440;-0.921474;-0.000001;,
  -0.000000;-1.000000;-0.000001;,
  0.354040;-0.935230;-0.000001;,
  0.351389;-0.936229;-0.000000;,
  -0.365319;-0.898070;0.244973;,
  0.000000;-0.958341;0.285627;,
  0.341078;-0.916074;0.210888;,
  0.339912;-0.938609;0.058932;,
  -0.297579;-0.780190;0.550227;,
  0.000000;-0.831608;0.555363;,
  0.301834;-0.829258;0.470348;,
  0.304176;-0.901591;0.307589;,
  -0.000000;-0.969518;0.245020;,
  -0.000000;-0.969518;0.245020;,
  -0.158951;-0.595419;0.787534;,
  0.000000;-0.602522;0.798102;,
  0.214330;-0.560604;0.799866;,
  0.229595;-0.512086;0.827680;,
  -0.000000;-0.879930;0.475103;,
  -0.000000;-0.879931;0.475102;,
  -0.000000;-0.879931;-0.475101;,
  1.000000;0.000000;0.000000;,
  1.000000;0.000005;0.000000;,
  1.000000;0.000002;0.000001;,
  1.000000;-0.000002;0.000004;,
  1.000000;0.000001;0.000003;,
  -0.000000;-0.969518;-0.245019;,
  1.000000;-0.000001;0.000002;,
  1.000000;-0.000004;-0.000000;,
  1.000000;-0.000004;-0.000000;,
  1.000000;-0.000004;0.000000;,
  -0.000000;-0.969518;0.245019;,
  1.000000;0.000005;-0.000000;,
  1.000000;0.000002;-0.000001;,
  1.000000;-0.000002;-0.000004;,
  1.000000;-0.000001;-0.000002;,
  -0.000000;-0.879931;0.475102;,
  1.000000;0.000001;-0.000003;,
  -0.000001;-0.000000;-1.000000;,
  0.000000;-0.000000;-1.000000;,
  0.157702;-0.098450;-0.982567;,
  0.157994;-0.304875;-0.939196;,
  -0.000000;-0.405586;-0.914057;,
  -0.000001;-0.000003;-1.000000;,
  -0.000000;-0.000003;-1.000000;,
  0.157969;-0.048699;-0.986242;,
  0.158711;-0.151993;-0.975556;,
  -0.000000;-0.204009;-0.978969;,
  -0.000000;0.000000;-1.000000;,
  0.000000;0.000000;-1.000000;,
  0.146679;0.000078;-0.989184;,
  0.146857;0.000078;-0.989158;,
  0.000000;-0.000000;-1.000000;,
  -0.000000;-0.000003;-1.000000;,
  -0.000000;-0.000004;-1.000000;,
  0.125507;0.050348;-0.990814;,
  0.126083;0.153195;-0.980120;,
  -0.000000;0.204013;-0.978968;,
  -0.000000;-0.000003;-1.000000;,
  0.089742;0.102824;-0.990643;,
  0.089873;0.307546;-0.947280;,
  -0.000000;0.405587;-0.914057;,
  -0.000000;0.000001;1.000000;,
  -0.000000;0.000002;1.000000;,
  0.157703;-0.098450;0.982567;,
  0.157994;-0.304878;0.939195;,
  0.000000;-0.405590;0.914055;,
  -0.000000;-0.000000;1.000000;,
  -0.000000;-0.000000;1.000000;,
  0.157971;-0.048698;0.986242;,
  0.158712;-0.151995;0.975555;,
  0.000000;-0.204012;0.978968;,
  -0.000000;-0.000001;1.000000;,
  -0.000000;-0.000002;1.000000;,
  0.146680;0.000077;0.989184;,
  0.146858;0.000078;0.989158;,
  0.000000;-0.000000;1.000000;,
  0.000000;0.000000;1.000000;,
  0.125507;0.050351;0.990814;,
  0.126084;0.153195;0.980119;,
  0.000000;0.204011;0.978968;,
  0.089742;0.102828;0.990643;,
  0.089874;0.307550;0.947278;,
  0.000000;0.405591;0.914055;,
  1.000000;-0.000000;-0.000000;,
  1.000000;-0.000000;-0.000000;,
  1.000000;-0.000004;-0.000000;,
  0.000001;-1.000000;-0.000000;,
  1.000000;-0.000000;-0.000000;,
  1.000000;-0.000000;0.000000;,
  1.000000;-0.000000;-0.000000;,
  1.000000;-0.000000;-0.000000;,
  0.000001;-1.000000;0.000001;,
  -0.000000;0.000004;-1.000000;,
  0.000000;-0.000000;-1.000000;,
  0.000000;-0.000000;-1.000000;,
  0.000000;-1.000000;0.000003;,
  1.000000;0.000003;0.000001;,
  1.000000;-0.000001;0.000001;,
  1.000000;-0.000001;-0.000001;,
  1.000000;0.000003;-0.000001;,
  -0.000001;0.000003;-1.000000;,
  -0.000001;0.000005;-1.000000;,
  -0.000001;-0.000000;-1.000000;,
  0.000000;0.000007;-1.000000;,
  -0.000001;-0.000002;-1.000000;,
  -0.000001;0.000000;-1.000000;,
  -0.000001;-0.000002;-1.000000;,
  -0.000000;-0.000002;-1.000000;,
  1.000000;-0.000009;-0.000000;,
  1.000000;-0.000000;-0.000000;,
  1.000000;-0.000000;-0.000000;,
  0.000001;-1.000000;-0.000000;,
  1.000000;-0.000009;-0.000000;,
  1.000000;-0.000009;-0.000000;,
  1.000000;-0.000000;0.000000;,
  1.000000;-0.000009;0.000000;,
  1.000000;-0.000000;-0.000000;,
  -0.000000;0.000009;-1.000000;;
  232;
  4;0,1,7,6;,
  4;1,2,8,7;,
  4;2,3,9,8;,
  4;3,4,10,9;,
  4;4,5,11,10;,
  4;5,40,46,11;,
  4;6,7,13,12;,
  4;7,8,14,13;,
  4;8,9,15,14;,
  4;9,10,16,15;,
  4;10,11,17,16;,
  4;11,46,52,17;,
  4;12,13,19,18;,
  4;13,14,20,19;,
  4;14,15,21,20;,
  4;15,16,22,21;,
  4;16,17,23,22;,
  4;17,52,58,23;,
  4;18,19,24,24;,
  4;19,20,24,24;,
  4;20,21,25,24;,
  4;21,22,26,25;,
  4;22,23,27,26;,
  4;23,58,64,27;,
  4;24,24,29,28;,
  4;24,24,30,29;,
  4;24,25,31,30;,
  4;25,26,32,31;,
  4;26,27,33,32;,
  4;27,64,70,33;,
  4;28,29,35,34;,
  4;29,30,36,35;,
  4;30,31,37,36;,
  4;31,32,38,37;,
  4;32,33,39,38;,
  4;33,70,76,39;,
  4;40,41,47,46;,
  4;41,42,48,47;,
  4;42,43,49,48;,
  4;43,44,50,49;,
  4;44,45,51,50;,
  4;45,82,88,51;,
  4;46,47,53,52;,
  4;47,48,54,53;,
  4;48,49,55,54;,
  4;49,50,56,55;,
  4;50,51,57,56;,
  4;51,88,94,57;,
  4;52,53,59,58;,
  4;53,54,60,59;,
  4;54,55,61,60;,
  4;55,56,62,61;,
  4;56,57,63,62;,
  4;57,94,99,63;,
  4;58,59,65,64;,
  4;59,60,66,65;,
  4;60,61,67,66;,
  4;61,62,68,67;,
  4;62,63,69,68;,
  4;63,99,103,69;,
  4;64,65,71,70;,
  4;65,66,72,71;,
  4;66,67,73,72;,
  4;67,68,74,73;,
  4;68,69,75,74;,
  4;69,103,107,75;,
  4;70,71,77,76;,
  4;71,72,78,77;,
  4;72,73,79,78;,
  4;73,74,80,79;,
  4;74,75,81,80;,
  4;75,107,113,81;,
  4;82,83,89,88;,
  4;83,84,90,89;,
  4;84,85,91,90;,
  4;85,86,92,91;,
  4;86,87,93,92;,
  4;87,119,125,93;,
  4;88,89,95,94;,
  4;89,90,96,95;,
  4;90,91,97,96;,
  4;91,92,98,97;,
  4;92,93,98,98;,
  4;93,125,98,98;,
  4;94,95,100,99;,
  4;95,96,101,100;,
  4;96,97,102,101;,
  4;97,98,98,102;,
  4;98,98,98,98;,
  4;98,98,98,98;,
  4;99,100,104,103;,
  4;100,101,105,104;,
  4;101,102,106,105;,
  4;102,98,98,106;,
  4;98,98,98,98;,
  4;98,98,98,98;,
  4;103,104,108,107;,
  4;104,105,109,108;,
  4;105,106,110,109;,
  4;106,98,111,110;,
  4;98,98,112,111;,
  4;98,98,130,112;,
  4;107,108,114,113;,
  4;108,109,115,114;,
  4;109,110,116,115;,
  4;110,111,117,116;,
  4;111,112,118,117;,
  4;112,130,135,118;,
  4;120,120,120,120;,
  4;120,121,121,120;,
  4;121,122,122,121;,
  4;122,123,123,122;,
  4;123,124,126,123;,
  4;124,196,197,126;,
  4;120,120,120,120;,
  4;126,197,127,127;,
  4;120,120,120,120;,
  4;127,127,128,128;,
  4;120,120,120,120;,
  4;128,128,129,129;,
  4;120,120,120,120;,
  4;129,129,198,134;,
  4;120,120,120,120;,
  4;120,131,131,120;,
  4;131,132,132,131;,
  4;132,133,133,132;,
  4;133,134,136,133;,
  4;134,198,199,136;,
  4;200,201,137,202;,
  4;201,203,138,137;,
  4;203,85,139,138;,
  4;85,84,140,139;,
  4;84,83,141,140;,
  4;83,82,45,141;,
  4;202,137,142,204;,
  4;137,138,143,142;,
  4;138,139,144,143;,
  4;139,140,145,144;,
  4;140,141,146,145;,
  4;141,45,44,146;,
  4;204,142,147,205;,
  4;142,143,148,147;,
  4;143,144,149,148;,
  4;144,145,150,149;,
  4;145,146,151,150;,
  4;146,44,43,151;,
  4;205,147,152,206;,
  4;147,148,153,152;,
  4;148,149,154,153;,
  4;149,150,155,154;,
  4;150,151,156,155;,
  4;151,43,42,156;,
  4;206,152,157,207;,
  4;152,153,153,157;,
  4;153,154,158,153;,
  4;154,155,159,158;,
  4;155,156,160,159;,
  4;156,42,41,160;,
  4;207,157,148,148;,
  4;157,153,148,148;,
  4;153,158,3,148;,
  4;158,159,4,3;,
  4;159,160,5,4;,
  4;160,41,40,5;,
  4;176,161,176,176;,
  4;161,162,176,176;,
  4;162,163,116,176;,
  4;163,164,115,116;,
  4;164,165,114,115;,
  4;165,81,113,114;,
  4;176,166,161,176;,
  4;166,167,162,161;,
  4;167,168,163,162;,
  4;168,169,164,163;,
  4;169,170,165,164;,
  4;170,80,81,165;,
  4;176,171,166,176;,
  4;171,172,167,166;,
  4;172,173,168,167;,
  4;173,174,169,168;,
  4;174,175,170,169;,
  4;175,79,80,170;,
  4;176,176,171,176;,
  4;176,176,172,171;,
  4;176,177,173,172;,
  4;177,178,174,173;,
  4;178,179,175,174;,
  4;179,78,79,175;,
  4;176,176,176,176;,
  4;176,176,176,176;,
  4;176,180,177,176;,
  4;180,181,178,177;,
  4;181,182,179,178;,
  4;182,77,78,179;,
  4;176,176,176,176;,
  4;176,176,176,176;,
  4;176,37,180,176;,
  4;37,38,181,180;,
  4;38,39,182,181;,
  4;39,76,77,182;,
  4;176,176,176,176;,
  4;24,24,24,24;,
  4;208,209,183,208;,
  4;176,176,176,176;,
  4;209,210,184,183;,
  4;176,176,176,176;,
  4;210,185,185,184;,
  4;176,176,176,176;,
  4;186,211,211,186;,
  4;185,120,120,185;,
  4;24,24,24,24;,
  4;208,183,187,212;,
  4;183,184,188,187;,
  4;184,185,185,188;,
  4;186,186,186,186;,
  4;185,120,120,185;,
  4;24,24,24,24;,
  4;212,187,189,213;,
  4;187,188,190,189;,
  4;188,185,185,190;,
  4;191,186,186,191;,
  4;185,120,120,185;,
  4;148,192,192,148;,
  4;24,24,24,24;,
  4;213,189,214,215;,
  4;192,193,193,192;,
  4;189,190,216,214;,
  4;193,194,194,193;,
  4;190,185,185,216;,
  4;195,191,191,195;,
  4;194,217,217,194;,
  4;185,120,120,185;;
 }
 MeshTextureCoords {
  304;
  0.000000;0.000000;,
  0.166670;0.000000;,
  0.166670;0.166670;,
  0.000000;0.166670;,
  0.333330;0.000000;,
  0.333330;0.166670;,
  0.500000;0.000000;,
  0.500000;0.166670;,
  0.666670;0.000000;,
  0.666670;0.166670;,
  0.833330;0.000000;,
  0.833330;0.166670;,
  1.000000;0.000000;,
  1.000000;0.166670;,
  0.166670;0.333330;,
  0.000000;0.333330;,
  0.333330;0.333330;,
  0.500000;0.333330;,
  0.666670;0.333330;,
  0.833330;0.333330;,
  1.000000;0.333330;,
  0.166670;0.500000;,
  0.000000;0.500000;,
  0.333330;0.500000;,
  0.500000;0.500000;,
  0.666670;0.500000;,
  0.833330;0.500000;,
  1.000000;0.500000;,
  0.166670;0.666670;,
  0.000000;0.666670;,
  0.333330;0.666670;,
  0.500000;0.666670;,
  0.666670;0.666670;,
  0.833330;0.666670;,
  1.000000;0.666670;,
  0.166670;0.833330;,
  0.000000;0.833330;,
  0.333330;0.833330;,
  0.500000;0.833330;,
  0.666670;0.833330;,
  0.833330;0.833330;,
  1.000000;0.833330;,
  0.166670;1.000000;,
  0.000000;1.000000;,
  0.333330;1.000000;,
  0.500000;1.000000;,
  0.666670;1.000000;,
  0.833330;1.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.166670;0.000000;,
  0.166670;0.166670;,
  0.000000;0.166670;,
  0.333330;0.000000;,
  0.333330;0.166670;,
  0.500000;0.000000;,
  0.500000;0.166670;,
  0.666670;0.000000;,
  0.666670;0.166670;,
  0.833330;0.000000;,
  0.833330;0.166670;,
  1.000000;0.000000;,
  1.000000;0.166670;,
  0.166670;0.333330;,
  0.000000;0.333330;,
  0.333330;0.333330;,
  0.500000;0.333330;,
  0.666670;0.333330;,
  0.833330;0.333330;,
  1.000000;0.333330;,
  0.166670;0.500000;,
  0.000000;0.500000;,
  0.333330;0.500000;,
  0.500000;0.500000;,
  0.666670;0.500000;,
  0.833330;0.500000;,
  1.000000;0.500000;,
  0.166670;0.666670;,
  0.000000;0.666670;,
  0.333330;0.666670;,
  0.500000;0.666670;,
  0.666670;0.666670;,
  0.833330;0.666670;,
  1.000000;0.666670;,
  0.166670;0.833330;,
  0.000000;0.833330;,
  0.333330;0.833330;,
  0.500000;0.833330;,
  0.666670;0.833330;,
  0.833330;0.833330;,
  1.000000;0.833330;,
  0.166670;1.000000;,
  0.000000;1.000000;,
  0.333330;1.000000;,
  0.500000;1.000000;,
  0.666670;1.000000;,
  0.833330;1.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.166670;0.000000;,
  0.166670;0.166670;,
  0.000000;0.166670;,
  0.333330;0.000000;,
  0.333330;0.166670;,
  0.500000;0.000000;,
  0.500000;0.166670;,
  0.666670;0.000000;,
  0.666670;0.166670;,
  0.833330;0.000000;,
  0.833330;0.166670;,
  1.000000;0.000000;,
  1.000000;0.166670;,
  0.166670;0.333330;,
  0.000000;0.333330;,
  0.333330;0.333330;,
  0.500000;0.333330;,
  0.666670;0.333330;,
  0.833330;0.333330;,
  1.000000;0.333330;,
  0.166670;0.500000;,
  0.000000;0.500000;,
  0.333330;0.500000;,
  0.500000;0.500000;,
  0.666670;0.500000;,
  0.833330;0.500000;,
  1.000000;0.500000;,
  0.166670;0.666670;,
  0.000000;0.666670;,
  0.333330;0.666670;,
  0.500000;0.666670;,
  0.666670;0.666670;,
  0.833330;0.666670;,
  1.000000;0.666670;,
  0.166670;0.833330;,
  0.000000;0.833330;,
  0.333330;0.833330;,
  0.500000;0.833330;,
  0.666670;0.833330;,
  0.833330;0.833330;,
  1.000000;0.833330;,
  0.166670;1.000000;,
  0.000000;1.000000;,
  0.333330;1.000000;,
  0.500000;1.000000;,
  0.666670;1.000000;,
  0.833330;1.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.166670;0.000000;,
  0.166670;0.166670;,
  0.000000;0.166670;,
  0.333330;0.000000;,
  0.333330;0.166670;,
  0.500000;0.000000;,
  0.500000;0.166670;,
  0.666670;0.000000;,
  0.666670;0.166670;,
  0.833330;0.000000;,
  0.833330;0.166670;,
  1.000000;0.000000;,
  1.000000;0.166670;,
  0.166670;0.333330;,
  0.000000;0.333330;,
  1.000000;0.333330;,
  0.833330;0.333330;,
  0.166670;0.500000;,
  0.000000;0.500000;,
  1.000000;0.500000;,
  0.833330;0.500000;,
  0.166670;0.666670;,
  0.000000;0.666670;,
  1.000000;0.666670;,
  0.833330;0.666670;,
  0.166670;0.833330;,
  0.000000;0.833330;,
  1.000000;0.833330;,
  0.833330;0.833330;,
  0.166670;1.000000;,
  0.000000;1.000000;,
  0.333330;0.833330;,
  0.333330;1.000000;,
  0.500000;0.833330;,
  0.500000;1.000000;,
  0.666670;0.833330;,
  0.666670;1.000000;,
  0.833330;1.000000;,
  1.000000;1.000000;,
  0.166670;0.000000;,
  0.166670;0.166670;,
  0.000000;0.166670;,
  0.333330;0.000000;,
  0.333330;0.166670;,
  0.500000;0.166670;,
  0.666670;0.000000;,
  0.666670;0.166670;,
  0.833330;0.000000;,
  0.833330;0.166670;,
  1.000000;0.166670;,
  0.166670;0.333330;,
  0.000000;0.333330;,
  0.333330;0.333330;,
  0.500000;0.333330;,
  0.666670;0.333330;,
  0.833330;0.333330;,
  1.000000;0.333330;,
  0.166670;0.500000;,
  0.000000;0.500000;,
  0.333330;0.500000;,
  0.500000;0.500000;,
  0.666670;0.500000;,
  0.833330;0.500000;,
  1.000000;0.500000;,
  0.166670;0.666670;,
  0.000000;0.666670;,
  0.333330;0.666670;,
  0.500000;0.666670;,
  0.666670;0.666670;,
  0.833330;0.666670;,
  1.000000;0.666670;,
  0.166670;0.833330;,
  0.000000;0.833330;,
  0.333330;0.833330;,
  0.500000;0.833330;,
  0.666670;0.833330;,
  0.833330;0.833330;,
  1.000000;0.833330;,
  0.166670;1.000000;,
  0.000000;1.000000;,
  0.333330;1.000000;,
  0.500000;1.000000;,
  0.666670;1.000000;,
  0.833330;1.000000;,
  1.000000;1.000000;,
  0.000000;0.833330;,
  0.166670;0.833330;,
  0.166670;1.000000;,
  0.333330;0.833330;,
  0.333330;1.000000;,
  0.500000;0.833330;,
  0.666670;0.833330;,
  0.666670;1.000000;,
  0.833330;0.833330;,
  0.833330;1.000000;,
  1.000000;0.833330;,
  0.000000;0.666670;,
  0.166670;0.666670;,
  0.333330;0.666670;,
  0.500000;0.666670;,
  0.666670;0.666670;,
  0.833330;0.666670;,
  1.000000;0.666670;,
  0.000000;0.500000;,
  0.166670;0.500000;,
  0.333330;0.500000;,
  0.500000;0.500000;,
  0.666670;0.500000;,
  0.833330;0.500000;,
  1.000000;0.500000;,
  0.000000;0.333330;,
  0.166670;0.333330;,
  0.333330;0.333330;,
  0.500000;0.333330;,
  0.666670;0.333330;,
  0.833330;0.333330;,
  1.000000;0.333330;,
  0.000000;0.166670;,
  0.166670;0.166670;,
  0.333330;0.166670;,
  0.500000;0.166670;,
  0.666670;0.166670;,
  0.833330;0.166670;,
  1.000000;0.166670;,
  0.000000;0.000000;,
  0.166670;0.000000;,
  0.333330;0.000000;,
  0.500000;0.000000;,
  0.666670;0.000000;,
  0.833330;0.000000;,
  1.000000;0.000000;,
  0.333330;0.166670;,
  0.166670;0.166670;,
  0.166670;0.333330;,
  0.333330;0.333330;,
  0.500000;0.166670;,
  0.500000;0.333330;,
  0.666670;0.166670;,
  0.666670;0.333330;,
  0.833330;0.166670;,
  0.833330;0.333330;,
  0.166670;0.500000;,
  0.333330;0.500000;,
  0.500000;0.500000;,
  0.666670;0.500000;,
  0.833330;0.500000;,
  0.166670;0.666670;,
  0.333330;0.666670;,
  0.500000;0.666670;,
  0.666670;0.666670;,
  0.833330;0.666670;,
  0.166670;0.833330;,
  0.333330;0.833330;,
  0.500000;0.833330;,
  0.666670;0.833330;,
  0.833330;0.833330;;
 }
}
